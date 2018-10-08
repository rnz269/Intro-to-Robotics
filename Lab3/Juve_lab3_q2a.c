#pragma config(StandardModel, "EV3_REMBOT").

int distanceToObstacle = 0;

task rangeSensorTask()
{
	sensorReset(S4);
	while(true){
	distanceToObstacle=getUSDistance(S4);
}
}
task displayTask()
{
	while(true){
	displayTextLine(3,"Distance to obstacle: %d CM", distanceToObstacle);
}
}
task main()
{
startTask(rangeSensorTask);
startTask(displayTask);
sleep(60000);

}
