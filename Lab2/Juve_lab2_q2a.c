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
		velocityX = rand()%4;
		velocityY = rand()%4;
		displayTextLine(3,"x: %d y: %d",velocityX,velocityY);
		sleep(3000);
		eraseEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);
		while(velocityX!=0){
			if (velocityX > 0)
			{
				if(currentPositionRight+1>xLimit){
					velocityX*=(-1);
					soundFlag = true;
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
				}
				else{
					updateBallPosition(-1,0);
					velocityX+=1;
				}
			}
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
		}
		drawEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);
	}
}


task main()
{
	width = 20;
	height = 20;\
	// generate random starting ellipse coordinates, ensuring all four dimensions always within 177 x 127 grid
	currentPositionLeft = abs(rand()%(xLimit-width+1));
	currentPositionBottom = abs(rand()%(yLimit-height+1));
	updateBallPosition(0,0);

	drawEllipse( currentPositionLeft , currentPositionBottom , currentPositionRight, currentPositionTop);

	startTask(moveEllipse);
	sleep(60000);
}
