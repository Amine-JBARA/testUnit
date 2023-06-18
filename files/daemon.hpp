#ifndef DAEMON_HPP_
#define DAEMON_HPP_

#include <csignal>
#include <functional>
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

#include "command-line-parser.hpp"
#include "daemon.hpp"
#include "log.hpp"
#include "ipc.hpp"
#include "mu_settings.hpp"
#include "mu_status.hpp"
#include "sqlite_interface.hpp"
class Daemon {
   public:
    static Daemon& instance() {
        static Daemon instance;
        return instance;
    }
    // Constructeur par défaut
    void setReloadFunction(std::function<void()> func);
    void setUser1Function(std::function<void()> func);

    bool IsRunning();
    bool IsReloadIPC();
    bool IsADCSampleAcqIPC();
    void SetReloadIPC();
    void ResetReloadIPC();
    void SetADCSampleAcqIPC();
    void ResetADCSampleAcqIPC();
    //void static reload();
    Daemon();
    Daemon(Daemon const&) = delete;

   private:
    std::function<void()> m_reloadFunc;
    std::function<void()> m_user1Func;

    bool m_reload;
    bool m_reloadIPC;
    bool m_ADCSampleAcq;
    bool m_ADCSampleAcqIPC;
    bool m_isRunning;

    void operator=(Daemon const&) = delete;

  
    static void signalHandler(int signal);
};

#endif  // DAEMON_HPP_
