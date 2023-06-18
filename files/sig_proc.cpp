


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
#include "sig_proc.hpp"
#include "mu_settings.hpp"
#include "mu_status.hpp"
#include "enums.hpp"

   SignalProc::SignalProc()
   {

   }

float SignalProc::RMSCalculation(float *values, uint32_t count) {
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