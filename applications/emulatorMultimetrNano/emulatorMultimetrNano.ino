#include <EEPROM.h>

String result = "!";
String ser;
int LED = 13;


//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void setup() {
	pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
		if (Serial.available() > 0){
		int cnt = 0;
		// delay(400);
		// digitalWrite(LED, 1);
		// delay(800);
		// digitalWrite(LED, 0);
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 13 && int(sr) != 10 && int(sr) != -1){
			// Serial.println(int(sr));
			//saveEEPROM(cnt, sr);
			ser += sr;
			delay(5);
			sr = Serial.read();
			cnt++;
		}
	}
	else {
		if (ser != ""){
			if (ser == "reset23") resetFunc();
			// Serial.println();
			// Serial.println("==================");
			// Serial.println("==================");
			// Serial.print("serial = ");
			// Serial.println(ser);
			answer(ser);
			ser = "";
		}
		//digitalWrite(LED, 0);
		//delay(500);
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

void saveEEPROM (int adr, char data) {
	digitalWrite(LED, 1);
	delay(200);
	digitalWrite(LED, 0);
	delay(50);
	// char red = EEPROM.read(adr);
	// if(data != red){
		// EEPROM.write(adr, data);
	// }
}

