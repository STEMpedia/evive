#ifndef SCREEN_H
#define SCREEN_H

#include "evive.h"

extern Adafruit_ST7735 lcd;

void lcd_init();
void lcd_update();

char* itostr2(const uint8_t& x);
char* itostr31(const int& xx);
char* itostr3(const int& xx);
char* itostr3left(const int& xx);
char* itostr4(const int& xx);
char* itostr4sign(const int& x);

char* ftostr3(const float& x);
char* ftostr4sign(const float& x);
char* ftostr31ns(const float& x); // float to string without sign character
char* ftostr31(const float& x);
char* ftostr32(const float& x);
char* ftostr43(const float& x);
char* ftostr12ns(const float& x);
char* ftostr32sp(const float& x); // remove zero-padding from ftostr32
char* ftostr5(const float& x);
char* ftostr51(const float& x);
char* ftostr52(const float& x);

#endif
