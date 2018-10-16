#pragma config(StandardModel, "EV3_REMBOT")

int initDegreeReading;
int degreeReading;
float currentDesiredDegree = 0;
int currentDesiredSpeed = 0;
int currentSpeed = 0;
int tolerance = radiansToDegrees(0.2);
task gyroDegreeReader()
{
	while(true)
		degreeReading = (getGyroDegrees(S2) - initDegreeReading) * (-1);
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
void point_Turn_Left(int desiredSpeed, int desiredDegree)
{
	repeatUntil(abs(desiredDegree - degreeReading) < tolerance)
	{
		slewMovement(desiredSpeed, -100);
	}
	stopMotors();
}
void point_Turn_Right(int desiredSpeed, int desiredDegree)
{
	repeatUntil(abs(desiredDegree - degreeReading) < tolerance)
	{
		slewMovement(desiredSpeed, 100);
	}
	stopMotors();
}
void point_Turn(int desiredSpeed, int desiredDegree)
{
	if( desiredDegree < 0 )
		point_Turn_Right(desiredSpeed, abs(desiredDegree));
	else
		point_Turn_Left(desiredSpeed, abs(desiredDegree));
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Gyro Degree: %d", degreeReading);
		displayTextLine(2,"Current Speed: %d", currentSpeed);
		displayTextLine(3,"Gyro init Reading: %d", initDegreeReading);
		displayTextLine(4,"Turn speed %d degree %f rad", currentDesiredSpeed, currentDesiredDegree );
	}
}

task main()
{
	initDegreeReading = getGyroDegrees(S2);
	startTask(gyroDegreeReader);
	startTask(displayTask);
	currentDesiredDegree = -2*(PI)/3;
	currentDesiredSpeed = 30;
	point_Turn(currentDesiredSpeed, (int)radiansToDegrees(currentDesiredDegree));
	sleep(3000);
	initDegreeReading = getGyroDegrees(S2);
	currentDesiredDegree = (PI)/2;
	point_Turn(currentDesiredSpeed, (int)radiansToDegrees(currentDesiredDegree));
	sleep(3000);
	initDegreeReading = getGyroDegrees(S2);
	currentDesiredDegree = -2*(PI)/3;
	currentDesiredSpeed = 60;
	point_Turn(currentDesiredSpeed, (int)radiansToDegrees(currentDesiredDegree));
	sleep(3000);
	initDegreeReading = getGyroDegrees(S2);
	currentDesiredDegree = (PI)/2;
	point_Turn(currentDesiredSpeed, (int)radiansToDegrees(currentDesiredDegree));
	while(true)
	{
		sleep(5000);
	}
}
