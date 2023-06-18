/*
 * sqlite_interface.cpp
 *
 *  Created on: 11 mai 2023
 *      Author: user
 */

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
#include <time.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sqlite3.h>

#include "sqlite_interface.hpp"

#include "mu_settings.hpp"

static mu_settings gSettings;

#define DEBUG

void sqlite_interface::trace_debug(std::string a_string)
{
#ifdef DEBUG
  std::cout << a_string << std::endl;
#endif  
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    //    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
      //        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	if (strcmp(azColName[i], "diinvert") == 0) {
	  gSettings.diinvert = atoi(azColName[i]);
	  printf("diinvert = %d\n", gSettings.diinvert);
	} else if (strcmp(azColName[i], "sv_goose_sign") == 0) {
	  gSettings.sv_goose_sign = atoi(azColName[i]);
	  printf("sv_goose_sign = %d\n", gSettings.sv_goose_sign);
	} else if (strcmp(azColName[i], "simulation") == 0) {
	  gSettings.simulation = atoi(azColName[i]);
	  printf("simulation = %d\n", gSettings.simulation);
	}
    }

    printf("\n");
    return 0;
}

// Open the data base
uint32_t sqlite_interface::open_db() {
  uint32_t rc;

  rc = sqlite3_open ( "mu.db", &m_db);

  this->trace_debug("Open DB : mu.db");

  if (rc) {
    this->trace_debug("ERROR: Unable to open the db.");
    exit (0);
  } else {
    this->trace_debug("SUCCESS: db open ok.");
  }
  return 0;
}


// Open the data base
uint32_t sqlite_interface::open_db_status() {
  uint32_t rc;

  rc = sqlite3_open ( "mu_status.db", &m_db_status);

  this->trace_debug("Open DB : mu_status.db");

  if (rc) {
    this->trace_debug("ERROR: Unable to open the status db.");
    exit (0);
  } else {
    this->trace_debug("SUCCESS: status db open ok.");
  }
  return 0;
}

// Open the data base
uint32_t sqlite_interface::open_db_meter() {
  uint32_t rc;

  rc = sqlite3_open ( "mu_meter.db", &m_db_meter);

  this->trace_debug("Open DB : mu_meter.db");
  if (rc) {
    this->trace_debug("ERROR: Unable to open the meter db.");
    exit (0);
  } else {
    this->trace_debug("SUCCESS: meter db open ok.");
  }
  return 0;
}
  
// Open the data base
uint32_t sqlite_interface::open_db_setting() {
  uint32_t rc;

  rc = sqlite3_open ( "mu_setting.db", &m_db_setting);

  this->trace_debug("Open DB : mu_setting.db");

  if (rc) {
    this->trace_debug("ERROR: Unable to open the setting db.");
    exit (0);
  } else {
    this->trace_debug("SUCCESS: setting db open ok.");
  }
  
  return 0;
}

// Close the data base
uint32_t sqlite_interface::close() {
	sqlite3_close (m_db);
	//	sqlite3_close (m_db_meter);
	//	sqlite3_close (m_db_setting);
	return 0;
}

// Put all measures (Urms and Irms)
uint32_t sqlite_interface::put_meter(mu_rms_values *a_mu_rms_values) {
	std::string sql;
	uint32_t rc=0;
	char* messaggeError;

	//	this->trace_debug("sqlite_interface::put_meter");

	if (m_db == NULL) {
	  this->trace_debug("DB not valid");
	  return 1;
	}

	if (a_mu_rms_values == NULL) {
	  this->trace_debug("Meter structure not valid");
	  return 1;
	}
	
	sql = "UPDATE Meter SET u1 = '" + std::to_string(a_mu_rms_values->u1_rms) + "' WHERE id = 1";
	
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//else
	//  this->trace_debug("SUCCESS: Update meter ok.");

	sql = "UPDATE Meter SET u2 = '" + std::to_string(a_mu_rms_values->u2_rms) + "' WHERE id = 1";
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//	else
	//  this->trace_debug("SUCCESS: Update meter ok.");


	sql = "UPDATE Meter SET u3 = '" + std::to_string(a_mu_rms_values->u3_rms) + "' WHERE id = 1";
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//else
	//  this->trace_debug("SUCCESS: Update meter ok.");

	/**
	   Update current
	 */
	sql = "UPDATE Meter SET i1 = '" + std::to_string(a_mu_rms_values->i1_rms) + "' WHERE id = 1";
	
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//else
	//  this->trace_debug("SUCCESS: Update meter ok.");

	sql = "UPDATE Meter SET i2 = '" + std::to_string(a_mu_rms_values->i2_rms) + "' WHERE id = 1";
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//else
	//  this->trace_debug("SUCCESS: Update meter ok.");


	sql = "UPDATE Meter SET i3 = '" + std::to_string(a_mu_rms_values->i3_rms) + "' WHERE id = 1";
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update meter fail.");
	  sqlite3_free(messaggeError);
	}
	//else
	//  this->trace_debug("SUCCESS: Update meter ok.");

	return 0;

}

uint32_t sqlite_interface::put_status(mu_system_status *a_mu_system_status) {
	std::string sql;
	uint32_t rc=0;
	char* messaggeError;

	this->trace_debug("sqlite_interface::put_status");

	if (m_db == NULL) {
	  this->trace_debug("DB not valid");
	  return 1;
	}

	if (a_mu_system_status == NULL) {
	  this->trace_debug("Status structure not valid");
	  return 1;
	}
	
	sql = "UPDATE Status SET R5SP_HEALTH = '" + std::to_string(a_mu_system_status->r5sp_health) + "'WHERE id = 1";
	
	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update status fail.");
	  sqlite3_free(messaggeError);
	}
	else
	  this->trace_debug("SUCCESS: Update status ok.");

	sql = "UPDATE Status SET R5NT_HEALTH = '" + std::to_string(a_mu_system_status->r5nt_health) + "'WHERE id = 1";

	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update status fail.");
	  sqlite3_free(messaggeError);
	}
	else
	  this->trace_debug("SUCCESS: Update status ok.");

	sql = "UPDATE Status SET A53_HEALTH = '" + std::to_string(a_mu_system_status->a53_health) + "'WHERE id = 1";

	rc = sqlite3_exec (m_db, sql.c_str(), NULL, 0, &messaggeError);
	if (rc != SQLITE_OK) {
	  this->trace_debug("ERROR: Update status fail.");
	  sqlite3_free(messaggeError);
	}
	else
	  this->trace_debug("SUCCESS: Update status ok.");

	
	return 0;
}

uint32_t sqlite_interface::get_settings(mu_settings *a_mu_settings) {
	uint32_t rc;

	this->trace_debug("sqlite_interface::get_setting");

	std::string data("CALLBACK FUNCTION");

	std::string sql("SELECT * FROM Setting;");


	rc = sqlite3_exec(m_db, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if (rc != SQLITE_OK)
	  this->trace_debug("ERROR: read settings from data base.");
	else {
	  this->trace_debug("SUCCESS: Read settings from data base.");
	  	  return 1;
	}
	return 0;
}
