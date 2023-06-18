#ifndef _MU_STATUS_
#define _MU_STATUS_

#include <stdint.h>

typedef struct {
    uint32_t acq_mode; // 0 = Do not get ADC sample. 1 = Get RAW ADC samples.
    uint32_t u1_val[9600];
    uint32_t u2_val[9600];
    uint32_t u3_val[9600];
    uint32_t i1_val[9600];
    uint32_t i2_val[9600];
    uint32_t i3_val[9600];
} mu_shared_ADCsamples;

typedef struct {
    float u1_val[96];
    float u2_val[96];
    float u3_val[96];
    float i1_val[96];
    float i2_val[96];
    float i3_val[96];
} mu_shared_samples;

typedef struct {
    float u1_rms;
    float u2_rms;
    float u3_rms;
    float i1_rms;
    float i2_rms;
    float i3_rms;
} mu_rms_values;

typedef struct {
    uint32_t r5sp_health;
    uint32_t r5nt_health;
    uint32_t a53_health;
    uint32_t ptp_synchro;
    uint32_t ptp_offset;
} mu_system_status;


#endif /* _MU_STATUS_ */
