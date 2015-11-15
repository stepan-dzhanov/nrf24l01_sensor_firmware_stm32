#ifndef _PWM_
#define _PWM_
void InitializeTimer();


void InitializePWMChannel(int pulse);

void InitializeLEDs();


void SetPWM_R(int p) ;  
void SetPWM_L(int p);



#endif