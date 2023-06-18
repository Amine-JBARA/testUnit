
#ifndef IPC_INTERFACE_HPP_
#define IPC_INTERFACE_HPP_

#include "mu_status.hpp"

class IPCInterface {
public:
    virtual void ipc_get_status(mu_system_status** a_mu_system_status) = 0;
    virtual mu_rms_values* ipc_get_meter() = 0;
private :
    virtual void  *thread_rproc_management(void *arg)=0;
    virtual int AllocateShareMemory(int *a_fd, void** a_base_address, void** a_virtual_address)=0;
    virtual int UnallocateShareMemory(int fd, void* ptr)=0;
    virtual void DumpADCSamples(mu_shared_ADCsamples *a_mu_shared_ADCsamples)=0;
    virtual inline void *fixup_addr(void *addr, size_t size)=0;

    virtual int recv_msg(int fd, int len, char *reply_msg, int *reply_len)=0;
    virtual int send_msg(int fd, char *msg, int len)=0;



};


#endif /* IPC_INTERFACE_HPP_ */

