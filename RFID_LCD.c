
#include <termios.h> // I/O Terminals interfacing
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iobb.h>
#include <linux/i2c-dev.h>
#include <fcntl.h> //Discriptor Flags Defiantion.
#include <sys/signal.h>
#include <stdlib.h>
#include <sys/ioctl.h> //sys I/O Control
#include <errno.h> //Defines macros ,error reporting library
#define BAUDRATE B9600 //Set a baudrate to 9600
#define PORT "/dev/ttyACM0" //Ardiuno USB port
#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1

//..............................LCD Interface................
#define I2C_BUS        "/dev/i2c-2" // I2C bus device on Beaglebone
#define I2C_ADDR       0x27        // I2C slave address for the LCD module
int i2cFile;

void i2c_start()
{ if((i2cFile = open(I2C_BUS, O_RDWR)) < 0)
{     printf("Error: Failed to open I2C bus \n");
      exit(-1);} // check if bus is working or not
      if (ioctl(i2cFile, I2C_SLAVE, I2C_ADDR) < 0)
 {printf("Error: Failed to set I2C address.\n");
  exit(-1); //setting slave address for all transfer }}
void i2c_stop()
 {}
void i2c_send_byte(unsigned char data) //function send data to i2c slave
{  unsigned char byte[1];
   byte[0] = data;
   write(i2cFile, byte, sizeof(byte)); // writing data to the bus
   usleep(1000);}

void lcd_init()
{  i2c_send_byte(0b00110100); // D7=0, D6=0, D5=1, D4=1, RS,RW=0 EN=1
   i2c_send_byte(0b00110000); // D7=0, D6=0, D5=1, D4=1, RS,RW=0 EN=0
   usleep(4100);              // delay 4.1msec
   i2c_send_byte(0b00110100); i2c_send_byte(0b00110000); 
   usleep(100);               // delay 100usec
   i2c_send_byte(0b00110100); usleep(4100);// delay 4.1msec
   i2c_send_byte(0b00100100); i2c_send_byte(0b00100000); //4-bit mode set(2 nibble)
   usleep(40);                // delay 40usec
   LCD_cmd(0x28); // 4-bit mode with 2 lines char 5x8
   usleep(40);                // delay 40use
   LCD_cmd(0x01);usleep(40);// delay 40usec
   LCD_cmd(0x06); //Increment cursor (shift cursor to right)
   usleep(40);// delay 40usec
   LCD_cmd(0x0E); // screen on, cursor blinking
   LCD_cmd(0x80);usleep(40);// delay 40usec}
void LCD_data (unsigned char data) //Data register of LCD
{char upper = data>>4 ; // diffrentiate msb of the data
char up1 =(upper<<4)|0xd; char up2 =(upper<<4)|0x9; // addding enable pin high, rs pin 1, rw pin 0
char lower= data & 0x0f;  // Diffrentiate lsb of the data
i2c_send_byte(up1); // transmit data bit by bit
i2c_send_byte(up2);i2c_send_byte(lw1);i2c_send_byte(lw2);
  usleep (10);
}
void LCD_string (const char *buf) // function to send string of data
{while (*buf)
    {usleep (10); // 10us delay
      LCD_data (*buf); // send each character to the bus
      buf++;
      usleep (10); // 10us delay}}
//..........................END_LCD Interface..................

volatile int STOP=FALSE; //Variable that may change any time
void signal_handler_IO(int status);
int wait_flag = TRUE;

int main ()

{
    int fd=0, res=0;
 int check=0;
    char SYNC  [] = {0x55};                                                             // memory adress
    char PID [] = {0x6A};
                                                                                        //Create a termios struct
    struct termios oldtio, newtio;                                                      //io function
    struct sigaction saio;*/checking i/o comming from aurdino/*
    char buff[255];

                                                                                        //Open the sys port file and set the parameters.;file pointer to open.....
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NONBLOCK);                                    //open port file of bbb
    if (fd<0) 
    {   
        perror(PORT); 
        exit(-1);
    }

    saio.sa_handler=signal_handler_IO;                                                 //signal handler i/o
    saio.sa_flags=0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio,NULL);
    fcntl(fd, F_SETFL, FASYNC);                                                        //function control l1ibrary,serial port programming
    check = tcgetattr(fd, &oldtio);                                                    //terminal interface to control communication protocal
    if (check<0)
    {
        perror("tcgetattr");
    }

                                                                                        //Checking the set parameters.
    check = newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ;                          //open port file of bbb
    if (check<0)
    {
        perror("c_cflag");
    }

    check = newtio.c_iflag = IGNPAR | IXON; if (check<0)
    {
        perror("c_iflag");
    }

    check = newtio.c_oflag = 0; if (check<0)
    {
        perror("c_oflag");
    }

                                                                                               //check = newtio.c_lflag = ICANON | ISIG;

    check = newtio.c_lflag = 0; if (check<0)
    {
        perror("c_lflag  ");
    }
  /* c_cc is responsible for an erno error */

    check = newtio.c_cc[VMIN]=1; if (check<0)
    {   
        perror("c_cc[VMIN]");
    }

    check = newtio.c_cc[VTIME]=0; if (check<0)
    {
        perror("c_cc[VTIME]");
    }

    tcflush(fd, TCIFLUSH); 
 

    check = tcsetattr(fd, TCSANOW, &newtio); if (check<0)
    {
        perror("tcsetattr");
    }
//........LCD_INIT............
i2c_start();usleep(15000); lcd_init(); //set i2c and display connection.
 LCD_string(" SMART LIBRARY "); sleep(2);
LCD_cmd(0x01);  usleep(1000);// clear screen
 LCD_cmd(0x80);  usleep(100);//cursor to 1 line
 LCD_string (" PLEASE SCAN.. ");  usleep(1000);
 LCD_cmd(0xC0); usleep(100);//move to 2nd line
 LCD_string (" RFID TAGS.. "); usleep(1000);
//.......END_LCD_INIT..........
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
  memset(&buff,'\0',255); //fill the mem block with value read.
  res = read(fd,buff,255);

    if (res < 0)
   {
        perror("read");
        //if(errno ==EINTR) continue;
    }
        //printf("%s",buff); //print a strings getting from ardiuno
        usleep(5000);
iolib_init();
char strg[]="1052452422";
         // printf("%s",buff);
          scanf("%s", buff);

if(strcmp(strg, buff)==0)
       {

 usleep(1000);LCD_cmd(0x80);
 LCD_cmd(0x01);  usleep(100); // clear screen initally to print new line
 LCD_string ("BOOK NAME : "); usleep(1000);
 LCD_cmd(0xC0);usleep(100);
 LCD_string (" C Programing  "); usleep(1000);
       printf("\nC Programing(2nd Ed.)");
 iolib_setdir(8,12,DigitalOut);
       pin_high(8,12);
       sleep(1);
       pin_low(8,12);
       usleep(10000);
}
else
{
 // Printf("\n Does not read..");
       iolib_setdir(8,14,DigitalOut);
 iolib_setdir(8,14,DigitalOut);
       pin_high(8,14);
       sleep(1);
       pin_low(8,14);
       usleep(10000);
       }

iolib_free();

}
i2c_stop();
 close (fd);
}
void signal_handler_IO(int status)
{
wait_flag=FALSE;
}

