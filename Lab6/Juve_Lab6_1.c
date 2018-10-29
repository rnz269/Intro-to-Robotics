#pragma config(StandardModel, "EV3_REMBOT")

const float power_Constant = 0.4;
float motorB_Power;
float motorC_Power;
int colorRead;
const int white_color_val = 44;
const int black_color_val = 6;
int distanceToObstacle = 0;
bool noObstacle = true;
bool alreadyTurning = false;
float degreeReading;
float tolerance = radiansToDegrees(0.1);
float get_time(float d)
{
	d = d * 1200;
	d = d / 11;
	return d;
}

task colorSensorTask()
{
	while(true)
	{
			colorRead = getColorReflected(S3);
	}
}

task RangeSensorTask()
{
	sensorReset(S4);
	while(true)
	{
		distanceToObstacle = getUSDistance(S4);
		noObstacle = (distanceToObstacle > 8) || (distanceToObstacle < 1);
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
	stopMotors();
	alreadyTurning = true;
	point_Turn(25, 90);
	move_Forward(50, 12);
	point_Turn(25, -90);
	move_Forward(50, 12);
	point_Turn(25, -45);
	move_Forward(50, 12);
	//point_Turn(25, 90);
	//sleep(1000);
	alreadyTurning = false;
}

void ColorSpeedFunction()
{
	motorB_Power = (white_color_val - colorRead)* power_Constant;
	motorC_Power = (colorRead - black_color_val)* power_Constant;
	setMotorSpeed(motorB, motorB_Power);
	setMotorSpeed(motorC, motorC_Power);
}

task motionController()
{
	while(true)
	{
		if(noObstacle && (!alreadyTurning))
		{
			ColorSpeedFunction();
		}
		else if (!alreadyTurning)
		{
			TurnAroundObstacle();
		}
	}
}

task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Color Read: %d", colorRead);
		displayTextLine(2,"motor B Power: %f", motorB_Power);
		displayTextLine(3,"motor C Power: %f", motorC_Power);
		displayTextLine(4,"Range to Obstacle: %d", distanceToObstacle);
	}
}

task main()
{
	startTask(motionController);
	startTask(colorSensorTask);
	startTask(gyroDegreeReader);
	startTask(RangeSensorTask);
	startTask(displayTask);
	while(true)
	{
		sleep(2000);
	}
}
