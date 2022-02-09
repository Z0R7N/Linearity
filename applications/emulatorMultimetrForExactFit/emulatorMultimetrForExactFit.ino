#include <EEPROM.h>

String result = "!";
String ser;
int LED = 13;
int counter = 0;


//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
		if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 13 && int(sr) != 10){// && int(sr) != -1){
			ser += sr;
			delay(5);
			sr = Serial.read();
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
	
	
String expa (double num) {
	String s = "";
	String result = "";
	char TempString[10];
	dtostrf(num,2,2,TempString);
 // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
	s = String(TempString);
	Serial.print("num = ");
	Serial.print(num);
	Serial.print("  s = ");
	Serial.println(s);
	String cn = String(counter);
	int cnt = s.length();
	//result = "0.";
	result = s;
	result += cn;
	result += "E";
	result += (cnt - 4);
	counter++;
	return result;
}

void answer(String req) {
	double x;
	switch (counter){
		case 0:
			for (int i = 0; i < 20; i++){
				x = random(5000, 5800);
				x /= 100;
			}
			break;
		case 1:
			x = random(3000, 4000);
			x /= 1000;
			break;
		case 10:
			x = 2.5;
			break;
		default:
			x = random(0, 3000);
			x /= 1000;
			break;
	}
	Serial.println(x);
	result = expa(x);
	Serial.print("result = ");
	Serial.println(result);
}

int randTime(){
	int tt = 0;
	String tmp;
	String res = "";
	long tm = millis();
	Serial.println(tm);
	tmp = String(tm);
	Serial.println(tmp);
	for (int i = tmp.length() - 1; i < tmp.length() - 4; i--){
		res += tmp[i];
	}
	Serial.println(res);
	tt = res.toInt();
	Serial.println(tt);
	
	return tt;
}