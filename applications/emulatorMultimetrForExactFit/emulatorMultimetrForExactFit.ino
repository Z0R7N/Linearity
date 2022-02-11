String ser;
int LED = 13;
int counter = 0;
bool check1 = false;
bool check2 = false;


//declare a function reset with address 0
void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
		if (Serial.available() > 0){
		ser = "";
		char sr = Serial.read();
		while (int(sr) != 10){// && int(sr) != -1){  int(sr) != 13 && 
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
	String result1 = "";
	char TempString[10];
	dtostrf(num,2,2,TempString);
 // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
	s = String(TempString);
	// Serial.print("num = ");
	// Serial.print(num);
	// Serial.print("  s = ");
	// Serial.println(s);
	String cn = String(counter);
	int cnt = s.length();
	//result1 = "0.";
	result1 = s;
	result1 += cn;
	result1 += "E";
	result1 += (cnt - 3);
	counter++;
	return result1;
}

void answer(String req) {
	double x;
	String result;
	int j = randTime();
	switch (counter){
		case 0:
			for (int i = 0; i < j; i++){
				x = random(5000, 5800);
				x /= 10000;
			}
			break;
		case 1:
			x = random(3000, 4000);
			x /= 100000;
			check1 = true;
			break;
		case 10:
			x = 2.5;
			break;
		default:
			double lim = 0.1;
			do {
				x = random(0, 3000);
				x /= 100000;
				if (check1){
					lim = 0.15;
					check2 = true;
				}
				if (check2) {
					lim = 0.24;
				}
			}while (x > lim);
			break;
	}
	//Serial.println();
	result = expa(x);
	// Serial.print("result = ");
	// for (int i = 0; i < result.length(); i++){
		// Serial.print(result[i]);
		// Serial.print(" - ");
		// Serial.print(int(result[i]));
		// Serial.println();
	// }
	Serial.println(result);
	Serial.flush();
}

int randTime(){
	int tt = 0;
	String tmp;
	String res = "";
	long tm = millis();
	// Serial.print("tm = ");
	// Serial.println(tm);
	tmp = String(tm);
	// Serial.print("tm.length = ");
	// Serial.println(tmp.length());
	for (int i = tmp.length() - 1; i > tmp.length() - 3; i--){
		res += tmp[i];
		// Serial.print("i = ");
		// Serial.println(i);
		// Serial.println(tmp[i]);
	}
	// Serial.print("res = ");
	// Serial.println(res);
	tt = res.toInt();
	// Serial.print("tt = ");
	// Serial.println(tt);
	
	return tt;
}