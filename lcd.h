LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcd_setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MQTT based");
  lcd.setCursor(0, 1);
  lcd.print("Air Quality");
  lcd.setCursor(0, 2);
  lcd.print("Monitoring");
  lcd.setCursor(0, 3);
  lcd.print("Powered By Shafira!");
  lcd.clear();
}

void lcd_print(float temp, float humi, float dust, float co) {
  //  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Skripsi Shafira");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.setCursor(10, 1);
  lcd.print("Humi:");
  lcd.print(humi);
  lcd.setCursor(0, 2);
  lcd.print("PM10:");
  lcd.print(dust);
  lcd.setCursor(10, 2);
  lcd.print("CO  :");
  lcd.print(co);
  lcd.setCursor(0, 3);
  lcd.print("        AMAN        ");
  //  lcd.clear();
}
