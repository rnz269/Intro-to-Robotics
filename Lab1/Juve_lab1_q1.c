
task main()
{
	int i;
	int i_sq;
	for(i=0; i<=10; i++)
	{
		i_sq = i*i;
		displayTextLine(i+1,"%d",i_sq);
	}
	sleep(5000);
}
