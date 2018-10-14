#pragma config(StandardModel, "EV3_REMBOT")
#define DATALOG_SERIES_0	0
#define DATALOG_SERIES_1	1

int gyroRateReading = 0;
float gyroAvgRate = 0;
const int bufferSize = 5;
int gyroBuffer[bufferSize];

void insertGyroBuffer(int x)
{
	int i;
	for (i = 0; i < bufferSize - 1; i++)
	{
		gyroBuffer[i]=gyroBuffer[i+1];
	}
	gyroBuffer[bufferSize-1]= x;
}

float getGyroAvgRate()
{
	int i;
	float sum;
	for (i = 0; i < bufferSize; i++)
	{
		sum += gyroBuffer[i];
	}
	return (sum/bufferSize);
}

task gyroSensorTask()
{
	while(true)
	{
			gyroRateReading = getGyroRate(S2);
			insertGyroBuffer(gyroRateReading);
			gyroAvgRate = getGyroAvgRate();
			datalogAddValue( DATALOG_SERIES_0, gyroRateReading);
			datalogAddValue( DATALOG_SERIES_1, gyroAvgRate);
			sleep(1000);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Gyro Rate: %d", gyroRateReading);
		displayTextLine(2,"Gyro Average Rate: %f", gyroAvgRate);
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
