#include "display.h"
#include "core/wifi/webInterface.h" // for server
#include "core/wifi/wg.h"           //for isConnectedWireguard to print wireguard lock
#include "mykeyboard.h"
#include "settings.h" //for timeStr
#include "utils.h"
#include <JPEGDecoder.h>
#include <interface.h> //for charging ischarging to print charging indicator

#define MAX_MENU_SIZE (int)(tftHeight / 25)

bool __attribute__((weak)) isCharging() { return false; }

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
    tft.setTextColor(buceConfig.priColor, bruceConfig.bgColor);
    tft.setTextSize(FP);
    tft.drawPixel(0, 0, 0);
    tft.fillRect(6, 30, tftWidth - 1‹
ˆ”œXÙPÛÛ™šYË˜™ĞÛÛÜ¢“°¢FgBæG&u7G&–ær‡F—FÆRÂ"Â3“° ¢–çBÖ–FFÆRÒ#R²‡FgD†V–v‡BÒ3’ò#°¢–çBÖ–FFÆU÷WÒÖ–FFÆRÒ‡FgD†V–v‡BÒC"’ò2ÒdÒ¢Ä‚ò"²C°¢–çBÖ–FFÆUöF÷vâÒÖ–FFÆR²‡FgD†V–v‡BÒC"’ò2ÒdÒ¢Ä‚ò#° ¢6öç7B6†"¦f—'7D÷F–öâĞ¢–æFW‚ÒãÒò÷F–öç5¶–æFW‚ÒÒæÆ&VÂæ5÷7G"‚’¢÷F–öç5¶ÖVçU6—¦RÒÒæÆ&VÂæ5÷7G"‚“°¢FgBç6WEFW‡E6—¦R„dÒ“°¢FgBç6WEFW‡D6öÆ÷"†''V6T6öæf–rç6V46öÆ÷"“°¢FgBæf–ÆÅ&V7BƒbÂÖ–FFÆU÷WÂFgEv–GF‚Ò"Â‚¢dÒÂ''V6T6öæf–ræ&t6öÆ÷"“°¢FgBæG&t6VçG&U7G&–ær†f—'7Q?F–öâÂFgEv–GF‚ò"ÂÖ–FFÆU÷WÂ“° ¢–çB6VÆV7FVEFW‡E6—¦RÒ÷F–öç5¶–æFW…ÒæÆ&VÂæÆVæwF‚‚’ÃÒFgEv–GF‚ò„År¢dr’Òòdr¢dÓ°¢FgBç6WEFW‡E6—¦R‡6VÆV7FVEFW‡E6—¦R“°¢FgBç6WEFW‡D6öÆ÷"†''V6T6öæf–rç&”6öÆ÷"“°¢FgBæf–ÆÅ&V7BƒbÂÖ–FFÆRÒdr¢Ä‚ò"ÒÂFgEv–GF‚Ò"Âdr¢Ä‚²RÂ''V6T6öæf–ræ&t6öÆ÷"“°¢FgBæG&t6VçG&U7G&–ær†÷F–öç5¶–æFW…ÒæÆ&VÂÂFgEv–GF‚ò"ÂÖ–FFÆRÒ6VÆV7FVEFW‡E6—¦R¢Ä‚ò"Â“°¢FgBæG&tf7D„Æ–æR€¢FgEv–GF‚ò"Ò7G&ÆVâ†÷F–öç5¶–æFW…ÒæÆ&VÂæ5÷7G"‚’’¢6VÆV7FVEFW‡E6—¦R¢Årò"À¢Ö–FFÆR²6VÆV7FVEFW‡E6—¦R¢Ä‚ò"²À¢7G&ÆVâ†÷F–öç5¶–æFW…ÒæÆ&VÂæ5÷7G"‚’’¢6VÆV7FVEFW‡E6—¦R¢ÅrÀ¢''V6T6öæf–rç&”6öÆ÷ ¢“° ¢6ööç7B6†"§F†—&D÷F–öâĞ¢–æFW‚²ÂÖVçU6—¦Rò÷F–öç5¶–æFW‚²ÒæÆ&VÂæ5÷7G"‚’¢÷F–öç5³ÒæÆ&VÂæ5÷7G"‚“°¢FgBç6WEFW‡E6—¦R„dÒ“°¢FgBç6WEFW‡D6öÆ÷"†''V6T6öæf–rç6V46öÆ÷"ŠNÂˆ™š[™Xİ
‹ZYWÙİÛ‹ÚYHL‹
ˆ“KœXÙPÛÛ™šYË˜™ĞÛÛÜŠNÂˆ™˜]ĞÙ[™Tİš[™Ê\™Ü[Û‹ÚYÈ‹ZYWÙİÛ‹JNÂˆ™š[™Xİ
ÚYHKKZYÚœXÙPÛÛ™šYË˜™ĞÛÛÜŠNÂˆ™š[™Xİ
ÚYHK[™^
ˆZYÚÈY[TÚ^™KKZYÚÈY[TÚ^™KœXÙPÛÛ™šYËœšPÛÛÜŠNÂŸB‚›ÚYš[›Ûİ›İJİš[™È^
HÂˆœÙ]^Ú^™J”
NÂˆ™˜]ÔšYÚİš[™Ê^ÚYH“Ô‘T—ÔQÖZYÚH“Ô‘T—ÔQÖH”
ˆJNÂŸB‚›ÚYš[Ù[\‘›Ûİ›İJİš[™È^
HÂˆ™š[™Xİ
LZYÚH“Ô‘T—ÔQÖH”
ˆ tftWidth - 20, FP, * LH, bruceConfig.bgColor);
    tft.setTextSize(FP);
    tft.drawCentreString(text, tftWidth / 2, tftHeight - BORDER_PAD_X - FP, * LH, 1);
}
