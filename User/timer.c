#include "stm32f4xx.h"
#include "timer.h"



#include "usart.h"
#include "ad7887.h"

#define C_TIMEOUT 10;

static int a=0;
static int flag=0;
void StartConvertion(void)      {
  flag =1;
}

void StopConvertion(void)      {
  flag =0;
}


void ResetTimer(void)   {
  a =0;
}
int GetTimer(void)      {
  return a;
}

void TimerRoutine(void) {
  
  a++;
  
  
   
}