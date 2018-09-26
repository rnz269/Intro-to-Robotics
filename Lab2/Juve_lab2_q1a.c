int desiredPower_B;
int currentPower_B;
int desiredPower_C;
int currentPower_C;

task motorBControlTask
{
   while(desiredPower_B-currentPower_B!=0)
   {
     if(desiredPower_B>currentPower_B)
     {
				currentPower_B++;
     }
     else
     {
       	currentPower_B--;
     }
     setMotorSpeed(motorB, currentPower_B);
     sleep(500);
   }
}
task motorCControlTask
{
	while(desiredPower_C-currentPower_C!=0)
   {
     if(desiredPower_C>currentPower_C)
     {
				currentPower_C++;
     }
     else
     {
       	currentPower_C--;
     }
     setMotorSpeed(motorC, currentPower_C);
     sleep(500);
   }
}
float getProgress(int x){
	return (60+x/2);
}
void rctControl(int top, int bottom, int currentProgress, int desired){
	if(desired>0){
		fillRect(60,top,getProgress(currentProgress),bottom);
	}
	else
	{
		fillRect(getProgress(currentProgress),top,60,bottom);
	}
}
task main()
{
	currentPower_B = 0;
	desiredPower_B = 67;
	currentPower_C = 0;
	desiredPower_C = -80;
	drawRect(10,30,110,50);
	drawRect(10,70,110,90);
	float xB = getProgress(desiredPower_B);
	float xC = getProgress(desiredPower_C);
	drawLine(xB,30,xB,50);
	drawLine(xC,70,xC,90);
   startTask(motorBControlTask);
   startTask(motorCControlTask);
   while(true)
   {
     rctControl(30,50,currentPower_B,desiredPower_B);
     rctControl(70,90,currentPower_C,desiredPower_C);
     sleep(500);
   }
}
