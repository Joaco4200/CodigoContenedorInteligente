#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

Servo servo;

int pinLedR = 6;  // pin Rojo del led RGB
int pinLedV = 5;  // pin Verde del led RGB
int pinLedA = 3;   // pin Azul del led RGB
int pausa = 3000;
int pos = servo.read();
int posf = 0;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

void setup(void) {
  pinMode(pinLedR, OUTPUT);    // pone el pinLedR como output
  pinMode(pinLedV, OUTPUT);    // pone el pinLedV como output
  pinMode(pinLedA, OUTPUT);    // pone el pinLedA como output
  Serial.begin(9600);
  servo.attach(9);
}

void loop(void) 
{
  servo.write(70);
  int luz = analogRead(A0);
  Serial.print("Nivel de luz:");
  Serial.println(luz);
  delay(pausa);

    if(luz<100)  //si no detecta luz el sensor de luz ambiental
    {
      uint16_t r, g, b, c, colorTemp, lux;
  
      tcs.getRawData(&r, &g, &b, &c);
      colorTemp = tcs.calculateColorTemperature(r, g, b);
      lux = tcs.calculateLux(r, g, b);
      
      Serial.print("Temperatura color: "); Serial.print(colorTemp, DEC); Serial.println(" K");
      Serial.print("Lux : "); Serial.println(lux, DEC);
      Serial.print("Rojo: "); Serial.println(r, DEC);
      Serial.print("Verde: "); Serial.println(g, DEC);
      Serial.print("Azul: "); Serial.println(b, DEC);
      Serial.print("Clear: "); Serial.println(c, DEC);
      Serial.println(" ");
      delay(pausa);
      
    if (luz >= 8 && colorTemp >= 3000 && lux >= 15){
      if (r > g && r > b) {
        if (b < 50 && g < 50) {
          color(234, 239, 89);  // Amarillo
          delay(pausa);
          color(0, 0, 0);
        }
        else if (b < 50 && g >= 50) {
          color(252, 173, 36);  // Naranja
          delay(pausa);
          color(0, 0, 0);
        }
        else {
          color(255, 0, 0);  // Rojo
          delay(pausa);
          color(0, 0, 0);
        }
    }
    else if (g > r && g > b) {
      if (r < 60 && b < 60) {
        color(0, 255, 0);  // Verde
        delay(pausa);
        color(0, 0, 0);
      }
      else {
          color(252, 98, 211);  // Rosado
          delay(pausa);
          color(0, 0, 0);
      }
    }
    else{
        color(0, 0, 255);  // Azul
        delay(pausa);
        color(0, 0, 0);
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
