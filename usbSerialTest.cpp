//This file should just print out anything in the serial port to
//test that it is working.


#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>

int main ()
{
  int fd ;
  int baud;
  char port[100];
  
  printf( "Enter a baudrate :");
  scanf("%d", &baud );

  printf( "Enter the portname in this format \"/dev/ttyACM0\" :");
  gets(port);


  if((fd=serialOpen(puts(port),baud))<0){
    fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    return 1;
  }

  for (;;){
    putchar(serialGetchar(fd));
    fflush(stdout);
  }
}
