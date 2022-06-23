// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//ultrasonic_sensor
const int trigPin = A1;
const int echoPin = A0;
const int buzzpin = 13;
// defines variables
long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzpin, OUTPUT);
  // set up the LCD's number of columns and rows:
lcd.begin(22, 2);
  // Print a message to the LCD.
lcd.print("Hello,starting_radar");
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
delayMicroseconds(10);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(20);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= (duration-5.1714)*0.01802256;
// Prints the distance on the Serial Monitor
lcd.print("Nearest_object_is: " );
lcd.print(distance);
lcd.print(" cm" );
}
