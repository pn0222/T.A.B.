/*        
 *        Kunal Shah, Dhruv Patel, Andy Cervantes, Paul Nguyen
 *        T.A.B. Arduino Track Code 
 *         
 *        COULD USE DELIMITER VALUE OF 999 TO DISTUINGISH SIGNALS
 * 
 *        ARDUINO #2
 *        Send output of 1 to begin pushing rod up ---> Arduino #3 
 *        Recieve input for bottles to use (1-4) ---> Arduino #1
 *        Recieve input of -1 to move track again
 *        
 *        
 *        Forward = 135 --->Continous
 *        Backwards = 45---> Continuous
 */

/*
 * Distances between the liqor dispensers
 */
#define DISTANCE_BEGIN 1800 //Distance between START-1 --> 7.00V
#define DISTANCE_BETWEEN 1700 //Distance between 1-2, 2-3, 3-4 -->All same distance
#define DISTANCE_END //Distnace between 4-END



int sendingNumber;
int incomingNumber = 999;

int buttonPin = 7;
int recieveLED = 6;
int sendLED = 5;

/*
 * Boolean values used for book-keeping
 */
int trackRun =1;
int bottleInput =1;

/*
 * Number of bottles being required to make the drink
 */
int bottleCount =0;
int bottles[] = {0,0,0,0};

#include <Servo.h>
Servo myTrack;

void setup() 
{
    Serial.begin(9600);
    myTrack.attach(10);
}

void loop() 
{
 
 myTrack.write(90);
 /*
  * Will run this loop four times, once for each bottle
  */
 while(bottleCount <4)
 {
  while(Serial.available() && bottleInput ==1)
  {
    /*
     * Obtain input from Arduino #1 and set bottles array index value to 1 if bottle is going
     * to be used. Will keep taking input until incomingNumer becomes -999. Then all the bottles
     * necessary will have been recorded.
     */
    while(incomingNumber != -999)
    {
      incomingNumber = Serial.parseInt();
      if(incomingNumber == 1)
      {
        bottles[0] = 1;
      }
      if(incomingNumber ==2)
      {
        bottles[1] == 1;
      }
      if(incomingNumber ==3)
      {
        bottles[2] = 1;
      }
      if(incomingNumber==4)
      {
        bottles[3] == 1;
      }
     bottleInput =0; 
    } //End of bottle input from Arduino #1
  
  } //End of while serial.available for bottleInput
  
  /*
   * Move the track as long as trackRun ==1
   */
  while(trackRun ==1)
  {
    //Move under the first bottle from the beginning
    int i;
    for(i=0;i<DISTANCE_BETWEEN;i++)
    {
      myTrack.write(135);
      delay(1);
    }
    myTrack.write(90);
    //If the bottle is required, then send 1 to Arduino #3 and wait
    //Set the track to stop running until further input is recieved
    if(bottles[bottleCount] ==1)
    {
      Serial.println(1);
      trackRun =0; 
    }
    
  }
  /*
   * Wait for signal of -1 from Arduino #1
   * When recieve signal, start moving trackAgain
   */
  while(Serial.available() && trackRun==0) //OR instead of AND just in case nothing is in the serial buffer at this point...
  {
    incomingNumber = Serial.parseInt();
    if(incomingNumber ==-1)
    {
      trackRun =1;
    }
  }
  
  bottleCount++;
 }//While for bottleCount
    
}
