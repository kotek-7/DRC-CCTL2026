#include "main.h"
#include "lcd_aqm1602.h"

namespace {
Aqm1602 lcd(&hi2c3);
}

extern "C" void setup(void) {
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DRC-CCTL2026");
  lcd.setCursor(0, 1);
  lcd.print("LCD example");
}

extern "C" void loop(void) {}
