#ifndef ACTIVE_DEVICE_H
#define ACTIVE_DEVICE_H

#include "device.h"

struct ActiveDevicePrivate;

class ActiveDevice : public Device {
public:
    ActiveDevice(std::string devpath);
    void evaluate();

private:
    ActiveDevicePrivate *d_ptr;
};

#endif // ACTIVE_DEVICE_H
