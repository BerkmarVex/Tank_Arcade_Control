#include "main.h"

int JoystickGetAnalog(unsigned char Joystick, unsigned char axis);
bool JoystickGetDigital(unsigned char Joystick, unsigned char buttonGroup, unsigned char button);
void motorSet(unsigned char channel, int speed);

int leftJoyV;
int leftJoyH;
int rightJoy;
bool rightR = false;
bool rightRcheck;

void module(){
	if ((rightJoy >=90 && rightJoy <= 120) || (rightJoy>=-90 && rightJoy<=-120)) {
      // divide number between 90 and 120, -90 and -120, to make the controls more precise
    if (rightJoy%2 == 1 || rightJoy%2 == -1) { //make power variable even so it can be divided by 2
    	rightJoy++;
    }
    rightJoy = rightJoy/2;
  }
  if ((leftJoyV >=-90 && leftJoyV <= -120) || (leftJoyV >=90 && leftJoyV <= 120)) {
    	// divide number between 90 and 120, -90 and -120, to make the controls more precise
    if (leftJoyV%2 == 1 || leftJoyV%2 == -1){ // make power2 variable even so it can be divided by 2
      leftJoyV++;
    }
	}
  	leftJoyV = leftJoyV/2;
	if ((leftJoyH >=-90 && leftJoyH <= -120) || (leftJoyH >=90 && leftJoyH <= 120)) {
	    	// divide number between 90 and 120, -90 and -120, to make the controls more precise
	   if (leftJoyH%2 == 1 || leftJoyH%2 == -1){ // make power2 variable even so it can be divided by 2
	   	leftJoyH++;
	   }
	  	leftJoyH = leftJoyH/2;
  }
	return;
}

void checkPressed(){
	if (rightRcheck && rightR){
		rightR = false;
	}
	 else if (rightRcheck && !rightR) {
		rightR = true;
	}
}

void update(){
	leftJoyV = joystickGetAnalog(1, 2);
	leftJoyH =
	rightJoy = joystickGetAnalog(1,3);
	rightRcheck = joystickGetDigital(1,8,JOY_RIGHT);
	module();
	checkPressed();
}

void tank(){
	update();
	motorSet(2, rightJoy);
	motorSet(3, leftJoyV);

}

void arcade(){
	update();
	motorSet(2, leftJoyV - leftJoyH);
	motorSet(2, leftJoyV - leftJoyH);
}


void operatorControl() {
	while (1) {
		if (!rightR){
			tank();
		}
		else if(rightR){
			arcade();
		}
		delay(20);
	}
}
