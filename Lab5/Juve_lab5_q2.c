#pragma config(StandardModel, "EV3_REMBOT")

int threshold = 24;
float turnRatioConstant = -1.75;
float currentTurnRatio = turnRatioConstant;
int currentError;
int colorRead;
int speed = 10;

task colorSensorTask()
{
	while(true)
	{
			colorRead = getColorReflected(S3);
			currentError = (colorRead - threshold);
	}
}

task followLine()
{
	while(true)
	{
		currentTurnRatio = turnRatioConstant * currentError;
		setMotorSync(motorB, motorC, currentTurnRatio, speed);
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(2,"Color Read: %d", colorRead);
		displayTextLine(3,"current turn ratio: %d", currentTurnRatio);
		displayTextLine(4,"current turn error: %d", currentError);
	}
}

task main()
{
	speed = 20;
	startTask(colorSensorTask);
	startTask(followLine);
	startTask(displayTask);
	while(true)
	{
		sleep(2000);
	}
}
