#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <LiquidCrystal_I2C.h>
//-----------------------------------------
#define RST_PIN  D3
#define SS_PIN   D4
#define BUZZER   D8
//-----------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
MFRC522::StatusCode status;      
//-----------------------------------------
int blockNum = 2;  
byte bufferLen = 18;
byte readBlockData[18];
//-----------------------------------------
String card_holder_name;
const String sheet_url = "https://script.google.com/macros/s/AKfycby_zISYIb-S-PgGi9TFuYQub1shorSaGbjTMFZYBZealS7kHIx0JCAtP3pIJvkltpcaqg/exec?name=";
//-----------------------------------------
#define WIFI_SSID "Vivo"  
#define WIFI_PASSWORD "mani12359"  
//-----------------------------------------

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);  


/**********************************
 * setup() function
 **********************************/
void setup()
{
  //--------------------------------------------------
  Serial.begin(9600);
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  for (int a = 5; a <= 10; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  
  //--------------------------------------------------
  //WiFi Connectivity
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //--------------------------------------------------
  pinMode(BUZZER, OUTPUT);
  SPI.begin();
}




/**********************************
 * loop() function
 **********************************/
void loop()
{
  //--------------------------------------------------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Scan your Card ");
  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  /* Look for new cards */
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  //--------------------------------------------------
  Serial.println();
  Serial.println(F("Reading last data from RFID..."));
  ReadDataFromBlock(blockNum, readBlockData);

  //--------------------------------------------------
  Serial.print(F("Last data in RFID:"));
  Serial.print(blockNum);
  Serial.print(F(" --> "));
  for (int j=0 ; j<16 ; j++)
  {
    Serial.write(readBlockData[j]);
  }

  card_holder_name = String((char*)readBlockData);

  //--------------------------------------------------
  // Trim the card_holder_name
  card_holder_name.trim();
  if (card_holder_name.length() == 0) {
    // Card with no name
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Name Found");
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(500);
  } else {
    // Card with name
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hey " + card_holder_name + "!");
    
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);

    if (WiFi.status() == WL_CONNECTED) {
      std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
      client->setInsecure();
      
      // Construct the full URL with two parameters: name and node
      String node_name = "ISRO";
      String full_url = sheet_url + "?name=" + card_holder_name + "&node=" + node_name;
      
      Serial.println("Sending to URL: " + full_url);
      
      HTTPClient https;
      Serial.print(F("[HTTPS] begin...\n"));

      if (https.begin(*client, full_url)){
        Serial.print(F("[HTTPS] GET...\n"));
        int httpCode = https.GET();

        if (httpCode > 0) {
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
          lcd.setCursor(0, 1);
          lcd.print("Data Recorded");
          delay(2000);
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }

        https.end();
        delay(1000);
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
    }
  }
}



/**********************************
 * ReadDataFromBlock() function
 **********************************/
void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{ 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  
  if (status != MFRC522::STATUS_OK){
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  } else {
    Serial.println("Authentication success");
  }

  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Block was read successfully");  
  }
}
