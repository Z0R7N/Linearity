#define an2 2
#define an3 3

#define in1 5
#define in2 6
#define in3 4

bool go = false;// move
bool cw = true; // direction
int dl = 3; 
long turn = 50; // 50 - one turn
long cnt = 0;
long trn = turn;
long pos = 0;
String ser = "";

void setup() {
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	Serial.begin(115200);
	pinMode(an2, INPUT);
	pinMode(an3, INPUT);
	attachInterrupt (0, inter, FALLING);
	attachInterrupt (1, inter, FALLING);
}

// void loop() { // стоп
// }

// void loop() { // один оборот по энкодеру
	// if (cnt <= 512) {
		// turnClockwice();
	// }
	// else {
		// noPosture();
		// delay(1000);
		// cnt = 0;
	// }
// }

// void loop(){ // один оборот на количество шагов
	// if (trn > 0) {
		// for(int i = 1; i <= 4; i++) posture(i);
		// trn--;
	// }
	// else {
		// noPosture();
		// trn = turn;
		// Serial.println(cnt);
		// cnt = 0;
		// delay(1000);
	// }
// }

void loop() { // оборот на угол по энкодеру
	noPosture();
	if (Serial.available() > 0){
		char sr = Serial.read();
		while (int(sr) != 10){
			ser += sr;
			delay(2);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			getSer(ser);
			ser = "";
		}
	}
}

void getSer(String x){
	if (x == "-"){
		cw = false;
	}
	else if (x == "+"){
		cw = true;
	}
	else{
		long angl = x.toInt();
		Serial.println(angl);
		turn = angl * 100 / 360;
		Serial.println(turn);
		turn = turn * 715 / 100;
		Serial.println(turn);
		delay(500);
		go = true;
		turning();
	}
}

void turning(){
	if (cw) {
		while (go) {
			for (int i = 1; i <= 4; i++){
				posture(i);
				if (!go) break;
			}
		}
	}
	else {
		while (go) {
			for (int i = 4; i > 0; i--) {
				posture(i);
				if (!go) break;
			}
		}
	}
	Serial.println("no posture");
	noPosture();
}

void inter() {
	turn--;
	if (turn <= 0) {
		go = false;
	}
	 // cnt++;
}

void noPosture(){
	digitalWrite(in1, LOW); 
	digitalWrite(in2, LOW); 
	digitalWrite(in3, LOW); 
	digitalWrite(in4, LOW);
}

void posture(int num) {
	switch(num){
		case 1:
			digitalWrite(in1, LOW); 
			digitalWrite(in2, LOW); 
			digitalWrite(in3, HIGH); 
			digitalWrite(in4, HIGH);
			delay(dl);
			break;
		case 2:
			digitalWrite(in1, LOW); 
			digitalWrite(in2, HIGH); 
			digitalWrite(in3, HIGH); 
			digitalWrite(in4, LOW);
			delay(dl);
		break;
		case 3:
			digitalWrite(in1, HIGH); 
			digitalWrite(in2, HIGH); 
			digitalWrite(in3, LOW); 
			digitalWrite(in4, LOW);
			delay(dl);
		break;
		case 4:
			digitalWrite(in1, HIGH); 
			digitalWrite(in2, LOW); 
			digitalWrite(in3, LOW); 
			digitalWrite(in4, HIGH);
			delay(dl);
		break;		
	}
	inter();
}

void turnCounterClockwice(){
	digitalWrite(in1, LOW); 
	digitalWrite(in2, LOW); 
	digitalWrite(in3, HIGH); 
	digitalWrite(in4, HIGH);
	delay(dl);

	digitalWrite(in1, LOW); 
	digitalWrite(in2, HIGH); 
	digitalWrite(in3, HIGH); 
	digitalWrite(in4, LOW);
	delay(dl);

	digitalWrite(in1, HIGH); 
	digitalWrite(in2, HIGH); 
	digitalWrite(in3, LOW); 
	digitalWrite(in4, LOW);
	delay(dl);

	digitalWrite(in1, HIGH); 
	digitalWrite(in2, LOW); 
	digitalWrite(in3, LOW); 
	digitalWrite(in4, HIGH);
	delay(dl);
}

void turnClockwice(){
	digitalWrite(in1, HIGH); 
	digitalWrite(in2, LOW); 
	digitalWrite(in3, LOW); 
	digitalWrite(in4, HIGH);
	delay(dl);

	digitalWrite(in1, HIGH); 
	digitalWrite(in2, HIGH); 
	digitalWrite(in3, LOW); 
	digitalWrite(in4, LOW);
	delay(dl);

	digitalWrite(in1, LOW); 
	digitalWrite(in2, HIGH); 
	digitalWrite(in3, HIGH); 
	digitalWrite(in4, LOW);
	delay(dl);

	digitalWrite(in1, LOW); 
	digitalWrite(in2, LOW); 
	digitalWrite(in3, HIGH); 
	digitalWrite(in4, HIGH);
	delay(dl);
}
