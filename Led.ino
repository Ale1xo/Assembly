#define TRIGGER_PIN 25
#define ECHO_PIN 32
#define LED_PIN  33

unsigned long currentTime;
unsigned long startTime;
unsigned long currentTimeBlink;
unsigned long startTimeBlink;
int dist;
int dist2; 
double power;
double bright;
boolean blink;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  startTime = micros();
  startTimeBlink = micros();
  ledcAttachPin(LED_PIN, 0);//Atribuimos o pino 33 ao canal 0.
  ledcSetup(0, 1000, 8);//Atribuimos ao canal 0 a frequencia de 100Hz com resolucao de 8bits.
  digitalWrite(TRIGGER_PIN,HIGH);
}

void loop() {
  currentTime = micros();
  currentTimeBlink = micros();
  if (currentTime - startTime >= (1000000 / 15)) {
    digitalWrite(TRIGGER_PIN,LOW);// verificar se o trigger está a 0
    int dist = pulseIn(ECHO_PIN,HIGH) * 0.017; // 170*10^-6*10^2
    digitalWrite(TRIGGER_PIN,HIGH);
    dist2 = dist;
    if(dist >= 49){
      dist2 = 49;
    }
    if (dist <= 2) {
      dist = 0;
      dist2 = 0;
    }
    if (dist >= 400) {
      dist = 400;
    }
    if(dist >= 50 && dist <= 150){  
      power = 6000 * dist;
      ledcDetachPin(LED_PIN);
      if(currentTimeBlink - startTimeBlink >= (1000000-power)){
        blink = !blink;
        digitalWrite(LED_PIN,blink);
        startTimeBlink += (1000000-power);
      }
    }
    bright = (dist2*255) / 49;
    
    if(dist < 50 || dist > 150){
      ledcAttachPin(LED_PIN, 0);//Atribuimos o pino 33 ao canal 0.
      ledcWrite(0, bright);
    }
    Serial.print("Distancia: ");
    Serial.println(dist);
    startTime += (1000000 / 15);
  } 
}
