#include "mbed.h"
#include "PowerTracking.h"
#include "PeturbObserb.h"
#include "IncConduct.h"

PeturbObserb PO;
//IncConduct INC;
// main() runs in its own thread in the OS
int main()
{
    
    PO.set_V_scalling(22.0);
    PO.set_I_scalling(2.0);
    PO.set_PWM_Frequency(10000); //10KHz PWM Frequency
    PO.set_overSample(100);  //16x over sample
    PO.sweep_duty();
    printf("\r\nStarting P&O\r\n");
    while (true) {

        PO.evaluate();
        wait_us(100000); //wait 100ms
    }
    
    /*
    INC.set_V_scalling(22.0);
    INC.set_I_scalling(2.0);
    INC.set_PWM_Frequency(10000);
    INC.set_overSample(100);
    //INC.sweep_duty();
    printf("\r\nStarting IncConc\r\n");
    while(1)
    {
        INC.evaluate();
        wait_us(100000);
    }
    */

}

