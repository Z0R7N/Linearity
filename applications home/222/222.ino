long x = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
	Serial.println(x);
	x++;
	delay(2000);
}