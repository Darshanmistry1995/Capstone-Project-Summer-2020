//Darshan Mistry.
//To checck a user name and password.

#include <stdio.h>
#include <string.h>
int main()
{
    char str[100], strP[]="C012345";
    int PSW=1234,a,x=2;
    printf("*****Welcome to the IoT Based Smart Library*******\nPlease enter the User ID and Password");
   while(x!=0)
   {
    printf("\nUser ID: ");
    scanf("%s", str);
    
    printf("Password: ");
    scanf("%d", &a);
     if (strcmp(str, strP)==0 && PSW==a )
     {
          printf("Welcom to the Library!");
          x=0;
     }
    else
    {
    printf("Access denied");
    
    }
   }    
    
        return 0;
}
