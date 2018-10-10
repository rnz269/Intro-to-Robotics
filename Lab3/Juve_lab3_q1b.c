#pragma config(StandardModel, "EV3_REMBOT").

string touchState;
int bumpedCount;
bool direction=false;
void pivot_turn_left(float s, int t){
	setMotorSpeed(motorB, -s);
	setMotorSpeed(motorC, s);
	sleep(t);
}
void pivot_turn_right(float s, int t){
	setMotorSpeed(motorB, s);
	setMotorSpeed(motorC, -s);
	sleep(t);
}
void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}
void turnAtBump(){
	if(direction){
		pivot_turn_right(12.5,6000);
	}
	else{
		pivot_turn_left(12.5,6000);
	}
	stopMotors();
	direction = !direction;
	resetBumpedValue(S1);
}
task touchSensorTask()
{
	resetBumpedValue(S1);
	while(true){
	bumpedCount=getBumpedValue(S1);
	if(bumpedCount>0){
		turnAtBump();
	}
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
sleep(60000);

}
