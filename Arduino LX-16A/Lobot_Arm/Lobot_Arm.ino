/*******************************************************************\
 *                          LOBOT_ARM                               *
 *                                                                  *
 *  Code pour forcer l'ID de tous les servos connectés à l'ID1      *
 *  et faire une rotation de 100 à 500.                             *                                 
 *                                                                  *
 *  V0.1                                                            *
 *  By Khelaf HAMICI 04/03/2019                                     *
\*******************************************************************/

#include "Lobot_Arm.h"

#define ID1 1  //Servo ID1
#define ID2 2  //Servo ID2
#define ID3 3  //Servo ID3
#define ID4 4  //Servo ID4
#define ID5 5  //Servo ID5
#define ID6 6  //Servo ID6
#define ID7 7  //Servo ID7
#define ID8 8  //Servo ID8

void LobotSerialServoMove();

void setup() {
   Serial.begin(115200);  // Débit d'initialisation
  //LobotSerialServoSetID(Serial, 254, ID1);   // Défini tous les servos présents à l'ID n°1

}
void loop() {
  
  LobotSerialServoMove(Serial, ID4, 100, 500);   // Fait tourner le servo ID n°1 à la position 100 en 500ms
  delay(1000);    // Delai d'exécution pour le servo
  LobotSerialServoReadPosition(Serial,ID4);
  LobotSerialServoMove(Serial, ID4, 500, 500);   // Fait tourner le servo ID n°1 sur 500 en 500ms
  delay(1000);    // Delai d'exécution pour le servo
  
}
