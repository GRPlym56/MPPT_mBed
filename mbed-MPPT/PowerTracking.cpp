#include "PowerTracking.h"
#include <cstdint>
#include <iterator>
PowerTracking::PowerTracking():CurrentSense(PA_4), VoltageSense(PA_0), PWM(PB_0){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.05f;

	this->DUTY_STEP[UP] = 0.01f;
	this->DUTY_STEP[DOWN] = 0.01f;
	
	this->duty[NOW] = 0.0f;
    this->duty[PREVIOUS] = 0.0f;
	
	this->voltage[NOW] = 0.0f;
    this->current[NOW] = 0.0f;
    this->power[NOW] = 0.0f;

    this->voltage[PREVIOUS] = 0.0f;
    this->current[PREVIOUS] = 0.0f;
    this->power[PREVIOUS] = 0.0f;

    this->VScaler = 1.0f;
    this->IScaler = 1.0f;

    this->OS_Rate = 1;
}

void PowerTracking::sweep_duty(){
	float step = 0.01f;
	for (float i = MIN_DUTY; i < MAX_DUTY; i += step){
        set_duty(i);
        wait_us(100000); //wait 100ms
        update_readings();
        peakCheck();
    }	
}

void PowerTracking::set_threshold(float t){
	if(t > 1.0f){t=1.0f;}
	else if(t<0.0f){t= 0.0f;}
	this->threshold = t;
}

float PowerTracking::get_peak_duty(){
	return MAX_POWER_DUTY;
}



bool PowerTracking::peakCheck(){
	if (power[NOW] > MAX_POWER){
		MAX_POWER = power[NOW];
		MAX_POWER_DUTY = duty[NOW];
		return true;
	}
	return false; //if new peak not detected return false
}
void PowerTracking::update_readings(){
	unsigned char i;
	float Vi, Ci, Duty_Percent;   //instantanious voltage and current


    for (int i = 0; i < OS_Rate; i++){
        Vi += VoltageSense.read()*VScaler;
        Ci += CurrentSense.read()*IScaler;
        wait_us(100);  //wait 1ms between samples
    }
    this->voltage[NOW] = Vi/OS_Rate; //Calculate Mean voltage
    this->current[NOW] = Ci/OS_Rate; //Calculate Mean current
    
	power[NOW] = voltage[NOW]*current[NOW];
	if (power[NOW] > MAX_POWER){
		this->MAX_POWER = power[NOW];
		this->MAX_POWER_DUTY = duty[NOW];
	}
	
    delta_v = voltage[NOW] - voltage[PREVIOUS];
    delta_c = current[NOW] - current[PREVIOUS];
    delta_p = power[NOW] - power[PREVIOUS];

    /*
    //this is a silly and danger
    voltage[PREVIOUS] = voltage[NOW];
    current[PREVIOUS] = current[NOW];
    power[PREVIOUS] = power[NOW];
    */

    Duty_Percent = 100*get_duty(NOW);

    printf("Duty: %3.0f% ,\tV: %5.3f V,\tI: %5.3f A,\tP: %5.3f W,\r\n", Duty_Percent, voltage[NOW], current[NOW], power[NOW]);
}

float PowerTracking::get_power(int index){
	return this->power[index];
}
	
float PowerTracking::get_duty(int index){
	return this->duty[index];
}

float PowerTracking::get_max_duty(){
	return this->MAX_DUTY;
}
float PowerTracking::get_min_duty(){
	return this->MIN_DUTY;
}
	

void PowerTracking::set_power(float val){
	this->power[NOW] = val;
}

void PowerTracking::set_overSample(uint16_t OSRate){
    this->OS_Rate = OSRate;
}

void PowerTracking::set_V_scalling(float SF){
    this->VScaler = SF;
}

void PowerTracking::set_I_scalling(float SF){
    this->IScaler = SF;
}

void PowerTracking::set_duty(float d){
	d = (d<this->MIN_DUTY) ? MIN_DUTY : d;
	d = (d>this->MAX_DUTY) ? MAX_DUTY : d;
	this->duty[NOW] = d;
	
	if(d>1.0f) d=1.0f;
	PWM.write(d);
}

void PowerTracking::set_PWM_Frequency(uint32_t PWM_Frq){
    PWM.period((float)(1.0/PWM_Frq));
}
void PowerTracking::set_max_duty(float val){
	this->MAX_DUTY = val;
}
void PowerTracking::set_min_duty(float val){
	this->MIN_DUTY = val;
}
