#define I2CBUS 1
#define LCD_ADDR 0x3e

#include <cstdio>
#include <string>

#include "ST7032_I2C.h"

int main(int argc, char *argv[])
{
    ST7032_I2C lcd;

    try {
        lcd = ST7032_I2C();
        lcd.init(I2CBUS, LCD_ADDR);

        lcd.print(1, "hello,world");
        lcd.print(2, "  NEW WORLD");

    } catch(std::bad_alloc ex) {
        fprintf(stderr, "Error: allocation failed : %s\n", ex.what());
        return -1;
    } catch(std::string &err_mes) {
        fprintf(stderr, "Error: %s\n", err_mes.c_str());
        return -1;
    }

    return 0;
}
