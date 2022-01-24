int led14 = 14;  // yellow
int led16 = 16;  // green
char readS;
int buf;

void setup() {
  pinMode(led14, OUTPUT);
  pinMode(led16, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    digitalWrite(led14, 0);
    digitalWrite(led16, 1);
    int ln = Serial.available();
    String bufRead = "";
    for (int i = 0; i < ln; i++) {
      buf = Serial.read();
      if	(i != (ln - 1)) {
        readS = buf;
        bufRead = bufRead + readS;
      }
    }
    answer(bufRead);
    delay(500);

  }
  else {
    digitalWrite(led14, 1);
    digitalWrite(led16, 0);
    delay(500);
  }
  // answer("1");
  // Serial.println("=========");
  // Serial.println();
  // delay(3000);
}

String expa (double num) {
	num = abs(num);
	String s = "";
	int cnt = 0;
	long a = round(num);
	char cstr[16];
	ltoa(a, cstr, 10);
	char n = cstr[0];
	int frstNum = n - '0';
	long tmp = a;
	while (frstNum < tmp) {
		cnt++;
		tmp /= 10;
	}
	s += frstNum;
	s += ".";
	s += cstr[1];
	s += cstr[2];
	s += "E";
	s += cnt;

	return s;
}

void answer(String req) {
	double x = random(30000, 970000);
	// Serial.print(x);
	// Serial.print(" = ");
	Serial.println(expa(x));
}