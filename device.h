#ifndef DEVICE_H
#define DEVICE_H

#include <string>

struct DevicePrivate;

class Device {
public:
    Device();

    std::string devpath();
    void setDevpath(std::string);

    std::string devnode();
    void setDevnode(std::string);

    std::string idProduct();
    void setIdProduct(std::string);

    std::string idVendor();
    void setIdVendor(std::string);

    std::string manufacturer();
    void setManufacturer(std::string);

    std::string product();
    void setProduct(std::string);

    std::string serial();
    void setSerial(std::string);

    std::string speed(); // WHAT IS THIS!? CHECK /SYS/USB/ files meaning
    void setSpeed(std::string);

    std::string version();
    void setVersion(std::string);

private:
    DevicePrivate *d_ptr;
};

#endif // DEVICE_H
