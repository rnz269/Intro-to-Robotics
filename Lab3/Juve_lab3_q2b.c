#pragma config(StandardModel, "EV3_REMBOT").

int distanceToObstacle = 0;
int motorBSpeed = 0;
int motorCSpeed = 0;
void stopMotors()
{
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}
task rangeSensorTask()
{
	sensorReset(S4);
	while(true)
	{
		distanceToObstacle=getUSDistance(S4);
	}
}
task displayTask()
{
	while(true){
	displayTextLine(3,"Distance to obstacle: %d CM", distanceToObstacle);
	displayTextLine(4,"MotorB: %d", motorBSpeed);
	displayTextLine(5,"MotorC: %d", motorCSpeed);
}
}
task main()
{
startTask(rangeSensorTask);
startTask(displayTask);
while((distanceToObstacle != 30) && (distanceToObstacle <= 60))
	{
		while( distanceToObstacle>32 )
		{
			//Move the robot forward
			motorBSpeed = 10;
			motorCSpeed = 10;
			setMotorSpeed(motorC, motorCSpeed);
			setMotorSpeed(motorB, motorBSpeed);
		}
		stopMotors();
		while( distanceToObstacle < 28)
		{
			//Move the robot backward
			motorBSpeed = -10;
			motorCSpeed = -10;
			setMotorSpeed(motorC, motorCSpeed);
			setMotorSpeed(motorB, motorBSpeed);
		}
		stopMotors();
	}
sleep(30000);
}
