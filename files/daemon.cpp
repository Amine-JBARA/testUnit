
#include "daemon.hpp"
#include "log.hpp"
#include "mu_settings.hpp"
#include "mu_settings.hpp"
#include "mu_status.hpp"
#include "sqlite_interface.hpp"
//mu_settings gSettings;
//mu_system_status *gStatus=NULL;
//mu_calibration gCalibration;
extern Daemon *gDaemon;
//extern sqlite_interface g_sqlite_interface;
//extern IPC *gIPC;


//Daemon::Daemon() {}

Daemon::Daemon() {
    m_isRunning = true;
    m_reload = false;
    m_ADCSampleAcq = false;
    signal(SIGINT, Daemon::signalHandler);
    signal(SIGTERM, Daemon::signalHandler);
    signal(SIGHUP, Daemon::signalHandler);
    //    signal(SIGUSR1, Daemon::signalHandler);
}

void Daemon::setReloadFunction(std::function<void()> func) {
  printf("setReloadFunction\n");

  m_reloadFunc = func;
}

void Daemon::setUser1Function(std::function<void()> func) {
  printf("setUser1Function\n");

  m_user1Func = func;
}

void Daemon::SetADCSampleAcqIPC() {
  m_ADCSampleAcq = true;
}

void Daemon::ResetADCSampleAcqIPC() {
  m_ADCSampleAcq = false;
}


bool Daemon::IsReloadIPC() {
	return m_reloadIPC;
}

bool Daemon::IsADCSampleAcqIPC() {
  return m_ADCSampleAcq;
}

void Daemon::ResetReloadIPC() {
	m_reloadIPC = false;
}

void Daemon::SetReloadIPC() {
	m_reloadIPC = true;
}


bool Daemon::IsRunning() {
    if (m_reload) {
        m_reload = false;
        m_reloadFunc();
    }
    return m_isRunning;
}

void Daemon::signalHandler(int signal) {
    LOG_INFO("Interrup signal number [", signal, "] recived.");
    switch (signal) {
        case SIGINT:
        case SIGTERM: {
            Daemon::instance().m_isRunning = false;
            break;
        }
        case SIGHUP: {
            Daemon::instance().m_reload = true;
            break;
        }
    }
}
/*std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}*/
 /*void trace_debug(std::string a_string)
{
#ifdef DEBUG
  std::cout << a_string;
#endif
}*/
/*
void Daemon::reload() {
    //trace_debug("RELOAD: Reload function called.");

    // Load configuration file
    std::ifstream myfile;

    /**
     * Get calibration values
     */
  /*
    myfile.open("/home/root/mu_config.cfg");


    std::string mystring;
    std::string myline;
 
    if ( myfile.is_open() ) { // always check whether the file is open
      while ( std::getline (myfile, myline) ) {
//    	  std::getline (myfile, myline);
    	  if (myline[0] != '#') {
    		 // gMU_Settings.push_back(myline);
			  // Parse the setting in order to get the destinatiaire, the name and the value
	    std::vector<std::string> substrings = split (myline, ':');
	    //std::cout << "Entry = " << substrings[0] << " " << substrings[1] << " " << substrings[2] << '\n';

			  if (substrings[1] == "CAL_GAIN_U1")
				  gCalibration.cal_gain_U1 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_U1")
				  gCalibration.cal_phase_U1 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_GAIN_U2")
				  gCalibration.cal_gain_U2 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_U2")
				  gCalibration.cal_phase_U2 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_GAIN_U3")
				  gCalibration.cal_gain_U3 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_U3")
				  gCalibration.cal_phase_U3 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_GAIN_I1")
				  gCalibration.cal_gain_I1 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_I1")
				  gCalibration.cal_phase_I1 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_GAIN_I2")
				  gCalibration.cal_gain_I2 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_I2")
				  gCalibration.cal_phase_I2 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_GAIN_I3")
				  gCalibration.cal_gain_I3 = std::stof(substrings[2]);
			  else if (substrings[1] == "CAL_PHASE_I3")
				  gCalibration.cal_phase_I3 = std::stof(substrings[2]);
    	  }
      }
      myfile.close();
    }

    gCalibration.calibration_update_count++;

    /**
     * Get data base settings
     */
//    g_sqlite_interface.get_settings(&gSettings);
//    std::cout << "Simulation = " << gSettings.simulation << std::endl;

    // Enable IPC update before data base synchronization.
    /*
    gDaemon->SetReloadIPC();
    gDaemon->SetADCSampleAcqIPC();
    // Get status from cores
    gIPC->ipc_get_status(&gStatus);
    // Update the data base with status
    g_sqlite_interface.put_status(gStatus);
    // Get setting
    g_sqlite_interface.get_settings(&gSettings);
}*/