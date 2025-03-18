#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define RESET_TIME 120000  // 2分钟
#define SERVO_OPEN_ANGLE 180
#define SERVO_CLOSED_ANGLE 0
#define SERVO_HOLD_TIME 2400  // 舵机保持打开状态的时间

MFRC522 rfid(SS_PIN, RST_PIN);  // 创建MFRC522实例
byte nuidPICC[4];               // 存储卡片UID的数组
Servo myservo;                  // 创建舵机实例

unsigned long lastReset = 0;     // 记录上次重启的时间
unsigned long lastAccessTime = 0; // 记录上次开门时间
bool doorOpen = false;           // 记录门是否已打开

void setup() {
  Serial.begin(9600);  // 初始化串口通信
  SPI.begin();         // 初始化SPI总线
  rfid.PCD_Init();     // 初始化RFID读卡器
  Wire.begin();        // 初始化I2C总线
  pinMode(5, OUTPUT);  // 设置引脚5为输出
  myservo.attach(8);   // 连接舵机到引脚8
  myservo.write(SERVO_CLOSED_ANGLE);  // 关闭舵机
  lastReset = millis();  // 记录启动时间
  Serial.println("系统启动完成，等待刷卡...");
}

void loop() {
  if (millis() - lastReset >= RESET_TIME) {
    Serial.println("重新初始化RFID...");
    rfid.PCD_Init(); 
    lastReset = millis();
  }

  // 舵机定时复位
  if (doorOpen && millis() - lastAccessTime >= SERVO_HOLD_TIME) {
    myservo.write(SERVO_CLOSED_ANGLE); // 关闭舵机
    Serial.println("门已关闭");
    doorOpen = false;
  }

  // 检测是否有新卡片
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  // 打印卡片 UID
  Serial.print("检测到卡片 UID: ");
  for (byte i = 0; i < 4; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // 存储卡号
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  rfid.PICC_HaltA();       // 让IC卡进入休眠状态
  rfid.PCD_StopCrypto1();  // 停止读卡模块加密

  // 检查是否为授权卡
  if (isAuthorized(nuidPICC)) {
    if (!doorOpen) { 
      myservo.write(SERVO_OPEN_ANGLE);
      Serial.println("门已打开");
      doorOpen = true;
      lastAccessTime = millis();
    }
  } else {
    Serial.println("未授权卡片\n");
  }
}

// 检查是否为授权卡
bool isAuthorized(byte *cardID) {
  byte authorizedCards[][4] = {
    {0x11, 0x11, 0x11, 0x11}, // 第一张授权卡
    {0x11, 0x11, 0x11, 0x11}, // 第二张授权卡
  //以此类推添加UID
  };

  for (byte i = 0; i < sizeof(authorizedCards) / sizeof(authorizedCards[0]); i++) {
    if (memcmp(cardID, authorizedCards[i], 4) == 0) {
      Serial.println("已授权");
      return true;
    }
  }
  return false;
}
