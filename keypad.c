#include <stdio.h>
#include <unistd.h>
#include <iobb.h> //GPIO input_output library..

int main(void)
{
iolib_init(); //Initializing Library

//Set GPIO PIN Direction IN/OUT
iolib_setdir(8, 7, DigitalIn);   //GPIO_66 In Direction
iolib_setdir(8, 9, DigitalIn);   //GPIO_69 In Direction
iolib_setdir(8, 11, DigitalIn);  //GPIO_45 In Direction
iolib_setdir(8, 15, DigitalIn);  //GPIO_47 In Direction
iolib_setdir(8, 8, DigitalOut);  //GPIO_67 Out Direction
iolib_setdir(8, 10, DigitalOut); //GPIO_68 Out Direction
iolib_setdir(8, 12, DigitalOut); //GPIO_44 Out Direction
iolib_setdir(8, 14, DigitalOut); //GPIO_26 Out Direction

//Set Column pins to high
pin_high(8,8);
pin_high(8,10);
pin_high(8,12);
pin_high(8,14);

//set Row pin to low and pulled up through resister.
pin_low(8,7);
pin_low(8,9);
pin_low(8,11);
pin_low(8,15);

//16 Keys 4x4 array 
char mat[4][4]={{'1','2','3','A'};
                {'4','5','6','B'};
                {'7','8','9','C'};
                {'7','8','9','C'};
                {'*','0','#','D'};

int ROW[4]={7,9,11,15}; //Row GPIO pins 
int COL[4]={8,10,12,14}; //Column GPIO pins
int i,j;

 while(1)// Infinite While loop..

{
 for(i=0;i<=3;i++)
{
 pin_low(8,COL[i]); //initialy set pin low
for(j=0;j<=3;j++)
{
if(is_low(8,ROW[j]) //Check input on Row..
{
printf("%c", mat[i][j]); //Print according i,j matrix elements...
}
}
pin_high(8,COL[i]); //Reset GPIO pin 
}
}
iolib_free();
return(0);
}


