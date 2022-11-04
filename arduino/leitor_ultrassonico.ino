// C++ code
//
/*
  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7

  http://www.arduino.cc/en/Tutorial/Ping

  This example code is in the public domain.
*/
#include <Adafruit_LiquidCrystal.h>
int ledVerde     = 6;//sensor 1 porta 7
int ledVermelha  = 5;//sensor 1 porta 7
int ledVerde2    = 4;//sensor 1 porta 8
int ledVermelha2 = 3;//sensor 1 porta 8

int cm = 0;
int acessas = 0;
int apagada = 0;
Adafruit_LiquidCrystal lcd_1(0);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  pinMode(ledVerde    , OUTPUT);
  pinMode(ledVermelha , OUTPUT);
  pinMode(ledVerde2   , OUTPUT);
  pinMode(ledVermelha2, OUTPUT);
}
int acendeApaga(int led1,int led2){
  int conseguiu = 0;
  conseguiu = 0;
  if (!digitalRead(led1)) {
    conseguiu = 1;
    digitalWrite(led1, HIGH); 
  }
  if (digitalRead(led2)) {
    digitalWrite(led2, LOW); 
  }
  return conseguiu;
/* */
};

void loop()
{
  // converte para centimetro
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  //Serial.println(String(cm)+" cm sensor 7");
  if (cm < 200) {
    //apaga a verde e ascende a vermelha
    apagada = apagada + acendeApaga(ledVermelha,ledVerde);
  }else{
    //apaga a vermelha e ascende a verde
    acessas = acessas + acendeApaga(ledVerde,ledVermelha);
  }
  // converte para centimetro
  cm = 0.01723 * readUltrasonicDistance(8, 8);
  Serial.println(String(cm)+" cm sensor 8");
  if (cm < 200) {
    //apaga a verde e ascende a vermelha
    apagada = apagada + acendeApaga(ledVermelha2,ledVerde2);
  }else{
    //apaga a vermelha e ascende a verde
    acessas = acessas + acendeApaga(ledVerde2,ledVermelha2);
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Vagas Livres: "+String(acessas));
  lcd_1.setCursor(0, 1);
  lcd_1.print("Vagas ocupadas:"+String(apagada));
  delay(1000); // Espera por 1 segundo para verificar novamente
}