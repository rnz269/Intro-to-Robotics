#pragma config(StandardModel, "EV3_REMBOT")


bool foundLowest = false;
bool direction;
int desiredSpeed = 5;
float distanceToObstacle = 250;
//float threshold = 0.3;
float tempLow;
float GetOneDecimalFloat( float dist )
{
	return ((float)((int)(dist * 10))) / 10;
}

void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

task DistanceFunction()
{
	sensorReset(S4);
	tempLow = GetOneDecimalFloat(getUSDistance(S4));
	while (!foundLowest)
	{
		sleep(500);
		distanceToObstacle = GetOneDecimalFloat(getUSDistance(S4));
		if(distanceToObstacle == tempLow)
		{
				stopMotors();
				foundLowest = true;
				displayTextLine(2, "Success");
		}
		else if(distanceToObstacle < tempLow)
		{
			tempLow = distanceToObstacle;
		}
		else
			direction = !direction;
	}
}
task TurnController()
{
	while (!foundLowest)
	{
		if(direction)
			setMotorSync(motorB,motorC, -100,desiredSpeed);
		else
			setMotorSync(motorB,motorC, 100,desiredSpeed);
	}
	stopMotors();
}

task displayTask()
{
	while(true)
	{
		displayTextLine(3,"Lowest: %f", tempLow);
		displayTextLine(4,"distanceToObstacle: %f", distanceToObstacle);
	}
}

task main()
{
	startTask(TurnController);
	startTask(DistanceFunction);
	startTask(displayTask);
	while(true)
	{
		sleep(2000);
	}
}
