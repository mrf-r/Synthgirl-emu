#include <stdint.h>
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    void bspDelayMs(const uint32_t time_ms);
    // void bspDelayUs(const uint32_t time_us);
    uint32_t bspGetMs(void);
    // uint32_t bspGetUs(void);
    
    // void bspHRTimerInit(void);
    // uint32_t bspHRTimerGetDelta(void);
    // uint32_t bspHRTimerGetFreq(void);
    
    // void bspLedToggle(uint8_t id);
    void bspLedSet(uint8_t id, bool state);
    // bool bspLedGet(uint8_t id);
    // bool bspButtonGet(uint8_t id);
    __attribute__((unused)) static void bspGpioSet(uint8_t id, bool state) {(void)id; (void)state; }
    __attribute__((unused)) static bool bspGpioGet(uint8_t id) {(void)id; return false; }

    #define GPIO_SYNC_OUT 0
    #define GPIO_SD_IN 0
    #define LED0 0
    #define LED1 1
    #define LED2 2
    #define SDPath "0:/"

    
    
#ifdef __cplusplus
}
#endif
