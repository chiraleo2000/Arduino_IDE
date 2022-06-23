//Joystick Pins
int x_key = A0;
int y_key = A1;
int x_pos;
int y_pos;
//Motor Pins     //Enable pin for first motor
int IN1 = 46;       //control pin for first motor
int IN2 = 47;       //control pin for first motor
int IN3 = 48;        //control pin for second motor
int IN4 = 49;        //control pin for second motor
//IR_4_sensors_board
int IR_Sensor_1 = 50;
int IR_Sensor_2 = 51;
int IR_Sensor_3 = 52;
int IR_Sensor_4 = 53;
//Initializing variables to store data
int motor_speed1;
int motor_speed2;
void setup ( ) {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //Initializng the joystick pins as input
  pinMode (x_key, INPUT) ;
  pinMode (y_key, INPUT) ;
  pinMode (IR_Sensor_1, INPUT);
  pinMode (IR_Sensor_2, INPUT);
  pinMode (IR_Sensor_3, INPUT);
  pinMode (IR_Sensor_4, INPUT);

}
void loop () {
  int statusSensor1 = digitalRead (IR_Sensor_1);
  int statusSensor2 = digitalRead (IR_Sensor_2);
  int statusSensor3 = digitalRead (IR_Sensor_3);
  int statusSensor4 = digitalRead (IR_Sensor_4);
  x_pos = analogRead (x_key) ;  //Reading the horizontal movement value
  y_pos = analogRead (y_key) ;  //Reading the vertical movement value

  if (x_pos > 800) {    //Rotating the left motor in clockwise direction
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
  }

  else if (x_pos < 300) {   //Rotating the left motor in anticlockwise direction
    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN2, LOW);
  }
  else if ( 300 < x_pos < 800) {  //Rotating the left motor in anticlockwise direction
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN2, LOW);
  }


  if (y_pos > 800) {        //Rotating the right motor in clockwise direction
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

  }

  else if (y_pos < 300) {       //Rotating the right motor in anticlockwise direction
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}
