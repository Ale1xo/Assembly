#define TRIGGER_PIN 25
#define ECHO_PIN 32

unsigned long startTime;
unsigned long currentTime;
unsigned long startTimeSonar;
unsigned long currentTimeSonar;
int count = 0;
int dist;


void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  startTime = millis();
  startTimeSonar = micros();
  digitalWrite(TRIGGER_PIN,HIGH);// verificar se o trigger está a 0
}

void loop() {
  currentTimeSonar = micros();  
  currentTime = millis();
  count ++;

  if(currentTimeSonar - startTimeSonar >= (1000000/15)){
    digitalWrite(TRIGGER_PIN,LOW);// verificar se o trigger está a 0
    int dist = pulseIn(ECHO_PIN,HIGH) * 0.017; // 170*10^-6*10^2
    digitalWrite(TRIGGER_PIN,HIGH);
    if(dist < 3){
      dist = 0;
     }
    if(dist > 399){
      dist = 400;
    }
    Serial.print("Distância: ");
    Serial.println(dist);
    startTimeSonar += (1000000/15);
  }
  if(currentTime - startTime >= 1000){
    Serial.print("Número de loops: ");
    Serial.println(count);
    count = 0;
    startTime += 1000;
  }
}
