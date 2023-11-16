#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Motor controller pins
#define M1A  6
#define M2A  7
#define M3A  8
#define M4A  9
#define M12A_ENABLE  12
#define M34A_ENABLE  13

// Chip Enable Chip Select
#define CE    7 
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

  pinMode(M1A, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M3A, OUTPUT);
  pinMode(M4A, OUTPUT);
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
    LYValue = text >> 8   & 0xFF;
    LXValue = text        & 0xFF;

    Serial.println();
    Serial.println(RXValue);
    Serial.println(RXValue);
    Serial.println(LYValue);
    Serial.println(LXValue);
    Serial.println();
  }

  // RX will be used for steering
  // LY will be used for power


  // Throttle Control (LY)
  // if (LYValue > 50) {
  //   digitalWrite(M1A, HIGH);
  //   digitalWrite(M2A, HIGH);
  //   digitalWrite(M3A, HIGH);
  //   digitalWrite(M4A, HIGH);
  // }
  // else {
  //   digitalWrite(M1A, LOW);
  //   digitalWrite(M2A, LOW);
  //   digitalWrite(M3A, LOW);
  //   digitalWrite(M4A, LOW);
  // }

}



