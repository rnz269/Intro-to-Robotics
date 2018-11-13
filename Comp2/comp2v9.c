#pragma config(StandardModel, "EV3_REMBOT")


// States
const int Scanning_State = 0;
const int Charging_State = 1;
const int Defense_State = 2;
const int DetectedEdge_State = 3;
const int Attacking_State = 4;
int current_State;


int bumped_from_where;
const int bumped_from_back = 5;
const int bumped_from_side = 6;

// set to 80 at comp time
const int max_Dist = 60;
int distanceToObstacle;
const int attack_Dist = 25;
int colorRead = 0;
int bumpedCount = 0;

// const int white_color_val = 85;
const int black_color_val = 6;
const int colorThreshold = 15;


// Motors
int motorBPower;
int motorCPower;
int motorSyncPower;

bool prepareForContact = false;
bool bumped = false;

float degreeReading;
float degreeReadingTimeOne;
float degreeReadingTimeTwo;
const float degreeGapThreshold = 70;


// FUNCTIONS
void stopMotors()
{
		setMotorSpeed(motorB, 0);
		setMotorSpeed(motorC, 0);
}


void sweeping_and_searching()
{
// set back to 25, -25
		motorBPower = 25;
		motorCPower = -25;
		setMotorSpeed(motorB, motorBPower);
		setMotorSpeed(motorC, motorCPower);
}

// At edge detected state
void back_up()
{
	stopMotors();
	setMotorSync(motorB,motorC, 30, -50);
	sleep(1000);
}

void charge_opponent()
{
	// insert zig zaggy motion to stay on target
	motorSyncPower = 35;
	setMotorSync(motorB, motorC,0, motorSyncPower);
}

void attack_opponent()
{
	motorBPower = 100;
	motorCPower = 100;
	setMotorSpeed(motorB, motorBPower);
	setMotorSpeed(motorC, motorCPower);
}

// evasive mechanism. bumped from back.
void run_away()
{
	switch(bumped_from_where)
	{
		case bumped_from_back:
			// bumped from back. perform 270 degree circular turn left to put in offensive position
		  // if our touch sensor is hit
			// reset bumped variable to false after ran away
			motorBPower = 80;
			motorCPower = 80;
			setMotorSpeed(motorB, motorBPower);
			setMotorSpeed(motorC, motorCPower);
			sleep(700);
			setMotorSync(motorB, motorC, 100, 100);
			// CHECK THIS SLEEP IN CLASS TO MAKE SURE IT'S SUFFICIENT FOR FULL 360 DEGREE TURN
			sleep(600);
			bumped = false;
			break;

		case bumped_from_side:
			// bumped from left or right. perform 180 degree circular turn left to put in offensive position
			// reset bumped variable to false after ran away
			motorBPower = 80;
			motorCPower = 80;
			setMotorSpeed(motorB, motorBPower);
			setMotorSpeed(motorC, motorCPower);
			sleep(700);
			setMotorSync(motorB, motorC, 100, 100);
			// CHECK THIS SLEEP IN CLASS TO MAKE SURE IT'S SUFFICIENT FOR FULL 360 DEGREE TURN
			sleep(600);
			bumped = false;
			break;
	}
}

// TASKS

//SENSOR TASKS

// COLOR SENSOR
task colorSensorTask()
{
	while(true)
		colorRead = getColorReflected(S3);
}


// GYRO SENSOR
task gyroDegreeReader()
{
	resetGyro(S2);
	while(true)
		degreeReading = getGyroDegrees(S2);
}

// RANGE SENSOR
task RangeSensorTask()
{
	sensorReset(S4);
	while(true)
	{
		distanceToObstacle = getUSDistance(S4);
	}
}


// touch sensor task
task touchSensorTask()
{
	resetBumpedValue(S1);
	bumpedCount = 0;
	while(true)
	{
		int newBumpedCount = getBumpedValue(S1);
		if(newBumpedCount>bumpedCount)
		{
			bumpedCount = newBumpedCount;
			bumped = true;
			bumped_from_where = bumped_from_back;
			sleep(1000);
		}
	}
}


task checkIfHitTask()
{
	while(true)
	{
		if(current_State == Scanning_State)
		{
			// record gyro orientation
			// sleep 2.5 seconds
			// record gyro orientation again
			// if difference is less than 20, then we're stuck. execute evasive mechanism
			degreeReadingTimeOne = degreeReading;
			sleep(2500);
			degreeReadingTimeTwo = degreeReading;
			if (degreeReadingTimeTwo - degreeReadingTimeOne < degreeGapThreshold)
			{
				bumped_from_where = bumped_from_side;
				bumped = true;
			}
		}
	}
}


task colorStateController()
{
	while(true)
		// If the current state is charging or scanning and found edge change to state detected edge
		if(current_State < 3)
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
			else if(bumped)
				current_State = Defense_State;
			else
				current_State = Scanning_State;
		}
	}
}



// Maps states to functions
task MotionController()
{
	while (true)
	{
		switch(current_State){

			case Charging_State:
				charge_opponent();
				break;

			case Attacking_State:
				attack_opponent();
				break;

			case DetectedEdge_State:
				back_up();
				current_State = Scanning_State;
				break;

			case Defense_State:
				run_away();
				break;

			default:
				sweeping_and_searching();
				break;
		}
	}
}





// Displays relevant information on ev3 screen
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Current state: %d", current_State);
		displayTextLine(2,"Range to Obstacle: %d", distanceToObstacle);
		displayTextLine(3,"Color Read: %d", colorRead);
		displayTextLine(4,"Current gyro reading: %f", degreeReading);
		displayTextLine(5, "Current Bumped Count: %d", bumpedCount);
		displayTextLine(6, "Current Motor B Value: %d", motorBPower);
		displayTextLine(7, "Current Motor C Value: %d", motorCPower);
		displayTextLine(8, "Current Motor Sync Value: %d", motorSyncPower);
	}
}




task main()
{
	startTask(displayTask);
	startTask(colorSensorTask);
	startTask(gyroDegreeReader);
	startTask(RangeSensorTask);
	startTask(touchSensorTask);
	startTask(checkIfHitTask);
	startTask(colorStateController);
	startTask(distanceStateController);
	startTask(MotionController);

	while(true)
	{
		sleep(2000);
	}
}
