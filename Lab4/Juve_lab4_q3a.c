#pragma config(StandardModel, "EV3_REMBOT")
#define DATALOG_SERIES_0	0
#define DATALOG_SERIES_1	1
#define DATALOG_SERIES_2	2

int gyroHeadingReading = 0;
float initGyroRad = 0;
int gyroRateReading = 0;
float gyroRadReading = 0;

task gyroSensorTask()
{
	initGyroRad = degreesToRadians(getGyroDegrees(S2));
	while(true)
	{
			gyroHeadingReading = getGyroHeading(S2) * (-1);
			gyroRadReading = degreesToRadians(getGyroDegrees(S2)) - initGyroRad;
			gyroRateReading = getGyroRate(S2);
			datalogAddValue( DATALOG_SERIES_0, gyroRateReading);
			datalogAddValue( DATALOG_SERIES_1, gyroHeadingReading);
			datalogAddValue( DATALOG_SERIES_2, gyroRadReading);
			sleep(1000);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Gyro Heading: %d", gyroHeadingReading);
		displayTextLine(2,"Gyro Rad: %f", gyroRadReading);
		displayTextLine(3,"Gyro init rad: %f", initGyroRad);
		displayTextLine(4,"Gyro Rate: %d",gyroRateReading);
	}
}
task main()
{
	startTask(gyroSensorTask);
	startTask(displayTask);
	while(true)
	{
		sleep(5000);
	}
}
