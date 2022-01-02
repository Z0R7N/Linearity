/*  команды
* - задает нулевую точку
+ - вращение по часовой стрелке
- - вращение против часовой
число - угол на который надо повернуть мотор
ss число - установить скорость, от 1 до 9
sa число - установить ускорение от 1 до 9
*/

#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int ps = 400; 			// delay for pause (400 minimum & 2000 maximum)
long encdr = 0;			// counting encoder
bool go = false; 		// if "true" motor rotate


void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(en2, INPUT);
  pinMode(en3, INPUT);
  //digitalWrite(ENA, HIGH);
  digitalWrite(ENA, LOW);
  digitalWrite(DIR, HIGH);
  // digitalWrite(DIR, LOW);
  Serial.begin(115200);
  attachInterrupt (0, inter, FALLING);
  attachInterrupt (1, inter, FALLING);
}

// the loop function runs over and over again forever
void loop() {
	if (Serial.available() > 0){
		String ser = "";
		char sr = Serial.read();
		while (int(sr) != 10){
			ser += sr;
			delay(2);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			getCommand(ser);
			ser = "";
		}
	}
}

// recognising commands got from port
void getCommand(String ser){
	if (ser.length() > 3) String st = ser.substring(0, 2);
	if (ser == "*") encdr = 0;
	if (ser == "+") DIR = HIGH;
	if (ser == "-") DIR = LOW;
	if (st == "ss") {
		String spd = ser.substring(3);
		speedMotor(
		double speed = spd.toDouble();
		if (speed > 9 || speed < 1) {
			instruction();
		}
		else{
			speed = 9 - speed;
			speed = speed * 100 / 8;
			speed = 1600 * speed / 100;
			ps = speed + 400;
		}
	}
}

// calculating speed
int speedMotor(String s){
	int res = 0;
	
	return res;
}

// instruction
void instruction(){
	Serial.println("команды");
	Serial.println("* - задает нулевую точку");
	Serial.println("+ - вращение по часовой стрелке");
	Serial.println("- - вращение против часовой");
	Serial.println("число - угол на который надо повернуть мотор");
	Serial.println("ss число - установить скорость, от 1 до 9");
	Serial.println("sa число - установить ускорение от 1 до 9");
}

void move(){
	while(go){
		// Serial.println("move go - " + go);
		
		stepSM();
		if(!go) break;
	}
}

void stepSM(){
	delayMicroseconds(ps);
	if(!go) {
		// Serial.println("stepSM go - " + go);
		return;
	}
	digitalWrite(PUL, HIGH);
	delayMicroseconds(ps);
	if(!go) return;
	digitalWrite(PUL, LOW);
}

void inter() {
	encdr--;
	// Serial.println(encdr);
	if (encdr <= 0) {
		go = false;
		// Serial.print("go = false");
	}
}