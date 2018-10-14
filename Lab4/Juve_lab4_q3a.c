#pragma config(StandardModel, "EV3_REMBOT").

int gyroHeadingReading = 0;
int gyroDegreesReading = 0;
int gyroRateReading = 0;

task gyroSensorTask()
{
	while(true)
	{
			gyroHeadingReading = getGyroHeading(S2);
			gyroDegreesReading = getGyroDegrees(S2);
			gyroRateReading = getGyroRate(S2);
			sleep(1000);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Gyro Heading: %d", gyroHeadingReading);
		displayTextLine(2,"Gyro Degrees: %d", gyroDegreesReading);
		displayTextLine(3,"Gyro Rate: %d",gyroRateReading);
	}
}
task main()
{
	startTask(gyroSensorTask);
	startTask(displayTask);
	int speed = 10;
	while(true)
	{
		setMotorSync(motorB,motorC,50,speed);
		sleep(5000);
		speed *= (-1);
	}
}
