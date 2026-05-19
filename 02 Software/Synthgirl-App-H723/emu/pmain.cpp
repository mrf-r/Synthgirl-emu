#include <stdio.h>
#include "Controller.h"

Controller controller;

extern "C" void init() {
    controller.timersInit();
    controller.initialize();

    // while (!controller.getPower()) {
    //     controller.systemUpdate_A();
    // }

    controller.systemStart();

    // while (controller.getPower()) {
    //     controller.systemUpdate_B();
    // }

    // controller.systemReset();
}


extern "C" void calculateNextSample(int32_t *data) {
    controller.interruptTransition();
    controller.interruptAudioSend(); // audioReverb_L/R + audioMetronome -> dac.i2s_data
    controller.interruptAudioMetronome(); // *** audioMetronome
    controller.interruptAudioSong(); // *** audioSong
    controller.interruptAudioLpf(); // audioSong -> audioLpf
    controller.interruptAudioEq(); // audioLpf -> audioEq
    controller.interruptAudioFilter(); // audioEq -> audioFilter
    controller.interruptAudioEffect(); // audioFilter -> audioEffect
    controller.interruptAudioReverb(); // audioEffect -> audioReverb_L/R
    int32_t left = (int32_t)((controller.dac.i2s_data[0] << 16) | controller.dac.i2s_data[1]);
    int32_t right = (int32_t)((controller.dac.i2s_data[2] << 16) | controller.dac.i2s_data[3]);
    // static uint32_t lcg = 0;
    // lcg = lcg * 0x41C64E6D + 0x3039;
    // *data = (int16_t)((left + lcg / 65536) / 65536);
    *data = left;
    data++;
    // *data = (int16_t)((right + lcg / 65536) / 65536);
    *data = right;
}

// TODO: midi out        controller.midiTxBusy = false;
extern "C" void midiReceiveByte(uint8_t data) {
    midiRxData = data;
    controller.receiveMidiCommand();
}

#define KEY_LEFT_OFFSET 0x20
#define KEY_RIGHT_OFFSET 0x30
#define KEY_BEAT_OFFSET 0x40

extern "C" void kbdPress(uint8_t key, uint8_t state) {
    if ((key > KEY_BEAT_OFFSET) && (key < KEY_BEAT_OFFSET + 13)) {
        if (state) {
            controller.keyboard.beatButton = key - KEY_BEAT_OFFSET;
        } else {
            controller.keyboard.beatButton = 0;
        }
    } else if ((key > KEY_RIGHT_OFFSET) && (key < KEY_RIGHT_OFFSET + 16)) {
        if (state) {
            controller.keyboard.rightButton = key - KEY_RIGHT_OFFSET;
        } else {
            controller.keyboard.rightButton = 0;
        }
    } else if ((key > KEY_LEFT_OFFSET) && (key < KEY_LEFT_OFFSET + 16)) {
        if (state) {
            controller.keyboard.leftButton = key - KEY_LEFT_OFFSET;
        } else {
            controller.keyboard.leftButton = 0;
        }
    }
}

extern "C" void getNextAudioBlock(int32_t* const buffer_out, const unsigned len) {
    for (unsigned i = 0; i < len; i++) {
        calculateNextSample(&buffer_out[i * 2]);
    }
}

extern "C" void loop(uint32_t clock) {
    controller.systemUpdate_B();
    controller.timersCheck(clock);
}

