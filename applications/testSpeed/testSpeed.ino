#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int ps = 4; // delay for pause
long cnt; 	// 

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(en2, INPUT);
  pinMode(en3, INPUT);
  //digitalWrite(ENA, HIGH);
  digitalWrite(ENA, LOW);
  digitalWrite(DIR, HIGH);
  //digitalWrite(DIR, LOW);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PUL, HIGH);
  delay(ps);
  digitalWrite(PUL, LOW);
  delay(ps);
}

bool timing(){
  
}