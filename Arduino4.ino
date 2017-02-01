/*        
 *         
 *        Kunal Shah, Dhruv Patel, Andy Cervantes, Paul Nguyen
 *        T.A.B. Arduino User Interface Code
 *         
 *         
 *        
 *        COULD USE DELIMITER VALUE OF 999 TO DISTUINGISH SIGNALS
 * 
 *        ARDUINO #4
 *        Display the proper L.E.D. based upon the position of the glass
 */

int pos = 0;  //Zero is set as no lights while moving


int bottle1 = 2;
int bottle2 = 3;
int bottle3 = 4;
int bottle4 = 5;

int delay1 = 250;
int delay2 = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(bottle1, OUTPUT);
  pinMode(bottle2, OUTPUT);
  pinMode(bottle3, OUTPUT);
  pinMode(bottle4, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  if(Serial.available())
  {
    pos = Serial.parseInt();
    if (pos != 0)
    {
      digitalWrite(pos, HIGH);
      delay(5000);
      digitalWrite(pos, LOW);
      delay(1);
      //reset the input
      pos = 0;
    }
    else  //While it is moving
    {
  
      digitalWrite(bottle1, HIGH);
      delay(delay1);
      digitalWrite(bottle1, LOW);
      delay(delay2);
      
      digitalWrite(bottle2, HIGH);
      delay(delay1);
      digitalWrite(bottle2, LOW);
      delay(delay2);
      
      digitalWrite(bottle3, HIGH);
      delay(delay1);
      digitalWrite(bottle3, LOW);
      delay(delay2);
      
      digitalWrite(bottle4, HIGH);
      delay(delay1);
      digitalWrite(bottle4, LOW);
      delay(delay2);}
  }
}
