#define in 23
#define led 2
long now;
long lastTrigger = 0;
volatile byte state = HIGH;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(in, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(in), ledchange, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, state);
  Serial.println(digitalRead(in));
  delay(200);
}

void ledchange(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if(interrupt_time - last_interrupt_time > 200){
    state = !state;
    Serial.println("interupt");
    
  }
  last_interrupt_time = interrupt_time;
}
