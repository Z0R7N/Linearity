/*  команды
* - задает нулевую точку
^ - задает основному углу 120 градусов
+ - вращение по часовой стрелке
- - вращение против часовой
/ - вращение на 3'
<> - проверка на установку абсолютного угла
[] - проверка датчика, если 0 то в нулевой точке
# - выводит основной угол
число - угол на который надо поставить ось мотора
ssчисло - установить скорость, от 1 до 9
e - запрос на число энкодера
abs - выводит абсолютный угол оси
hlo - запрос на проверку порта
reset - перезагрузить устройство
! - поиск нулевой позиции, которая равна 120 градусам прибора
blck - включить и
unblck - отключить программное ограничение поворота на углы меньше 40 и больше 320 градусов
*/

#define en2 2
#define en3 3

#define stp 7 // button for enable moving
#define zero 12 // zero point by sensor

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int maxPs = 1000;
int minPs = 80;

bool blck = true;					// block for danger rotate (<40 and >320 degrees)
bool goMove = true;					// if block for move (<40 and >320 degrees)
String ser = "";					// string from serial
long mainAngle = -1;				// countong for angle of position steper motor (from 0 to 51200)
long newAngl = 0;					// angle for motor move
long preAngl;						// angle there motor must move before new angle
long absAngle = -1;					// angle for check zero point equals 180 degrees
int ps = 120;						// delay for pause (80 minimum & 1000 maximum)
long encdr = -1;						// counting encoder
double angleStep = 142.2222222222;	// coefficient for convert microstep to angle
double enCoeff = 2.844444444444;	// coefficient for convert encoder to angle
bool cw = true;						// clockwise or counterclockwise rotating
int coefAngl = 1422;				// coefficient for pre angle
bool rotate = false;				// bool value for checking rotation
bool zeroPoint = false;				// bool value for set sensor point


//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void inter() {
	if(!cw && digitalRead(DIR) == HIGH) {
		encdr++;
	}
	else if (!cw && digitalRead(DIR) == LOW) {
		encdr--;
	}
	else if (cw && digitalRead(DIR) == LOW) {
		encdr++;
	}
	else if (cw && digitalRead(DIR) == HIGH) {
		encdr--;
	}
}

// send pulse to driver
void stepSM(){
	goMove = true;
	if(!cw && digitalRead(DIR) == HIGH) {
		absAngle--;
		mainAngle++;
	if (blockMove()) returnAbsAngle(true, false);
	}
	else if (!cw && digitalRead(DIR) == LOW) {
		absAngle++;
		mainAngle--;
		if (blockMove()) returnAbsAngle(false, true);
	}
	else if (cw && digitalRead(DIR) == LOW) {
		absAngle++;
		mainAngle++;
		if (blockMove()) returnAbsAngle(false, false);
	}
	else if (cw && digitalRead(DIR) == HIGH) {
		absAngle--;
		mainAngle--;
		if (blockMove()) returnAbsAngle(true, true);
	}
	if (goMove) {
		digitalWrite(PUL, HIGH);
		delayMicroseconds(ps);
		digitalWrite(PUL, LOW);
		delayMicroseconds(ps);
		if (absAngle == -1) absAngle = 51199;
		if (absAngle == 51200) absAngle = 0;
	}
}

// change back absAngle
void returnAbsAngle (bool incrA, bool incrM) {
	absAngle = incrA ? ++absAngle : --absAngle;
	mainAngle = incrM ? ++mainAngle : -- mainAngle;
	goMove = false;
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
		mainAngle = 0;
		encdr = 0;
		Serial.println("0");
		Serial.flush();
	}
	else if (com == "zero" || com == "!") {
		searchZero();
		Serial.flush();
	}
	else if (com == "blck") {
		blck = true;
		Serial.println(blck);
		Serial.flush();
	}
	else if (com == "unblck") {
		blck = false;
		Serial.println(blck);
		Serial.flush();
	}
	else if (com == "<>") {
		Serial.println(zeroPoint);
		Serial.flush();
	}
	else if (com == "[]"){
		Serial.println(digitalRead(zero));
		Serial.flush();
	}
	else if (com == "#") {
		long ma = mainAngle >= 0 ? round(mainAngle / angleStep) : mainAngle;
		Serial.println(ma);
		Serial.flush();
	}
	else if (com == "abs") {
		long x = absAngle >= 0 ? round(absAngle / angleStep) : absAngle;
		Serial.println(x);
		Serial.flush();
	}
	else if (com == "+") {
		digitalWrite(DIR, HIGH);
		cw = false;
		Serial.println(com);
		Serial.flush();
	}
	else if (com == "-") {
		digitalWrite(DIR, LOW);
		cw = true;
		Serial.println(com);
		Serial.flush();
	}
	else if (com == "^") {
		mainAngle = 17066.33333333;
		encdr = 341;
		Serial.println(round(mainAngle / angleStep));
		Serial.flush();
	}
	else if (com == "/") {
		angleSet(mainAngle + 2);
		Serial.flush();
	}
	else if (com == "reset") {
		resetFunc();
	}
	else if (com == "dir") {
		Serial.println(digitalRead(DIR) ? "+" : "-");
		Serial.flush();
	}
	else if (com == "hlo") {
		Serial.println("hlo");
		Serial.flush();
	}
	else if (com == "e") {
		long enn = encdr >= 0 ? round(encdr / enCoeff) : encdr;
		Serial.println(enn);
		Serial.flush();
	}
	else if (com == "help") {
		instruction();
		Serial.flush();
	}
	else if (st == "ss") {
		String spd = com.substring(2);
		ps = speedMotor(spd);
		Serial.println(ps);
		Serial.flush();
	}
	else if (num > 0) {
		angleSet(num);
		Serial.flush();
	}
	else if (com == "0") {
		angleSet(0);
		Serial.flush();
	}
	else {
		Serial.println("error");
		Serial.flush();
	}
}

// search point zero
void searchZero(){
	int tmpPs = ps;
	ps = 80;
	if (digitalRead(zero)) {
		if (zeroPoint) {
			calculateDir();
		}
		long cnt = 0;
		bool tmpBlck = blck;
		blck = false;
		while (cnt < 700) {
			if (!digitalRead(zero)) {
				cnt++;
			} else {
				cnt = 0;
			}
			stepSM();
		}
		blck = tmpBlck;
	}
	setValueZero();
	ps = tmpPs;
	Serial.println(round(mainAngle / angleStep));
	Serial.flush();
}

// rotate to 180 abs
void calculateDir(){
	long d = absAngle - 25599.5;
	if (d == 0) return;
	if (d > 0) {
		digitalWrite(DIR, HIGH);
	} else {
		digitalWrite(DIR, LOW);
	}
	
}

// set zero point for value
void setValueZero(){
	if (!zeroPoint) {
		mainAngle = 17066.33333333;
		encdr = 341;
	}
	zeroPoint = true;
	absAngle = 25599.5;
	// absAngle = 25600;
}

// setting angle
void angleSet(double a){
	double tmp = a * angleStep;
	preAngl = round(tmp);
	newAngl = preAngl - coefAngl;
	if (preAngl < mainAngle) {
		setParam();
	}
	newAngl = preAngl;
	setParam();
	Serial.println(round(encdr / enCoeff));
	Serial.flush();
}

// instruction
void instruction(){
	Serial.println("команды:");
	Serial.println("* - задает нулевую точку");
	Serial.println("^ - задает основному углу 120 градусов");
	Serial.println("+ - вращение по часовой стрелке");
	Serial.println("- - вращение против часовой");
	Serial.println("/ - вращение на 3'");
	Serial.println("число - угол на который надо поставить ось мотора");
	Serial.println("ssчисло - установить скорость, от 1 до 9");
	Serial.println("e - запрос на число энкодера");
	Serial.println("hlo - запрос на проверку порта");
	Serial.println("<> - проверка на установку абсолютного угла");
	Serial.println("[] - проверка датчика, если 0 то в нулевой точке");
	Serial.println("# - выводит основной угол");
	Serial.println("abs - выводит абсолютный угол оси");
	Serial.println("reset - перезагрузить устройство");
	Serial.println("! - поиск нулевой позиции, которая равна 120 градусам прибора");
	Serial.println("blck - включить и");
	Serial.println("unblck - отключить программное ограничение поворота на углы меньше 40 и больше 320 градусов");
}

// calculating speed
int speedMotor(String s){
	int res = -1;
	double speed = s.toDouble();
	if (speed > 9 || speed < 1 || s.length() == 0) {
		instruction();
	}
	else{
		speed = 9 - speed;
		speed = speed * 100 / 8;
		speed = 920 * speed / 100;
		res = round(speed);
		res += 80;
	}
	res = res == -1 ? ps : res;
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
	if (newAngl != mainAngle) move();
}

// move to new angle
void move() {
	long n = mainAngle - newAngl;
	n = n < 0 ? n * -1 : n;
	rotate = true;
	for (long i = 0; i < n; i++) {
		if(digitalRead(stp)) {
			stepSM();
		}
	}
	rotate = false;
}

// check for rotating over boundaries
bool blockMove(){
	bool blocker = false;
	if (blck) {
		if (absAngle == 5689 || absAngle < 5689) {
			blocker = true;
		}
		if (absAngle == 45511 || absAngle > 45511) {
			blocker = true;
		}
	}
	return blocker;
}

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(en2, INPUT);
  pinMode(en3, INPUT);
  pinMode(stp, INPUT);
  pinMode(zero, INPUT);
  //digitalWrite(ENA, HIGH);
  digitalWrite(ENA, LOW);
  // digitalWrite(DIR, HIGH);
  digitalWrite(DIR, LOW);
  Serial.begin(115200);
  if (!digitalRead(zero)) {
	  setValueZero();
  }
  attachInterrupt (0, inter, CHANGE);
  attachInterrupt (1, inter, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
	if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != -1){// && int(sr) != -1 && int(sr) != 13){
			if (int(sr) != 10 && int(sr) != 13){
				ser += sr;
			}
			delay(5);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			ser.trim();
			getCommand(ser);
			ser = "";
		}
	}
}