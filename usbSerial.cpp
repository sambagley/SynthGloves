/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int USB = open( "/dev/ttyUSB0", O_RDWR | O_NONBLOCK | O_NDELAY );

if (USB < 0 )
{
	cout<< "Error opening usb serial connection" << endl;
}

struct termios tty;
struct termios tty_old;
memset (&tty, 0 , sizeof tty);

if ( tcgetattr ( USB, &tty ) !=0 );
{
	cout << "Error " << errno << << "from tcgettattr: " << strerror(errno) << endl;
}

cfsetospeed (&tty, B9600);
cfsetispeed (&tty, B9600);

tty.c_cflag &= ~PARENB;       // Make 8n1
tty.c_cflag &= ~CSTOPB;
tty.c_cflag &= ~CSIZE;
tty.c_cflag |= CS8;

tty.c_cflag &= ~CRTSCTS
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringSerial.h>

int main ()
{
  int fd ;

  if((fd=serialOpen("/dev/ttyACM0",9600))<0){
    fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    return 1;
  }

  for (;;){
    putchar(serialGetchar(fd));
    fflush(stdout);
  }
}
