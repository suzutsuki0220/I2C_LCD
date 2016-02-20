#ifndef __ST7032_I2C_H__
#define __ST7032_I2C_H__

#include <cerrno>
#include "i2c_access.h"

#define ST7032_I2C_DEFAULT_ADDR 0x3e

class ST7032_I2C {
private:
     i2c_access *i2c;

public:
     ST7032_I2C();
     ~ST7032_I2C();

    void init(const unsigned int slot, const unsigned int chip_address = ST7032_I2C_DEFAULT_ADDR);
    void print(const unsigned int line, const char *message);
};

#endif  // __ST7032_I2C_H__
