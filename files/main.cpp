#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
//#include <libconfig.h++>
#include <thread>

#ifdef TARGET_ARM
	#include <linux/rpmsg.h>
	#include <ti_rpmsg_char.h>
#endif

#include "config.hpp"
#include "command-line-parser.hpp"
#include "daemon.hpp"
#include "log.hpp"
#include "ipc.hpp"
#include "mu_settings.hpp"
#include "mu_status.hpp"
#include "sqlite_interface.hpp"

#define DEBUG

//mu_settings gMU_Settings;
std::vector<std::string> gMU_RawSettings;
extern mu_calibration gCalibration;
extern mu_settings gSettings;
extern mu_system_status *gStatus;
mu_rms_values *gMeter=NULL;
Config *gConf=NULL;

Daemon *gDaemon=NULL;
IPC *gIPC=NULL;
sqlite_interface g_sqlite_interface;





void user1() {
  printf("USER1: Set acq_mode to 1.\n");

  // initiate ADC sample acquisition
  //  gDaemon->SetADCSampleAcqIPC();
}

// This function will be called when the daemon receive a SIGHUP signal.

 void trace_debug(std::string a_string)
{
#ifdef DEBUG
  std::cout << a_string;
#endif
}

int main(int argc, char** argv) {
    int count = 0;
    int ret;
    pthread_t thread_rpoc;
    // Command line and config file example
    CommandLineParser commandLine(argc, argv);

    gCalibration.calibration_update_count=0;

    trace_debug("Create daemon\n");

    // The Daemon class is a singleton to avoid be instantiate more than once
    

    IPC& ipc = IPC::instance();

    //gIPC= &ipc;

    Config& configuration = Config::instance();
    //gConf= &configuration;

    Daemon& daemon = Daemon::instance();
    gDaemon= &daemon;


    // Set the reload function to be called in case of receiving a SIGHUP signal
    daemon.setReloadFunction(configuration.reload);
    daemon.setUser1Function(user1);

    
    g_sqlite_interface.open_db();
    //    g_sqlite_interface.open_db_meter();
    //    g_sqlite_interface.open_db_setting();
    /*
    if (commandLine.cmdOptionExist("--config")) {
        const std::string configFileName = commandLine.getCmdOptionValue("--config");
        LOG_INFO("Config file name = ", configFileName);
        libconfig::Config config;
        config.readFile(configFileName.c_str());
        std::string test{};
        config.lookupValue("test", test);
        LOG_INFO("Config option test = ", test);
    }
    */
    /**
       Create thread for IPC communication
     */

//    /* Use auto-detection for SoC */
//    ret = rpmsg_char_init(NULL);
//    if (ret) {
//      printf("rpmsg_char_init failed, ret = %d\n", ret);
//      return EXIT_FAILURE;
//    }
//    printf("rpmsg_char_init done\n");
    
    pthread_create(&thread_rpoc, NULL, ipc.thread_rproc_management, NULL);

    configuration.reload();

    gMeter = ipc.ipc_get_meter();
    
    // Daemon main loop
    while (daemon.IsRunning()) {
      //LOG_DEBUG("Count: ", count++);

      // Update the db_meter data base with RMS values.
      g_sqlite_interface.put_meter(gMeter);
      
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pthread_join(thread_rpoc, NULL);
    g_sqlite_interface.close();
}
