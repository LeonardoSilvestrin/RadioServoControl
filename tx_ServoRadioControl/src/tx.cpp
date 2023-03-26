//Include Libraries
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>


#ifdef ARDUINO_ARCH_ESP8266 // muda a configuração dos pinos dependendo da placa que estou usando
// CE, CSN esp8266
#define CE 0
#define CSN 2
// CE, CSN arduino
#else
#define CE 9
#define CSN 10
#endif 
#define uC_serial 9600

//cria um objeto servo
//create an RF24 object
RF24 radio(CE, CSN); 
//address through which two modules communicate.
const byte address[6] = "00001";
int pos = 90;
bool keep_position = 1;
  
void setup(){
  Serial.begin(uC_serial);
  delay(2000);
  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  //Set module as receiver
  radio.stopListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  Serial.print("Começando transmissão - ");
  Serial.println(radio.isChipConnected());
}
void loop(){
//Read the data if available in buffer
  if (Serial.available()) {    // if data is available to read
    char c = Serial.read();    // read the incoming character
    if (c == '+') {            // if the character is '+', increase the servo position by 1
      pos=pos+90;
      if (pos > 180) {         // limit the servo position to 180 degrees
        pos = 180;
      }
    } else if (c == '-') {     // if the character is '-', decrease the servo position by 1
      pos=pos-90;
      if (pos < 0) {           // limit the servo position to 0 degrees
        pos = 0;
      }
    }
    keep_position = 1;
    }
    while(keep_position){
      byte buffer_mensagem[sizeof(pos)];
      memcpy(buffer_mensagem, &pos, sizeof(pos));
      radio.write(&buffer_mensagem,sizeof(buffer_mensagem));
      Serial.println(pos);
      if (Serial.available()){
        keep_position = 0;
      }
    }
}