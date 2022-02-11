#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int ps = 3000; 			// delay for pause (50 minimum & 1000 maximum)
int acc = 5;			// acceleration motor speed
long encdr1 = 0;			// counting encoder A
long encdr2 = 0;			// counting encoder B
long stp = 0;

void inter0() {
	Serial.print("stp A = ");
	Serial.println(stp);
	stp = 0;
}

void inter1() {
	Serial.print("stp B = ");
	Serial.println(stp);
	stp = 0;
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
  attachInterrupt (0, inter0, CHANGE);
  attachInterrupt (1, inter1, CHANGE);
}

void loop() {
	for (long i = 0; i < 51200; i++) {
		stp++;
		stepSM();
	}
}