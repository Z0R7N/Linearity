/*  команды
* - задает нулевую точку
+ - вращение по часовой стрелке
- - вращение против часовой
/ - вращение на 3'
число - угол на который надо поставить ось мотора
ssчисло - установить скорость, от 1 до 9
saчисло - установить ускорение от 1 до 9
hlo - запрос на проверку порта
e - запрос на число энкодера
*/

изменить скорость подхода к нужному углу при убирании люфта

#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int maxPs = 1000;
int minPs = 80;

String ser = "";					// string from serial
long mainAngle = 0;					// countong for angle of position steper motor (from 0 to 51200)
long newAngl = 0;					// angle for motor move
long preAngl;						// angle there motor must move before new angle
int acc = 5;						// acceleration motor speed
int ps = 150;						// delay for pause (80 minimum & 1000 maximum)
long encdr = 0;						// counting encoder
double angleStep = 142.2222222222;	// coefficient for convert microstep to angle
bool cw = false;					// clockwise or counterclockwise rotating
int coefAngl = 800;					// coefficient for pre angle


void inter() {
	if(!cw && digitalRead(DIR) == HIGH) {
		encdr++;
		// if (encdr >= newAngl) {
			// Serial.print(go);
//			 Serial.println("lse");
		// }
	}
	else if (!cw && digitalRead(DIR) == LOW) {
		encdr--;
		// if (encdr <= newAngl) {
			// Serial.print(go);
			// Serial.println(" go false");
		// }
	}
	else if (cw && digitalRead(DIR) == LOW) {
		encdr++;
		// if (encdr >= newAngl) {
			// Serial.print(go);
			// Serial.println(" go false");
		// }
	}
	else if (cw && digitalRead(DIR) == HIGH) {
		encdr--;
		// if (encdr <= newAngl) {
			// Serial.print(go);
			// Serial.println(" go false");
		// }
	}
}

// send pulse to driver
void stepSM(){
	digitalWrite(PUL, HIGH);
	delayMicroseconds(ps);
	digitalWrite(PUL, LOW);
	delayMicroseconds(ps);
	if(!cw && digitalRead(DIR) == HIGH) {
		mainAngle++;
	}
	else if (!cw && digitalRead(DIR) == LOW) {
		mainAngle--;
	}
	else if (cw && digitalRead(DIR) == LOW) {
		mainAngle++;
	}
	else if (cw && digitalRead(DIR) == HIGH) {
		mainAngle--;
	}
}

// recognising commands got from port
void getCommand(String com){
	String st = "";
	double num = -1;
	if (com.length() > 0) {
		num = com.toDouble();
		// Serial.println(num);
	}
	if (com.length() > 2) st = com.substring(0, 2);
	if (com == "*") {
		Serial.println("угол 0");
		mainAngle = 0;
		encdr = 0;
	}
	else if (com == "+") {
		digitalWrite(DIR, HIGH);
		cw = true;
	}
	else if (com == "-") {
		digitalWrite(DIR, LOW);
		cw = false;
	}
	else if (com == "/") {
		angleSet(mainAngle + 2);
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
void angleSet(double a){
	double tmp = a * angleStep;
	preAngl = round(tmp);
	newAngl = preAngl - coefAngl;
	Serial.println("pre and new angles");
	Serial.print(preAngl);
	Serial.print("        ");
	Serial.println(newAngl);
	if (preAngl < mainAngle) {
		setParam();
	}
	newAngl = preAngl;
	setParam();
}

// instruction
void instruction(){
	Serial.println("команды");
	Serial.println("* - задает нулевую точку");
	Serial.println("+ - вращение по часовой стрелке");
	Serial.println("- - вращение против часовой");
	Serial.println("/ - вращение на 3'");
	Serial.println("число - угол на который надо поставить ось мотора");
	Serial.println("ssчисло - установить скорость, от 1 до 9");
	//Serial.println("saчисло - установить ускорение от 1 до 9");
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
		speed = 920 * speed / 100;
		res = round(speed);
		res += 80;
	}
	// Serial.println(res + " - calcul speed res = ");
	// Serial.println(s + " string coming");
	res = res == -1 ? ps : res;
	return res;
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

// setting parameters for moving
void setParam (){
	if (!cw) {
		if (mainAngle < newAngl) {
			digitalWrite(DIR, HIGH);
		}
		else {
			digitalWrite(DIR, LOW);
		}
	}
	else {
		if (mainAngle > newAngl) {
			digitalWrite(DIR, HIGH);
		}
		else {
			digitalWrite(DIR, LOW);
		}
	}
	// Serial.println(go);
	if (newAngl != mainAngle) move();
}

// move to new angle
void move() {
	long n = mainAngle - newAngl;
	n = n < 0 ? n * -1 : n;
	// Serial.println("main  and  new  Angles");
	// Serial.print(mainAngle);
	// Serial.print("steps to move = ");
	// Serial.println(n);
	for (int i = 0; i < n; i++) {
		stepSM();
	}
	Serial.print("угол = ");
	Serial.println(newAngl);
	Serial.print("encoder = ");
	Serial.println(encdr);
	Serial.println();
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

// the loop function runs over and over again forever
void loop() {
	if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 10){
			ser += sr;
			delay(5);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			Serial.println();
			Serial.println("==================");
			Serial.println("==================");
			Serial.print("serial = ");
			Serial.println(ser);
			getCommand(ser);
			ser = "";
		}
	}
}