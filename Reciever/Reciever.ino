#include <nRF24L01.h>
#include <RF24.h>

byte oneA = 3;
byte twoA = 9;
byte threeA = 5;
byte fourA = 6;

#define CE    7  //Chip Enable Chip Select
#define CSN   8

RF24 radio(CE, CSN);
const byte address[6] = "00001";

byte LXVALUE = 0;
byte LYVALUE = 0;
byte RXVALUE = 0;
byte RYVALUE = 0;

void setup() {
  Serial.begin(9600);

  pinMode(oneA, OUTPUT);
  pinMode(twoA, OUTPUT);
  pinMode(threeA, OUTPUT);
  pinMode(fourA, OUTPUT);

  
  radio.begin();
  radio.openReadingPipe(0, address);
  //radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {

  if (radio.available()) {
    int text;
    radio.read(&text, sizeof(text));

    RXVALUE = text >> 8   & 0xFF;
    LYVALUE = text        & 0xFF;

    move(LYVALUE, RXVALUE);
  }

// LYVALUE 
// 0; FULL POWER
// 10; BACKWARD

// RXVALUE
// 0: RIGHT
// 10: LEFT
}


void forwardMotion (byte RXVALUE) {
  if (RXVALUE <= 3) {       // TURN RIGHT
    analogWrite(oneA, 0);
    analogWrite(twoA, 255);
    analogWrite(threeA, 0);
    analogWrite(fourA, 100);
  }
  else if (RXVALUE <= 7) {  //GO FORWARD
    forward();
  }
  else if (RXVALUE <= 10) { //TURN LEFT
    analogWrite(oneA, 0);
    analogWrite(twoA, 100);
    analogWrite(threeA, 0);
    analogWrite(fourA, 255);
  }
  else { 
    forward();
  }
}

void backwardMotion(byte RXVALUE) {
  if (RXVALUE <= 3) { // TURN LEFT
    analogWrite(oneA, 255);
    analogWrite(twoA, 0);
    analogWrite(threeA, 100);
    analogWrite(fourA, 0);
  }
  else if (RXVALUE <= 7) { //GO BACKWARD
    backward();
  }
  else if (RXVALUE <= 10) { //TURN RIGHT
    analogWrite(oneA, 100);
    analogWrite(twoA, 0);
    analogWrite(threeA, 255);
    analogWrite(fourA, 0);
  }
  else { 
    backward();
  }
}

void move(byte LYVALUE, byte RXVALUE) {
  if (LYVALUE <= 3){      //0-3 are backwards
    forwardMotion(RXVALUE);
    delay(10);
  }
  else if (LYVALUE <=7){  //4-7 are stopped
    stop();
    delay(10);
  }
  else if (LYVALUE <= 10) { //8-10 are forwards
    backwardMotion(RXVALUE);
    delay(10);
  }
  else{
    stop();
    delay(10);
  }
}

void forward() {
  // //forward
  digitalWrite(oneA, LOW);
  digitalWrite(twoA, HIGH);
  digitalWrite(threeA, LOW);
  digitalWrite(fourA, HIGH);
}

void backward() {
  //backward
  digitalWrite(oneA, HIGH);
  digitalWrite(twoA, LOW);
  digitalWrite(threeA, HIGH);
  digitalWrite(fourA, LOW);

}

void stop() {
  //stop
  digitalWrite(oneA, LOW);
  digitalWrite(twoA, LOW);
  digitalWrite(threeA, LOW);
  digitalWrite(fourA, LOW);
}