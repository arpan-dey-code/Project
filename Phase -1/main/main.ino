#include <SPI.h>  
 #include <MFRC522.h>  
 #include <Wire.h>  
 #include <LiquidCrystal_I2C.h>  
 // Set the LCD address to 0x27 for a 16 chars and 2 line display  
 LiquidCrystal_I2C lcd(0x27, 16, 2);  
 #define SS_PIN 10  
 #define RST_PIN 9  
 #define LED_G 5 //define green LED pin  
 #define LED_R 4 //define red LED pin  
 #define BUZZER 2 //buzzer pin  
 MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.  
 void setup()  
 {  
  Serial.begin(9600);  // Initiate a serial communication  
  SPI.begin();   // Initiate SPI bus  
  mfrc522.PCD_Init();  // Initiate MFRC522  
  lcd.begin();  
  lcd.backlight(); // Turn on the blacklight and print a message.  
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_R, OUTPUT);  
  pinMode(BUZZER, OUTPUT);  
  noTone(BUZZER);  
 }  
 void loop()  
 {  
  // Look for new cards  
  if ( ! mfrc522.PICC_IsNewCardPresent())  
  {    
  lcd.setCursor(3,0);  
  lcd.print("SHOW YOUR");  
  lcd.setCursor(4,1);  
  lcd.print("ID CARD");  
  return;  
  }  
  else{  
    lcd.clear();  
  }  
  // Select one of the cards  
  if ( ! mfrc522.PICC_ReadCardSerial())  
  {  
   return;  
  }  
  //Show UID on serial monitor  
  Serial.print("UID tag :");  
  String content= "";  
  byte letter;  
  for (byte i = 0; i < mfrc522.uid.size; i++)  
  {  
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
    Serial.print(mfrc522.uid.uidByte[i], HEX);  
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  
  }  
  Serial.println();  
  content.toUpperCase();  
  if (content.substring(1) == "B8 0A 2A 12") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Master Tag Detected"); 
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");    
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else if (content.substring(1) == "62 CD 0F 51") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Dr. Misbah Shafi");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else if (content.substring(1) == "63 6A C2 15") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Arpan Dey");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }
  else if (content.substring(1) == "D3 A4 9E 15") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Manish Kumar");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }
  else if (content.substring(1) == "D3 86 9E 15") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Marut Kumar Yadav");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }
  else if (content.substring(1) == "73 43 B2 15") //change here the UID of the card/cards that you want to give access  
  {  
   lcd.print("Muktai Malekar");  
   lcd.setCursor(0,1);  
   lcd.print("PRESENT");  
   digitalWrite(LED_G, HIGH);  
   tone(BUZZER, 500);  
   delay(500);  
   noTone(BUZZER);  
   delay(0);  
   digitalWrite(LED_G, LOW);  
   lcd.clear();  
  }  
  else  {  
   lcd.print("UNAUTHORIZE");  
   lcd.setCursor(0,1);  
   lcd.print("ACCESS");    
   digitalWrite(LED_R, HIGH);  
   tone(BUZZER, 250);  
   delay(2000);  
   digitalWrite(LED_R, LOW);  
   noTone(BUZZER);  
   lcd.clear();  
  }  
 }
