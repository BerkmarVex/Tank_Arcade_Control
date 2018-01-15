/************
*  imports  *
*************/
#include "main.h"

/*************************
*  local initialization  *
**************************/

//Controller variables

int leftJoyV;
int leftJoyH;
int rightJoy;
bool rightR = false;
bool rightRcheck;
bool stillPressed = false;
bool prevRightRcheck = false;

//Motor variables

int leftMotor = 3;
int rightMotor = 2;

//Function definition

void module();
void checkPressed();
void update();
void tank();
void arcade();

/************************
*  function definition  *
*************************/

void update(){
	/**********************************************************************
	*  this function just updates the varables that get used every cylce  *
	***********************************************************************/
	leftJoyV = joystickGetAnalog(1, 3);
	leftJoyH = joystickGetAnalog(1, 4);
	rightJoy = joystickGetAnalog(1, 2);
	rightRcheck = joystickGetDigital(1, 8, JOY_RIGHT);
	module();
	checkPressed();
}

void buttonStatus(){
	/************************************************************
	*  This function is used to ensure that the varable rightR  *
	*  does not get changed if the user holds down the switch   *
	*  button for more than 20 milliseconds                     *
 	*************************************************************/
	if(rightRcheck == true){
		if(rightRcheck == !prevRightRcheck){
			stillPressed = false;
		}
		else{
			stillPressed = true;
		}
	}
	else if(rightRcheck == false){
		stillPressed = false;
	}
}

void checkPressed(){
	/************************************************************
	*  this function switches tank and arcade controls          *
	*  this if statments take in 3 booleans                     *
	*  if the button was pressed for an extended amount of time *
	*  if the button was pressed                                *
	*  and the current drive style                              *
	*************************************************************/
	buttonStatus();
	if (!stillPressed && rightRcheck && rightR){
		rightR = false;
	}
	else if (!stillPressed && rightRcheck && !rightR) {
		rightR = true;
	}
}

void module(){
/********************************************************
*  This function zones the controller to have a slower  *
*  inner ring to allow for more precise controll and    *
*  a faster outer ring for faster movment               *
*********************************************************/
	if((rightJoy >=90 && rightJoy <= 120) || (rightJoy>=-90 && rightJoy<=-120)) {
    rightJoy = rightJoy/2;
  }

  else if((leftJoyV >=-90 && leftJoyV <= -120) || (leftJoyV >=90 && leftJoyV <= 120)) {
		leftJoyV = leftJoyV/2;
  }

	else if((leftJoyH >=-90 && leftJoyH <= -120) || (leftJoyH >=90 && leftJoyH <= 120)) {
	  	leftJoyH = leftJoyH/2;
  }
}


void tank(){
	/***********************************************************
	*  This function splits the controls for the               *
	*  left and right motors to the left and right joy sticks  *
	************************************************************/
	update();
	motorSet(rightMotor, rightJoy);
	motorSet(leftMotor, leftJoyV);

}

void arcade(){
	/*****************************************
	*  This functions combines left and      *
	*  right motor control to one joy stick  *
	******************************************/
	update();
	motorSet(rightMotor, leftJoyV - leftJoyH);
	motorSet(leftMotor, leftJoyV - leftJoyH);
}

void operatorControl() {
	/******************
	*  main function  *
	*******************/

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
