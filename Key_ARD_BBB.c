//Darshan Mistry.
//Keypad Interface with BBB using Ardiuno..
//using UART bus.

#include <termios.h> //I/O Terminals interfacing
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> //Discriptor Flags Defiantion.
#include <sys/signal.h>
#include <stdlib.h>
#include <sys/ioctl.h> sys I/O Control
#include <errno.h> //Defines macros ,error reporting library
#define BAUDRATE B9600 //Set a baudrate to 9600
#define PORT "/dev/ttyACM0" //Ardiuno USB port 
#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE; //Variable that may change any time
void signal_handler_IO(int status);
int wait_flag = TRUE;

int main ()

{
    int fd=0, res=0;
    int check=0;
    char SYNC  [] = {0x55};
    char PID [] = {0x6A};
//Create a termios struct
    struct termios oldtio, newtio;
    struct sigaction saio;
    char buff[255];

//Open the sys port file and set the parameters.
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd<0) {perror(PORT); exit(-1);}

    saio.sa_handler=signal_handler_IO;
    saio.sa_flags=0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio,NULL);
    fcntl(fd, F_SETFL, FASYNC);
    check = tcgetattr(fd, &oldtio);
    if (check<0){perror("tcgetattr");}

//Checking the set parameters.
    check = newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ; if (check<0){perror("c_cflag");}

    check = newtio.c_iflag = IGNPAR | IXON; if (check<0){perror("c_iflag");}

    check = newtio.c_oflag = 0; if (check<0){perror("c_oflag");}

    //check = newtio.c_lflag = ICANON | ISIG;

    check = newtio.c_lflag = 0; if (check<0){perror("c_lflag  ");}
/* c_cc is responsible for an erno error */

    check = newtio.c_cc[VMIN]=1; if (check<0){perror("c_cc[VMIN]");}

    check = newtio.c_cc[VTIME]=0; if (check<0){perror("c_cc[VTIME]");}

    tcflush(fd, TCIFLUSH); 
 

    check = tcsetattr(fd, TCSANOW, &newtio); if (check<0){perror("tcsetattr");}

 Printf("Welcom to smart IOT Library automation");

for(;;) //infinit loop

{
    ioctl(fd, TIOCSBRK); //set a send bit to zero

    usleep(1300);

    ioctl(fd,TIOCCBRK);// turn break off

    usleep(200);

 
/* send request to actuator to receive the current setting and setup */
    check = write(fd, SYNC, sizeof(SYNC));  if (check<0){perror("SYNC");}

    check = write(fd,PID, sizeof(PID)); if (check<0){perror("PID");}

/* read response*/
memset(&buff,'\0',buff); //fill the mem block with value read.
    res = read(fd, buff,255); 

    if (res < 0)
   {
        perror("read");
        //if(errno ==EINTR) continue;
    }
        printf("%s\n", res,buff); //print a strings getting from ardiuno

usleep(10000);

}
    close (fd);
} 
void signal_handler_IO(int status)
{
wait_flag=FALSE;
}
