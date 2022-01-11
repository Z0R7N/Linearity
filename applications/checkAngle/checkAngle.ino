#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int ps = 100; 			// delay for pause (50 minimum & 1000 maximum)
int acc = 5;			// acceleration motor speed
long encdr = 0;			// counting encoder

void inter() {
	encdr++;
}
	
void stepSM(){
	delayMicroseconds(ps);
	digitalWrite(PUL, HIGH);
	delayMicroseconds(ps);
	digitalWrite(PUL, LOW);
}

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(en2, INPUT);
  pinMode(en3, INPUT);
  //digitalWrite(ENA, HIGH);
  digitalWrite(ENA, LOW);
  // digitalWrite(DIR, HIGH);
  digitalWrite(DIR, LOW);
  Serial.begin(115200);
  attachInterrupt (0, inter, CHANGE);
  attachInterrupt (1, inter, CHANGE);
}

void loop() {
	for (long i = 0; i < 51200; i++) {
		stepSM();
	}
	delay(200);
	Serial.println(encdr);
	encdr = 0;
}