Fait en Novembre 2024 avec la libraire SDL2.
Le makefile est compatible uniquement avec linux.

Installez SDL2 via le apt :
- sudo apt update
- sudo apt install libsdl2-dev libsdl2-ttf-dev

pour compiler le jeu :
- make 

pour executer le programme :
- ./bin/pacman

pour nettoyer l'exécutable et les fichiers .o :
- make clean

Les fichiers utilitaires pour compiler le programme sous Windows sont fournis :
- les bibliothèques de liens dynamiques (.dll) sont dans : bin/
- les bibliothèques de liens statiques (.a) sont dans : lib/SDL2/
- les includes (.h) sont dans : lib/SDL2/include/SDL2/

A vous de faire la compilation sur Windows avec les fichiers fournis
