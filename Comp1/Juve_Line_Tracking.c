#pragma config(StandardModel, "EV3_REMBOT")
#define DATALOG_SERIES_0	0
#define DATALOG_SERIES_1	1
const float power_Constant = 0.4;
float motorB_Power;
float motorC_Power;
int colorRead;
const int white_color_val = 68;
const int black_color_val = 6;

task colorSensorTask()
{
	while(true)
	{
			colorRead = getColorReflected(S3);
			datalogAddValue( DATALOG_SERIES_0, motorB_Power);
			datalogAddValue( DATALOG_SERIES_1, motorC_Power);
	}
}

task motorBController()
{
	while(true)
	{
		motorB_Power = (white_color_val - colorRead)* power_Constant;
		setMotorSpeed(motorB, motorB_Power);
	}
}
task motorCController()
{
	while(true)
	{
		motorC_Power = (colorRead - black_color_val)* power_Constant;
		setMotorSpeed(motorC, motorC_Power);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(1,"Color Read: %d", colorRead);
		displayTextLine(2,"motor B Power: %f", motorB_Power);
		displayTextLine(3,"motor C Power: %f", motorC_Power);
	}
}

task main()
{
	startTask(colorSensorTask);
	startTask(motorBController);
	startTask(motorCController);
	startTask(displayTask);
	while(true)
	{
		sleep(2000);
	}
}
