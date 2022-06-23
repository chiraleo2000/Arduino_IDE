// defines pins numbers
const int trigPin = A1;
const int echoPin = A0;
const int buzzpin = 13;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzpin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
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
 if(distance <= 15 && distance >= 0){
 // if in distance it will acttivate buzzing module
 digitalWrite(buzzpin, HIGH);
 delay(distance*10);
 digitalWrite(buzzpin, LOW);
 }
 else{
 // if not in distance it will acttivate buzzing module
 digitalWrite(buzzpin, LOW);
 }
//cheak or display in sensor monitor
//Serial.println(duration);
Serial.print("Distance in centimeters: ");
Serial.println(distance);
//delay(1000);
}
