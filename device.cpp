#include "device.h"

struct DevicePrivate {
    std::string devpath;
};

Device::Device() : d_ptr(new DevicePrivate)
{

}
