#ifndef ROBO_AUTO_h
#define ROBO_AUTO_h

#include "Servo.h"

#define SERVO_PIN 3
#define SERVO_MS_PRO_GRAD 15
#define SERVO_LINKS 160
#define SERVO_VORNE 90
#define SERVO_RECHTS 30

#define LINIE_LED_LINKS  2
#define LINIE_LED_MITTE  4
#define LINIE_LED_RECHTS 10
#define DUNKEL   0
#define HELL     1

#define IR_FERNBEDIENUNG_PIN    12


//     Left motor truth table
//  ENA         IN1               IN2         Description  
//  LOW   Not Applicable    Not Applicable    Motor is off
//  HIGH        LOW               LOW         Motor is stopped (brakes)
//  HIGH        HIGH              LOW         Motor is on and turning forwards
//  HIGH        LOW               HIGH        Motor is on and turning backwards
//  HIGH        HIGH              HIGH        Motor is stopped (brakes)

//     Right motor truth table
//  ENB         IN3             IN4         Description  
//  LOW   Not Applicable   Not Applicable   Motor is off
//  HIGH        LOW             LOW         Motor is stopped (brakes)
//  HIGH        LOW             HIGH        Motor is on and turning forwards
//  HIGH        HIGH            LOW         Motor is on and turning backwards
//  HIGH        HIGH            HIGH        Motor is stopped (brakes)      


#define RICHTUNG_RAEDER_LINKS_1 7
#define RICHTUNG_RAEDER_LINKS_2 8
#define RICHTUNG_RAEDER_RECHTS_1 9
#define RICHTUNG_RAEDER_RECHTS_2 11

#define KONTROLLE_RAEDER_LINKS    5
#define KONTROLLE_RAEDER_RECHTS   6


#define ULTRASCHALL_TRIGGER_PIN   A5
#define ULTRASCHALL_ECHO_PIN      A4
// Schallgeschwindigkeit: 334 m/s => 0.0334 cm/µs
#define SCHALLGESCHWINDIGKEIT_IN_CM_PER_US   0.0334 

// Liniensensor Helligkeitswerte
#define DUNKEL		1
#define HELL		0

#define KURVE_INNEN_GESCHWINDIGKEITS_FAKTOR .2

static int servoWartezeit;
extern int ultraschallAbstand;


// Servo - servo
void servoInit();
int servoDrehen(int um);
int servoSetzen(int winkel);
int servoNachVorne();
int servoNachLinks();
int servoNachRechts();
void servoWarteBisBewegt();

// IR Linien LEDS
void linieInit();
int linieLinks(); 
int linieMitte(); 
int linieRechts();

// Ultraschall
void initUltraschall();
int ultraschallAbstandCM();

// Motoren
void initMotoren();
void geschwindigkeit(int geschwindigkeitLinks, int geschwindigkeitRechts);
void geschwindigkeit(int g);

// Stop => Geschwindigkeit = 0
void stop();
void rechtsStop();
void linksStop();

// aktiv die Räder blockieren!
void blockieren();
void rechtsBblockieren();
void linksBblockieren();


// Drehrichtung
void dreheLinksVorwaerts();
void dreheLinksRueckwaerts();
void dreheRechtsVorwaerts();
void dreheRechtsRueckwaerts();
void dreheRueckwaerts();
void dreheVorwaerts();


// Bequemlichkeitsfunktionen
void fahreVorwaerts(int geschwindigkeit, int dauer);
void fahreRueckwaerts(int geschwindigkeit, int dauer);
void fahreLinkskurve(int geschwindigkeit, int dauer);
void fahreRechtskurve(int geschwindigkeit, int dauer);
#endif
