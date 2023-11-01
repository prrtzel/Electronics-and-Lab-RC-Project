#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE    10  //Chip Enable Chip Select
#define CSN   11

RF24 radio(CE, CSN);
const byte address[6] = "69420";

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);  // MAY NEED TO CHANGE POWER
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int text;
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}



