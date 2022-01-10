/*  команды
* - задает нулевую точку
+ - вращение по часовой стрелке
- - вращение против часовой
число - угол на который надо поставить ось мотора
ssчисло - установить скорость, от 1 до 9
saчисло - установить ускорение от 1 до 9
*/

#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int maxPs = 1000;
int minPs = 50;

String ser = "";		// string from serial
int ps = minPs;			// delay for pause (400 minimum & 2000 maximum)
int oldPs = ps;			// for counting delay
int acc = 5;			// acceleration motor speed
long encdr = 0;			// counting encoder
long oldEncdr = encdr;	// for counting delay
long newAngl;			// angle there motor must move
long preAngl;			// angle there motor must move before new angle
bool go = false; 		// if "true" motor rotate
bool cw = true;			// clockwise or counterclockwise rotating
int accCheck = 0;		// 1 - acceleration; 0 - even movement; -1 - slow down
int pathMotor = 0;		// length which must count encoder
int stepAccel = 0; 		// path to acceleration and slow down
int beginPth;			// start encoder number
int coefAccel = 3;		// koefficient for acceleration
int coefAngl = 15;		// koefficient for pre angle


void inter() {
	if(!cw && digitalRead(DIR) == HIGH) {
		encdr++;
		if (encdr >= newAngl) {
			go = false;
			// Serial.print(go);
			// Serial.println(" go false");
		}
	}
	else if (!cw && digitalRead(DIR) == LOW) {
		encdr--;
		if (encdr <= newAngl) {
			go = false;
			// Serial.print(go);
			// Serial.println(" go false");
		}
	}
	else if (cw && digitalRead(DIR) == LOW) {
		encdr++;
		if (encdr >= newAngl) {
			go = false;
			// Serial.print(go);
			// Serial.println(" go false");
		}
	}
	else if (cw && digitalRead(DIR) == HIGH) {
		encdr--;
		if (encdr <= newAngl) {
			go = false;
			// Serial.print(go);
			// Serial.println(" go false");
		}
	}
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
  attachInterrupt (0, inter, FALLING);
  attachInterrupt (1, inter, FALLING);
}

// the loop function runs over and over again forever
void loop() {
	if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 10){
			ser += sr;
			delay(2);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			// Serial.println(ser + " - loop port coming");
			getCommand(ser);
			ser = "";
		}
	}
}

// recognising commands got from port
void getCommand(String com){
	String st = "";
	long num = -1;
	if (com.length() > 0) {
		num = com.toInt();
		// Serial.println(num);
	}
	if (com.length() > 2) st = com.substring(0, 2);
	if (com == "*") encdr = 0;
	else if (com == "+") {
		digitalWrite(DIR, HIGH);
		cw = true;
	}
	else if (com == "-") {
		digitalWrite(DIR, LOW);
		cw = false;
	}
	else if (st == "ss") {
		String spd = com.substring(2);
		// Serial.println(spd + " get command ss");
		ps = speedMotor(spd);
		// Serial.print("ps ");
		// Serial.println(ps);
	}
	else if (st == "sa") {
		String accel = com.substring(2);
		acc = accelerationMotor(accel);
	}
	else if (num > 0) {
		angleSet(num);
	}
	else if (com == "0") {
		angleSet(0);
	}
	else {
		instruction();
	}
}

// setting angle
void angleSet(long a){
	double tmp = a * 100 / 360;
	preAngl = tmp * 512 / 100;
	newAngl = preAngl - coefAngl;
	if (newAngl < encdr) {
		setParam();
	}
	newAngl = preAngl;
	setParam();
}

// calculating acceleration
int accelerationMotor(String a){
	int res = -1;
	int acceleration = a.toInt();
	if (acceleration > 9 || acceleration < 1 || a.length() == 0) {
		instruction();
	}
	else {
		res = acceleration;
	}
	res = res == -1 ? acc : res;
	return res;
}

// calculating speed
int speedMotor(String s){
	int res = -1;
	double speed = s.toDouble();
	if (speed > 9 || speed < 1 || s.length() == 0) {
		instruction();
	}
	else{
		// Serial.print("calculate speed ");
		// Serial.println(speed);
		speed = 9 - speed;
		speed = speed * 100 / 8;
		speed = 1600 * speed / 100;
		res = speed + 400;
	}
	// Serial.println(res + " - calcul speed res = ");
	// Serial.println(s + " string coming");
	res = res == -1 ? ps : res;
	return res;
}

// instruction
void instruction(){
	Serial.println("команды");
	Serial.println("* - задает нулевую точку");
	Serial.println("+ - вращение по часовой стрелке");
	Serial.println("- - вращение против часовой");
	Serial.println("число - угол на который надо поставить ось мотора");
	Serial.println("ssчисло - установить скорость, от 1 до 9");
	Serial.println("saчисло - установить ускорение от 1 до 9");
}

// setting parameters for moving
void setParam (){
	if (!cw) {
		if (encdr < newAngl) {
			digitalWrite(DIR, HIGH);
			go = true;
		}
		else {
			digitalWrite(DIR, LOW);
			go = true;
		}
	}
	else {
		if (encdr > newAngl) {
			digitalWrite(DIR, HIGH);
			go = true;
		}
		else {
			digitalWrite(DIR, LOW);
			go = true;
		}
	}
	// Serial.println(go);
	if (newAngl != encdr) move();
}

// setting for start moving with acceleration
void startMoveAccel(){
	// Serial.print("angle new = ");
	// Serial.println(newAngl);
	accCheck = 1;
	oldEncdr = encdr;
	oldPs = ps;
	ps = maxPs;
	beginPth = calculatePath();
	pathMotor = encdr - newAngl;
	pathMotor = pathMotor < 0 ? pathMotor * -1 : pathMotor;
}

// move to new angle
void move(){
	// Serial.print("");
	startMoveAccel();
	// Serial.println(accCheck);
	while(go) {
		if (accCheck == 0) {
			// Serial.println("check 0");
			// Serial.println(ps);
			if (checkPath()) accCheck = -1;
		}
		else if (accCheck == 1) {
			// Serial.println("check 1");
			ps -= (acc * coefAccel);
			// Serial.println(ps);
			if (ps <= oldPs) {
				accCheck = 0;
				stepAccel = beginPth - calculatePath();
				stepAccel = stepAccel < 0 ? stepAccel * -1 : stepAccel;
				ps = oldPs;
			}
			if (checkPath() && calculatePath() < (pathMotor / 2)) accCheck = -1;
		}
		else {
			// Serial.println("check -1");
			ps += (acc * coefAccel);
			// Serial.println(ps);
			// Serial.print("old ps = ");
			// Serial.println(oldPs);
			if (ps >= maxPs) ps = maxPs;
		}
		// Serial.println(encdr);
		// delayMicroseconds(100);
		stepSM();
	}
	ps = oldPs;
}

// check path for slow down motor
bool checkPath(){
	bool res = false;
	int p = calculatePath();
	if (stepAccel >= p) {
		// Serial.print("step accel = ");
		// Serial.println(stepAccel);
		res = true;
	}
	return res;
}

// calculate path left
int calculatePath(){
	int p = encdr - newAngl;
	p = p < 0 ? p * -1 : p;
	// Serial.print("calculate Path: int p = ");
	// Serial.println(p);
	return p;
}

// send pulse to driver
void stepSM(){
	delayMicroseconds(ps);
	if(!go) return;
	digitalWrite(PUL, HIGH);
	delayMicroseconds(ps);
	if(!go) return;
	digitalWrite(PUL, LOW);
}
