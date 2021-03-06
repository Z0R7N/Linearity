#define RES A0

String ser;
// int RES = 1;
double koef = 9.142857142857;

//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(115200);
  analogReference(DEFAULT);
  pinMode(RES, INPUT);
}

void loop() {
	// answer();
	// delay(500);
	if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != -1){//  int(sr) != 13 && int(sr) != 10 || 
			if (int(sr) != 13 && int(sr) != 10) ser += sr;
			delay(5);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			// int x;
			// for (int i = 0; i < ser.length(); i++){
				// x = ser[i];
				// Serial.println(x);
			// }
			if (ser == "reset") resetFunc();
			else if (ser == "*idn?") {
				Serial.println("DM, GDM8255A, 1.0");
				// Serial.flush();
			}
			else if (ser == "conf:stat:rang?") {
				Serial.println("3");
				// if (millis() % 2 == 0){
					// Serial.println("1");
				// }
				// else {
					// Serial.println("2");
				// }
				// Serial.flush();
			}
			else{
				answer();
				//Serial.flush();
			}
			ser = "";
			//Serial.flush();
		}
	}
}
	
	
String expa (int num) {
	String result = "";
	double r = num / koef;
	if (r == 0) {
		r = 0.001;
	}
	int cnt = 0;
	while (r > 1){
		r /= 10;
		cnt++;
	}
	cnt--;
	String s = String(r, 4);
	result += s;
	result += "E";
	result += cnt;
	return result;
}

void answer() {
	double x;
	int result;
	result = analogRead(RES);
	// Serial.print("result = ");
	// Serial.println(result);
	String exp = expa(result);
	Serial.println(exp);
	// Serial.flush();
}
