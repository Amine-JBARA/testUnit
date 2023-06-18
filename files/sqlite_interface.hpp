/*
 * sqlite_interface.hpp
 *
 *  Created on: 11 mai 2023
 *      Author: user
 */
#ifndef SQLITE_INTERFACE_HPP_
#define SQLITE_INTERFACE_HPP_


#include "mu_status.hpp"
#include "mu_settings.hpp"
#include <sqlite3.h>

class sqlite_interface {

public:

  sqlite_interface() {
    m_db_status = NULL;
    m_db_meter = NULL;
    m_db_setting = NULL;
    m_db = NULL;
  }
  
  // Open the data base
  uint32_t open_db();
  uint32_t open_db_status();
  uint32_t open_db_meter();
  uint32_t open_db_setting();
  // Close the data base
  uint32_t close();
  // Put all measures (Urms and Irms)
  uint32_t put_meter(mu_rms_values *a_mu_rms_values);
  
  uint32_t put_status(mu_system_status *a_mu_system_status);
  
  uint32_t get_settings(mu_settings *a_mu_settings);
  

private:
  void trace_debug(std::string);
  
  sqlite3 * m_db;
  sqlite3 * m_db_status;
  sqlite3 * m_db_meter;
  sqlite3 * m_db_setting;
};


#endif /* SQLITE_INTERFACE_HPP_ */
