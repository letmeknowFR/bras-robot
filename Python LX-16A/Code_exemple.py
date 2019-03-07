"""														  
                      Lobot_Arm
  ************************************************
  * Code d'exemple pour faire une rotation sur   * 
  * le servo n°3 avec la carte Lobot LX-16A      *
  ************************************************
  V0.1
  By Khelaf HAMICI 04/03/2019 
"""														  


import serial
import lewansoul_lx16a
import time

# Le port COM sur lequelle votre carte est branché.
SERIAL_PORT = 'COM3' # Numéro du port COM '...'

# Initialise la vitesse du port série
controller = lewansoul_lx16a.ServoController(
    serial.Serial(SERIAL_PORT, 115200, timeout=1),
)

# Fait tourner le moteur sélectionné à une position définit
controller.move(4, 100) # Fait tourner le servo ID=3 à la position 100
time.sleep(2)           # Délai pour la rotation du servo
controller.move(4, 500) # Fait tourner le servo ID=3 à la position 500
time.sleep(2)           # Délai pour la rotation du servo
