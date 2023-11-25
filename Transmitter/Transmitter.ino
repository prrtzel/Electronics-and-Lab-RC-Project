#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LVRX  A0  // Arduino pin connected to LVRX pin
#define LVRY  A1  // Arduino pin connected to LVRY pin

#define RVRX  A2  // Arduino pin connected to RVRX pin
#define RVRY  A3  // Arduino pin connected to RVRY pin

#define LED1  5  //LED's D2
#define LED2  6  // D3

#define CE    7  //Chip Enable Chip Select
#define CSN   8

typedef uint8_t byte;

RF24 radio(CE, CSN);
const byte address[6] = "00001";

  byte LXValue = 0;
  byte LYValue = 0;
  byte RXValue = 0;
  byte RYValue = 0;
  byte dataBuffer[] = {0, 0};

void setup() {

  Serial.begin(9600);

  // set up pins
  pinMode(LVRX, INPUT);
  pinMode(LVRY, INPUT);

  pinMode(RVRX, INPUT);
  pinMode(RVRY, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //RF Transceiver
  radio.begin();
  radio.openWritingPipe(address);
  //radio.setPALevel(RF24_PA_MIN); // MAY NEED TO CHANGE POWER
  radio.stopListening();
}

void loop() {

  dataBuffer[0] = analogRead(LVRY) / 100;
  dataBuffer[1] = analogRead(RVRX) / 100;

  radio.write(&dataBuffer, sizeof(dataBuffer));

}