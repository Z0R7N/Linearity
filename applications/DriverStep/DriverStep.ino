/*  команды
* - задает нулевую точку
+ - вращение по часовой стрелке
- - вращение против часовой
/ - вращение на 5'
число - угол на который надо поставить ось мотора
ssчисло - установить скорость, от 1 до 9
saчисло - установить ускорение от 1 до 9
*/

#define en2 2
#define en3 3

#define PUL 5 // impulse for driver
#define DIR 6 // direction for driver
#define ENA 4 // enable

int maxPs = 1000;
int minPs = 80;


// send pulse to driver
void stepSM(){
	delayMicroseconds(ps);
	if(!go) return;
	digitalWrite(PUL, HIGH);
	delayMicroseconds(ps);
	if(!go) return;
	digitalWrite(PUL, LOW);
}
