#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <math.h>

#ifdef TARGET_ARM
	#include <linux/rpmsg.h>
	#include <ti_rpmsg_char.h>
#endif
#include "daemon.hpp"
#include "mu_settings.hpp"
#include "mu_status.hpp"
#include "enums.hpp"
#include "sig_proc.hpp"

extern Daemon *gDaemon;
extern IPC *gIPC;
SignalProc *SP=NULL;

extern std::vector<std::string> gMU_Settings;
extern mu_calibration gCalibration;
mu_calibration *gReadCalibration;
mu_shared_samples *gSharedSamples;
mu_shared_ADCsamples *gSharedADCSamples;
mu_rms_values gmu_rms_values;
mu_system_status gmu_system_status = { 8, 6, 2, 1, 100};

#define REMOTE_ENDPT	14

#define lswap( x ) \
                  ((((x) & 0xff000000) >> 24) | \
                  (((x) & 0x00ff0000) >>  8) | \
                  (((x) & 0x0000ff00) <<  8) | \
                  (((x) & 0x000000ff) << 24))


#ifndef htonl_ts
#define htonl_ts(l)      (lswap(l))
#endif


typedef struct {
	uint8_t ready;
} SV_CORE_MSG;

void IPC::ipc_get_status(mu_system_status** a_mu_system_status) {
  printf("ipc_get_status %x \n", &gmu_system_status);
  *a_mu_system_status = &gmu_system_status;
}

mu_rms_values* IPC::ipc_get_meter() {
  return &gmu_rms_values;
}

void IPC::DumpADCSamples(mu_shared_ADCsamples *a_mu_shared_ADCsamples) {
  FILE *fd=NULL;
  float i1,i2,i3,u1,u2,u3;
  printf("Dump ADC samples...\n");

  // Open file
  fd = fopen("/home/root/RAW_ADC_Samples_9600.csv", "w");
  if (fd==NULL) {
    printf("ERROR: Unable to create ADC sample file.\n");
  }
  fprintf(fd,"sample nbr;u1;u2,u3,i1,i2,i3\n");

  for (int i=0; i < 9600; i++)
    {
      i1 = a_mu_shared_ADCsamples->i1_val[i];
      i2 = a_mu_shared_ADCsamples->i2_val[i];
      i3 = a_mu_shared_ADCsamples->i3_val[i];
      u1 = a_mu_shared_ADCsamples->u1_val[i];
      u2 = a_mu_shared_ADCsamples->u2_val[i];
      u3 = a_mu_shared_ADCsamples->u3_val[i];
      //      fprintf(fd, "%d;%f;%f;%f;%f;%f;%f\n", i, i1, i2,i3,u1,u2,3);
      fprintf(fd, "%d;%d;%d;%d;%d;%d;%d\n",
	      i,
	      a_mu_shared_ADCsamples->u1_val[i],
	      a_mu_shared_ADCsamples->u2_val[i],
	      a_mu_shared_ADCsamples->u3_val[i],
	      a_mu_shared_ADCsamples->i1_val[i],
	      a_mu_shared_ADCsamples->i2_val[i],
	      a_mu_shared_ADCsamples->i3_val[i]);
      
    }
  fflush(fd);
  fclose(fd);
}

inline void * IPC::fixup_addr(void *addr, size_t size)
{
#ifdef FORCE_STRICT_ALIGNMENT
	unsigned long aligned_addr = (unsigned long)addr;
	aligned_addr &= ~(size - 1);
	addr = (void *)aligned_addr;
#endif
	return addr;
}

/*float IPC::RMSCalculation(float *values, uint32_t count) {
	float Usquare=0;
	float sum=0;
	float sum2=0;
	for (int i=0; i < count; i++) {
		Usquare=values[i]*values[i];
		sum+=Usquare;
	}
	sum2=sum/count;
	return sqrt(sum2);
}
*/
int IPC::UnallocateShareMemory(int fd, void* ptr) {
	unsigned long MAP_SIZE = sysconf(_SC_PAGE_SIZE);

    printf("Memory unmapped at address %x.\n", ptr);

//	if(munmap(ptr, MAP_SIZE) == -1) {
//		printf("ERROR: Unable to unpam\n");
//	}
    close(fd);
}

int IPC::AllocateShareMemory(int *a_fd, void** a_base_address, void** a_virtual_address) {
	off_t base_physical_address = 0xA0000000;
	unsigned long MAP_SIZE = sysconf(_SC_PAGE_SIZE);
	unsigned long MAP_MASK = (MAP_SIZE - 1);
    void *map_base, *virt_addr;

	//	void *base_address = (void *)0xA5000000;

	int fd;
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		printf("Unable to open /dev/mem\n");
		return 1;
	}
    printf("/dev/mem opened.\n");

	printf("INFO MAP = %d %x %x\n", MAP_SIZE, MAP_MASK, base_physical_address);
	map_base = mmap(0, MAP_SIZE*100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base_physical_address & ~MAP_MASK);
	if(map_base == MAP_FAILED){
	    perror("Can't map memory");
	    return 1;
	}
    printf("Memory mapped at address %p.\n", map_base);

    virt_addr = map_base + (base_physical_address & MAP_MASK);
    virt_addr = fixup_addr(virt_addr, sizeof(uint32_t));

	*a_fd = fd;
	*a_virtual_address = virt_addr;
	*a_base_address = map_base;

	return 0;
}

uint32_t ntohf_ts(float net32)
{
    union {
        float f;
        uint32_t u;
    } value;

    value.f = net32;
    // Swap bytes if necessary and store to value
    value.u = htonl_ts(value.u);
    // return value as integer
    return value.u;
}



void * IPC::thread_rproc_management(void *arg) {

#ifdef TARGET_ARM
    rproc_id rproc_id = R5F_MAIN0_0;
    rpmsg_char_dev_t *rcdev;
#endif
    int ret;
    int remote_endpt = REMOTE_ENDPT;
    char *dev_name = NULL;
    int flags = 0;
    char eptdev_name[32] = { 0 };
    int msg_in_len = 0;
    char msg_in_buf[512] = { 0 };
    SV_CORE_MSG R5_msg;
    float RMSValue=0;

//    printf("Start thread for reveice rproc messages\n");
//
//    // Init of rproc
//    rcdev = rpmsg_char_open(rproc_id, dev_name, remote_endpt,
//			    eptdev_name, flags);
//    if (!rcdev) {
//      perror("Can't create an endpoint device");
//      pthread_exit(NULL);
//    }
//
//    printf("Created endpt device %s, fd = %d port = %d\n", eptdev_name,
//	   rcdev->fd, rcdev->endpt);
//
//    // Send ready and configuration to R5
//    R5_msg.ready = true;
//    ret = send_msg(rcdev->fd, (char *) &R5_msg, sizeof(R5_msg));
//    if (ret < 0) {
//      printf("send_msg failed ret = %d\n", ret);
//      pthread_exit(NULL);
//    }

    if (gDaemon==NULL)
    {
    	printf("ERROR: Daemon pointer NULL !!!\n");
    	exit(1);
    }

    // Allocate shared memory for calibration settings
    int fd;
    void *virtual_address, *base_address;
    ret = gIPC->AllocateShareMemory(&fd, &base_address, &virtual_address);
    if (ret != 0) {
    	printf("ERROR: unable to use shared memory for calibration settings\n");
    	return NULL;
    }

    gReadCalibration = (mu_calibration*)virtual_address;
    gSharedSamples   = (mu_shared_samples*)(virtual_address+0x100);
    gSharedADCSamples = (mu_shared_ADCsamples*)(virtual_address+0x1000);
    // Run rproc receive messages
    while (gDaemon->IsRunning())
    {
      //printf("Setting Manager: IPC, synhcronize settings and status ... \n");
	    
     /**
	Synhcronization of settings with R5.
      */

      if (gDaemon->IsADCSampleAcqIPC()) {
	printf("Get ADC samples...\n");
	
	// Change acquisition mode
	gSharedADCSamples->acq_mode=1;
	// Wait 1s sec that R5SP fill the buffer
	sleep(1);
	// Dump data to file
	DumpADCSamples(gSharedADCSamples);

	gDaemon->ResetADCSampleAcqIPC();
      }

      if (gDaemon->IsReloadIPC())
      {
    	  // Update calibration settings
    	  memcpy(virtual_address, &gCalibration, sizeof(gCalibration));
//			*((uint32_t *) virtual_address) = count;
	  printf("Update calibration values\n");
    	  printf("Gain U  = %f %f %f\n", gReadCalibration->cal_gain_U1, gReadCalibration->cal_gain_U2, gReadCalibration->cal_gain_U3);
    	  printf("Phase U = %f %f %f\n", gReadCalibration->cal_phase_U1, gReadCalibration->cal_phase_U2, gReadCalibration->cal_phase_U3);
    	  printf("Gain I  = %f %f %f\n", gReadCalibration->cal_gain_I1, gReadCalibration->cal_gain_I2, gReadCalibration->cal_gain_I3);
	  printf("Phase I = %f %f %f\n", gReadCalibration->cal_phase_I1, gReadCalibration->cal_phase_I2, gReadCalibration->cal_phase_I3);

	  gDaemon->ResetReloadIPC();
      } else { // Get R5SP status and samples
    	//  printf("U1 = %f\n", gSharedSamples->u1_val[0]);
	//printf("============RMS values===========\n");
    	  RMSValue = SP->RMSCalculation(gSharedSamples->i1_val, 96);
    	  //printf("I1rms = %f\n", RMSValue);
    	  gmu_rms_values.i1_rms = RMSValue;
    	  RMSValue = SP->RMSCalculation(gSharedSamples->i2_val, 96);
    	  //printf("I2rms = %f\n", RMSValue);
    	  gmu_rms_values.i2_rms = RMSValue;
    	  RMSValue = SP->RMSCalculation(gSharedSamples->i3_val, 96);
    	  //printf("I3rms = %f\n", RMSValue);
    	  gmu_rms_values.i3_rms = RMSValue;
    	  RMSValue = SP->RMSCalculation(gSharedSamples->u1_val, 96);
    	  //printf("U1rms = %f\n", RMSValue);
    	  gmu_rms_values.u1_rms = RMSValue;
    	  RMSValue = SP->RMSCalculation(gSharedSamples->u2_val, 96);
    	  //printf("U2rms = %f\n", RMSValue);
    	  gmu_rms_values.u2_rms = RMSValue;
    	  RMSValue = SP->RMSCalculation(gSharedSamples->u3_val, 96);
    	  //printf("U3rms = %f\n", RMSValue);
    	  gmu_rms_values.u3_rms = RMSValue;
      }
      sleep(1);

    }

    //    printf("BASE ADDRESS = %x\n", base_address);
    gIPC->UnallocateShareMemory(fd, base_address);

#ifdef TARGET_ARM
    rpmsg_char_exit();
#endif
    // Arrêt propre du thread
    pthread_exit(NULL);

    // Exit
    exit(0);
}

