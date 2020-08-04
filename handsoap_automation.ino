const int trigger_pin = 8;
const int echo_pin = 9;

const int dig1 = 1;
const int dig2 = 2;
const int dig3 = 3;
const int dig4 = 4;

const int a = 12;
const int b = 10;
const int c = 8;
const int d = 6;
const int e = 5;
const int f = 11;
const int g = 9;
const int dp = 7;


#define TRIGDIST 5

/*
 * echo module
 * https://www.petitmonte.com/robot/howto_distance_measurement_2.html
 * servo motor
 * https://kokensha.xyz/arduino/arduino-control-servo-speed-with-varspeedservo/
 * 7 segment led
 * https://www.petitmonte.com/robot/howto_osl40562.html
 * Sugoku sankouni narisou
 * https://www.sys-link.jp/it/electronic-kit/arduino/arduino-011/
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  pinMode(pin7segA, OUTPUT); 
  pinMode(pin7segB, OUTPUT); 
  pinMode(pin7segC, OUTPUT); 
  pinMode(pin7segD, OUTPUT); 
  pinMode(pin7segE, OUTPUT); 
  pinMode(pin7segF, OUTPUT); 
  pinMode(pin7segG, OUTPUT); 
  pinMode(pin7segDig1, OUTPUT); 
  pinMode(pin7segDig2, OUTPUT); 
  pinMode(pin7segDig3, OUTPUT); 
  pinMode(pin7segDig4, OUTPUT); 
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
