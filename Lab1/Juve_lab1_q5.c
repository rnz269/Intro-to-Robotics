float get_time(float d){
d = d*1200;
d = d/11;
return d;
}
void pivot_turn_left(float s, int t){
	setMotorSpeed(motorB, -s);
	setMotorSpeed(motorC, s);
	sleep(t);
}
void pivot_turn_right(float s, int t){
	setMotorSpeed(motorB, s);
	setMotorSpeed(motorC, -s);
	sleep(t);
}
void move_forward(float s, float d){
	float t = get_time(d);
	setMotorSpeed(motorB, s);
	setMotorSpeed(motorC, s);
	sleep(t);
}
task main()
{
	move_forward(50,17.75);
	pivot_turn_right(12.5,1500);
	move_forward(50,11);
	pivot_turn_left(12.5,750);
	move_forward(50,17.75);
	pivot_turn_right(12.5,1500);
	move_forward(50,20.75);
	pivot_turn_right(12.5,1500);
	move_forward(50,4.25);
	pivot_turn_right(12.5,750);
	move_forward(50,11);
	pivot_turn_left(12.5,1500);
	move_forward(50,6.75);
}
