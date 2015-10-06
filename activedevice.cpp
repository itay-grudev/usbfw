#include "activedevice.h"

struct ActiveDevicePrivate {
    ActiveDevicePrivate(ActiveDevice* q_ptr) : q_ptr(q_ptr)
    {
    }

    std::string deviceDir() {
        return "/sys" + q_ptr->devpath();
    }

private:
    ActiveDevice *q_ptr;
};

ActiveDevice::ActiveDevice(std::string devpath) : Device(), d_ptr(new ActiveDevicePrivate(this))
{

}

void ActiveDevice::evaluate()
{

}
