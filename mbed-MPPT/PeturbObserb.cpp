#include "PeturbObserb.h"


PeturbObserb::PeturbObserb(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.01f;
	this->DUTY_STEP[UP] = 0.01f;
	this->DUTY_STEP[DOWN] = 0.01f;
    this->threshold = 0.5f;
}
void PeturbObserb::evaluate(){
	update_readings();
	if (delta_p >= 0.0f){								//if power has increased
			
        if(delta_v >= 0.0f ){                           //if Voltage and power have increased
            next_duty = duty[NOW] - DUTY_STEP[DOWN];    //decrease duty (something ... load resistance)
        }else{                                          //if power has increased but voltage has decreased
            next_duty = duty[NOW] + DUTY_STEP[UP];      //increase duty
        }
	}else{										            //if power has decreased
        if (delta_v >= 0.0f){                               //if power has decreased and voltage has increased 
            next_duty = duty[NOW] + DUTY_STEP[UP];          //increase duty 
        }else{                                              //if power has decreased and voltage has decreased
            next_duty = duty[NOW] - DUTY_STEP[DOWN];        //decrease duty ()
        }	
	}

    next_duty = (next_duty>MAX_DUTY)?MAX_DUTY:next_duty;
    next_duty = (next_duty<MIN_DUTY)?MIN_DUTY:next_duty;
    voltage[PREVIOUS] = voltage[NOW];
	current[PREVIOUS] = current[NOW];
    power[PREVIOUS] = power[NOW];
	duty[PREVIOUS] = duty[NOW];
	set_duty(next_duty);
}

