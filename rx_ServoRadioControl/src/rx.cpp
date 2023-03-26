//Include Libraries
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <Servo.h>


#ifdef ARDUINO_ARCH_ESP8266 // muda a configuração dos pinos dependendo da placa que estou usando
// CE, CSN esp8266
#define CE 0
#define CSN 2
#define Servo_pin 5
// CE, CSN arduino
#else
#define CE 9
#define CSN 10
#define Servo_pin 6
#endif 
#define uC_serial 9600

//cria um objeto servo
Servo myservo;
//create an RF24 object
RF24 radio(CE, CSN); 
//address through which two modules communicate.
const byte address[6] = "00001";
int motor_comando;

void setup(){
  myservo.attach(Servo_pin);  
  Serial.begin(uC_serial);
  delay(2000);
  radio.begin();
  //set the address
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  //Set module as transmitter
  radio.startListening();
  Serial.print("Esperando comandos - ");
  Serial.println(radio.isChipConnected());

}
void loop(){
//Read the data if available in buffer
  if (radio.available())
  {
    byte buffer_mensagem[sizeof(motor_comando)];
    radio.read(&buffer_mensagem,sizeof(buffer_mensagem));
    memcpy(&motor_comando, buffer_mensagem, sizeof(buffer_mensagem));
  }
  myservo.write(motor_comando);
  Serial.println(motor_comando);
  delay(5);
}
//========================================================================================================================
//                                     DAQUI PRA BAIXO É O CÓDIGO P/ CONTROLAR O MOTOR VIA SERIAL
//========================================================================================================================
//Include Libraries
//#include <Arduino.h>
//#include <SPI.h>
//#include <RF24.h>
//#include <Servo.h>
//
//
//#ifdef ARDUINO_ARCH_ESP8266 // muda a configuração dos pinos dependendo da placa que estou usando
//// CE, CSN esp8266
//#define CE 0
//#define CSN 2
//// CE, CSN arduino
//#else
//#define CE 9
//#define CSN 10
//#endif 
//#define uC_serial 9600
//
////cria um objeto servo
//Servo myservo;
////create an RF24 object
//RF24 radio(CE, CSN); 
////address through which two modules communicate.
//const byte address[6] = "00001";
//int motor_comando;
//int pos = 90;
//
//void setup(){
//  myservo.attach(6);  
//  Serial.begin(uC_serial);
//  delay(2000);
//  radio.begin();
//  //set the address
//  radio.openReadingPipe(0, address);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setPALevel(RF24_PA_MAX);
//  //Set module as transmitter
//  radio.startListening();
//  Serial.print("Esperando comandos - ");
//  Serial.println(radio.isChipConnected());
//
//}
//void loop(){
//  if (Serial.available()) {    // if data is available to read
//    char c = Serial.read();    // read the incoming character
//    if (c == '+') {            // if the character is '+', increase the servo position by 1
//      pos=pos+90;
//      if (pos > 180) {         // limit the servo position to 180 degrees
//        pos = 180;
//      }
//    } else if (c == '-') {     // if the character is '-', decrease the servo position by 1
//      pos=pos-90;
//      if (pos < 0) {           // limit the servo position to 0 degrees
//        pos = 0;
//      }
//    }
//  motor_comando = pos;
//  myservo.write(motor_comando);
//  Serial.println(motor_comando);
//  delay(333);
//  }
//}