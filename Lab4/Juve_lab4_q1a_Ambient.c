#pragma config(StandardModel, "EV3_REMBOT").

string colorSensorState = "waiting";
string colorSensorMode = "Not Started";
int colorMode = 0;
int bumpedCount = 0;
bool useColorSensor = false;
int colorRead = 0;
long redValue = 0;
long blueValue = 0;
long greenValue = 0;

task touchSensorTask()
{
	resetBumpedValue(S1);
	bumpedCount = 0;
	while(true)
	{
		int newBumpedCount = getBumpedValue(S1);
		if(newBumpedCount>bumpedCount)
		{
			useColorSensor = !(useColorSensor);
			bumpedCount = newBumpedCount;
		}
	}
}
task colorSensorTask()
{
	while(true)
	{
		if(useColorSensor)
		{
			colorSensorState="Reading";
			switch(colorMode)
			{
				case 1:
					colorSensorMode="Ambient";
					colorSensorState="Reading";
					colorRead=getColorAmbient(S3);
					break;
				case 2:
					colorSensorMode="Reflected";
					colorSensorState="Reading";
					colorRead=getColorReflected(S3);
					break;
				case 3:
					colorSensorMode="Name";
					colorSensorState="Reading";
					colorRead=getColorName(S3);
					break;
				case 4:
					colorSensorMode="RGB";
					colorSensorState="Reading";
					getColorRGB(S3, redValue, greenValue, blueValue);
					break;
				default:
					colorSensorMode="NA";
					colorSensorState="NA";
					colorRead=0;
					break;
			}
		}
		else
		{
			colorSensorState="Waiting";
			colorRead=0;
			colorSensorMode="off";
		}
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(2,"Color Sensor State: %s", colorSensorState);
		displayTextLine(3,"Sensor Mode: %s", colorSensorMode);
		displayTextLine(4,"Bumped Value: %d", bumpedCount);
		if(colorSensorMode=="RGB")
		{
			displayTextLine(5,"Colors Detected: %d, %d, %d", redValue, greenValue, blueValue);
		}
		else
		{
			displayTextLine(5,"Color Read: %d", colorRead);
		}
	}
}
task main()
{
	colorMode=1;
	startTask(touchSensorTask);
	startTask(colorSensorTask);
	startTask(displayTask);
	while(true)
	{
		sleep(1000);
	}
}
