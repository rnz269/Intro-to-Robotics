#pragma config(StandardModel, "EV3_REMBOT")

float turnsRecord[5];
int colorRead;
const int white_color_val = 45;
//const int black_color_val = 6;
bool turning = false;
int speed = 50;
int currentTurnNum = 0;
float degreeReading;
int currentSpeed = 0;
float tolerance = radiansToDegrees(0.1);
int threshold = 5;
task gyroDegreeReader()
{
	while(true)
		degreeReading = getGyroDegrees(S2);
}

void slewMovement(int desiredSpeed, int speedRatio){
	if(desiredSpeed>currentSpeed)
     {
				currentSpeed++;
     }
     else
     {
       	currentSpeed--;
     }
     setMotorSync(motorB, motorC, speedRatio, currentSpeed);
     sleep(500);
}
void stopMotors()
{
	currentSpeed = 0;
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}
void point_Turn_Left(int desiredSpeed, float desiredDegree)
{
	repeatUntil(abs(degreeReading - tolerance) > desiredDegree)
	{
		slewMovement(desiredSpeed, -100);
	}
	stopMotors();
}
void point_Turn_Right(int desiredSpeed, float desiredDegree)
{
	repeatUntil(abs(degreeReading - tolerance) > desiredDegree)
	{
		slewMovement(desiredSpeed, 100);
	}
	stopMotors();
}
void point_Turn(int desiredSpeed, float desiredDegree)
{
	if( desiredDegree < 0 )
		point_Turn_Right(desiredSpeed, abs(desiredDegree));
	else
		point_Turn_Left(desiredSpeed, abs(desiredDegree));
	resetGyro(S2);
}

task colorSensorTask()
{
	while(true)
	{
			colorRead = getColorReflected(S3);
			if(colorRead > (white_color_val-threshold))
				turning = true;
			else
				turning = false;
	}
}
void moveBack()
{
	setMotorSync(motorB,motorC,0,-25);
	sleep(500);
	stopMotors();
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Gyro Degree: %d", degreeReading);
		displayTextLine(2,"Current Speed: %d", currentSpeed);
		displayTextLine(3,"cuurent Turn Degree: %d", turnsRecord[currentTurnNum]);
		displayTextLine(4,"state:", turning ? "Turning" : "Forward" );
		displayTextLine(5,"Color Read: %d", colorRead);

	}
}
task movementController()
{
	while(true)
		{
			if(turning){
				stopMotors();
				resetGyro(S2);
				if(currentTurnNum>=5)
					currentTurnNum = 0;
				moveBack();
				point_Turn(speed, turnsRecord[currentTurnNum]);
				currentTurnNum++;
			}
			else
			{
				setMotorSync(motorB,motorC,0,speed);
			}
	}
}


task main()
{
	resetGyro(S2);
	startTask(gyroDegreeReader);
	startTask(colorSensorTask);
	startTask(displayTask);
	startTask(movementController);
	turnsRecord[0] = 90;
	turnsRecord[1] = 120;
	turnsRecord[2] = -30;
	turnsRecord[3] = 120;
	turnsRecord[4] = 90;
	while(true)
	{
		sleep(2000);
	}
}
