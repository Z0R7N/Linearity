int led14 = 14;  // yellow
int led16 = 16;  // green
char readS;
int buf;

void setup() {
  pinMode(led14, OUTPUT);
  pinMode(led16, OUTPUT);
  Serial.begin(115200);
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
}

void answer(String req) {
  double x = random(30000, 970000);
  Serial.println(x);
}
