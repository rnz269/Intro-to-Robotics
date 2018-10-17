#pragma config(StandardModel, "EV3_REMBOT")

int threshold = 24;
const int choosenTurnRatio = 30;
int currentTurnRatio = choosenTurnRatio;
int colorRead;

bool onLine = false;

task colorSensorTask()
{
	while(true)
	{
			colorRead = getColorReflected(S3);
			if(colorRead < threshold)
			{
				onLine = true;
			}
			else
			{
				onLine = false;
			}
	}
}

task followLine()
{
	int speed = 10;
	while(true)
	{
		if(onLine)
			currentTurnRatio=choosenTurnRatio;
		else
			currentTurnRatio = -(choosenTurnRatio);
		setMotorSync(motorB,motorC,currentTurnRatio,speed);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(2,"Color Read: %d", colorRead);
		displayTextLine(3,"current turn ratio: %d", currentTurnRatio);
	}
}

task main()
{
	//desiredSpeed = 25;
	startTask(colorSensorTask);
	startTask(followLine);
	startTask(displayTask);
	while(true)
	{
		//desiredSpeed += 5;
		sleep(5000);
	}
}
