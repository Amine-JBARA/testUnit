#ifndef SIG_PROC_HPP_
#define SIG_PROC_HPP_

#include <stdint.h>


class SignalProc {
   public:
   static SignalProc& instance() {
        static SignalProc instance;
        return instance;
    }
    // Constructeur par défaut
   float RMSCalculation(float *values, uint32_t count);

   SignalProc();
   SignalProc(SignalProc const&) = delete;

   private:


};

#endif  // Sig_Proc_HPP_