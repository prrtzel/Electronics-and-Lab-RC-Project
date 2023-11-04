#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LVRX  A5  // Arduino pin connected to LVRX pin
#define LVRY  A6  // Arduino pin connected to LVRY pin
#define LSW   5  // D4

#define RVRX  A3  // Arduino pin connected to RVRX pin
#define RVRY  A2  // Arduino pin connected to RVRY pin
#define RSW   8  // D5

#define LED1  5  //LED's D2
#define LED2  6  // D3

#define CE    7  //Chip Enable Chip Select
#define CSN   8

typedef uint8_t byte;
typedef uint16_t word;

RF24 radio(CE, CSN);
const byte address[6] = "69420";

byte dataBuffer[] = {0, 0, 0, 0};

void setup() {

  Serial.begin(9600);

  // set up pins
  pinMode(LVRX, INPUT);
  pinMode(LVRY, INPUT);
  pinMode(LSW, INPUT);

  pinMode(RVRX, INPUT);
  pinMode(RVRY, INPUT);
  pinMode(RSW, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //RF Transceiver
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // MAY NEED TO CHANGE POWER
  radio.stopListening();
}

void loop() {

  dataBuffer[0] = byte(analogRead(LVRY));
  dataBuffer[1] = byte(analogRead(LVRX));
  dataBuffer[2] = analogRead(RVRY);
  dataBuffer[3] = analogRead(RVRX);

  radio.write(&dataBuffer, sizeof(dataBuffer));
}






