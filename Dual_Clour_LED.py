#Darshan Mistry
#!/usr/bin/python

#	Blinks two LED wired to P9_15 and P9_16.


import Adafruit_BBIO.GPIO as GPIO
import time

//Assignining port to aLED's

red = "P9_16"
green = "P9_15"

 
GPIO.setup(red, GPIO.OUT) //For Red LED
GPIO.setup(green, GPIO.OUT) //For Green LED
 
while True:
//Red Led Controll.
    GPIO.output(red, GPIO.HIGH) 
    time.sleep(0.5)
    
    GPIO.output(red, GPIO.LOW)
    time.sleep(0.5)

//Green Led Controll.
    GPIO.output(green, GPIO.HIGH)
    time.sleep(0.1)
    
    GPIO.output(green, GPIO.LOW)
    time.sleep(0.1)
