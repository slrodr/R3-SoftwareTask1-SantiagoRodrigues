// Program 2 7-segment displays to display a number between 0
// and 99 based on the potentiometer's output
const int pinABCD1[]={2, 3, 4, 5}; // digital pins of first decoder (display for multiples of 10)
const int pinABCD2[]={6, 7, 8, 9}; //digital pins of second decoder(display for n%10)
const int pinLE1 = 11; 
const int pinLE2 = 12;
#define sensorPin A0 //analog pin for potentiometer
int sensorValue = 0;


void setup()
{
 Serial.begin(9600);
 delay(100);
 // Set digital pins as output
 pinMode(pinABCD1[0], OUTPUT);
 pinMode(pinABCD1[1], OUTPUT);
 pinMode(pinABCD1[2], OUTPUT);
 pinMode(pinABCD1[3], OUTPUT);
 pinMode(pinABCD2[0], OUTPUT);
 pinMode(pinABCD2[1], OUTPUT);
 pinMode(pinABCD2[2], OUTPUT);
 pinMode(pinABCD2[3], OUTPUT);
 pinMode(pinLE1, OUTPUT);
 digitalWrite(pinLE1, HIGH); // Latch is enabled, display output stays 0
 pinMode(pinLE2, OUTPUT);
 digitalWrite(pinLE2, HIGH); //Latch is enabled, display output stays 0
}

void firstNumber (byte num, int pinLE){
  // Fuction to get the 4 bit data input corresponding to a decimal digit between 0 and 9
  digitalWrite(pinLE, LOW); // Latch disabled so segment output can change
  for(int i =0; i<4; i++){
    digitalWrite(pinABCD1[i], bitRead(num, i)); //writes 4 bit sequence corresponding to the decimal number 
  }
  digitalWrite(pinLE,HIGH); //Latch enabled, segment output stays the same
}

void secondNumber (byte num, int pinLE){
   // Fuction to get the 4 bit data input corresponding to a decimal number between 0 and 9
  digitalWrite(pinLE, LOW);// Latch disabled so segment output can change
  for(int i =0; i<4; i++){
    digitalWrite(pinABCD2[i], bitRead(num, i));//writes 4 bit sequence corresponding to the decimal number
  }
  digitalWrite(pinLE,HIGH);//Latch enabled, segment output stays the same
}

void loop()
{
  sensorValue = analogRead(sensorPin); // read analog pin input
  sensorValue = map(sensorValue, 0, 1023, 0, 99); //map potentiometer values so they are between 0 and 99
  Serial.println(sensorValue); //for checking displays are correct
  int secondDigit = sensorValue % 10; //gets the second digit (unit)
  int firstDigit = (sensorValue - secondDigit)/ 10; //gets first digit (tens)
  firstNumber(firstDigit, pinLE1);
  secondNumber(secondDigit, pinLE2);
  delay(500);
}
