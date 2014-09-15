/*
 * Reaction Timer 
 * Written by: B. Huang, Feb. 20, 2014
 * 
 * Hardware connections:
 * LED: Pin 9 & GND
 * Button: Pins 2 & 3 --> Pin 2 (Input) & Pin 3 (GND)
 *
 * Upload this example, open up the serial monitor - set to 9600 bps. 
 * Push the button as soon as the light turn on.
 */

int ledPin = 9;
int buttonPin = 2;
int buttonGND = 3;      // Wiring trick -- use the I/O pin #3 as GND.
int buzzerPin =  10;    // Optional: Add a buzzer for sound as well as light -- use tone() command.

int gamesPlayed = 1;    // Contains the total number of games played for the life of the device
int totalTime = 0;      // stores total time -- used for calculating average

unsigned long waitTime;  // Random "waiting" time before turning on the light
unsigned long zeroTime;  // Zero reference time
unsigned long reactTime; // Reaction Time


void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Sets the pull-up resistor for the button
  pinMode(buttonGND, OUTPUT);
  digitalWrite(buttonGND, LOW); // sets pin LOW (GND)
  pinMode(buzzerPin, OUTPUT);
  
  Serial.print("Game");
  Serial.print("\t");
  Serial.print("React");
  Serial.print("\t");
  Serial.print("Ave(ms)");
  Serial.println();
  Serial.print("======================");
  Serial.println();
  
}

void loop()
{
  randomSeed(analogRead(A5));    // Get noise to seed the random number generator
                                 // Use an un-used pin for the random noise.
  waitTime = random(2000, 3500); // randomTime from 2 to 3.5 seconds
  delay(waitTime);               // delay randomTime
  digitalWrite(ledPin, HIGH);    // turn on LED!
  zeroTime = millis();           // set zeroTime reference

  while(digitalRead(buttonPin) == HIGH)  // holding loop until button is pressed.
  {
  }

  reactTime = millis() - zeroTime; // calculation of reaction time
  totalTime = totalTime + reactTime;
  digitalWrite(ledPin, LOW);    // turn off LED!

// Display information to Serial Monitor //
  Serial.print(gamesPlayed);
  Serial.print("\t");
  Serial.print(reactTime);
  Serial.print("\t");
  Serial.print((float) totalTime / gamesPlayed, 1); 
  Serial.println();  

  fastBlink();  // feedback to show that you did something!
  gamesPlayed++;  // increment the game counter;
}

// Quickly blinks to button indicating the end of a game
void fastBlink()
{
  for(int x = 0 ; x < 7 ; x++)
  {
    digitalWrite(ledPin, HIGH);
    delay(60);
    digitalWrite(ledPin, LOW);
    delay(60);
  }
}
