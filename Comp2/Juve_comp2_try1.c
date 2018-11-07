#pragma config(StandardModel, "EV3_REMBOT")


// States
const int Scanning_State = 0;
const int Charging_State = 1;
const int DetectedEdge_State = 2;
const int Defense_State = 3;
const int Attacking_State = 4;
int current_State;

// Sensors
const int max_Dist = 40;
int distanceToObstacle = 0;
int colorRead = 0;

const int white_color_val = 47;
const int black_color_val = 6;


// Motors
int extraTurnPower = 5;
int motorB_Power;
int motorC_Power;


bool noObstacle = true;
bool alreadyTurning = false;
float degreeReading;


void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

task colorSensorTask()
{
	while(true)
		colorRead = getColorReflected(S3);
}

task RangeSensorTask()
{
	sensorReset(S4);
	while(true)
		distanceToObstacle = getUSDistance(S4);
}
void back_up()
{
	stopMotors();
	setMotorSync(motorB,motorC, 100, 100);
	sleep(1000);
}

task gyroDegreeReader()
{
	resetGyro(S2);
	while(true)
		degreeReading = getGyroDegrees(S2);
}

// Write Squiggly Movement
void charge_opponent()
{
	setMotorSync(motorB,motorC, 0, 50);
}
task MotionController()
{
	while (true)
	{
		switch(current_State){
			case Charging_State:
				charge_opponent();
				break;
			case DetectedEdge_State:
				back_up();
				break;
			default:
				charge_opponent();
				//setMotorSync(motorB,motorC, 100, 25);
				break;
		}
	}
}
task StateController()
{
	while (true)
	{
		if( distanceToObstacle < max_Dist)
			current_State = Charging_State;
		else if ( colorRead < (black_color_val + 10))
			current_State = DetectedEdge_State;
		else
			current_State = 0;
	}
}

task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Color Read: %d", colorRead);
		displayTextLine(2,"motor B Power: %d", motorB_Power);
		displayTextLine(3,"motor C Power: %d", motorC_Power);
		displayTextLine(4,"Range to Obstacle: %d", distanceToObstacle);
	}
}

task main()
{
	startTask(MotionController);
	startTask(colorSensorTask);
	startTask(gyroDegreeReader);
	startTask(RangeSensorTask);
	startTask(displayTask);
	startTask(StateController);

	while(true)
	{
		sleep(2000);
	}
}
