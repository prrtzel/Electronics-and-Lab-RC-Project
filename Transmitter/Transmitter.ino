#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LVRX  A1  // Arduino pin connected to LVRX pin
#define LVRY  A0  // Arduino pin connected to LVRY pin
#define LSW   7  // D4

#define RVRX  A3  // Arduino pin connected to RVRX pin
#define RVRY  A2  // Arduino pin connected to RVRY pin
#define RSW   8  // D5

#define LED1  5  //LED's D2
#define LED2  6  // D3

#define CE    10  //Chip Enable Chip Select
#define CSN   11

typedef uint8_t byte;

RF24 radio(CE, CSN);
const byte address[6] = "69420";

  byte LXValue = 0;
  byte LYValue = 0;
  byte RXValue = 0;
  byte RYValue = 0;
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

  dataBuffer[0] = analogRead(LVRY) / 100;
  dataBuffer[1] = analogRead(LVRX) / 100;

  dataBuffer[2] = analogRead(RVRY) / 100;
  dataBuffer[3] = analogRead(RVRX) / 100;

  Serial.println(dataBuffer[0]);

  radio.write(&dataBuffer[0], sizeof(dataBuffer));

}