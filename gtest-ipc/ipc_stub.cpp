#include "ipc_stub.hpp"
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


void  *thread_rproc_management(void *arg) {
    
}
int IPCStub::AllocateShareMemory(int *a_fd, void** a_base_address, void** a_virtual_address) 
{

	return 0;
}
int UnallocateShareMemory(int fd, void* ptr) {

    return 0;
}
 void DumpADCSamples(mu_shared_ADCsamples *a_mu_shared_ADCsamples) {

 }
    inline void *fixup_addr(void *addr, size_t size) {
        
    }