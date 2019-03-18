/*******************************************************************\
 *                       LOBOT_ARM                                  *
 *                                                                  *
 * Fichier d'en tete contenant les définitions disponibles          *
 * liées à la lecture et écriture des données à envoyer sur         *
 * la carte LX-16A pour piloté le(s) servo(s) présent(s)            *
 *                                                                  *
 * V0.1                                                             *   
 * By Khelaf HAMICI 04/03/2019                                      *
/********************************************************************/
#pragma once // Indique au compilateur qui implémente cette directive de ne plus lire le fichier à partir de la seconde fois, ce qui accèlére la compilation. 
#include <Arduino.h>

extern byte LobotCheckSum();
void LobotSerialServoMove(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time);
void LobotSerialServoSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID);
int LobotSerialServoReadPosition(HardwareSerial &SerialX, uint8_t id);
int LobotSerialServoReceiveHandle(HardwareSerial &SerialX, byte *ret);
