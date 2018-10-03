// Motor vars
int desiredPower_B;
int currentPower_B;
int desiredPower_C;
int currentPower_C;
int motorPowerLevel;

//// screen dimension limits
int xLimit = 177;
int yLimit = 127;

int velocityX;
int velocityY;

// Ellipse dimensions
int width;
int height;

//Position
int currentPositionBottom;
int currentPositionLeft;
int currentPositionRight;
int currentPositionTop;


void updateBallPosition(int x, int y){
		currentPositionLeft += x;
		currentPositionBottom += y;
		currentPositionRight = currentPositionLeft + width;
		currentPositionTop = currentPositionBottom + height;
		displayTextLine(1,"Left: %d Bottom: %d",currentPositionLeft,currentPositionBottom);
		displayTextLine(2,"Top: %d Right: %d",currentPositionTop,currentPositionRight);
}

void stopMotors(){
	currentPower_B = 0;
	currentPower_C = 0;
}

// set up flags
bool soundFlag = false;

// TASKS
task moveEllipse
{
	while(true){
		if(soundFlag){
			playSound(soundBlip);
			soundFlag = false;
		}

		displayTextLine(3,"x: %d y: %d",velocityX,velocityY);
		sleep(3000);
		eraseEllipse( currentPositionLeft , currentPositionTop , currentPositionRight, currentPositionBottom);
			if (velocityX > 0)
			{
				// ball hits right side
				if(currentPositionRight+velocityX>xLimit){
					velocityX*=(-1);
					soundFlag = true;
					currentPositionRight = xLimit;
					desiredPower_B = motorPowerLevel;
					desiredPower_C = -1 * motorPowerLevel;
					// sleep for a designated amount of time
					//sleep(5000);
					// stop the motors
					//stopMotors();
				}
				else{
					updateBallPosition(velocityX,0);
				}
			}
			// hit left side
			else if (velocityX < 0)
			{
				if(currentPositionLeft+velocityX<0){
					velocityX*=(-1);
					soundFlag = true;
					currentPositionRight = 0;
					desiredPower_B = -1 * motorPowerLevel;
					desiredPower_C = motorPowerLevel;
					// sleep for a designated amount of time
					
					// stop the motors
					//stopMotors();
				}
				else{
					updateBallPosition(velocityX,0);
				}
				
			}

			// hit top side
			if (velocityY > 0)
			{
				if(currentPositionTop+velocityY>yLimit){
					velocityY*=(-1);
					soundFlag = true;
					currentPositionTop = yLimit;
					desiredPower_B = motorPowerLevel;
					desiredPower_C = motorPowerLevel;
					// sleep for a designated amount of time
					// stop the motors
					//stopMotors();
				}
				else{
					updateBallPosition(0,velocityY);
				}
			}
			// hit bottom side
			else if (velocityY < 0)
			{
				if(currentPositionBottom+velocityY<0){
					velocityY*=(-1);
					soundFlag = true;
					currentPositionBottom = 0;
					desiredPower_B = -1 * motorPowerLevel;
					desiredPower_C = -1 * motorPowerLevel;
					// sleep for a designated amount of time
					//sleep(5000);
					// stop the motors
					//stopMotors();
				}
				else{
					updateBallPosition(0,velocityY);
				}
			}
		drawEllipse(currentPositionLeft , currentPositionTop , currentPositionRight, currentPositionBottom);
		//sleep(500);
		stopMotors();
	}
}
task motorBControlTask
{
   while(true)
   {
     if(desiredPower_B>currentPower_B)
     {
				currentPower_B++;
     }
     else if(desiredPower_B<currentPower_B)
     {
       	currentPower_B--;
     }
     setMotorSpeed(motorB, currentPower_B);
     sleep(100);
   }
}
task motorCControlTask
{
	while(true)
   {
     if(desiredPower_C>currentPower_C)
     {
				currentPower_C++;
     }
     else if(desiredPower_C<currentPower_C)
     {
       	currentPower_C--;
     }
     setMotorSpeed(motorC, currentPower_C);
     sleep(100);
   }
}


task main()
{
	width = 20;
	height = 20;\
	// generate random starting ellipse coordinates, ensuring all four dimensions always within 177 x 127 grid
	currentPositionLeft = abs(rand()%(xLimit-width+1));
	currentPositionBottom = abs(rand()%(yLimit-height+1));
	velocityX = (abs(rand())%20) - 10;
	velocityY = (abs(rand())%20) - 10;
	motorPowerLevel = sqrt((velocityX)*(velocityX) + (velocityY) * (velocityY))*10;
	updateBallPosition(0,0);

	drawEllipse( currentPositionLeft , currentPositionTop , currentPositionRight, currentPositionBottom);

	startTask(moveEllipse);
	sleep(60000);
	
	startTask(motorBControlTask);
  startTask(motorCControlTask);


	// Initial Velocities + set desired powers
	currentPower_B = 0;
	currentPower_C = 0;
	// newVelocity();

	// Start Motors
  startTask(motorBControlTask);
  startTask(motorCControlTask);

	startTask(moveEllipse);
	sleep(60000);
}
