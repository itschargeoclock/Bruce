#include "display.h"
#include "core/wifi/webInterface.h" // for server
#include "core/wifi/wg.h"           //for isConnectedWireguard to print wireguard lock
#include "mykeyboard.h"
#include "settings.h" //for timeStr
#include "utils.h"
#include <JPEGDecoder.h>
#include <interface.h> //for charging ischarging to print charging indicator
#include <memory>

#define MAX_MENU_SIZE (int)(tftHeight / 25)

// Send the ST7789 into or out of sleep mode
void panelSleep(bool on) {
#if defined(ST7789_2_DRIVER) || defined(ST7789_DRIVER)
    if (on) {
        tft.writecommand(0x10); // SLPIN: panel off
        delay(5);
    } else {
        tft.writecommand(0x11); // SLPOUT: panel on
        delay(120);
    }
#endif
    // Disables tft writings on the display
    tft.setSleepMode(on);
}

bool __attribute__((weak)) isCharging() { return false; }

// FIX: PNGdec 1.1.6 requires int return type
int PNGDraw(PNGDRAW *pDraw) {
    uint16_t usPixels[MAX_IMAGE_WIDTH];
    png->getLine(pDraw, usPixels);
    tft.pushImage(_x, _y + pDraw->y, pDraw->iWidth, 1, usPixels);
    return 1;
}

bool drawPNG(FS fs, String filename, int x, int y, bool center) {
    _fs = &fs;
    _x = x;
    _y = y;
    int16_t rc;
    png = new PNG();
    rc = png->open(filename.c_str(), myOpen, myClose, myRead, mySeek, PNGDraw);
    if (rc == PNG_SUCCESS) {
        tft.setSwapBytes(true);
        if (center) {
            _x = x + (tftWidth - png->getWidth()) / 2;
            _y = y + (tftHeight - png->getHeight()) / 2;
        }
        rc = png->decode(NULL, 0);
        png->close();
        tft.setSwapBytes(false);
    }
    delete png;
    return (rc == PNG_SUCCESS);
}

void drawSubmenu(int index, std::vector<Option> &options, const char *title) {
    drawStatusBar();
    int menuSize = options.size();
    tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
    tft.setTextSize(FP);
    tft.drawPixel(0, 0, 0);
    tft.fillRect(6, 30, tftWidth - 12, 8 * FP, bruceConfig.bgColor);
    tft.drawString(title, 12, 30);

    int middle = 25 + (tftHeight - 30) / 2;
    int middle_up = middle - (tftHeight - 42) / 3 - FM * LH / 2 + 4;
    int middle_down = middle + (tftHeight - 42) / 3 - FM * LH / 2;

    const char *firstOption =
        index - 1 >= 0 ? options[index - 1].label.c_str() : options[menuSize - 1].label.c_str();
    tft.setTextSize(FM);
    tft.setTextColor(bruceConfig.secColor);
    tft.fillRect(6, middle_up, tftWidth - 12, 8 * FM, bruceConfig.bgColor);
    tft.drawCentreString(firstOption, tftWidth / 2, middle_up, 1);

    int selectedTextSize = options[index].label.length() <= tftWidth / (LW * FG) - 1 ? FG : FM;
    tft.setTextSize(selectedTextSize);
    tft.setTextColor(bruceConfig.priColor);
    tft.fillRect(6, middle - FG * LH / 2 - 1, tftWidth - 12, FG * LH + 5, bruceConfig.bgColor);
    tft.drawCentreString(options[index].label, tftWidth / 2, middle - selectedTextSize * LH / 2, 1);
    tft.drawFastHLine(
        tftWidth / 2 - strlen(options[index].label.c_str()) * selectedTextSize * LW / 2,
        middle + selectedTextSize * LH / 2 + 1,
        strlen(options[index].label.c_str()) * selectedTextSize * LW,
        bruceConfig.priColor
    );

    const char *thirdOption =
        index + 1 < menuSize ? options[index + 1].label.c_str() : options[0].label.c_str();
    tft.setTextSize(FM);
    tft.setTextColor(bruceConfig.secColor);
    tft.fillRect(6, middle_down, tftWidth - 12, 8 * FM, bruceConfig.bgColor);
    tft.drawCentreString(thirdOption, tftWidth / 2, middle_down, 1);
    tft.fillRect(tftWidth - 5, 0, 5, tftHeight, bruceConfig.bgColor);
    tft.fillRect(tftWidth - 5, index * tftHeight / menuSize, 5, tftHeight / menuSize, bruceConfig.priColor);
}

void printFootnote(String text) {
    tft.setTextSize(FP);
    tft.drawRightString(text, tftWidth - BORDER_PAD_X, tftHeight - BORDER_PAD_X - FP * LH, 1);
}

void printCenterFootnote(String text) {
    tft.fillRect(10, tftHeight - BORDER_PAD_X - FP * LH, tftWidth - 20, FP * LH, bruceConfig.bgColor);
    tft.setTextSize(FP);
    tft.drawCentreString(text, tftWidth / 2, tftHeight - BORDER_PAD_X - FP * LH, 1);
}
