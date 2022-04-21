#include "IncConduct.h"


IncConduct::IncConduct(){
    set_duty(0.1);
    
    
}

void IncConduct::evaluate()
{
	
	update_readings(); //reads V and I, calcs delta V, I and P
		
	if(delta_v == 0)
	{
		if(delta_c == 0)
		{
			//return
		}else if(delta_c>0)
		{
				next_duty = duty[NOW] - ABS_DUTY_STEP; //increase vref
		}else{ //less than
			next_duty = duty[NOW] + ABS_DUTY_STEP; //decrease vref
		}
	}else 
	{
		if((delta_c/delta_v) == -(current[NOW]/voltage[NOW]))
		{
			//return
		}else if((delta_c/delta_v) > -(current[NOW]/voltage[NOW]))
		{
			next_duty = duty[NOW] - ABS_DUTY_STEP;
		}else //less than
		{
			next_duty = duty[NOW] + ABS_DUTY_STEP;
		}
	}
		
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(next_duty);
	voltage[PREVIOUS] = voltage[NOW];
	current[PREVIOUS] = current[NOW];
    power[PREVIOUS] = power[NOW];
}
