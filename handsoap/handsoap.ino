int trigger_pin = 8;
int echo_pin = 9;

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
