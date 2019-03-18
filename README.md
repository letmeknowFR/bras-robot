Driver pour piloter des servos avec la carte LewanSoul LX-16A
=============================================================

LewanSoul LX-16A est un servo puissant bien que son utilisation nécessite de mettre en œuvre un protocole série personnalisé que vous devrez prélablement configurer avant utilisation (définir des identifiants uniques pour tous les servos, configurer les limites, etc.).
Le constructeur fournit un outil pour cela, mais ne fonctionne malheureusement que sous Windows.

Ce projet vise à combler les lacunes des utilisateurs autres que Windows. 
Il consiste en une bibliothèque qui est implémenté en une interface pour communiquer avec les servos en utilisant leur protocole.

Cette carte peut être piloté par :

	- Arduino
	- Mblock
	- Python
	- Logiciel constructeur (Windows)
