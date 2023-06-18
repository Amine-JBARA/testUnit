#ifndef IPC_STUB_HPP_
#define IPC_STUB_HPP_

#include "ipc_interface.hpp"

class IPCStub : public IPCInterface {
public:
    void  *thread_rproc_management(void *arg) override;
    int AllocateShareMemory(int *a_fd, void** a_base_address, void** a_virtual_address) override;
    int UnallocateShareMemory(int fd, void* ptr) override ;
    void DumpADCSamples(mu_shared_ADCsamples *a_mu_shared_ADCsamples) override;
    inline void *fixup_addr(void *addr, size_t size) override;
};

#endif  // IPC_STUB_HPP_
