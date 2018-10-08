#pragma config(StandardModel, "EV3_REMBOT").

string touchState;
int bumpedCount;
task touchSensorTask()
{
	resetBumpedValue(S1);
	while(true){
	bumpedCount=getBumpedValue(S1);
	if(getTouchValue(S1) == 1){
		touchState="Pressed";
	}
	else
	{
		touchState="Released";
	}
}
}
task displayTask()
{
	while(true){
	displayTextLine(1,"Touch Sensor state is:");
	displayTextLine(2,"Touch Value: %s", touchState);
	displayTextLine(3,"Bumped Value: %d",bumpedCount);
}
}
task main()
{
startTask(touchSensorTask);
startTask(displayTask);
sleep(30000);

}
