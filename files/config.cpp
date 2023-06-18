#include "config.hpp"
#include "mu_settings.hpp"
#include "daemon.hpp"
#include "mu_status.hpp"
#include "sqlite_interface.hpp"
#include "ipc.hpp"

mu_settings gSettings;
mu_system_status *gStatus=NULL;
mu_calibration gCalibration;
extern Daemon *gDaemon;
extern sqlite_interface g_sqlite_interface;
extern IPC *gIPC;
Config::Config() {}
//ConfigReader::ConfigReader() {}
std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}


void Config::reload() {
    //trace_debug("RELOAD: Reload function called.");

    // Load configuration file
    std::ifstream myfile;

    /**
     * Get calibration values
     */
  
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
    gDaemon->SetReloadIPC();
    gDaemon->SetADCSampleAcqIPC();
    // Get status from cores
    gIPC->ipc_get_status(&gStatus);
    // Update the data base with status
    g_sqlite_interface.put_status(gStatus);
    // Get setting
    g_sqlite_interface.get_settings(&gSettings);
}