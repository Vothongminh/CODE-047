#include <PS2X_lib.h>
//https://www.youtube.com/channel/UCpzhReI3a9MZaFaS-nw4wDw?view_as=subscriber
/////////////////////////////////
#define PS2_DAT 7 // data     //
#define PS2_CMD 6 //command   //
#define PS2_SEL 4 // attention//
#define PS2_CLK 5 //clock     //  
/////////////////////////////////
int relay1 = 19;
int relay2 = 18;
int relay3 = 17;
int relay4 = 16;
int relay5 = 15;
int relay6 = 14;
int relay7 = 3;
int relay8 = 2;
int relay9 = 11;
int relay10 = 10;
int relay11 = 9;
int relay12 = 8;
//#define pressures   true
#define pressures false
//#define rumble      true
#define rumble false
int dem_L3;
#include <VirtualWire.h> // khai báo thư viện VirtualWire
byte msg[VW_MAX_MESSAGE_LEN];// biến lưu dữ liệu nhận được
byte msgLen = VW_MAX_MESSAGE_LEN;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);// uno Sda scl: a4, a5// mega2560: 21, 22
PS2X ps2x; // tạo PS2 điều khiển lớp
int error = 0;
byte type = 0;
byte vibrate = 0;
//Biến cho analog
int tempLY;
int tempLX;
int tempRY;
int tempRX;

void setup()
{
  Serial.begin(57600);
  lcd.begin();//Initializing display
  lcd.backlight();//To Power ON the back light
  pinMode(relay1 , OUTPUT);
  pinMode(relay2 , OUTPUT);
  pinMode(relay3 , OUTPUT);
  pinMode(relay4 , OUTPUT);
  pinMode(relay5 , OUTPUT);
  pinMode(relay6 , OUTPUT);
  pinMode(relay7 , OUTPUT);
  pinMode(relay8 , OUTPUT);
  pinMode(relay9 , OUTPUT);
  pinMode(relay10 , OUTPUT);
  pinMode(relay11 , OUTPUT);
  pinMode(relay12 , OUTPUT);
  //lcd.backlight();// To Power OFF the back light
  //delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.print("Đã tìm thấy bộ điều khiển ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Hãy thử tất cả các nút;");
    Serial.println("giữ L1 hoặc R1 sẽ in ra các giá trị analog.");
  }
  else if (error == 1)
    Serial.println("Không kết nối đc, thử lại...");

  else if (error == 2)
    Serial.println("Bộ điều khiển tìm thấy nhưng không chấp nhận lệnh");

  else if (error == 3)
    Serial.println("Bộ điều khiển từ chối để vào chế độ Pressures ");

  //  Serial.print(ps2x.Analog(1), HEX);
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Tay điều khiển không phù hợp ");
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("--Disconnected--");
      lcd.setCursor(0, 1);
      lcd.print("Please try again");
      break;
    case 1:
      Serial.print("Đã tìm thấy DualShock ");
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(" Try your best!");
      break;
    case 2:
      Serial.print("Đã tìm thấy GuitarHero ");
      break;
    case 3:
      Serial.print("Không dây của Sony DualShock điều khiển tìm thấy ");
      break;
  }
}

void loop()
{
  //Cho về 0 xét lại
  if (error == 1)
    return;

  if (type == 2) {
    ps2x.read_gamepad();
  }
  else {


set:
    ps2x.read_gamepad();
    lcd.setCursor(0, 0);
    lcd.print("  Connected :0)");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    digitalWrite(relay1 , HIGH);
    digitalWrite(relay2 , HIGH);
    digitalWrite(relay3 , HIGH);
    digitalWrite(relay4 , HIGH);
    digitalWrite(relay5 , HIGH);
    digitalWrite(relay6 , HIGH);
    digitalWrite(relay7 , HIGH);
    digitalWrite(relay8 , HIGH);
    digitalWrite(relay9 , HIGH);
    digitalWrite(relay10 , HIGH);
    digitalWrite(relay11 , HIGH);
    digitalWrite(relay12 , HIGH);
    /////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_CROSS) == HIGH)
    {
      Serial.println("PAD_CROSS");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_CROSS");
      digitalWrite(relay6 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_CROSS) == LOW)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////////

    while (ps2x.Button(PSB_TRIANGLE) == HIGH)
    {
      Serial.println("TRIANGLE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("TRIANGLE");
      digitalWrite(relay5 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_TRIANGLE) != HIGH)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_UP) == HIGH)
    {
      Serial.println("PAD_UP");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_UP");
      digitalWrite(relay1 , LOW);
      digitalWrite(relay3 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_UP) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_DOWN) == HIGH)
    {
      Serial.println("PAD_DOWN");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_DOWN");
      digitalWrite(relay2 , LOW);
      digitalWrite(relay4 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_DOWN) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_SQUARE) == HIGH )
    {
      Serial.println("SQUARE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("SQUARE");
      digitalWrite(relay8 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_SQUARE) != HIGH)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_CIRCLE) == HIGH )
    {
      Serial.println("CIRCLE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("CIRCLE");
      digitalWrite(relay7 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_CIRCLE) != HIGH)
      {
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_LEFT) == HIGH)
    {
      Serial.println("PAD_LEFT");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_LEFT");
      digitalWrite(relay3 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_LEFT) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_RIGHT) == HIGH)
    {
      Serial.println("PAD_RIGHT");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_RIGHT");
      digitalWrite(relay1 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_RIGHT) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_R1) == HIGH)
    {
      Serial.println("PSB_R1");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_R1");
      digitalWrite(relay9 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_R1) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_R2) == HIGH)
    {
      Serial.println("PSB_R2");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_R2");
      digitalWrite(relay10 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_R2) == LOW)
      {
        break;
        goto set;
      }
    }

    ///////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_L1) == HIGH)
    {
      Serial.println("PSB_L1");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_L1        ");
      digitalWrite(relay11 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_L1) != HIGH)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_L2) == HIGH)
    {
      Serial.println("PSB_L2");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_L2");
      digitalWrite(relay12 , LOW);
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_L2) == LOW)
      {
        break;
        goto set;
      }
    }
  }
}
