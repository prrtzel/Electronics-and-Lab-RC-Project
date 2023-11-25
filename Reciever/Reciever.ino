#include <nRF24L01.h>
#include <RF24.h>

byte oneA = 3;
byte twoA = 9;
byte threeA = 5;
byte fourA = 6;

#define CE    7  //Chip Enable Chip Select
#define CSN   8

RF24 radio(CE, CSN);
const byte address[6] = "000001";

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
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {

  if (radio.available()) {
    int text;
    radio.read(&text, sizeof(text));

    /*
    Parsing the data:
    text = [LYVALUE, LXVALUE, RYVALUE, RXVALUE]
    This is 4 bytes in total which are shifted accordingly
    and then bitwise AND with an 8 bit mask to trim off the 
    unneeded data
    Example: 
    (data is sent backwards so the LSB is actually the first byte)
    (RX RY LX LY) >> 8 =
    (00 RX RY LX) & FF =
    (00 00 00 LX) parsed out the 2nd byte
    */

    RXVALUE = text >> 32  & 0xFF;
    RYVALUE = text >> 16  & 0xFF; 
    LXVALUE = text >> 8   & 0xFF;
    LYVALUE = text        & 0xFF;

    Serial.println(LYVALUE);
  }


  /*
  Values sent from transmitter are from:
  0 (backwards)
  5 (stop)
  10 (forwards)
  */

  LYVALUE = 10;
  RXVALUE = 0;
  move(LYVALUE, RXVALUE);

}

// RX = 0;  TURN LEFT
// RX = 5;  GO FORWARD
// RX = 10; TURN RIGHT


void forwardMotion (byte RXVALUE) {
  if (RXVALUE <= 3) {       // TURN LEFT
    analogWrite(oneA, 0);
    analogWrite(twoA, 100);
    analogWrite(threeA, 0);
    analogWrite(fourA, 255);
  }
  else if (RXVALUE <= 7) {  //GO FORWARD
    forward();
  }
  else if (RXVALUE <= 10) { //TURN RIGHT
    analogWrite(oneA, 0);
    analogWrite(twoA, 255);
    analogWrite(threeA, 0);
    analogWrite(fourA, 100);
  }
  else { 
    forward();
  }
}

void backwardMotion(byte RXVALUE) {
  if (RXVALUE <= 3) { // TURN LEFT
    analogWrite(oneA, 100);
    analogWrite(twoA, 0);
    analogWrite(threeA, 255);
    analogWrite(fourA, 0);
  }
  else if (RXVALUE <= 7) { //GO BACKWARD
    backward();
  }
  else if (RXVALUE <= 10) { //TURN RIGHT
    analogWrite(oneA, 255);
    analogWrite(twoA, 0);
    analogWrite(threeA, 100);
    analogWrite(fourA, 0);
  }
  else { 
    backward();
  }
}

void move(byte LYVALUE, byte RXVALUE) {
  if (LYVALUE <= 3){      //0-3 are backwards
    backwardMotion(RXVALUE);
    delay(10);
  }
  else if (LYVALUE <=7){  //4-7 are stopped
    stop();
    delay(10);
  }
  else if (LYVALUE <= 10) { //8-10 are forwards
    forwardMotion(RXVALUE);
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