#pragma config(StandardModel, "EV3_REMBOT")

const int Scanning_State = 0;
const int Charging_State = 1;
const int DetectedEdge_State = 2;
//const int Defense_State = 3;
const int Attacking_State = 4;
int current_State;
const int max_Dist = 40;
const int attack_Dist = 10;
int distanceToObstacle = 0;
int colorRead;
float rateRead = 0;
int Attack_Power = 50;
int squigglyMotionConstant;
const int white_color_val = 47;
const int black_color_val = 6;
const int colorThreshold = 10;
void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

void back_up()
{
	stopMotors();
	setMotorSync(motorB,motorC, 30, -50);
	sleep(1000);
}
void scanForOpponent(){
	setMotorSync(motorB,motorC, 100, 20);
}
void charge_opponent()
{
	setMotorSync(motorB, motorC, squigglyMotionConstant, 50);
}
task squigglyMotionController()
{
	squigglyMotionConstant = 10;
	while(true){
		squigglyMotionConstant*=(-1);
		sleep(500);
		}
}
/*
task attackPowerController()
{
	while(true)
	{
		if(current_State==Attacking_State){
			Attack_Power+=10;
			sleep(500);
		}
		else
			Attack_Power = 50;
	}
}*/
void attack_opponent()
{
	setMotorSync(motorB, motorC, 0, Attack_Power);
}

task colorSensorTask()
{
	sensorReset(S2);
	while(true)
			colorRead = getColorReflected(S3);
}
task RangeSensorTask()
{
	sensorReset(S4);
	while(true)
		distanceToObstacle = getUSDistance(S4);
}
task gyroRatingReader()
{
	resetGyro(S2);
	while(true)
		rateRead = getGyroRate(S2);
}
task colorStateController()
{
	while(true)
		if(current_State==Scanning_State)
			if(colorRead < (black_color_val + colorThreshold))
				current_State = DetectedEdge_State;
}
task distanceStateController()
{
	while(true)
	{
		if( current_State != DetectedEdge_State )
		{
			if(distanceToObstacle < attack_Dist)
				current_State = Attacking_State;
			else if(distanceToObstacle < max_Dist)
				current_State = Charging_State;
			else
				current_State = Scanning_State;
		}
	}
}
task MotionController()
{
	current_State = Scanning_State;
	while (true)
	{
		switch(current_State){
			case DetectedEdge_State:
				back_up();
				current_State = Scanning_State;
				break;
			case Charging_State:
				charge_opponent();
				break;
			case Attacking_State:
				attack_opponent();
				break;
			default:
				scanForOpponent();
				break;
		}
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Color Read: %d", colorRead);
		displayTextLine(2,"current state: %d", current_State);
		displayTextLine(3,"attack power: %d", Attack_Power);
		displayTextLine(4,"Range to Obstacle: %f", distanceToObstacle);
	}
}
task main()
{
	colorRead = 100;
	startTask(colorSensorTask);
	startTask(gyroRatingReader);
	startTask(RangeSensorTask);
	startTask(displayTask);
	startTask(colorStateController);
	startTask(distanceStateController);
	startTask(squigglyMotionController);
	startTask(attackPowerController);
	startTask(MotionController);
	while(true){
		sleep(1000);
	}
}
