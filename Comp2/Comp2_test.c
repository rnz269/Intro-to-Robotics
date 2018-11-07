#pragma config(StandardModel, "EV3_REMBOT")


float distanceToObstacle = 0;
float rateRead = 0;
int colorRead = 0;
void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
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
	}
}
task gyroRatingReader()
{
	resetGyro(S2);
	while(true)
		rateRead = getGyroRate(S2);
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Color Read: %d", colorRead);
		//displayTextLine(2,"motor B Power: %f", motorB_Power);
		displayTextLine(3,"Gyro rate: %f", rateRead);
		displayTextLine(4,"Range to Obstacle: %f", distanceToObstacle);
	}
}
task main()
{
	startTask(displayTask);
	startTask(gyroRatingReader);
	startTask(RangeSensorTask);
	startTask(colorSensorTask);
	int speed = 50;
	//int direction = 50;
	while(true){
		sleep(7000);
		//stopMotors();
		//setMotorSync(motorB,motorC, direction, speed);
		//direction = -direction;
	}
}
