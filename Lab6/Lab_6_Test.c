#pragma config(StandardModel, "EV3_REMBOT")

int distanceToObstacle = 0;
bool alreadyTurning = false;
float degreeReading;
bool noObstacle = true;
float tolerance = radiansToDegrees(0.1);

float get_time(float d)
{
	d = d * 1200;
	d = d / 11;
	return d;
}

task RangeSensorTask()
{
	sensorReset(S4);
	while(true)
	{
		distanceToObstacle = getUSDistance(S4);
		noObstacle = (distanceToObstacle > 10);
	}
}

task gyroDegreeReader()
{
	resetGyro(S2);
	while(true)
		degreeReading = getGyroDegrees(S2);
}

void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

void point_Turn_Left(int desiredSpeed, float desiredDegree)
{
	repeatUntil(abs(degreeReading - tolerance) > desiredDegree)
	{
		setMotorSync(motorB,motorC, -100,desiredSpeed);
	}
	stopMotors();
}

void point_Turn_Right(int desiredSpeed, float desiredDegree)
{
	repeatUntil(abs(degreeReading + tolerance) > desiredDegree)
	{
		setMotorSync(motorB,motorC, 100, desiredSpeed);
	}
	stopMotors();
}

void point_Turn(int desiredSpeed, float desiredDegree)
{
	resetGyro(S2);
	if( desiredDegree < 0 )
		point_Turn_Right(desiredSpeed, abs(desiredDegree));
	else
		point_Turn_Left(desiredSpeed, abs(desiredDegree));
}

void move_Forward(int desiredSpeed, int distance)
{
	float t = get_time(distance);
	setMotorSync(motorB,motorC,0,25);
	sleep(t);
}

void TurnAroundObstacle()
{
	alreadyTurning = true;
	displayTextLine(2,"First Turn");
	point_Turn(25, 90);
	displayTextLine(2,"Moving Forward");
	move_Forward(50, 20);
	displayTextLine(2,"Second Turn");
	point_Turn(25, -90);
	displayTextLine(2,"Moving Forward");
	move_Forward(50, 25);
	displayTextLine(2,"Third Turn");
	point_Turn(25, -90);
	displayTextLine(2,"Moving Forward");
	move_Forward(50, 20);
	displayTextLine(2,"Forth Turn");
	point_Turn(25, 90);
	displayTextLine(2,"Moving Forward");
	alreadyTurning = false;
}

task displayTask()
{
	while(true)
	{
		displayTextLine(4,"Range to Obstacle: %d", distanceToObstacle);
		displayTextLine(5,"degreeReading: %d", degreeReading);
	}
}
task motionController()
{
	while(true)
	{
		if(noObstacle && (!alreadyTurning))
		{
			setMotorSync(motorB,motorC,0,25);
		}
		else if (!alreadyTurning)
		{
			stopMotors();
			TurnAroundObstacle();
			//waitUntil(!alreadyTurning);
		}
		else
			displayTextLine(3,"Waiting");
	}
}
task main()
{
	startTask(motionController);
	startTask(RangeSensorTask);
	startTask(gyroDegreeReader);
	startTask(displayTask);
	while(true)
	{
		sleep(2000);
	}
}
