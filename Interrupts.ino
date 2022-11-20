#define TRIGGER_PIN 25
#define ECHO_PIN 32

unsigned long startTime;
hw_timer_t * timer_n = NULL; 
unsigned long currentTime;
int count;
bool turn; // Activar ou Desativar o trigger (Low,High)
bool state; // Estado do ECHO_PIN 
unsigned long startTimeEcho;
unsigned long currentTimeEcho;
unsigned long startTimeDist;
unsigned long currentTimeDist;
// volatile é usado para variaveis que são chamadas fora das funções interrupt
volatile unsigned long dist;
volatile unsigned long waveTime;

void IRAM_ATTR triggerFunction(){ //  Emitir o sinal Trigger 
  digitalWrite(TRIGGER_PIN,turn);
  turn = !turn;
}

void IRAM_ATTR echoFunction(){ // Receber o sinal da onda (medir o tempo)
  state = digitalRead(ECHO_PIN);
  if(state == HIGH){
    startTimeEcho = micros();
  }else{
    currentTimeEcho = micros();
    waveTime = currentTimeEcho - startTimeEcho ;
  }
  
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  startTime = millis();
  startTimeDist = micros();
  timer_n = timerBegin(0,80,true);
  timerAttachInterrupt(timer_n,triggerFunction,true);
  timerAlarmWrite(timer_n,(1000000/15),true);
  timerAlarmEnable(timer_n);
  attachInterrupt(ECHO_PIN,echoFunction,CHANGE);
}

void loop() {
  currentTime = millis();
  currentTimeDist = micros();
  count++;
  
  if(currentTimeDist - startTimeDist >= (1000000/15)){
    dist = waveTime * 0.017;
    Serial.print("Distância: ");
    Serial.println(dist);
    startTimeDist += (1000000/15);
  }
  if(currentTime - startTime >= 1000){
    Serial.print("Número de loops: ");
    Serial.println(count);
    count = 0;
    startTime += 1000;
    
  }
}
