#ifndef _IPC_HPP_
#define _IPC_HPP_

#include "mu_status.hpp"
class IPC {
public:
static IPC& instance() {
        static IPC instance;
        return instance;
    }
    mu_rms_values* ipc_get_meter();
    void ipc_get_status(mu_system_status** a_mu_system_status);
    void static *thread_rproc_management(void *arg);

private:

int AllocateShareMemory(int *a_fd, void** a_base_address, void** a_virtual_address);
int UnallocateShareMemory(int fd, void* ptr) ;
//float RMSCalculation(float *values, uint32_t count);
static void DumpADCSamples(mu_shared_ADCsamples *a_mu_shared_ADCsamples);
static inline void *fixup_addr(void *addr, size_t size);



 // Déclarations des fonctions membres privées
};
#endif /* _IPC_HPP_ */