String result = "!";
String ser;


//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void setup() {
	pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
		if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 10 && int(sr) != 13){// && int(sr) != -1){
			// Serial.println(int(sr));
			ser += sr;
			delay(5);
			sr = Serial.read();
			//saveEEPROM(cnt, sr);
			//cnt++;
		}
	}
	else {
		if (ser != ""){
			if (ser == "reset") resetFunc();
			else if (ser == "*idn?") {
				Serial.println("GW, GDM8255A, 1.0");
			}
			else if (ser == "conf:stat:rang?") {
				if (millis() % 2 == 0){
					Serial.println("DCV: 1");
				}
				else {
					Serial.println("DCV: 2");
				}
			}
			else{
				answer(ser);
			}
			ser = "";
			//Serial.flush();
		}
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
	result = expa(x);
	Serial.println(result);
}
