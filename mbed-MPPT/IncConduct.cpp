#include "IncConduct.h"


IncConduct::IncConduct(){
	duty[NOW] = 0.1; //default value
}

void IncConduct::evaluate()
{
	
	update_readings();
	
	V[NOW] = this->voltage[NOW];
	I[NOW] = this->current[NOW];
	
	deltaV = V[NOW] - V[PREVIOUS];
	deltaI = I[NOW] - I[PREVIOUS];
	
	if(delta_v == 0)
	{
		if(delta_c == 0)
		{
			//return
		}else if(delta_c>0)
		{
				next_duty = duty[NOW] + DUTY_STEP[UP];
		}else{ //less than
			next_duty = duty[NOW] - DUTY_STEP[DOWN];
		}
	}else 
	{
		if((delta_c/delta_v) == -(I[NOW]/V[NOW]))
		{
			//return
		}else if((deltaI/deltaV) > -(I[NOW]/V[NOW]))
		{
			next_duty = duty[NOW] + DUTY_STEP[UP];
		}else //less than
		{
			next_duty = duty[NOW] - DUTY_STEP[DOWN];
		}
	}
		
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(next_duty);
	V[PREVIOUS] = V[NOW];
	I[PREVIOUS] = I[NOW];
}
