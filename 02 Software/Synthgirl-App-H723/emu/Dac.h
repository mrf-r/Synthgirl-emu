#ifndef __DAC_H
#define __DAC_H

#include <stdint.h>

class Dac {
   public:
    Dac() {};
    ~Dac() {};
    volatile uint16_t i2s_data[4];

    void initialize() {};
    void audioOn() {};
    void audioOff() {};
};

#endif
