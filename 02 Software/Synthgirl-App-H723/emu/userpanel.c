#include "panel_conf.h"
#include "panel.h"
#include "mbwmidi.h"
#include "userpanel.h"
#include "bsp.h"

void panelConstruct(SDL_Renderer* rend);
void appStart(void);
void appLoop(uint32_t clock);

uint8_t emu_ram_d2[32 * 1024];
uint8_t emu_ram_d3[16 * 1024];
uint8_t emu_sdram[128 * 1024 * 1024]; // whoa!

uint8_t syncInData[2];
uint8_t syncOutData[2];
uint8_t midiRxData;
void init();
void calculateNextSample(int16_t *data);
void midiReceiveByte(uint8_t data);
void kbdPress(uint8_t key, uint8_t state);
void loop(uint32_t clock);
void getNextAudioBlock(int32_t* const buffer_out, const unsigned len);

void synthAudioCallback(const WAudioT* const buffer_in, WAudioT* const buffer_out, const unsigned length) {
    (void)buffer_in;
    getNextAudioBlock(buffer_out, length);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Pots

/////////////////////////////////////////////////////////////////////////////////////////////////
// Buttons
typedef struct {
    const char* name;
    const char* hint;
    const SDL_KeyCode keycode;
    const uint8_t midikey;
} ButtonDef;

typedef enum {
    KEY_RESET = 0x06 + 1,
    KEY_PLAYSTOP = 0x07 + 1,
    KEY_REC = 0x01 + 1,
    KEY_UP = 0x00 + 1,
    KEY_DOWN = 0x08 + 1,
    KEY_LEFT = 0x04 + 1,
    KEY_RIGHT = 0x03 + 1,
    KEY_CENTER = 0x0E + 1,
    KEY_ADD = 0x05 + 1,
    KEY_ERASE = 0x02 + 1,
    KEY_COPY = 0x0B + 1,
    KEY_PASTE = 0x0C + 1,
    KEY_POWER = 0x0A + 1,
    KEY_OCTAVE_DOWN = 0x09 + 1,
    KEY_OCTAVE_UP = 0x0D + 1,
    LEFT_RELEASE = 0x00
} KeyLeft;

typedef enum {
    KEY_FILE = 0x06 + 1,
    KEY_SYNTHKIT = 0x07 + 1,
    KEY_SYSTEM = 0x01 + 1,
    KEY_RHYTHM = 0x05 + 1,
    KEY_METRONOME = 0x00 + 1,
    KEY_EQ = 0x02 + 1,
    KEY_OSC_A = 0x04 + 1,
    KEY_OSC_B = 0x0E + 1,
    KEY_FILTER = 0x03 + 1,
    KEY_ENVELOPE = 0x0B + 1,
    KEY_EFFECT = 0x08 + 1,
    KEY_REVERB = 0x0C + 1,
    KEY_MODE_KEY = 0x0A + 1,
    KEY_MODE_SONG = 0x09 + 1,
    KEY_BANK = 0x0D + 1,
    RIGHT_RELEASE = 0x00
} KeyRight;

typedef enum {
    KEY_00 = 0x05 + 1,
    KEY_01 = 0x03 + 1,
    KEY_02 = 0x06 + 1,
    KEY_03 = 0x02 + 1,
    KEY_04 = 0x07 + 1,
    KEY_05 = 0x08 + 1,
    KEY_06 = 0x01 + 1,
    KEY_07 = 0x09 + 1,
    KEY_08 = 0x00 + 1,
    KEY_09 = 0x0A + 1,
    KEY_10 = 0x04 + 1,
    KEY_11 = 0x0B + 1,
    BEAT_RELEASE = 0x00
} KeyBeat;

#define KEY_LEFT_OFFSET 0x20
#define KEY_RIGHT_OFFSET 0x30
#define KEY_BEAT_OFFSET 0x40

static ButtonDef bdef[] = {
    { .name = "Reset", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + KEY_RESET},
    { .name = "Play", .hint = "spc", .keycode = SDLK_SPACE, .midikey = KEY_LEFT_OFFSET + KEY_PLAYSTOP},
    { .name = "Rec", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + KEY_REC},
    { .name = "Add", .hint = "=", .keycode = SDLK_EQUALS, .midikey = KEY_LEFT_OFFSET + KEY_ADD},
    { .name = "Up", .hint = "^", .keycode = SDLK_UP, .midikey = KEY_LEFT_OFFSET + KEY_UP},
    { .name = "Erase", .hint = "bcksp", .keycode = SDLK_BACKSPACE, .midikey = KEY_LEFT_OFFSET + KEY_ERASE},
    { .name = "Left", .hint = "<-", .keycode = SDLK_LEFT, .midikey = KEY_LEFT_OFFSET + KEY_LEFT},
    { .name = "Center", .hint = "ret", .keycode = SDLK_RETURN, .midikey = KEY_LEFT_OFFSET + KEY_CENTER},
    { .name = "Right", .hint = "->", .keycode = SDLK_RIGHT, .midikey = KEY_LEFT_OFFSET + KEY_RIGHT},
    { .name = "Copy", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + KEY_COPY},
    { .name = "Down", .hint = "V", .keycode = SDLK_DOWN, .midikey = KEY_LEFT_OFFSET + KEY_DOWN},
    { .name = "Paste", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + KEY_PASTE},
    { .name = "Power", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + KEY_POWER},
    { .name = "OctDwn", .hint = "<", .keycode = SDLK_COMMA, .midikey = KEY_LEFT_OFFSET + KEY_OCTAVE_DOWN},
    { .name = "OctUp", .hint = ">", .keycode = SDLK_PERIOD, .midikey = KEY_LEFT_OFFSET + KEY_OCTAVE_UP},
    // { .name = "Lrelease", .hint = "", .keycode = -1, .midikey = KEY_LEFT_OFFSET + LEFT_RELEASE},

    { .name = "File", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_FILE},
    { .name = "Synkit", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_SYNTHKIT},
    { .name = "System", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_SYSTEM},
    { .name = "Rhythm", .hint = "1", .keycode = SDLK_1, .midikey = KEY_RIGHT_OFFSET + KEY_RHYTHM},
    { .name = "Metro", .hint = "2", .keycode = SDLK_2, .midikey = KEY_RIGHT_OFFSET + KEY_METRONOME},
    { .name = "Eq", .hint = "3", .keycode = SDLK_3, .midikey = KEY_RIGHT_OFFSET + KEY_EQ},
    { .name = "Osc_a", .hint = "4", .keycode = SDLK_4, .midikey = KEY_RIGHT_OFFSET + KEY_OSC_A},
    { .name = "Osc_b", .hint = "5", .keycode = SDLK_5, .midikey = KEY_RIGHT_OFFSET + KEY_OSC_B},
    { .name = "Filter", .hint = "6", .keycode = SDLK_6, .midikey = KEY_RIGHT_OFFSET + KEY_FILTER},
    { .name = "Env", .hint = "7", .keycode = SDLK_7, .midikey = KEY_RIGHT_OFFSET + KEY_ENVELOPE},
    { .name = "Effect", .hint = "8", .keycode = SDLK_8, .midikey = KEY_RIGHT_OFFSET + KEY_EFFECT},
    { .name = "Reverb", .hint = "9", .keycode = SDLK_9, .midikey = KEY_RIGHT_OFFSET + KEY_REVERB},
    { .name = "mKey", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_MODE_KEY},
    { .name = "mSong", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_MODE_SONG},
    { .name = "Bank", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + KEY_BANK},
    // { .name = "Rrelease", .hint = "", .keycode = -1, .midikey = KEY_RIGHT_OFFSET + RIGHT_RELEASE},
    
    { .name = "00", .hint = "z", .keycode = SDLK_z, .midikey = KEY_BEAT_OFFSET + KEY_00},
    { .name = "01", .hint = "s", .keycode = SDLK_s, .midikey = KEY_BEAT_OFFSET + KEY_01},
    { .name = "02", .hint = "x", .keycode = SDLK_x, .midikey = KEY_BEAT_OFFSET + KEY_02},
    { .name = "03", .hint = "d", .keycode = SDLK_d, .midikey = KEY_BEAT_OFFSET + KEY_03},
    { .name = "04", .hint = "c", .keycode = SDLK_c, .midikey = KEY_BEAT_OFFSET + KEY_04},
    { .name = "05", .hint = "v", .keycode = SDLK_v, .midikey = KEY_BEAT_OFFSET + KEY_05},
    { .name = "06", .hint = "g", .keycode = SDLK_g, .midikey = KEY_BEAT_OFFSET + KEY_06},
    { .name = "07", .hint = "b", .keycode = SDLK_b, .midikey = KEY_BEAT_OFFSET + KEY_07},
    { .name = "08", .hint = "h", .keycode = SDLK_h, .midikey = KEY_BEAT_OFFSET + KEY_08},
    { .name = "09", .hint = "n", .keycode = SDLK_n, .midikey = KEY_BEAT_OFFSET + KEY_09},
    { .name = "10", .hint = "j", .keycode = SDLK_j, .midikey = KEY_BEAT_OFFSET + KEY_10},
    { .name = "11", .hint = "m", .keycode = SDLK_m, .midikey = KEY_BEAT_OFFSET + KEY_11},
    // { .name = "12", .hint = "", .keycode = -1, .midikey = KEY_BEAT_OFFSET + BEAT_RELEASE},
};

#define BUTTONS_COUNT (sizeof(bdef) / sizeof(ButtonDef))
static WidgetButton buttons[BUTTONS_COUNT];

void bspLedSet(uint8_t id, bool state) {
    switch (id) {
        case 0: // this one is seq key
            widgetLed(&buttons[0].v, state ? 0x00808000 : 0);
            break;
        case 1:
            widgetLed(&buttons[1].v, state ? 0x00808000 : 0);
            break;
        case 2:
            widgetLed(&buttons[2].v, state ? 0x00808000 : 0);
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Other
WID_DISPLAY_MULTI_DEFINE(disp_tft, 854, 480)
// WID_AUDIO_CALLBACK_DEFINE(paCallback, synthAudioCallback)
static WidgetFrameCounter framecounter;
// static WidgetMidi wmidi_io;
static WidgetAudio waudio;

void panelConstruct(SDL_Renderer* rend)
{
    wFrameCounterInit(&framecounter, 20, 0, rend);

    uint16_t xinit = PAN_BORDER;
    uint16_t yinit = PAN_BORDER;
    uint16_t y = yinit;
    uint16_t x = xinit;

    uint16_t but = 0;
    for (unsigned i = 0; i < 5; i++) {
        x = xinit;
        for (unsigned j = 0; j < 3; j++) {
            wButtonInit(&buttons[but], bdef[but].name, bdef[but].hint, bdef[but].keycode, bdef[but].midikey, x, y, rend);
            but++;
            x += PAN_BUT_INC;
        }
        y += PAN_BUT_INC;
    }
    
    y = yinit;
    wDisplayMultiInit(&disp_tft, &disp_tft_mgldisp, x, y, PANEL_SCALE, rend);

    xinit = PAN_RBXOFF;
    y = yinit;
    for (unsigned i = 0; i < 5; i++) {
        x = xinit;
        for (unsigned j = 0; j < 3; j++) {
            wButtonInit(&buttons[but], bdef[but].name, bdef[but].hint, bdef[but].keycode, bdef[but].midikey, x, y, rend);
            but++;
            x += PAN_BUT_INC;
        }
        y += PAN_BUT_INC;
    }

    yinit = y + PAN_BUT_INC / 2;
    x = PAN_RBXOFF;
    for (unsigned i = 0; i < 3; i++) {
        y = yinit;
        for (unsigned j = 0; j < 4; j++) {
            if (but < BUTTONS_COUNT) {
                wButtonInit(&buttons[but], bdef[but].name, bdef[but].hint, bdef[but].keycode, bdef[but].midikey, x, y, rend);
            }
            but++;
            y += PAN_BUT_INC;
        }
        x += PAN_BUT_INC;
    }
    //*/
    // wMidiInit(&wmidi_io, 70, 0, rend, "MPK", "MPK", 31250, 115200);
    wAudioInit(&waudio, 120, 0, rend, 0, 0, 48000, 32, synthAudioCallback);
    mgsDisplay(&disp_tft_mgldisp);
    mgdHsvTestFill();
}

void appStart() {
    init();
}

void appHandleMidi(MidiTsMessageT mt)
{
    MidiMessageT m = mt.mes;
    if (MIDI_CN_LOCALPANEL == m.cn) {
        switch (m.cin)
        {
        case MIDI_CIN_NOTEOFF:
            kbdPress(m.byte2, 0);
            break;
        case MIDI_CIN_NOTEON:
            kbdPress(m.byte2, 1);
            break;
        default:
            break;
        }
    }
}

void appLoop(uint32_t clock)
{
    loop(clock);

    MidiTsMessageT mt;
    while (MIDI_RET_OK == midiRead(&mt)) {
        appHandleMidi(mt);
    }
    (void)clock;
}


