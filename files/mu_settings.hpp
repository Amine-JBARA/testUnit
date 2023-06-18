#ifndef _MU_SETTINGS_
#define _MU_SETTINGS_

#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>


typedef struct {
  float cal_gain_U1;
  float cal_phase_U1;
  float cal_gain_U2;
  float cal_phase_U2;
  float cal_gain_U3;
  float cal_phase_U3;
  float cal_gain_I1;
  float cal_phase_I1;
  float cal_gain_I2;
  float cal_phase_I2;
  float cal_gain_I3;
  float cal_phase_I3;
  uint32_t calibration_update_count;
} mu_calibration;

typedef struct {
  uint8_t diinvert;
  uint8_t sv_goose_sign; 
  uint8_t simulation;
  uint8_t attempt_count;
  //char32_t device_name;
  uint8_t password_exp_time;
} mu_settings;


#endif /* _MU_SETTINGS_ */
