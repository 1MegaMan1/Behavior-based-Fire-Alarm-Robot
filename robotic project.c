#include <ev3.h>
#include <ev3_lcd.h>
#include <stdio.h>
#include <ev3.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define FIX_ANGLE 4
#define CHECK_ANGLE 2
#define ROTATE_RIGHT 1
#define ROTATE_LEFT -1
#define FORWARD_ONE_SQR 8
#define FORWARD_HALF_SQR 4
#define NORMAL_SPEED 19
#define SONAR_RANGE_MIN 25
#define SONAR_FOLLOW_RANGE 5
#define Wall_THRESHOLD 20
void turnRearMotor(int ROTATION, int DIRECTION);
void turnFrontMotor(int ROTATION, int DIRECTION);
void rightTurn(void);
void leftTurn(void);
void search(void);
void forward(int y, int speed);
void forward_LIGHT(int y, int speed,int light);
void sonarSTUFF(int sonar_FRONT,int sonar_LEFT,int sonar_RIGHT);
void Truewander();
void rndTurn();
void fix(int sonar_LEFT,int sonar_RIGHT);
x
void rightTurn(void)
{
	turnFrontMotor(45,ROTATE_RIGHT);
	turnRearMotor(45,ROTATE_LEFT);
	forward(1,NORMAL_SPEED);
	turnFrontMotor(45,ROTATE_LEFT);
	turnRearMotor(45,ROTATE_RIGHT);
}
void leftTurn(void)
{
	turnFrontMotor(45,ROTATE_LEFT);
	turnRearMotor(45,ROTATE_RIGHT);
	forward(1,NORMAL_SPEED);
	turnFrontMotor(45,ROTATE_RIGHT);
	turnRearMotor(45,ROTATE_LEFT);
}

void search(void)
{
	Off(OUT_AD);
	RotateMotor(OUT_C,-30,450);
	Wait(SEC_2);
	RotateMotor(OUT_C,30,900);
	Wait(SEC_2);
	RotateMotor(OUT_C,-30,470);
	Wait(SEC_2);
}
void forward(int y,int speed)
{
	y = y*125;
	OnFwdSync(OUT_AD,speed);
	while (0 <= y)
	{
		y = y - 1;
		Wait(1);
	}
}
void backward(int y,int speed)
{
	Off(OUT_AD);
	y = y*125;
	OnRevSync(OUT_AD,speed);
	while (0 <= y)
	{
		y = y - 1;
		Wait(1);
	}
	Off(OUT_AD);
}
void turnRearMotor(int ROTATION, int DIRECTION)
{
	ROTATION = ROTATION * 5;// 1 = 5 degrees
	RotateMotor(OUT_B,50*DIRECTION,ROTATION);
	//450 is 90 degrees
	//1800 is full rotation
}
void turnFrontMotor(int ROTATION, int DIRECTION)
{
	ROTATION = ROTATION * 5;// 1 = 5 degrees
	RotateMotor(OUT_C,50*(-DIRECTION),ROTATION);
	//450 is 90 degrees
	//1800 is full rotation
}
int randomgenerator()
{
	time_t t;
	srand((unsigned) time(&t));
	return rand() % 10;
}
void forward_LIGHT(int y,int speed,int light)
{
	int sonar_FRONT = readSensor(IN_1);
	int sonar_LEFT = readSensor(IN_2);
	int sonar_RIGHT = readSensor(IN_3);
	char mp = MotorPower(OUT_AD);
	y = y*125;
	OnFwdSync(OUT_AD,speed);
	while (0 <= y)
	{
		sonar_FRONT = readSensor(IN_1);
		sonar_LEFT = readSensor(IN_2);
		sonar_RIGHT = readSensor(IN_3);
		if(sonar_FRONT > SONAR_RANGE_MIN)
		{
			fix(sonar_LEFT,sonar_RIGHT);
		}
		light = readSensor(IN_4);
		y = y - 1;
		if(light == 2)
		{
			y = -1;
			Off(OUT_AD);
		}
		Wait(1);
	}
}
void Truewander()
{
	if(randomgenerator() == 0)
	{
		rightTurn();
	}
	else if(randomgenerator() == 1)
	{
		leftTurn();
	}
	else 
	{
		forward(FORWARD_ONE_SQR,NORMAL_SPEED);
	}
}
void rndTurn()
{
	if(randomgenerator() < 5)
	{
		rightTurn();
	}
	else 
	{
		leftTurn();
	}
}
void sonarSTUFF(int sonar_FRONT,int sonar_LEFT,int sonar_RIGHT)
{
	if(sonar_FRONT < SONAR_RANGE_MIN && sonar_LEFT > SONAR_RANGE_MIN && sonar_RIGHT > SONAR_RANGE_MIN)
	{
		rndTurn();
	}
	else if(sonar_FRONT < SONAR_RANGE_MIN && sonar_RIGHT < SONAR_RANGE_MIN)
	{
		leftTurn();
	}
	else if(sonar_FRONT < SONAR_RANGE_MIN && sonar_LEFT < SONAR_RANGE_MIN)
	{
		rightTurn();
	}
	else if(sonar_FRONT < SONAR_RANGE_MIN && sonar_LEFT < SONAR_RANGE_MIN && sonar_RIGHT < SONAR_RANGE_MIN)
	{
		backward(FORWARD_ONE_SQR,NORMAL_SPEED);
		forward(FORWARD_HALF_SQR,NORMAL_SPEED);
		rndTurn();
	}
}
void fix(int sonar_LEFT,int sonar_RIGHT){
	if(sonar_LEFT > SONAR_FOLLOW_RANGE && sonar_LEFT < SONAR_FOLLOW_RANGE + 4)
	{
		//left
		turnFrontMotor(Wall_THRESHOLD, ROTATE_LEFT);
		forward(1 , NORMAL_SPEED);
		turnFrontMotor(Wall_THRESHOLD, ROTATE_RIGHT);
	}
else if(sonar_LEFT < SONAR_FOLLOW_RANGE)
{
	turnFrontMotor(Wall_THRESHOLD, ROTATE_RIGHT);
	forward(1 , NORMAL_SPEED);
	turnFrontMotor(Wall_THRESHOLD, ROTATE_LEFT);
}
if(sonar_RIGHT > SONAR_FOLLOW_RANGE && sonar_RIGHT < SONAR_FOLLOW_RANGE + 4)
	{
		//right
		turnFrontMotor(Wall_THRESHOLD, ROTATE_RIGHT);
		forward(1 , NORMAL_SPEED);
		turnFrontMotor(Wall_THRESHOLD, ROTATE_LEFT);
	}
	else if(sonar_RIGHT < SONAR_FOLLOW_RANGE)
	{
		turnFrontMotor(Wall_THRESHOLD, ROTATE_LEFT);
		forward(1, NORMAL_SPEED);
		turnFrontMotor(Wall_THRESHOLD, ROTATE_RIGHT);
	}
}
int main(void)
{
	InitEV3();
	setAllSensorMode(US_DIST_CM,US_DIST_CM,US_DIST_CM,COL_COLOR);
	int sonar_FRONT = 0;
	int sonar_RIGHT = 0;
	int sonar_LEFT = 0;
	int light = 0;
	int breaker = 0;
	LcdInit();
		while(breaker == 0)
		{
			sonar_FRONT = readSensor(IN_1);
			sonar_LEFT = readSensor(IN_2);
			sonar_RIGHT = readSensor(IN_3);
			light = readSensor(IN_4);
			if(light == 2)
			{
				breaker = 1;
			}
			else
			{
				forward_LIGHT(1 , NORMAL_SPEED,light);
				sonarSTUFF(sonar_FRONT,sonar_LEFT,sonar_RIGHT);
			}
		}
	FreeEV3();
	return 0;
}
