#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE    7  //Chip Enable Chip Select
#define CSN   8

RF24 radio(CE, CSN);
const byte address[6] = "69420";


typedef uint8_t byte;
typedef uint16_t word;

byte LXValue = 0;
byte LYValue = 0;
byte RXValue = 0;
byte RYValue = 0;

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

    /*
    Parsing the data:
    text = [LYValue, LXValue, RYValue, RXValue]

    This is 4 bytes in total which are shifted accordingly
    and then bitwise AND with an 8 bit mask to trim off the 
    unneeded data

    Example: 
    (data is sent backwards so the LSB is actually the first byte)

    (RX RY LX LY) >> 8 =
    (00 RX RY LX) & FF =
    (00 00 00 LX) parsed out the 2nd byte
    */
    RXValue = text >> 32  & 0xFF;
    RYValue = text >> 16  & 0xFF; 
    LXValue = text >> 8   & 0xFF;
    LYValue = text        & 0xFF;


    Serial.println(LYValue);
  }
}



