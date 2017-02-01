 /*     Kunal Shah, Dhruv Patel, Andy Cervantes, Paul Nguyen
 *      T.A.B. Arduino Lifter Mechanism Code
 *
 *
 *       COULD USE DELIMITER VALUE OF -999 TO DISTUINGISH SIGNALS
 * 
 *        ARDUINO #3
 *        Send output of 1 to begin moving again ---> Arduino #1
 *        Recieve input of 1 to begin moving rod up <--- Arduino #2
 * 
 */

int incomingNumber;
int sendingNumber;

int buttonPin = 7;
int recieveLED = 6;
int sendLED = 5;

int pos;


#include <Servo.h>
Servo myActivator;


void setup() 
{
    myActivator.attach(10);
}
void loop() 
{
  myActivator.write(0);
  /*
   * If recieve signal of 1 from serial, then activate the mechanism to press the dispenser activator
   * Wait four seconds and then depress the mechanism
   */
  if(Serial.available())
  {
    incomingNumber = Serial.parseInt();

    if(incomingNumber == 1)
    {
      //Spin servo up
      for(pos=0;pos<180;pos++)
      {
        myActivator.write(pos);
        delay(1);
      }
      //Four-Count Dispenser
      delay(4000);
      
      //Spin servo back down
      for(pos=179;pos>=0;pos--)
      {
        myActivator.write(pos);
        delay(1);
      }
      //Send signal of 1 to Arduino #1 so that it signals the track to move again
      Serial.println(1);
    }
  }
  myActivator.write(0);
  
    
  
    
}
