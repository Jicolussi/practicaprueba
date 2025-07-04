#include <Arduino.h>

int pul = 8;
int pinesA[7] = {27, 26, 25, 33, 32, 35, 34};
int Estados[7][7]={
                  {1,0,0,0,0,0,0},
                  {0,1,0,0,0,0,0},
                  {0,0,1,0,0,0,0},
                  {0,0,0,1,0,0,0},
                  {0,0,0,0,1,0,0},
                  {0,0,0,0,0,1,0},
                  {0,0,0,0,0,0,1}
}
int pinC = 33;
int pinAC = 0;
int Tinicial = 0;
int tiempo = 1000;
int puntaje = 0;
int direccion = 0;
volatile bool flag = false;

void IRAM_ATTR ISR()
{
  flag = true;
}

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(pinesA[i], OUTPUT);
  }

  pinMode(pul, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pul), ISR, FALLING);
  Serial.println("inicio el juego");
}

void loop()
{
  int Tactual = millis();
  if (Tactual - Tinicial >= tiempo)
  {
    Tinicial = Tactual;
    for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8;j++){
        digitalWrite(pinesA[j], Estados[j][i]);
      }
    }
  }
  if (flag)
  {
    flag = false;
    if (j==3&&i==3)
    {
      Serial.println("acertaste");
      for (int i = 0; i < 7; i++)
      {
        digitalWrite(pinesA[i], LOW);
      }
      puntaje++;
      Serial.print("Tu puntaje es: ");
      Serial.println(puntaje);
      tiempo = tiempo * 0.75;
    }
    else
    {
      Serial.println("burro");
      for (int i = 0; i < 7; i++)
      {
        digitalWrite(pinesA[i], LOW);
      }
      Serial.print("Tu puntaje fue de: ");
      Serial.println(puntaje);
      puntaje = 0;
      tiempo = 1000;
    }
  }
}
