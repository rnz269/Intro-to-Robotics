#pragma config(StandardModel, "EV3_REMBOT")

int threshold = 20;
int currentSpeed = 0;
int currentTurnRatio = 0;
int desiredSpeed = 0;
bool alreadyTurning = false;
int colorRead;

bool turnDirection = true; //true is right, false is left

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

void slewMovement(){
	if(desiredSpeed>currentSpeed)
  {
		currentSpeed++;
  }
  else if(desiredSpeed < currentSpeed)
  {
    currentSpeed--;
  }
  setMotorSync(motorB, motorC, currentTurnRatio, currentSpeed);
  sleep(500);
}

void slewMoveForward()
{
	currentTurnRatio=0;
	slewMovement();
}

void activeRightTurn()
{
	currentTurnRatio++;
}
void activeLeftTurn()
{
	currentTurnRatio--;
}

void turnToDirection()
{
	if( turnDirection )
		activeRightTurn();
	else
		activeLeftTurn();
}

task followLine()
{
	while(true)
	{
		if(onLine)
		{
			slewMoveForward();
			alreadyTurning = false;
		}
		else if (!online && !alreadyTurning)
		{
			turnDirection = !turnDirection;
			alreadyTurning = true;
		}
		else
		{
			turnToDirection();
			slewMovement();
			sleep(500);
		}
	}
}
task displayTask()
{
	while(true)
	{
		displayTextLine(2,"Color Read: %d", colorRead);
		displayTextLine(3,"current turn ratio: %d", currentTurnRatio);
		displayTextLine(4,"currentSpeed: %d", currentSpeed);
	}
}

task main()
{
	desiredSpeed = 25;
	startTask(colorSensorTask);
	startTask(followLine);
	startTask(displayTask);
	while(true)
	{
		desiredSpeed += 5;
		sleep(5000);
	}
}
