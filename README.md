Driver pour piloter des servos avec la carte LewanSoul LX-16A
=============================================================

LewanSoul LX-16A est un servo merveilleux bien que leur utilisation nécessite
mettre en œuvre un protocole série personnalisé et vous devez les configurer
avant utilisation (définir des identifiants uniques pour tous les servos, configurer les limites, etc.).
Le constructeur fournit un outil pour cela, mais cela ne fonctionne que sous Windows.

Ce projet vise à combler les lacunes des utilisateurs autres que Windows. 
Il consiste en une bibliothèque qui est implémenté en une interface pour communiquer 
avec les servos en utilisant leur protocole.

Cette carte peut être piloté par :
	
	- Mblock
	- Python
	- Logiciel constructeur (Windows)

