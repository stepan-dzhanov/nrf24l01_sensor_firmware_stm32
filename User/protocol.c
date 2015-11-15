
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "protocol.h"
#include "settings.h" 
#include "timer.h"

#include "pwm.h"
#include "leds.h"

#define STEP_SPEED 1
#define MAX_SPEED  500
#define STEP_PWM   20
#define MAX_PWM    100



static int r_pwm =0;
static int l_pwm =0;
static int speed =5;

static char data_buf[100];
static unsigned char pointer =0;
static char ready =0;
static char flash =0;
extern unsigned short array[];
extern unsigned short array1[];
extern unsigned short array2[];
extern unsigned int a_pointer;
char GetFlash(void)     {
  return flash;
}
#define MAX_COMMAND 22

const char * strings[23] = {
"?"

};



#define FRQ_COEFF2      0.005556
#define FRQ_COEFF1      0.005556


char xstr[50];
char fmt_str[]="%d";





char CheckReady() {
  return ready;
  
}

void clear_buff() {
  char ii;
  for (ii=0; ii<=90; ii++)  {
    data_buf[ii]=0;
  }
  pointer =0;
  ready = 0;
   
}


void UART0_RXC(void)  {
   
    char temp;     
    temp = USART_ReceiveData(Open_USART);
    if(ready) return;
    if(pointer<sizeof(data_buf)) data_buf[pointer++] = temp;
    
    if(pointer>=2)      {
      pointer=0;
    }
    
    
   
                                                                 
    if((data_buf[pointer-1]==0x0D)&&(data_buf[pointer-2]==0x0A)) {
      ready =1;
      temp=temp;
      
    }
    
}


int Processing_request(void) {
  
  
 
  static char a = 0;
  unsigned char i=0;
  
 
   
  if(CheckReady()==0) return 0;
  i = data_buf[0];
  
  switch (i)  {
    
    case 'L'://StartConv
      
      if(r_pwm<l_pwm) {
        r_pwm += STEP_PWM;
        if(r_pwm>MAX_PWM) r_pwm = MAX_PWM;
        SetPWM_R(r_pwm*speed);
        SetPWM_L(l_pwm*speed);
        clear_buff();
        break; 
      }
      if(r_pwm>=l_pwm) {
        l_pwm -= STEP_PWM;
        if(l_pwm<0) l_pwm = 0;
        SetPWM_R(r_pwm*speed);
        SetPWM_L(l_pwm*speed);
        clear_buff();
        break; 
      }
    
    case 'R'://StartConv
      if(l_pwm<r_pwm) {
        l_pwm += STEP_PWM;
        if(l_pwm>MAX_PWM) l_pwm = MAX_PWM;
        if(r_pwm<0) r_pwm = 0;
        SetPWM_R(r_pwm*speed);
        SetPWM_L(l_pwm*speed);
        break; 
      }
        
      if(l_pwm>=r_pwm) {
        r_pwm -= STEP_PWM;
        if(r_pwm<0) r_pwm = 0;
        SetPWM_R(r_pwm*speed);
        SetPWM_L(l_pwm*speed);
        break; 
      }
    
    case 'U'://StartConv
       r_pwm +=STEP_PWM;
       l_pwm +=STEP_PWM;
       if (l_pwm>MAX_PWM) l_pwm = MAX_PWM;
       if (r_pwm>MAX_PWM) r_pwm = MAX_PWM;
       SetPWM_R(r_pwm*speed);
       SetPWM_L(l_pwm*speed);
       
       clear_buff();
    break;
      
    case 'D'://StartConv
       r_pwm -=STEP_PWM;
       l_pwm -=STEP_PWM;
       if (l_pwm<=0) l_pwm = 0;
       if (r_pwm<=0) r_pwm = 0;
       SetPWM_R(r_pwm*speed);
       SetPWM_L(l_pwm*speed);
       clear_buff();
    break;
      
    case 'S'://StartConv
     SetPWM_L(0);
     SetPWM_R(0);
      r_pwm =0;
       l_pwm =0;
     clear_buff();
    break;
    
    case 'N'://StartConv
     a ^=1;
     if (a) Reverse();
       else Forward();
     clear_buff();
    break;
    
    

  
  default :
   
    break;
    
  }
  clear_buff();
  return 1;
  
}
