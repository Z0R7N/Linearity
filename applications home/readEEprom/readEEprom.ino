#include <EEPROM.h>

void setup() {
	Serial.begin(9600);
	//EEPROM.begin(50);
	eprormRead();
}

void loop() {
	
}

void eprormRead(){
	byte val;
	for (int i = 0; i < 14; i++){
		val = EEPROM.read(i);
		Serial.print("adres: ");
		Serial.print(i);
		Serial.print("   data: ");
		Serial.println(val);
	}
}