Driver Python pour Lewansoul LX-16A
==============================
Librairie pour piloter le(s) servo(s) moteur(s) avec la carte Lewansoul LX-16A via Python.

Installation
============
Il suffit d'installer un paquet pour l'utiliser:

```
( cd Python LX-16A && python setup.py install )
```

Pour lancer le code, vous pouvez envoyer la commande

"python Code_exemple"

Vous verrez à ce moment là, le servo aller à 100 puis à 500.

Code exemple
============

```python
import serial
import lewansoul_lx16a
import time

# Défini le port COM sur lequelle votre carte LX-16A est branché
# Vous pouvez vérifier ce port COM sur votre gestionnaire de périphérique
SERIAL_PORT = 'COM12' # Numéro du port COM '...'

# Initialise la vitesse du port série
controller = lewansoul_lx16a.ServoController(
    serial.Serial(SERIAL_PORT, 115200, timeout=1),
)

# Fait tourner le moteur sélectionné à une position définit
controller.move(1, 100) # Fait tourner le servo ID=1 à la position 100
time.sleep(2)           # Délai pour la rotation du servo
controller.move(1, 500) # Fait tourner le servo ID=1 à la position 500
time.sleep(2)           # Délai pour la rotation du servo
```

Open-Source
===========

Ce projet est tiré du github suivant:
```
https://github.com/maximkulkin/lewansoul-lx16a
```
