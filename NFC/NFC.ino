#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define RESET_TIME 30000  // 2分钟

MFRC522 rfid(SS_PIN, RST_PIN);  // 创建MFRC522实例
byte nuidPICC[4];               // 存储卡片UID的数组
Servo myservo;                  // 创建舵机实例
unsigned long lastReset = 0;    // 记录上次重启的时间

void setup() {
  Serial.begin(9600);  // 初始化串口通信
  SPI.begin();         // 初始化SPI总线
  rfid.PCD_Init();     // 初始化RFID读卡器
  Wire.begin();        // 初始化I2C总线
  pinMode(5, OUTPUT);  // 设置引脚5为输出
  myservo.attach(8);   // 连接舵机到引脚8
  myservo.write(0);    // 将舵机归零位置
}

void loop() {
  if (millis() - lastReset >= RESET_TIME) {
    // 到达重启时间
    Serial.println("重启中...");
    delay(100);            // 等待一段时间以便输出串口信息
    setup();               // 重新初始化
    lastReset = millis();  // 更新上次重启时间
  }

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("16位UID: ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  rfid.PICC_HaltA();       // 使IC卡进入休眠状态
  rfid.PCD_StopCrypto1();  // 停止读卡模块加密

  if (nuidPICC[0] == 0x22 && nuidPICC[1] == 0xB3 && nuidPICC[2] == 0xA4 && nuidPICC[3] == 0x55) {
    myservo.write(180);  // 如果卡片匹配，则将舵机旋转到180度。
    //要添加自己的门禁卡请修改此处的 22 B3 A4 55即可，详细教程请看README.md或者百度
  }
  if (nuidPICC[0] == 0xAA && nuidPICC[1] == 0xAA && nuidPICC[2] == 0xAA && nuidPICC[3] == 0xAA) {
    myservo.write(180);  
  }
  if (nuidPICC[0] == 0xAA && nuidPICC[1] == 0xAA && nuidPICC[2] == 0xAA && nuidPICC[3] == 0xAA) {
    myservo.write(180);  
  }

  delay(2400);
  myservo.write(0);  // 延迟后将舵机归零位置
}
