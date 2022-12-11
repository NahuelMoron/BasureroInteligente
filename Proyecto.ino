#include <Servo.h>
long distanciaCm1 = 300;
long tiempo1;
int echo1=12;
int trigg1=13;
long ultimaDist1 = 300;

long distanciaCm2;
long tiempo2;
int echo2=10;
int trigg2=9;
long ultimaDist2;

int lecturaTemp;
float temperatura;
float tempCelsius;

long anguloServo = 0;
Servo servo;

char bloqueado = false;
char abierto = false;
int tiempoAbierto;

void setup() {
 Serial.begin(9600);
 pinMode(echo1, INPUT);
 pinMode(trigg1, OUTPUT);
 servo.attach(6);
 pinMode(4, OUTPUT);
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(echo2, INPUT);
 pinMode(trigg2, OUTPUT);
}
void loop() {
 while (!bloqueado) {
 //temperatura
 lecturaTemp = analogRead(5);
 temperatura = (lecturaTemp * 5) / 1023.0;
 tempCelsius = temperatura * 100;
 Serial.print("Temperatura: ");
 Serial.print(tempCelsius);
 Serial.println(" C");
 if (tempCelsius > 80) {
  bloqueado = true;
  digitalWrite(3, HIGH);
 } else {
  bloqueado = false;
  digitalWrite(3, LOW);
 }
 //Luces LED
 digitalWrite(4, HIGH);
 digitalWrite(2, LOW);
 //Sensor tapa
 digitalWrite(trigg1, LOW);
 delayMicroseconds(5);
 digitalWrite(trigg1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigg1, LOW);

 tiempo1=pulseIn(echo1, HIGH);
 distanciaCm1 = (0.034*tiempo1) / 2;
 Serial.print("Ultima distancia en centimetros tapa: ");
 Serial.println(ultimaDist1);
 Serial.print("Distancia en centimetros tapa: ");
 Serial.println(distanciaCm1);
 delay(1000);
 ultimaDist1 = distanciaCm1;

 if (distanciaCm1 = ultimaDist1 && distanciaCm1 <=20) {
   abierto = true;
   tiempoAbierto = 0;
 }
 
 while (abierto){
  servo.write(90);
  Serial.print("Tiempo de apertura: ");
  Serial.println(tiempoAbierto);
  tiempoAbierto = tiempoAbierto + 1;
  delay(1000);
  if (tiempoAbierto > 10) {
    abierto = false;
  }
 }
  if(!abierto){
  servo.write(0);
  }
 //Sensor capacidad
 digitalWrite(trigg2, LOW);
 delayMicroseconds(5);
 digitalWrite(trigg2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigg2, LOW);

 tiempo2=pulseIn(echo2, HIGH);
 distanciaCm2= (0.034*tiempo2) / 2;
 Serial.print("Ultima distancia en centimetros capacidad: ");
 Serial.println(ultimaDist2);
 Serial.print("Distancia en centimetros capacidad: ");
 Serial.println(distanciaCm2);
 delay(1000);
 ultimaDist2 = distanciaCm2;

 if (distanciaCm2 = ultimaDist2 && distanciaCm2 <= 5) {
   bloqueado = true;
   }
 }
 //bloqueo
 if(bloqueado){
  digitalWrite(4, LOW);
  digitalWrite(2, HIGH);
  servo.write(0);
 }
 //Pulsador
 if (digitalRead(7) == HIGH){
  digitalWrite(3, LOW);
  tiempoAbierto = 0;
  abierto = true;
  while (abierto){
    servo.write(90);
    Serial.print("Tiempo de apertura: ");
    Serial.println(tiempoAbierto);
    tiempoAbierto = tiempoAbierto + 1;
    delay(1000);
    if (tiempoAbierto > 10) {
      abierto = false;
    }
  }
  bloqueado = false;
 }
}
