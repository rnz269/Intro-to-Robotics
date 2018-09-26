
task main()
{
	int i;
	int temp;
	int f0=0;
	int f1=1;
	displayCenteredBigTextLine(2,"%d",f0);
	sleep(1000);
	displayCenteredBigTextLine(2,"%d",f1);
	for(i=0; i<19; i++)
	{
		sleep(1000);
		temp=f0+f1;
		f0=f1;
		f1=temp;
		displayCenteredBigTextLine(2,"%d",temp);
	}
	sleep(5000);
}
