#include <string.h>
#include <stdio.h>
#include "usart2.h"
#include "nmea_protocol.h"

static char nmea_buff[128];
static char nmea_pointer =0;
static char lat[16];
static char lon[16];
//#define DEBUG_NMEA

#ifdef DEBUG_NMEA
char test_gpgll[50] = ",5212.83335,N,00425.92468,E,102148.00,A,A*6F" ;
#endif

void nmea_parser(char *str)     {
  char i;
  char j =0;
  char markers [5];
  
  if(str[4] == 'L'){
#ifdef DEBUG_NMEA
  for(i=0;i<50;i++) str [5+i] = test_gpgll[i];   
#endif
  for(i=0;i<40; i++){
    if(str[i]==',')markers[j++] = i;
    if (j>=4) break;
  }
  for(i=0;i<16;i++){
    lon[i]=0;
    lat[i]=0;
  }
  memcpy(lat,&str[markers[0]+1] ,(markers[1]-markers[0])-1);
  memcpy(lon,&str[markers[2]+1] ,(markers[3]-markers[2])-1);
  memcpy(lon,&str[markers[2]+1] ,(markers[3]-markers[2])-1);
  
  }
  
  
}

void clear_nmea_buff() {
  char ii;
  for (ii=0; ii<128; ii++)  {
    nmea_buff[ii]=0;
  }
  nmea_pointer =0;
   
}



void UART2_RXC(void){
  static char start =0;
  char stop =0;
  char temp;     
  temp = USART_ReceiveData(Open_USART2);
  USART_SendChar( temp );
   
if(!start){
  if(temp == '$') {
    start =1;
    return;
  }
  else return;
}   

if(start){
   nmea_buff[nmea_pointer++] = temp;
   if (temp == 0x0A){
     nmea_parser(nmea_buff);
     clear_nmea_buff();
     start =0;
   }
     
   else return;
  
}
    



 
}