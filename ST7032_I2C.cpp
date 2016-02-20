#include <cstring>
#include <unistd.h>

#include "ST7032_I2C.h"
#include "ST7032_defs.h"

ST7032_I2C::ST7032_I2C()
{
    i2c = NULL;
}

ST7032_I2C::~ST7032_I2C()
{
    if (i2c) {
        delete i2c;
    }
}

void ST7032_I2C::init(const unsigned int slot, const unsigned int chip_address) 
{
    try {
        const int retry_times = 5;

        i2c = new i2c_access(retry_times);
        i2c->init(slot, chip_address);

        usleep(100);
        const unsigned char init_commands[] = {
            LCD_FUNCTIONSET  | 0b11000,
            LCD_FUNCTIONSET  | 0b11001,
            LCD_INTERNAL_OSC_FREQUENCY | 0b0100,
            LCD_CONTRAST_SET | 0b0011,
            LCD_ICON_CONTROL | 0b1111,
            LCD_FOLLOWER_CONTROL | 0b1010
        };
        i2c->write(0x00, init_commands, sizeof(init_commands));
        usleep(200000);

        i2c->write(0x00, LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
        usleep(1000000);
        i2c->write(0x00, LCD_CLEARDISPLAY);
        usleep(50);
        i2c->write(0x00, LCD_ENTRYMODESET | LCD_ENTRYLEFT);
        usleep(50);
    } catch(...) {
        throw;
    }
}

void ST7032_I2C::print(const unsigned int line, const char *message)
{
    const int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    int offset;

    if (line > sizeof(row_offsets)) {
        throw "line parameter is too large";
    }

    offset = LCD_SETDDRAMADDR + row_offsets[line - 1];

    i2c->write(0x00, offset);
    usleep(50);

    i2c->write(0x40, (unsigned char*)message, strlen(message));
    usleep(50);
}
