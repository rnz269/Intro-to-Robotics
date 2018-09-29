// Motor vars
int desiredPower_B;
int currentPower_B;
int desiredPower_C;
int currentPower_C;

// screen dimension limits
int xLimit = 177;
int yLimit = 127;

// set up flags
bool soundFlag = false;

// Velocities
int velocityX;
int velocityY;

// Ellipse dimensions
int width;
int height;

// Position
int currentPositionBottom;
int currentPositionLeft;
int currentPositionRight;
int currentPositionTop;

// Update Position
void updateBallPosition(int x, int y){
		currentPositionLeft += x;
		currentPositionBottom += y;
		currentPositionRight = currentPositionLeft + width;
		currentPositionTop = currentPositionBottom + height;
}

// Update Power
void updateMotorPower(){
	desiredPower_B = sqrt(velocityX*velocityX+velocityY*velocityY);
	desiredPower_C = sqrt(velocityX*velocityX+velocityY*velocityY);
}

void newVelocity(){
		velocityX = rand()%20;
		velocityY = rand()%20;
		updateMotorPower();
}
void stopMotors(){
	currentPower_B = 0;
	currentPower_C = 0;
}

// TASKS
task moveEllipse
{
	while(true){
		if(soundFlag){
			playSound(soundBlip);
			soundFlag = false;
		}
		displayTextLine(3,"x: %d y: %d",desiredPower_B,desiredPower_C);
		sleep(5000);
		eraseEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);
		while(velocityX!=0){
			if (velocityX > 0)
			{
				if(currentPositionRight+1>xLimit){
					velocityX*=(-1);
					soundFlag = true;
					stopMotors();
				}
				else{
					updateBallPosition(1,0);
					velocityX+=(-1);
				}
			}
			else if (velocityX < 0)
			{
				if(currentPositionLeft-1<0){
					velocityX*=(-1);
					soundFlag = true;
					stopMotors();
				}
				else{
					updateBallPosition(-1,0);
					velocityX+=1;
				}
			}
			sleep(100);
		}
		while(velocityY!=0){
			if (velocityY > 0)
			{
				if(currentPositionTop+1>yLimit){
					velocityY*=(-1);
					soundFlag = true;
				}
				else{
					updateBallPosition(0,1);
					velocityY+=(-1);
				}
			}
			else if (velocityY < 0)
			{
				if(currentPositionBottom-1<0){
					velocityY*=(-1);
					soundFlag = true;
				}
				else{
					updateBallPosition(0,-1);
					velocityY+=1;
				}
			}
			updateMotorPower();
			sleep(100);
		}
		drawEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);
		newVelocity();
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
	// Set Ball size
	width = 20;
	height = 20;

	// generate random starting ellipse coordinates, ensuring all four dimensions always within 177 x 127 grid
	currentPositionLeft = abs(rand()%(xLimit-width+1));
	currentPositionBottom = abs(rand()%(yLimit-height+1));
	updateBallPosition(0,0);

	// Start Motors
  startTask(motorBControlTask);
  startTask(motorCControlTask);

	// generate random starting ellipse coordinates, ensuring all four dimensions always within 177 x 127 grid
	currentPositionLeft = abs(rand()%(xLimit-width+1));
	currentPositionBottom = abs(rand()%(yLimit-height+1));
	updateBallPosition(0,0);

	drawEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);

	// Initial Velocities + set desired powers
	currentPower_B = 0;
	currentPower_C = 0;
	newVelocity();

	// Start Motors
  startTask(motorBControlTask);
  startTask(motorCControlTask);

	startTask(moveEllipse);
	sleep(60000);
}
