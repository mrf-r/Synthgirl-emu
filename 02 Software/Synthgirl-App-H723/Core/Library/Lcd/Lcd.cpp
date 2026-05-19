#include <stdio.h>
#include <string.h>
#include "Lcd.h"
#include "bsp.h"
#include "mgl.h"

Lcd::Lcd(LcdRotation rotation_, RGB16Color foreColor_, RGB16Color backColor_, LcdFont font_)
    : rotation(rotation_),
      foreColor(foreColor_),
      backColor(backColor_),
      fontAlignment(LEFT) {
    switch (rotation) {
        case 0:
            width = kLCD_WIDTH;
            height = kLCD_HEIGHT;
            break;
        case 1:
            width = kLCD_HEIGHT;
            height = kLCD_WIDTH;
            break;
        case 2:
            width = kLCD_WIDTH;
            height = kLCD_HEIGHT;
            break;
        case 3:
            width = kLCD_HEIGHT;
            height = kLCD_WIDTH;
            break;
    }
    setFont(font_);
}

Lcd::~Lcd() {}

/* Private functions ---------------------------------------------------------*/

uint8_t Lcd::getLetter(char letter) {
    switch (letter) {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        case 'A':
        case 'a':
            return 10;
            break;
        case 'B':
        case 'b':
            return 11;
            break;
        case 'C':
        case 'c':
            return 12;
            break;
        case 'D':
        case 'd':
            return 13;
            break;
        case 'E':
        case 'e':
            return 14;
            break;
        case 'F':
        case 'f':
            return 15;
            break;
        case 'G':
        case 'g':
            return 16;
            break;
        case 'H':
        case 'h':
            return 17;
            break;
        case 'I':
        case 'i':
            return 18;
            break;
        case 'J':
        case 'j':
            return 19;
            break;
        case 'K':
        case 'k':
            return 20;
            break;
        case 'L':
        case 'l':
            return 21;
            break;
        case 'M':
        case 'm':
            return 22;
            break;
        case 'N':
        case 'n':
            return 23;
            break;
        case 'O':
        case 'o':
            return 24;
            break;
        case 'P':
        case 'p':
            return 25;
            break;
        case 'Q':
        case 'q':
            return 26;
            break;
        case 'R':
        case 'r':
            return 27;
            break;
        case 'S':
        case 's':
            return 28;
            break;
        case 'T':
        case 't':
            return 29;
            break;
        case 'U':
        case 'u':
            return 30;
            break;
        case 'V':
        case 'v':
            return 31;
            break;
        case 'W':
        case 'w':
            return 32;
            break;
        case 'X':
        case 'x':
            return 33;
            break;
        case 'Y':
        case 'y':
            return 34;
            break;
        case 'Z':
        case 'z':
            return 35;
            break;
        case '/':
            return 36;
            break;
        case '-':
            return 37;
            break;
        case '+':
            return 38;
            break;
        case '%':
            return 39;
            break;
        case '.':
            return 40;
            break;
        case ',':
            return 41;
            break;
        case ':':
            return 42;
            break;
        case '<':
            return 43;
            break;
        case '>':
            return 44;
            break;
        case '[':
            return 45;
            break;
        case ']':
            return 46;
            break;
        case '_':
            return 47;
            break;
        case '|':
            return 48;
            break;
        case '?':
            return 49;
            break;
        case '#':
            return 50;
            break;
        case '!':
            return 51;
            break;
        case ' ':
            return 52;
            break;
        default:
            return 52;
            break;
    }
}

RGB16Color Lcd::alphaColor(RGB16Color color_, float alpha) {
    uint16_t red = (uint16_t)((color_ >> 11) * alpha);
    uint16_t green = (uint16_t)(((color_ >> 5) & 0b00111111) * alpha);
    uint16_t blue = (uint16_t)((color_ & 0b00011111) * alpha);
    RGB16Color color = (red << 11) | (green << 5) | (blue);
    return color;
}

RGB16Color Lcd::alphaColor(struct RGB24RawColor color_, float alpha) {
    uint16_t red = (uint16_t)(color_.red * alpha) >> 3;
    uint16_t green = (uint16_t)(color_.green * alpha) >> 2;
    uint16_t blue = (uint16_t)(color_.blue * alpha) >> 3;
    RGB16Color color = (red << 11) | (green << 5) | (blue);
    return color;
}

RGB16Color Lcd::convertColor(struct RGB24RawColor color_) {
    uint16_t red = color_.red >> 3;
    uint16_t green = color_.green >> 2;
    uint16_t blue = color_.blue >> 3;
    RGB16Color color = (red << 11) | (green << 5) | (blue);
    return color;
}

/* Public functions ----------------------------------------------------------*/

void Lcd::setFont(LcdFont font_) {
    font = font_;
    switch (font) {
        case FONT_05x07:
            fontData = &kFontData_05x07[0][0];
            fontWidth = kFontWidth_05x07;
            fontHeight = kFontHeight_05x07;
            fontSpacing = kFontSpacing_05x07;
            break;
        case FONT_07x09:
            fontData = &kFontData_07x09[0][0];
            fontWidth = kFontWidth_07x09;
            fontHeight = kFontHeight_07x09;
            fontSpacing = kFontSpacing_07x09;
            break;
        case FONT_10x14:
            fontData = &kFontData_10x14[0][0];
            fontWidth = kFontWidth_10x14;
            fontHeight = kFontHeight_10x14;
            fontSpacing = kFontSpacing_10x14;
            break;
        case FONT_14x18:
            fontData = &kFontData_14x18[0][0];
            fontWidth = kFontWidth_14x18;
            fontHeight = kFontHeight_14x18;
            fontSpacing = kFontSpacing_14x18;
            break;
    }
}

void Lcd::initialize() {
}

void Lcd::clearScreen() {
    fillScreen(backColor);
}

void Lcd::fillScreen() {
    fillScreen(foreColor);
}

#define CCONV(c) ((MglColor){.blue = (uint8_t)((c&0x1F)<<3), .green = (uint8_t)(((c>>5)&0x3F)<<2), .red = (uint8_t)((c>>11)<<3)})

void Lcd::fillScreen(RGB16Color color) {
    mgsWorkingArea(0,0, width, height);
    mgdFill(CCONV(color));
}

void Lcd::drawPixel(uint16_t x, uint16_t y) {
    mgxSetZone(x, y, 1, 1);
    mgxPixelOut(CCONV(foreColor));
}

void Lcd::drawHLine(uint16_t x, uint16_t y, uint16_t l) {
    mgsWorkingArea(x, y, l, 1);
    mgdFill(CCONV(foreColor));
}

void Lcd::drawVLine(uint16_t x, uint16_t y, uint16_t l) {
    mgsWorkingArea(x, y, 1, l);
    mgdFill(CCONV(foreColor));
}

void Lcd::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) {
        if (steep) {
            drawPixel(y0, x0);
        } else {
            drawPixel(x0, y0);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void Lcd::drawRect(uint16_t x, uint16_t y, uint32_t w, uint32_t h) {
    if ((x < width) && (y < height)) {
        if ((x + w - 1) >= width) {
            w = width - x;
        }
        if ((y + h - 1) >= height) {
            h = height - y;
        }
        drawHLine(x, y, w);
        drawHLine(x, y + h - 1, w);
        drawVLine(x, y, h);
        drawVLine(x + w - 1, y, h);
    }
}

void Lcd::fillRect(uint16_t x, uint16_t y, uint32_t w, uint32_t h) {
    mgsWorkingArea(x, y, w, h);
    mgdFill(CCONV(foreColor));
}

void Lcd::drawCircle(uint16_t x, uint16_t y, uint16_t r) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t xc = 0;
    int16_t yc = r;
    drawPixel(x, y + r);
    drawPixel(x, y - r);
    drawPixel(x + r, y);
    drawPixel(x - r, y);
    while (xc < yc) {
        if (f >= 0) {
            yc--;
            ddF_y += 2;
            f += ddF_y;
        }
        xc++;
        ddF_x += 2;
        f += ddF_x;
        drawPixel(x + xc, y + yc);
        drawPixel(x - xc, y + yc);
        drawPixel(x + xc, y - yc);
        drawPixel(x - xc, y - yc);
        drawPixel(x + yc, y + xc);
        drawPixel(x - yc, y + xc);
        drawPixel(x + yc, y - xc);
        drawPixel(x - yc, y - xc);
    }
}

void Lcd::drawCircleHelper(uint16_t x, uint16_t y, uint16_t r, uint8_t cornername) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t xh = 0;
    int16_t yh = r;

    while (xh < yh) {
        if (f >= 0) {
            yh--;
            ddF_y += 2;
            f += ddF_y;
        }
        xh++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            drawPixel(x + xh, y + yh);
            drawPixel(x + yh, y + xh);
        }
        if (cornername & 0x2) {
            drawPixel(x + xh, y - yh);
            drawPixel(x + yh, y - xh);
        }
        if (cornername & 0x8) {
            drawPixel(x - yh, y + xh);
            drawPixel(x - xh, y + yh);
        }
        if (cornername & 0x1) {
            drawPixel(x - yh, y - xh);
            drawPixel(x - xh, y - yh);
        }
    }
}

void Lcd::drawQuarterCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t quarter) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t xc = 0;
    int16_t yc = r;
    switch (quarter) {
        case 0:
            drawPixel(x, y - r);
            drawPixel(x + r, y);
            break;

        case 1:
            drawPixel(x, y - r);
            drawPixel(x - r, y);
            break;

        case 2:
            drawPixel(x, y + r);
            drawPixel(x - r, y);
            break;

        case 3:
            drawPixel(x, y + r);
            drawPixel(x + r, y);
            break;

        default:
            break;
    }

    while (xc < yc) {
        if (f >= 0) {
            yc--;
            ddF_y += 2;
            f += ddF_y;
        }
        xc++;
        ddF_x += 2;
        f += ddF_x;
        switch (quarter) {
            case 0:
                drawPixel(x + xc, y - yc);
                drawPixel(x + yc, y - xc);
                break;

            case 1:
                drawPixel(x - xc, y - yc);
                drawPixel(x - yc, y - xc);
                break;

            case 2:
                drawPixel(x - xc, y + yc);
                drawPixel(x - yc, y + xc);
                break;

            case 3:
                drawPixel(x + xc, y + yc);
                drawPixel(x + yc, y + xc);
                break;

            default:
                break;
        }
    }
}

void Lcd::drawHalfCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t half) {
    uint8_t h0;
    uint8_t h1;

    switch (half) {
        case 0:
            h0 = 0;
            h1 = 1;
            break;

        case 1:
            h0 = 1;
            h1 = 2;
            break;

        case 2:
            h0 = 2;
            h1 = 3;
            break;

        case 3:
            h0 = 3;
            h1 = 0;
            break;

        default:
            h0 = 0;
            h1 = 1;
            break;
    }

    drawQuarterCircle(x, y, r, h0);
    drawQuarterCircle(x, y, r, h1);
    /*
    while (xc < yc) {
    if (f >= 0) {
    yc--;
    ddF_y += 2;
    f += ddF_y;
  }
  xc++;
  ddF_x += 2;
  f += ddF_x;
  switch (half) {
  case 0:
  drawPixel(x + xc, y - yc);
  drawPixel(x + yc, y - xc);
  break;

  case 1:
  drawPixel(x - xc, y - yc);
  drawPixel(x - yc, y - xc);
  break;

  case 2:
  drawPixel(x - xc, y + yc);
  drawPixel(x - yc, y + xc);
  break;

  case 3:
  drawPixel(x + xc, y + yc);
  drawPixel(x + yc, y + xc);
  break;

  default:
  break;
  }
  }
  */
}

void Lcd::fillCircle(uint16_t x, uint16_t y, uint16_t r) {
    drawVLine(x, y - r, 2 * r + 1);
    fillCircleHelper(x, y, r, 3, 0);
}

void Lcd::fillCircleHelper(uint16_t x, uint16_t y, uint16_t r, uint8_t cornername, uint16_t delta) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t xh = 0;
    int16_t yh = r;

    while (xh < yh) {
        if (f >= 0) {
            yh--;
            ddF_y += 2;
            f += ddF_y;
        }
        xh++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x1) {
            drawVLine(x + xh, y - yh, 2 * yh + 1 + delta);
            drawVLine(x + yh, y - xh, 2 * xh + 1 + delta);
        }
        if (cornername & 0x2) {
            drawVLine(x - xh, y - yh, 2 * yh + 1 + delta);
            drawVLine(x - yh, y - xh, 2 * xh + 1 + delta);
        }
    }
}

void Lcd::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    drawLine(x0, y0, x1, y1);
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x0, y0);
}

void Lcd::fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    int16_t a, b, y, last;

    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }
    if (y1 > y2) {
        swap(y2, y1);
        swap(x2, x1);
    }
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y0 == y2) {
        a = b = x0;
        if (x1 < a)
            a = x1;
        else if (x1 > b)
            b = x1;
        if (x2 < a)
            a = x2;
        else if (x2 > b)
            b = x2;
        drawHLine(a, y0, b - a + 1);
        return;
    }

    int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
    int32_t sa = 0, sb = 0;

    if (y1 == y2) {
        last = y1;
    } else {
        last = y1 - 1;
    }

    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if (a > b) swap(a, b);
        drawHLine(a, y, b - a + 1);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if (a > b) swap(a, b);
        drawHLine(a, y, b - a + 1);
    }
}

void Lcd::drawText(const char text[], uint16_t textLength, uint16_t x, uint16_t y) {
    uint16_t wText = textLength * (fontWidth + fontSpacing);
    uint16_t hText = fontHeight;
    uint16_t xPos;
    uint16_t yPos = y;
    // set start position
    switch (fontAlignment) {
        case LEFT:
            xPos = x;
            break;
        case CENTER:
            xPos = x - (wText / 2);
            break;
        case RIGHT:
            xPos = x - wText;
            break;
        default:
            xPos = x;
            break;
    }
    // draw Text
    mgxSetZone(xPos, yPos, wText, hText);
    // row --> letter --> column
    for (uint16_t row = 0; row < hText; row++) {
        for (uint16_t letter = 0; letter < textLength; letter++) {
            // draw letter
            for (uint16_t column = 0; column < fontWidth; column++) {
                uint16_t offset = (getLetter(text[letter]) * fontHeight) + row;
                bool pixel = (*(fontData + offset) >> (fontWidth - column - 1)) & 0x01;
                if (pixel) {
                    mgxPixelOut(CCONV(foreColor));
                } else {
                    mgxPixelOut(CCONV(backColor));
                }
            }
            // draw spacing
            for (uint8_t i = 0; i < fontSpacing; i++) {
                mgxPixelOut(CCONV(backColor));
            }
        }
    }
}

void Lcd::drawNumber(int32_t num, uint8_t numSize, uint16_t x, uint16_t y) {
    if ((numSize > 0) && (numSize <= 10)) {
        char numChar[numSize];
        switch (numSize) {
            case 1:
                sprintf(numChar, "%d", (int)num);
                break;

            case 2:
                sprintf(numChar, "%2d", (int)num);
                break;

            case 3:
                sprintf(numChar, "%3d", (int)num);
                break;

            case 4:
                sprintf(numChar, "%4d", (int)num);
                break;

            case 5:
                sprintf(numChar, "%5d", (int)num);
                break;

            case 6:
                sprintf(numChar, "%6d", (int)num);
                break;

            case 7:
                sprintf(numChar, "%7d", (int)num);
                break;

            case 8:
                sprintf(numChar, "%8d", (int)num);
                break;

            case 9:
                sprintf(numChar, "%9d", (int)num);
                break;

            case 10:
                sprintf(numChar, "%10d", (int)num);
                break;
        }
        drawText(numChar, numSize, x, y);
    }
}

void Lcd::clearHLine(uint16_t x, uint16_t y, uint16_t l) {
    mgsWorkingArea(x, y, l, 1);
    mgdFill(CCONV(backColor));
}

void Lcd::clearVLine(uint16_t x, uint16_t y, uint16_t l) {
    mgsWorkingArea(x, y, 1, l);
    mgdFill(CCONV(backColor));
}

void Lcd::clearRect(uint16_t x, uint16_t y, uint32_t w, uint32_t h) {
    mgsWorkingArea(x, y, w, h);
    mgdFill(CCONV(backColor));
}

void Lcd::drawRGB16Image(const RGB16Color* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // draw image
    mgxSetZone(x, y, w, h);
    for (uint32_t i = 0; i < (w * h); i++) {
        mgxPixelOut(CCONV(indexPtr[pixelPtr[i]]));
    }
}

void Lcd::drawRGB16Image(const RGB16Color* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, float alpha, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // create 16 bit color index
    RGB16Color indexRGB16[indexSize]; // TODO!!!!!!!!!!!! WWWWWTTTTTTFFFFF!!!!!!
    for (uint8_t i = 0; i < indexSize; i++) {
        indexRGB16[i] = alphaColor(indexPtr[i], alpha);
    }
    // draw image
    mgxSetZone(x, y, w, h);
    for (uint32_t j = 0; j < (w * h); j++) {
        mgxPixelOut(CCONV(indexRGB16[pixelPtr[j]]));
    }
}

void Lcd::drawRGB24Image(const RGB24RawColor* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // create 16 bit color index
    RGB16Color indexRGB16[indexSize];
    for (uint8_t i = 0; i < indexSize; i++) {
        indexRGB16[i] = convertColor(indexPtr[i]);
    }
    // draw image
    mgxSetZone(x, y, w, h);
    for (uint32_t j = 0; j < (w * h); j++) {
        mgxPixelOut(CCONV(indexRGB16[pixelPtr[j]]));
    }
}

void Lcd::drawRGB24Image(const RGB24RawColor* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, float alpha, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    // create 16 bit color index
    RGB16Color indexRGB16[indexSize];
    for (uint8_t i = 0; i < indexSize; i++) {
        indexRGB16[i] = alphaColor(indexPtr[i], alpha);
    }
    // draw image
    mgxSetZone(x, y, w, h);
    for (uint32_t j = 0; j < (w * h); j++) {
        mgxPixelOut(CCONV(indexRGB16[pixelPtr[j]]));
    }
}

void Lcd::fadeRGB16Image(const RGB16Color* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool mode, uint8_t step, uint16_t delay) {
    RGB16Color indexRGB16[indexSize];
    float alphaStep = 1.0f / step;
    float alpha;

    (mode) ? alpha = 0.0 : alpha = 1.0;

    for (uint8_t i = 0; i <= step; i++) {
        // generate index
        for (uint8_t j = 0; j < indexSize; j++) {
            indexRGB16[j] = alphaColor(indexPtr[j], alpha);
        }
        // draw image
        mgxSetZone(x, y, w, h);
        for (uint32_t k = 0; k < (w * h); k++) {
            mgxPixelOut(CCONV(indexRGB16[pixelPtr[k]]));
        }
        bspDelayMs(delay);
        (mode) ? alpha += alphaStep : alpha -= alphaStep;
    }
}

void Lcd::fadeRGB24Image(const RGB24RawColor* indexPtr, const uint8_t* pixelPtr, uint8_t indexSize, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool mode, uint8_t step, uint16_t delay) {
    RGB16Color indexRGB16[indexSize];
    float alphaStep = 1.0f / step;
    float alpha;

    (mode) ? alpha = 0.0 : alpha = 1.0;

    for (uint8_t i = 0; i <= step; i++) {
        // generate index
        for (uint8_t j = 0; j < indexSize; j++) {
            indexRGB16[j] = alphaColor(indexPtr[j], alpha);
        }
        // draw image
        mgxSetZone(x, y, w, h);
        for (uint32_t k = 0; k < (w * h); k++) {
            mgxPixelOut(CCONV(indexRGB16[pixelPtr[k]]));
        }
        bspDelayMs(delay);
        (mode) ? alpha += alphaStep : alpha -= alphaStep;
    }
}

void Lcd::drawInitSdAlert(SdResult sdResult) {
    uint16_t x;
    uint16_t y;
    RGB16Color indexRGB16[kSdIconIndexSize];

    // draw sdcard icon

    for (uint8_t i = 0; i < kSdIconIndexSize; i++) {
        uint16_t red = kSdIconIndex[i] >> 3;
        uint16_t green = kSdIconIndex[i] >> 2;
        uint16_t blue = kSdIconIndex[i] >> 3;
        indexRGB16[i] = (red << 11) | (green << 5) | (blue);
    }

    x = 388;
    y = 190;
    mgxSetZone(x, y, kSdIconWidth, kSdIconHeight);
    for (uint32_t j = 0; j < (kSdIconWidth * kSdIconHeight); j++) {
        mgxPixelOut(CCONV(indexRGB16[kSdIconData[j]]));
    }

    // draw sd card detail icon

    for (uint8_t i = 0; i < kSdDetailIconIndexSize; i++) {
        uint16_t red = kSdDetailIconIndex[i] >> 3;
        uint16_t green = kSdDetailIconIndex[i] >> 2;
        uint16_t blue = kSdDetailIconIndex[i] >> 3;
        indexRGB16[i] = (red << 11) | (green << 5) | (blue);
    }

    uint16_t offset;
    (sdResult != SD_ERROR_DETECT) ? offset = 0 : offset = 600;

    x += 27;
    y += 68;
    mgxSetZone(x, y, kSdDetailIconWidth, kSdDetailIconHeight);
    for (uint32_t j = 0; j < (kSdDetailIconWidth * kSdDetailIconHeight); j++) {
        mgxPixelOut(CCONV(indexRGB16[kSdDetailIconData[offset + j]]));
    }

    setForeColor(BLACK);
    fillRect(327, 390, 200, 20);

    setBackColor(BLACK);
    setForeColor(RED);

    // draw frame
    for (uint8_t i = 0; i < 32; i++) {
        uint16_t red = kCircleIndex[i] >> 3;
        uint16_t green = 0;  // kSdDetailIconIndex[i] >> 2;
        uint16_t blue = 0;   // kSdDetailIconIndex[i] >> 3;
        indexRGB16[i] = (red << 11) | (green << 5) | (blue);
    }

    x = 314;
    y = 382;
    mgxSetZone(x, y, 13, 25); // TODO: numbers
    for (uint32_t j = 0; j < (13 * 25); j++) {
        mgxPixelOut(CCONV(indexRGB16[kCircleLeftData[j]]));
    }

    x = 314 + 213;
    y = 382;
    mgxSetZone(x, y, 13, 25); // TODO: numbers
    for (uint32_t j = 0; j < (13 * 25); j++) {
        mgxPixelOut(CCONV(indexRGB16[kCircleRightData[j]]));
    }

    x = 327;
    drawHLine(x, y, 200);
    drawHLine(x, y + 24, 200);

    // draw text
    const char* alertPtr = NULL;

    switch (sdResult) {
        case SD_OK:
            break;

        case SD_ERROR:
            break;

        case SD_ERROR_DETECT:
            alertPtr = kSdAlertTextInsert;
            break;

        case SD_ERROR_MOUNT:
            alertPtr = kSdAlertTextFormat;
            break;

        case SD_ERROR_SERIAL:
            alertPtr = kSdAlertTextSerial;
            break;

        case SD_ERROR_SYSTEMFOLDER:
            alertPtr = kSdAlertTextSystemFolder;
            break;

        case SD_ERROR_WAVETABLEFOLDER:
            alertPtr = kSdAlertTextWavetableFolder;
            break;

        case SD_ERROR_SYSTEMFILE:
            alertPtr = kSdAlertTextSystemFile;
            break;
    }

    setAlignment(CENTER);
    setFont(FONT_07x09);
    drawText(alertPtr, strlen(alertPtr), 427, 390);
}

void Lcd::drawInitSdReadAlert() {
    setForeColor(RED);
    setBackColor(BLACK);
    setAlignment(CENTER);
    setFont(FONT_07x09);
    drawText("READING SDCARD", 15, 427, 390);
}

void Lcd::clearInitSdAlert() {
    setForeColor(BLACK);
    fillRect(307, 190, 240, 220);
    setForeColor(WHITE);
}
