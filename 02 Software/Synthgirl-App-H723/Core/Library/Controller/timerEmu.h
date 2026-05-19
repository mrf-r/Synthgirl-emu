#pragma once
#include <stdint.h>
// #include <iostream>

class ClassPtr {};
typedef void (ClassPtr::*MethodPtr)();

class TimerEmu {
    private:
    uint32_t period;
    bool enable;
    bool res;
    uint32_t previous;
    MethodPtr callback_func;
    ClassPtr *inst;

    public:
    void init(const uint32_t period_, ClassPtr* inst_, MethodPtr callback_func_) {
        enable = false;
        res = true;
        period = period_;
        inst = inst_;
        callback_func = callback_func_;
    }
    void start() {
        enable = true;
        res = true;
    }
    void stop() {
        enable = false;
    }
    void reset() {
        res = true;
    }
    void check(uint32_t now) {
        if (res) {
            res = false;
            previous = now;
        }
        if (enable) {
            while (now - previous >= period) {
                previous += period;
                (inst->*callback_func)();
            }
        }
    }
};
