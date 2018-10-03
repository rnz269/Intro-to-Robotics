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
				if(currentPositionRight+velocityX>xLimit){
					velocityX*=(-1);
					soundFlag = true;
					currentPositionRight = xLimit;
				}
				else{
					updateBallPosition(velocityX,0);
				}
			}
			else if (velocityX < 0)
			{
				if(currentPositionLeft+velocityX<0){
					velocityX*=(-1);
					soundFlag = true;
					currentPositionRight = 0;
				}
				else{
					updateBallPosition(velocityX,0);
				}
			}

			if (velocityY > 0)
			{
				if(currentPositionTop+velocityY>yLimit){
					velocityY*=(-1);
					soundFlag = true;
					currentPositionTop = yLimit;
				}
				else{
					updateBallPosition(0,velocityY);
				}
			}
			else if (velocityY < 0)
			{
				if(currentPositionBottom+velocityY<0){
					velocityY*=(-1);
					soundFlag = true;
					currentPositionBottom = 0;
				}
				else{
					updateBallPosition(0,velocityY);
				}
			}

		drawEllipse( currentPositionLeft , currentPositionTop , currentPositionRight, currentPositionBottom);
	}
}


task main()
{
	width = 20;
	height = 20;\
	// generate random starting ellipse coordinates, ensuring all four dimensions always within 177 x 127 grid
	currentPositionLeft = abs(rand()%(xLimit-width+1));
	currentPositionBottom = abs(rand()%(yLimit-height+1));
	velocityX = (abs(rand())%7) - 3;
	velocityY = (abs(rand())%7) - 3;
	updateBallPosition(0,0);

	drawEllipse( currentPositionLeft , currentPositionTop , currentPositionRight, currentPositionBottom);

	startTask(moveEllipse);
	sleep(60000);
}
