#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
//Parte del codigo que controla el servomotor y el nivel de luz 
Servo servo;

int pinLedR = 6;  // pin Rojo del led RGB
int pinLedV = 5;  // pin Verde del led RGB
int pinLedA = 3;   // pin Azul del led RGB
int pausa = 3000;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

void setup(void) {
  pinMode(pinLedR, OUTPUT);    // pone el pinLedR como output
  pinMode(pinLedV, OUTPUT);    // pone el pinLedV como output
  pinMode(pinLedA, OUTPUT);    // pone el pinLedA como output
  Serial.begin(9600);
  servo.attach(9);
}

void loop(void) {
servo.write(80);

int analogico = analogRead(A0);
  Serial.print("Nivel de luz:");
  Serial.println(analogico);
  delay(1000);
  if(analogico<100)
  {
    uint16_t r, g, b, c;
    
    tcs.getRawData(&r, &g, &b, &c);
    
    Serial.print("Rojo: "); Serial.println(r, DEC);
    Serial.print("Verde: "); Serial.println(g, DEC);
    Serial.print("Azul: "); Serial.println(b, DEC);
    Serial.println(" ");
    delay(500);
      if (r>50)
      {
        Serial.println("Objeto rojo"); 
        color(255, 0, 0);   // rojo
          for (pos = 80; pos <= 180; pos += 1) 
          {
          myservo.write(pos);
          }
        delay(pausa);
        color(0, 0, 0);
          for (pos = 180; pos >= 80; pos -= 1) 
          {
          myservo.write(pos);
          }
      }
}
}

// funcion para generar colores
void color (int rojo, int azul, int verde) {
  analogWrite(pinLedR, rojo);
  analogWrite(pinLedV, verde);
  analogWrite(pinLedA, azul);
}
