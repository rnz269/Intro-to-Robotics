#pragma config(StandardModel, "EV3_REMBOT").

int speed = 10;
bool withinLines = true;
bool onLine = true;
task colorSensorTask()
{
	while(true)
	{
			int colorRead = getColorReflected(S3);
			if(colorRead<10)
			{
				onLine = true;
				withinLines = false;
			}
			else
			{
				onLine = false;
				withinLines = true;
			}
	}
}

task main()
{
	startTask(colorSensorTask);
	while(true)
	{
		while(withinLines)
		{
			setMotorSync(motorB,motorC,0,speed);
		}
		setMotorSync(motorB,motorC,0,0);
		speed *= (-1);
		while(onLine)
		{
			setMotorSync(motorB,motorC,0,speed);
		}
	}
}
