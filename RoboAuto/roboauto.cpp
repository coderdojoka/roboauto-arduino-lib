#include <Arduino.h>
#include "roboauto.h"

static Servo servo;
static int aktuellerWinkel;
int ultraschallAbstand;

void servoInit() {
  servo.attach(SERVO_PIN);
}

void linieInit() {
// für den Linienfolger
  pinMode(LINIE_LED_LINKS,INPUT);
  pinMode(LINIE_LED_MITTE,INPUT);
  pinMode(LINIE_LED_RECHTS,INPUT);
}

void initUltraschall(){ 
  // für das Ultraschallmodul
  pinMode(ULTRASCHALL_ECHO_PIN,INPUT);
  pinMode(ULTRASCHALL_TRIGGER_PIN,OUTPUT);
}

void initMotoren(){
    // Richtungs und Kontroll Ausgänge
    pinMode(RICHTUNG_RAEDER_LINKS_1,OUTPUT);
    pinMode(RICHTUNG_RAEDER_LINKS_2,OUTPUT);

    pinMode(RICHTUNG_RAEDER_RECHTS_1,OUTPUT);
    pinMode(RICHTUNG_RAEDER_RECHTS_2,OUTPUT);

    pinMode(KONTROLLE_RAEDER_LINKS, OUTPUT);
    pinMode(KONTROLLE_RAEDER_RECHTS ,OUTPUT);
}

int servoNachVorne() {     return servoSetzen(SERVO_VORNE);    }
int servoNachLinks() {     return servoSetzen(SERVO_LINKS);    }
int servoNachRechts(){     return servoSetzen(SERVO_RECHTS);   }
void servoWarteBisBewegt() { delay(servoWartezeit);      }
int servoDrehen(int um){
  return servoSetzen(aktuellerWinkel + um);
}

int servoSetzen(int winkel) {
  int tmp = max(SERVO_RECHTS,min(SERVO_LINKS,winkel));
  servoWartezeit = abs(aktuellerWinkel - tmp) * SERVO_MS_PRO_GRAD;
  aktuellerWinkel = winkel;
  servo.write(aktuellerWinkel);
  return servoWartezeit;
}

int linieLinks()   {  return !digitalRead(LINIE_LED_LINKS);  }
int linieMitte()   {  return !digitalRead(LINIE_LED_MITTE);   }
int linieRechts()  {  return !digitalRead(LINIE_LED_RECHTS); }

int ultraschallAbstandCM(){

  // sicherstellen, dass nicht HIGH
  digitalWrite(ULTRASCHALL_TRIGGER_PIN, LOW);   
  delayMicroseconds(2);
  
  // sende Signal für 10µs aus ->
  digitalWrite(ULTRASCHALL_TRIGGER_PIN, HIGH);  
  delayMicroseconds(10);
  digitalWrite(ULTRASCHALL_TRIGGER_PIN, LOW);   
  
  // <- misst Zeit bis HIGH gemessen wird (zurückreflektiert)
  // Default Abbruch-Timeout nach 1s
  float zeitHinundZurueckMS = pulseIn(ULTRASCHALL_ECHO_PIN, HIGH);  
  
  // geschwindigkeit * zeit / 2 => Abstand bis zum Hindernis
  ultraschallAbstand = (int)zeitHinundZurueckMS * SCHALLGESCHWINDIGKEIT_IN_CM_PER_US / 2;
  return ultraschallAbstand;
}


void geschwindigkeit(int geswLinks, int geswRechts) {
  analogWrite(KONTROLLE_RAEDER_LINKS, geswLinks);
  analogWrite(KONTROLLE_RAEDER_RECHTS, geswRechts);

}
void geschwindigkeit(int gesw) { geschwindigkeit(gesw, gesw); }

void rechtsStop(){
  digitalWrite(KONTROLLE_RAEDER_RECHTS, LOW);
}

void linksStop(){
  digitalWrite(KONTROLLE_RAEDER_LINKS, LOW);
}

void stop() {
  digitalWrite(KONTROLLE_RAEDER_LINKS, LOW);
  digitalWrite(KONTROLLE_RAEDER_RECHTS, LOW);   
}

void linksBlockieren() {
  digitalWrite(RICHTUNG_RAEDER_LINKS_1, HIGH);
  digitalWrite(RICHTUNG_RAEDER_LINKS_2, HIGH);   
}

void rechtsBlockieren() {
  digitalWrite(RICHTUNG_RAEDER_LINKS_1, HIGH);
  digitalWrite(RICHTUNG_RAEDER_LINKS_2, HIGH);   
}

void blockieren() {
  rechtsBlockieren();
  linksBlockieren();
}

void dreheLinksVorwaerts() {
  digitalWrite(RICHTUNG_RAEDER_LINKS_1, HIGH);
  digitalWrite(RICHTUNG_RAEDER_LINKS_2, LOW);   
}

void dreheLinksRueckwaerts() {
  digitalWrite(RICHTUNG_RAEDER_LINKS_1, LOW);
  digitalWrite(RICHTUNG_RAEDER_LINKS_2, HIGH);   
}
void dreheRechtsRueckwaerts() {
  digitalWrite(RICHTUNG_RAEDER_RECHTS_1, HIGH);
  digitalWrite(RICHTUNG_RAEDER_RECHTS_2, LOW);   
}
void dreheRechtsVorwaerts() {
  digitalWrite(RICHTUNG_RAEDER_RECHTS_1, LOW);
  digitalWrite(RICHTUNG_RAEDER_RECHTS_2, HIGH);   
}

void dreheRueckwaerts(){
  dreheRechtsRueckwaerts(); 
  dreheLinksRueckwaerts();
}

void dreheVorwaerts(){
  dreheRechtsVorwaerts(); 
  dreheLinksVorwaerts();
}


void fahreVorwaerts(int geschwindigkeit, int dauer){
  dreheVorwaerts();
  geschwindigkeit(geschwindigkeit);
  delay(dauer);
  stop();
}

void fahreRueckwaerts(int geschwindigkeit, int dauer){
  dreheRueckwaerts();
  geschwindigkeit(geschwindigkeit);
  delay(dauer);
  stop();
}

// TODO: Kurven testen
void fahreLinkskurve(int geschwindigkeit,int dauer){
  dreheVorwaerts();
  geschwindigkeit(geschwindigkeit * KURVE_INNEN_GESCHWINDIGKEITS_FAKTOR, geschwindigkeit)
  delay(dauer);
  stop();
}

void fahreRechtskurve(int dauer){
  dreheVorwaerts();
  geschwindigkeit(geschwindigkeit, geschwindigkeit * KURVE_INNEN_GESCHWINDIGKEITS_FAKTOR)
  delay(dauer);
  stop();
}