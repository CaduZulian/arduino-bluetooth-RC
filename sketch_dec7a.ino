//including the libraries
#include <SoftwareSerial.h>  // TX RX software library for bluetooth
#include <Servo.h>           // lib for use servo motor

#define SERVO 6  // Porta Digital 6 PWM

Servo s;  // Variável Servo
int pos;  // Posição Servo

//Initializing pins for bluetooth Module
int bluetoothRx = 2;  // bluetooth rx to 2 pin
int bluetoothTx = 3;  // bluetooth tx to 3 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//Start L298N pin
int start_motors = A3;

//Front Motor Pins
int Enable1 = 8;
int Motor1_Pin1 = 9;
int Motor1_Pin2 = 10;

//Back Motor Pins
int Motor2_Pin1 = 11;
int Motor2_Pin2 = 12;
int Enable2 = 13;

//Headlight pin
int headlight_light = A0;

//Arrows light pin
int arrows_light = A1;

//Reverse light pin
int reverse_light = A2;

char command = "";  //variable to store the data
int velocity = 0;  //Variable to control the speed of motor

void setup() {
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600);
  bluetooth.begin(9600);

  s.attach(SERVO);
  s.write(180);  // Inicia motor posição zero

  //Setting the L298N and LED pins as output pins.
  pinMode(start_motors, OUTPUT);
  pinMode(Motor1_Pin1, OUTPUT);
  pinMode(Motor1_Pin2, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(Motor2_Pin1, OUTPUT);
  pinMode(Motor2_Pin2, OUTPUT);
  pinMode(Enable2, OUTPUT);
  pinMode(headlight_light, OUTPUT);
  pinMode(arrows_light, OUTPUT);
  pinMode(reverse_light, OUTPUT);


  //Setting the enable pins as HIGH.
  digitalWrite(Enable1, HIGH);
  digitalWrite(Enable2, HIGH);
}

void loop() {

   if (bluetooth.available() > 0) {  //Checking if there is some data available or not
     command = bluetooth.read();     //Storing the data in the 'command' variable
     Serial.print(command);        //Printing it on the serial monitor

     //Change pin mode only if new command is different from previous.
     switch (command) {
       case 'M':  //Start L298N board
         digitalWrite(start_motors, HIGH);
         break;
       case 'm':  //stop L298N board
         digitalWrite(start_motors, LOW);
         break;
       case 'f':  //Moving the Car Forward
         digitalWrite(Motor2_Pin1, HIGH);
         digitalWrite(Motor2_Pin2, LOW);
         break;
       case 'b':  //Moving the Car Backward
         digitalWrite(Motor2_Pin1, LOW);
         digitalWrite(Motor2_Pin2, HIGH);
         digitalWrite(reverse_light, HIGH);
         break;
       case 's':  //Stop drive
         digitalWrite(Motor2_Pin2, LOW);
         digitalWrite(Motor2_Pin1, LOW);
         digitalWrite(reverse_light, LOW);
         break;
       case 'r':  //Moving the Car Right
         digitalWrite(Motor1_Pin1, LOW);
         digitalWrite(Motor1_Pin2, HIGH);
         break;
       case 'l':  //Moving the Car Left
         digitalWrite(Motor1_Pin1, HIGH);
         digitalWrite(Motor1_Pin2, LOW);
         break;
       case 'S':  //stop Steering
         digitalWrite(Motor1_Pin2, LOW);
         digitalWrite(Motor1_Pin1, LOW);
         break;
       case 'P':  //Change position in servo motor
         s.write(0);
         break;
       case 'p':  //Go back in start position in servo motor
         s.write(180);
         break;
       case 'H':  //Headlight ON
         digitalWrite(headlight_light, HIGH);
         break;
       case 'h':  //Headlight OFF
         digitalWrite(headlight_light, LOW);
         break;
       case 'A':  //Arrows light ON
         digitalWrite(arrows_light, HIGH);
         break;
       case 'a':  //Arrows light OFF
         digitalWrite(arrows_light, LOW);
         break;
     }

  //     //Controlling the Speed of Car
  //     default:  //Get velocity
  //       if (command == 'q') {
  //         velocity = 255;  //Full velocity
  //         analogWrite(Enable2, velocity);
  //       } else {
  //         //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
  //         if ((command >= 48) && (command <= 57)) {
  //           //Subtracting 48 changes the range from 48-57 to 0-9.
  //           //Multiplying by 25 changes the range from 0-9 to 0-225.
  //           velocity = (command - 48) * 25;
  //           analogWrite(Enable2, velocity);
  //         }
  //       }
  //   }
   }
}
