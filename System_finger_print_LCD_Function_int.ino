#include "U8glib.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <MsTimer2.h> 
/*通信协议*/
#define Voice 6
U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9); 
SoftwareSerial mySerial(A8, A9);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
extern int finger_sign=1;
extern char inByte='/';
extern int true_ID=1;
extern int true_face_ID=1;
extern int face_ID=1;
extern int voice_ID=1;
extern int input_going=1;
extern int output_going=1;
int data_Voice_Verify;
//void finger_enroll();
//void U8gliab_setup();
//void finger_print_setup();
//void getFingerprintIDez();
//void draw_Parcel();
//void draw_Input();
//void draw_Running(void);
//void draw_Verify(void);
//void U8gliab_setup(void);
//void U8gliab_setup(void);
//void U8gliab_setup(void);
//void U8gliab_setup(void);
//void U8gliab_setup(void);





void finger_print(void)
{
  digitalWrite(Voice, HIGH);
  Serial2.print("@PlayFlashText#021$");//***************************文字
  delay(2000);
  digitalWrite(Voice, LOW);
  finger_print_setup();
  finger_sign=2;
  while(finger_sign==2)
  {
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
  }
  Verify(1,1);
}

void finger_enroll(void)
{
  finger_sign=1;
  digitalWrite(Voice, HIGH);
   Serial2.print("@PlayFlashText#021$");//***************************文字
   delay(2000);
   digitalWrite(Voice, LOW);
   MsTimer2::set(9000, flash);        // 中断设置函数，每 500ms 进入一次中断
  MsTimer2::start();                //开始计时
  finger_enroll_setup();
  while(finger_sign==1)
  {
 //finger_sign=finger_sign+1;
  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  while ((!  getFingerprintEnroll())&&finger_sign==1);
  }
  MsTimer2::stop();
}


void flash()                        //中断处理函数，改变灯的状态
  
{                        
 if(finger_sign==1)
  finger_sign=2;
    digitalWrite(Voice, HIGH);
   Serial2.print("@PlayFlashText#015$");//***************************文字
   delay(2000);
   digitalWrite(Voice, LOW);
}



uint8_t readnumber(void) {
  uint8_t num = 0;
  
//  while (num == 0) {
//    while (! Serial.available());
//    num = Serial.parseInt();
//  }
//  return num;
return 3;
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  finger_sign=finger_sign+1;
  return finger.fingerID; 
}
void Verify(int a,int b)
{

   digitalWrite(Voice, HIGH);
     if(a==b)
   Serial2.print("@PlayFlashText#014$");//**************************
   else
   Serial2.print("@PlayFlashText#013$");//**************************
   delay(4000);
   digitalWrite(Voice, LOW);
}

void USART_Input(void)
{
   digitalWrite(Voice, HIGH);
   Serial2.print("@PlayFlashText#007$");
   delay(4000);
   digitalWrite(Voice, LOW);
   digitalWrite(LED_BUILTIN, LOW); 
  Serial1.write('a');
//  delay(2000);
    while(inByte!='b')
  {
    if (Serial1.available()) 
    {
        inByte = char(Serial1.read());
        digitalWrite(LED_BUILTIN, HIGH);
        //Serial1.write(inByte);
        if (inByte=='a')
        {
          face_ID=1;
        digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite(Voice, HIGH);
          Serial2.print("@PlayFlashText#008$");
          delay(4000);
          digitalWrite(Voice, LOW);
          inByte='/';
//          while(1)
//          {}
//        break;
        }
        if (inByte=='b')
        {
          face_ID=2;
        digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(Voice, HIGH);
          Serial2.print("@PlayFlashText#015$");
          delay(4000);
          digitalWrite(Voice, LOW);
        break;
        }
        else
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200); 
      }
   }
   Verify(face_ID,true_face_ID);
}


void USART_Running(void)
{  
 inByte='/';
  Serial1.write('b');
  delay(200); 
        digitalWrite(Voice, HIGH);
        Serial2.print("@PlayFlashText#009$");
        delay(2000);
        digitalWrite(Voice, LOW);
       while(inByte!='b')
  {
    if (Serial1.available()) 
    {
        inByte = Serial1.read();
        if (inByte=='b')
        {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(Voice, HIGH);
        Serial2.print("@PlayFlashText#0016$");
        delay(2000);
        digitalWrite(Voice, LOW);
        break;
        }
        else
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200); 
      }
   }
}


void USART_Verify(void)
{  
 inByte='/';
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial1.write('c');
       while(inByte!='a'||inByte!='b')
  {
    if (Serial1.available()) 
    {
        inByte = Serial1.read();
        if (inByte=='a')
        {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(Voice, HIGH);
        Serial2.print("@PlayFlashText#011$");
        delay(2000);
        digitalWrite(Voice, LOW);
        inByte='/';
        break;
        }
       if (inByte=='b')
        {
        digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(Voice, HIGH);
          Serial2.print("@PlayFlashText#012$");
          delay(2000);
          digitalWrite(Voice, LOW);
        break;
        }
        else
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200); 
      }
   }
}



void U8gliab_setup()
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
    u8g.setColorIndex(255);     // white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    u8g.setColorIndex(3);         // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    u8g.setColorIndex(1);         // pixel on

  // u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(3); 
  Serial.begin(9600);
  u8g.setFont(u8g_font_6x10);//u8g_font_6x10   u8g_font_osb18
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

//************************************************DRAW
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Nice to meet you");
  u8g.drawHLine(0, 1+34, 40);
  u8g.setScale2x2();          // Scale up all draw procedures
  u8g.drawStr(0, 12, "Parcel");      // actual display position is (0,24)
  u8g.drawHLine(0, 12+14, 40);    // All other procedures are also affected
  u8g.undoScale();          // IMPORTANT: Switch back to normal mode
}

void finger_enroll_setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}




void finger_print_setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}




uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  digitalWrite(Voice, HIGH);
  Serial2.print("@PlayFlashText#005$");//***************************文字
  delay(2000);
  digitalWrite(Voice, LOW);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
      digitalWrite(Voice, HIGH);
  Serial2.print("@PlayFlashText#015$");//***************************文字
  delay(2000);
  finger_sign=2;
  digitalWrite(Voice, LOW);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  finger_sign=finger_sign+1;
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #


void draw_Parcel(void)
{
    //整段用于OLED
  uint8_t h;
  u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Nice to meet you");
  u8g.setScale2x2();          // Scale up all draw procedures
  u8g.drawStr(0, 12, "Parcel");      // actual display position is (0,24)
  u8g.drawHLine(0, 12+14, 50);    // All other procedures are also affected
  u8g.undoScale();          // IMPORTANT: Switch back to normal mode
  } while(u8g.nextPage());
  delay(100);
}

void draw_Input(void)
{
    //整段用于OLED
  uint8_t h;
  u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Nice to meet you");
  u8g.setScale2x2();          // Scale up all draw procedures
  u8g.drawStr(0, 12, "Input");      // actual display position is (0,24)
  u8g.drawHLine(0, 12+14, 40);    // All other procedures are also affected
  u8g.undoScale();          // IMPORTANT: Switch back to normal mode
  } while(u8g.nextPage());
  delay(100);
}

void draw_Running(void)
{
    //整段用于OLED
  uint8_t h;
  u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Nice to meet you");
  u8g.setScale2x2();          // Scale up all draw procedures
  u8g.drawStr(0, 12, "Running");      // actual display position is (0,24)
  u8g.drawHLine(0, 12+14, 55);    // All other procedures are also affected
  u8g.undoScale();          // IMPORTANT: Switch back to normal mode
  } while(u8g.nextPage());
  delay(100);
}


void draw_Verify(void)
{
    //整段用于OLED
  uint8_t h;
  u8g.firstPage();  
  do {
      u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.drawStr(0, 1, "Nice to meet you");
  //u8g.drawHLine(0, 1+34, 40);
  u8g.setScale2x2();          // Scale up all draw procedures
  u8g.drawStr(0, 12, "Verify");      // actual display position is (0,24)
  u8g.drawHLine(0, 12+14, 50);    // All other procedures are also affected
  u8g.undoScale();          // IMPORTANT: Switch back to normal mode
  } while(u8g.nextPage());
  delay(100);
}


void setup()
{
  Serial.begin(9600);//指纹模块
  Serial1.begin(9600);//视觉
  Serial2.begin(9600);//语音模块
  Serial3.begin(9600);//蓝牙
 U8gliab_setup();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Voice, OUTPUT);
  digitalWrite(Voice, LOW);
  delay(100);
}

void loop()                     // run over and over again
{
  while (Serial3.available())
  {
    char data = Serial3.read();
    Serial3.println(data);
    if (data == '0')//启动
    {
        draw_Parcel();
        delay(100);
        digitalWrite(Voice, HIGH);
        Serial2.print("@PlayFlashText#018$");//***************************文字
        delay(4000);
        Serial2.print("@PlayFlashText#019$");//***************************文字
        delay(4000);
        digitalWrite(Voice, LOW);
    }
    else if (data == '1')//指纹输入信息
    {
        draw_Input();
        delay(100);
        finger_enroll();
    }

    else if (data == '3')//面部输入信息
    {
      USART_Input();
    }
    else if (data == '4')//巡线
    {
       draw_Running();
       delay(100);
      USART_Running();
      draw_Verify();
    }
    else if (data == '5')//人脸识别
    {
       USART_Verify();//人脸识别
    }
    
    else if (data == '6')//指纹检测
    {
       finger_print();
    } 
        else if (data == '7')//验证
    {
          digitalWrite(Voice, HIGH);
          Serial2.print("@PlayFlashText#010$");//***************************文字
          delay(2500);
          digitalWrite(Voice, LOW);
          input_going=1;
          while(input_going)
          {
                 while (Serial2.available())
                {
                      Serial.write('a');
                       data_Voice_Verify = Serial2.read();
                       Serial.write(data_Voice_Verify);
                      if (data_Voice_Verify == 1)
                      {
                        true_ID=1;
                       digitalWrite(Voice, HIGH);
                       Serial2.print("@PlayFlashText#001$");//***************************文字
                       delay(2000);
                       Serial2.print("@PlayFlashText#011$");//***************************文字
                       delay(3500);
                       digitalWrite(Voice, LOW);
                        input_going=0;
                        break;
                      }
                       else if (data_Voice_Verify == 2)
                      {
                        true_ID=2;
                       digitalWrite(Voice, HIGH);
                       Serial2.print("@PlayFlashText#001$");//***************************文字
                       delay(2000);
                       Serial2.print("@PlayFlashText#012$");//***************************文字
                       delay(3500);
                       digitalWrite(Voice, LOW);
                        input_going=0;
                        break;
                      }
                 }
          }
    }   
    else if (data == '8')//验证
    {
          digitalWrite(Voice, HIGH);
          Serial2.print("@PlayFlashText#020$");//***************************文字
          delay(3000);
          digitalWrite(Voice, LOW);
          output_going=1;
          while(output_going)
          {
               while (Serial2.available())
              {
                     data_Voice_Verify = Serial2.read();
                    if (data_Voice_Verify == 3)
                    {
                      voice_ID=1;
                       digitalWrite(Voice, HIGH);
                       Serial2.print("@PlayFlashText#003$");//***************************文字
                       delay(2000);
                       Serial2.print("@PlayFlashText#011$");//***************************文字
                       delay(3500);
                       digitalWrite(Voice, LOW);
                      output_going=0;
                      Verify(voice_ID,true_ID);
                      break;
    
                    }
                     else if (data_Voice_Verify == 4)
                    {
                      voice_ID=2;
                       digitalWrite(Voice, HIGH);
                       Serial2.print("@PlayFlashText#004$");//***************************文字
                       delay(2000);
                       Serial2.print("@PlayFlashText#012$");//***************************文字
                       delay(3500);
                       digitalWrite(Voice, LOW);
                      output_going=0;
                      Verify(voice_ID,true_ID);
                      break;
                    }
               }
          }
    }
      else if (data == '9')//致谢
    {
         digitalWrite(Voice, HIGH);
         Serial2.print("@PlayFlashText#011$");//***************************文字
         delay(3500);
         digitalWrite(Voice, LOW);
    }
    else {}
  }
}
