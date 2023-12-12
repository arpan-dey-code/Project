#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD with the I2C address and the number of columns and rows
  lcd.begin();
  // Turn on the backlight (adjust the value if needed)
  lcd.setBacklight(HIGH);

  // Print a message to the LCD
  lcd.print("Hello, Arduino!");
}

void loop() {
  // Your loop code here
}
