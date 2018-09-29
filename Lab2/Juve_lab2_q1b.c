int desiredPower_B;
int currentPower_B;
int desiredPower_C;
int currentPower_C;

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
	currentPower_B = 0;
	desiredPower_B = 67;
	currentPower_C = 0;
	desiredPower_C = -80;
  startTask(motorBControlTask);
  startTask(motorCControlTask);
   while(true)
   {
     displayBigTextLine(3,"MotorB:%d/%d",currentPower_B,desiredPower_B);
   	 displayBigTextLine(5,"MotorC:%d/%d",currentPower_C,desiredPower_C);
     sleep(500);
   }
}
