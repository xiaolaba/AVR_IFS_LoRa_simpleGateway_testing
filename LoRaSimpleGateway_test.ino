// xiaolaba 
/*
- https://www.facebook.com/invisiblefun/posts/2951385615082036
- invisiblefun.com Mini LoRa Development Board
- Samtech SX1276 for 915Mhz and 923Mhz application, LoRaWan chip
- MCU ATMEGA328PB
- AM1805 RTC (I2C interface, PC5/SCL0, PC4/SDA0)
- Extra Interrupt pin for further development, PC0 / PC1 / PC3 pin used
 */

// install this library, a must
// https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
// testing done, sucess, 2022-06-20

/*
PC3 ADC3 (ADC Input Channel 3)
PCINT11 (Pin Change Interrupt 11)

PC2 ADC2 (ADC Input Channel 2)
PCINT10 (Pin Change Interrupt 10)

PC1 SCK1 (SPI1 Master Clock output)
ADC1 (ADC Input Channel 1)
PCINT9 (Pin Change Interrupt 9)

PC0 MISO1
ADC0 (ADC Input Channel 0)
PCINT8 (Pin Change Interrupt 8)





/*
  LoRa Simple Gateway/Node Exemple

  This code uses InvertIQ function to create a simple Gateway/Node logic.

  Gateway - Sends messages with enableInvertIQ()
          - Receives messages with disableInvertIQ()

  Node    - Sends messages with disableInvertIQ()
          - Receives messages with enableInvertIQ()

  With this arrangement a Gateway never receive messages from another Gateway
  and a Node never receive message from another Node.
  Only Gateway to Node and vice versa.

  This code receives messages and sends a message every second.

  InvertIQ function basically invert the LoRa I and Q signals.

  See the Semtech datasheet, http://www.semtech.com/images/datasheet/sx1276.pdf
  for more on InvertIQ register 0x33.

  created 05 August 2018
  by Luiz H. Cassettari
*/

#include <SPI.h>              // include libraries
#include <LoRa.h>

/*
const long frequency = 915E6;  // LoRa Frequency

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 9;        // LoRa radio reset
const int irqPin = 2;          // change for your board; must be a hardware interrupt pin
*/

//xiaolaba, 2022-06-17
//#define F_CPU 1000000L
// uses MiniCore 328PB, no bootloader, 1MHz internal RC 
const int csPin = PIN_PB2;          // PIN_PB2, PB2, LoRa radio chip select
const int resetPin = PIN_PC2;       // PC2, LoRa radio reset
const int irqPin = PIN_PD2;          // PD2, change for your board; must be a hardware interrupt pin
const int reedSwitchPin =  PIN_PB0;// the number of the reedSwitch pin

const int ledPin = PIN_PD5;         // on broad LED testing
// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int reedSwitchState = LOW;      // ledState used to set the LED



const long frequency = 923E6;  // LoRa Frequency 923MHZ, TW CHINA A923-1

void setup() {

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(reedSwitchPin, INPUT_PULLUP);
  
  
  Serial.begin(9600);                   // initialize serial
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
  Serial.println();
  Serial.println("LoRa Simple Gateway");
  Serial.println("Only receive messages from nodes");
  Serial.println("Tx: invertIQ enable");
  Serial.println("Rx: invertIQ disable");
  Serial.println();

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();
}

void loop() {
  if (runEvery(5000)) { // repeat every 5000 millis

    String message = "HeLoRa World! ";
    message += "I'm a Gateway! ";
    message += millis();

    LoRa_sendMessage(message); // send a message

    Serial.println("Send Message!");

    blinkLED ();
  }
}

void LoRa_rxMode(){
  LoRa.disableInvertIQ();               // normal mode
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.enableInvertIQ();                // active invert I and Q signals
}

void LoRa_sendMessage(String message) {
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.print(message);                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}

void onReceive(int packetSize) {
  String message = "";

  while (LoRa.available()) {
    message += (char)LoRa.read();
  }

  Serial.print("Gateway Receive: ");
  Serial.println(message);
}

void onTxDone() {
  Serial.println("TxDone");
  LoRa_rxMode();
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}




// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

void blinkLED () {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }   
}
