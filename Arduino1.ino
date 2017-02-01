/*        
 *         
 *        Kunal Shah, Dhruv Patel, Andy Cervantes, Paul Nguyen
 *        T.A.B. Arduino User Interface Code
 *         
 *         
 *        
 *        COULD USE DELIMITER VALUE OF 999 TO DISTUINGISH SIGNALS
 * 
 *        ARDUINO #1
 *        Send output of bottle number (1-4) ---> Arduino #2
 *        Send input of -1 to begin moving again ---> Arduino #2
 *        (When recieved from Arduino #3)
 *        
 *        Recieve input of 1 to begin moving <--- Arduino #3
 */


/*
 * Define statements for easily changable drink names
 */
#define NUM_DRINKS 6

#define DRINK_1 "Drink #1"
#define DRINK_2 "Drink #2"
#define DRINK_3 "Drink #3"
#define DRINK_4 "Drink #4"
#define DRINK_5 "Drink #5"
#define DRINK_6 "Drink #6"
/*
 * Setting up the LCD
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/*
 * Values to be sent and recieved between arduinos 
 */
int incomingNumber;
int sendingBottle = 0;
int sendingMove = -1;
/*
 * Button Pins
 */
int UP_Button = 7;
int DOWN_Button = 8;
int ENTER_Button = 9;
int EXIT_Button = 10;
/*
 * Button States for each respective button
 */
int UP_STATE;
int DOWN_STATE;
int ENTER_STATE;
int EXIT_STATE;
/*
 * Send a recieve LED pins
 */
int recieveLED = 13;
int sendLED = 6;



/*
 * Array of drink names and the iterator for the respective array
 */
String drinkName[NUM_DRINKS];
int DRINK_ITERATOR = 0;




void setup() 
{
  Serial.begin(9600);
  pinMode (recieveLED, OUTPUT);
  pinMode (sendLED, OUTPUT);
  pinMode (UP_Button, INPUT);
  pinMode (DOWN_Button, INPUT);
  pinMode (ENTER_Button, INPUT);
  pinMode (EXIT_Button, INPUT);
  lcd.begin(16, 2);
  loadDrinks(drinkName);
}

/*
 * Functoin which will load the drink names into the drinkName array
 * Sadly, this has to be manually changed if the NUM_DRINKS is changed...
 */
void loadDrinks(String drinkName[])
{
  drinkName[0] = DRINK_1;
  drinkName[1] = DRINK_2;
  drinkName[2] = DRINK_3;
  drinkName[3] = DRINK_4;
  drinkName[4] = DRINK_5;
  drinkName[5] = DRINK_6;
}

/*
 * Will obtain the current drink name that was entered by user and send it to Arduino #2
 */
void sendDrink(String drinkName[], int DRINK_ITERATOR)
{
  String drink = drinkName[DRINK_ITERATOR];
  if(drink.equals(DRINK_1))
  {
    
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println("1");
      Serial.println("-999");
      digitalWrite(sendLED,LOW);
      
  }
  else if(drink.equals(DRINK_2))
  {
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println("2");
      Serial.println("-999");
      digitalWrite(sendLED,LOW);
      
  }
  else if(drink.equals(DRINK_3))
  {
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println("3");
      Serial.println("-999");
      digitalWrite(sendLED,LOW);
     
  }
  else if(drink.equals(DRINK_4))
  {
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println("4");
      Serial.println("-999");
      digitalWrite(sendLED,LOW);
  }   

  else if(drink.equals(DRINK_5))
  {
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println("3");
      Serial.println("2");
      Serial.println("-999");
      digitalWrite(sendLED,LOW);
      
  }
  else if(drink.equals(DRINK_6))
  {
      digitalWrite(sendLED,HIGH);
      delay(250);
      Serial.println(1);
      Serial.println(2);
      Serial.println(3);
      Serial.println(4);
      Serial.println(-999);
      digitalWrite(sendLED,LOW);
      
  }  
}

int firstTime =1;

void loop() 
{
  UP_STATE = digitalRead(UP_Button);
  DOWN_STATE = digitalRead(DOWN_Button);
  ENTER_STATE = digitalRead(ENTER_Button);
  EXIT_STATE = digitalRead (EXIT_Button);

  if(firstTime==1)
  {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WELCOME!!!");
    delay(1750);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(drinkName[0]);
    firstTime=0;
  }
  
  /*
   * If the UP Button is pressed, show next drink name
   * Edges roll over
   */
  if(UP_STATE == LOW)
  {
    if(DRINK_ITERATOR == NUM_DRINKS-1)
    {
      DRINK_ITERATOR = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(drinkName[DRINK_ITERATOR]);
    }
    else
    {
      DRINK_ITERATOR++;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(drinkName[DRINK_ITERATOR]);
    }
  }

  /*
   * If DOWN Button is pressed, show previous drink name
   * Edge's roll over
   */
  if(DOWN_STATE == LOW)
  {
    if(DRINK_ITERATOR == 0)
    {
      DRINK_ITERATOR = NUM_DRINKS-1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(drinkName[DRINK_ITERATOR]);
    }
    else
    {
      DRINK_ITERATOR--;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(drinkName[DRINK_ITERATOR]);
    }
  }

  /*
   * If EXIT Button is pressed, print goodbye message and exit program
   */
  if(EXIT_STATE == LOW)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HAPPY DRINKING!");
    delay(1000);
    lcd.clear();
    exit(0);
  }

  /*
   * If ENTER Button is pressed, obtain the selected drink name
   * Send over the respective bottles required to Arduino #2
   */
  if(ENTER_STATE == LOW)
  {
    sendDrink(drinkName, DRINK_ITERATOR);
  }
  
  /*
   * Now, check if there's a number being sent over to this #1 from #3
   * If 1 is recieved, then send over a -1 to Arduino #2 telling it to begin moving
   */
  if(Serial.available())
  {
    incomingNumber = Serial.parseInt();
    digitalWrite(recieveLED, HIGH);
    delay(250);
    digitalWrite(recieveLED,LOW);
    if(incomingNumber == 1)
    {
      digitalWrite(sendLED, HIGH);
      Serial.println(sendingMove);
      digitalWrite(sendLED, LOW);
    }
  }
  
  delay(250);

}
