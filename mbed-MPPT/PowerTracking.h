#ifndef _PT_H__
#define _PT_H__

#include "mbed.h"
#include <cstdint>

class PowerTracking{
	public:
        enum{PREVIOUS = 0, NOW};
		enum{DOWN = 0, UP};
        enum{VOLTAGE = 0, CURRENT};
        
		PowerTracking();
		virtual void 	evaluate() = 0;
		void update_readings();
		float get_power(int index);
		float get_duty(int index);
		float get_avg_power();
		float get_duty();
		float get_max_duty();
		float get_min_duty();
		float get_peak_duty();
		
        
        void set_overSample(uint16_t OS_Rate);
		void set_power(float val);
		void set_avg_power(float val);
		void set_duty(float val);
        void set_PWM_Frequency(uint32_t PWM_Frq);
		void set_max_duty(float val);
		void set_min_duty(float val);
		void sweep_duty();
		void set_threshold(float t);
		void set_OS_AVG_PWR(float p);
		bool peakCheck();
        void set_V_scalling(float SF);
        void set_I_scalling(float SF);
		
        
	protected:
		
		volatile float delta_p;
        volatile float delta_v;
        volatile float delta_c;

		volatile float duty[2];
		volatile float next_duty;
		volatile float delta_d;
		volatile float MAX_DUTY;
		volatile float MIN_DUTY;
		volatile float DUTY_STEP[2];
        volatile float ABS_DUTY_STEP = 0.01f;
		volatile float MAX_POWER;
		volatile float MAX_POWER_DUTY;
		volatile float threshold;
        volatile uint16_t OS_Rate;
		

    protected:
        volatile float power[2];
        volatile float voltage[2];
        volatile float current[2];
        volatile float VScaler;
        volatile float IScaler;
        AnalogIn CurrentSense, VoltageSense;
        PwmOut PWM;

};

#endif
