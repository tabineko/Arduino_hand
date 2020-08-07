#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW
#define TRIGDIST 5

const int trigger_pin = 1;
const int echo_pin = 4;

const int digitPins[] = {7, 9, 10, 13};                                        // ディジット(コモン)に接続するArduinoのピン
const int segmentPins[] = {12, 8, 5, 3, 2, 11, 6};                             // セグメントピンに接続するArduinoのピン
const int numberOfDigitPins = sizeof(digitPins) / sizeof(digitPins[0]);        // ディジットの数
const int numberOfSegmentPins = sizeof(segmentPins) / sizeof(segmentPins[0]);  // セグメントの数

// 数字と表示させるセグメントの関係
const int digits[] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00100111,  // 7
    0b01111111,  // 8
    0b01101111,  // 9
};

/*
 * echo module
 * https://www.petitmonte.com/robot/howto_distance_measurement_2.html
 * servo motor
 * https://kokensha.xyz/arduino/arduino-control-servo-speed-with-varspeedservo/
 * 7 segment led
 * https://www.petitmonte.com/robot/howto_osl40562.html
 * https://garretlab.web.fc2.com/arduino/introduction/beginning_with_7segment_led/
 * Sugoku sankouni narisou
 * https://www.sys-link.jp/it/electronic-kit/arduino/arduino-011/
 */

void displayNumber(int n) {
  // digits[n]の各ビットを調べて対応するセグメントを点灯・消灯する
  for (int i = 0; i < numberOfSegmentPins; i++) {
    digitalWrite(segmentPins[i], digits[n] & (1 << i) ? SEGMENT_ON : SEGMENT_OFF);
  }
}

// セグメントをすべてオフにする
void clearSegments() {
  for (int j = 0; j < numberOfSegmentPins; j++) {
    digitalWrite(segmentPins[j], SEGMENT_OFF);
  }
}

// 4桁の数字を表示する
void displayNumbers(int n) {
  for (int i = 0; i < numberOfDigitPins; i++) {  // 右の桁からディジットを選択する
    digitalWrite(digitPins[i], DIGIT_ON);        // ディジットをオンにする
    displayNumber(n % 10);                       // 10で割った余りを求めて、1の位を求め、表示する
    delay(1);
    clearSegments();                        // セグメントをすべてオフにする
    digitalWrite(digitPins[i], DIGIT_OFF);  // ディジットをオフにする
    n /= 10;                                // 10で割り、次に表示する数字を、1の位に移す
  }
}

// setup()　は，最初に一度だけ実行される
void setup() {
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  for (int i = 0; i < numberOfDigitPins; i++) {
    pinMode(digitPins[i], OUTPUT);  // digitPinsを出力モードに設定する
    digitalWrite(digitPins[i], DIGIT_OFF);
  }
  for (int i = 0; i < numberOfSegmentPins; i++) {
    pinMode(segmentPins[i], OUTPUT);  // segmentPinsを出力モードに設定する
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // [超音波の発射]
  // ※トリガーとなるHIGH時間は「10us ～ 60ms」まで
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(18);
  digitalWrite(trigger_pin, LOW);

  // [距離の取得]
  // ※echoピンに入力されるパルスの長さを検出する(HIGH時間の取得/μ秒)
  int duration = pulseIn(echo_pin, HIGH);
  if (duration > 0) {
    // 距離(cm) = ECHOのHIGH時間 x 超音波速度(0.034cm/μ秒) / 2
    float distance = (duration * 0.034) / 2;
    Serial.print(distance);
    Serial.println("cm");
  }

  if (distance > 0 && distance < TRIGDIST) {
    
  } 
  
  delay(200);
}
