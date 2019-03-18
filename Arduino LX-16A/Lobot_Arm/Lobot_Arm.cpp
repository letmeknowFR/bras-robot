/**************************************************************\
 *                        LOBOT_ARM                            *
 *                                                             *
 *  Fichier source comprenant les fonctions liées à            *
 *  la lecture et écriture des données à envoyer sur           *
 *  la carte LX-16A pour piloter le(s) servo(s) présent(s)     *
 *                                                             *
 *  V0.1                                                       *
 *  By Khelaf HAMICI 04/03/2019                                *
/**************************************************************/

#include <Arduino.h>
#include "Lobot_Arm.h"

#define LOBOT_DEBUG 1  // Voir le retour de données sur le moniteur série

// Taille du paquet sur 16 Bits à envoyer qui doit être décomposer en deux parties A et B
#define GET_LOW_BYTE(A) (uint8_t)((A))
// Fonction qui stoque les huit bits inférieurs de A
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
// Fonction qui récupère les huit bits supérieurs de A
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
// Défini A comme 8 bits supérieurs et B comme 8 bits inférieurs qui seront fusionnés en un entier de 16 bits
#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_POS_READ             28

extern byte LobotCheckSum(byte buf[])   // Fonction qui calcule le format du paquet (obligatoire à la fin de transmission de la trame)
{
  byte i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) {
    temp += buf[i];
  }
  temp = ~temp;
  i = (byte)temp;
  return i;
}

void LobotSerialServoMove(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time)  // Défini la rotation du servo
{
  byte buf[10];
  if (position < 0)
    position = 0;
  if (position > 1000)
    position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
  SerialX.write(buf, 10);
}
int LobotSerialServoReceiveHandle(HardwareSerial &SerialX, byte *ret) // Fonction qui permet d'avoir un retour de données sur les datas envoyés et si le checksum est bon ou pas
{
  bool frameStarted = false;
  bool receiveFinished = false;
  byte frameCount = 0;
  byte dataCount = 0;
  byte dataLength = 2;
  byte rxBuf;
  byte recvBuf[32];
  byte i;

  while (SerialX.available()) {
    rxBuf = SerialX.read();
    delayMicroseconds(100);
    if (!frameStarted) {
      if (rxBuf == LOBOT_SERVO_FRAME_HEADER) {
        frameCount++;
        if (frameCount == 2) {
          frameCount = 0;
          frameStarted = true;
          dataCount = 1;
        }
      }
      else {
        frameStarted = false;
        dataCount = 0;
        frameCount = 0;
      }
    }
    if (frameStarted) {
      recvBuf[dataCount] = (uint8_t)rxBuf;
      if (dataCount == 3) {
        dataLength = recvBuf[dataCount];
        if (dataLength < 3 || dataCount > 7) {
          dataLength = 2;
          frameStarted = false;
        }
      }
      dataCount++;
      if (dataCount == dataLength + 3) {
        
#ifdef LOBOT_DEBUG
        Serial.println();
        Serial.print("RECEIVE DATA:");
        for (i = 0; i < dataCount; i++) {
          Serial.print(recvBuf[i], HEX);
          Serial.print(":");
        }
        Serial.println(" ");
#endif

        if (LobotCheckSum(recvBuf) == recvBuf[dataCount - 1]) {
          
#ifdef LOBOT_DEBUG
          Serial.println();
          Serial.println("Check SUM OK !");
          Serial.println("");
#endif

          frameStarted = false;
          memcpy(ret, recvBuf + 4, dataLength);
          return 1;
        }
        else
        {
#ifdef LOBOT_DEBUG
          Serial.println();
          Serial.println("ERROR Check SUM !");
          Serial.println("");
#endif
        return -1;
        }
      }
    }
  }
}

int LobotSerialServoReadPosition(HardwareSerial &SerialX, uint8_t id) // Fonction qui permet de connaître la position du servo
{
  int count = 10000;
  int ret;
  byte buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);

#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO Pos READ");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
#endif

  while (SerialX.available())
    SerialX.read();

  SerialX.write(buf, 6);

  while (!SerialX.available()) {
    count -= 1;
    if (count < 0)
      return -1;
  }

  if (LobotSerialServoReceiveHandle(SerialX, buf) > 0)
    ret = BYTE_TO_HW(buf[2], buf[1]);
  else
    ret = -1;

#ifdef LOBOT_DEBUG
  Serial.println(ret);
#endif
  return ret;
}

void LobotSerialServoSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID)    // Défini l'ID du servo
{
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
  SerialX.write(buf, 7);
}
