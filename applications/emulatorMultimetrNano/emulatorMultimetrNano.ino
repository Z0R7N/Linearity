String result = "!";
String ser;
int LED = 13;

void setup() {
	pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
		if (Serial.available() > 0){
		
		// delay(400);
		// digitalWrite(LED, 1);
		// delay(800);
		// digitalWrite(LED, 0);
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 10){
		digitalWrite(LED, 1);
		delay(400);
		digitalWrite(LED, 0);
		delay(200);
			ser += sr;
			delay(5);
			sr = Serial.read();
		}
	}
	else {
		if (ser != ""){
			// Serial.println();
			// Serial.println("==================");
			// Serial.println("==================");
			// Serial.print("serial = ");
			// Serial.println(ser);
			answer(ser);
			ser = "";
		}
		digitalWrite(LED, 0);
		delay(500);
	}
}
	
	
String expa (long num) {
	String s = "";
	String result = "";
	char cstr[16];
	ltoa(num, cstr, 10);
	s = cstr;
	int cnt = s.length();
	result = "0.";
	result += s;
	result += "E";
	result += (cnt - 4);
	
	return result;
}

void answer(String req) {
	long x = random(1000, 100100);
	 // Serial.println(x);
	// Serial.print(x);
	// Serial.print(" = ");
	result = expa(x);
	Serial.println(result);
}