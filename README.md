# Pacman <!-- omit in toc -->

- [1. Introduction](#1-introduction)
- [2. How to play](#2-how-to-play)
- [3. How to build](#3-how-to-build)
  - [3.1. With Makefile](#31-with-makefile)
  - [3.2. With CMakeLists](#32-with-cmakelists)

## 1. Introduction
This is a 4th year project of INSA Centre Val de Loire. A pacman game with very simple rule: you are pacman and you try to survive, eat all the point and win the fantome.

## 2. How to play

- joueur 1 : les fleches
- joueur 2 : ZSQD

Veuillez utiliser le clavier francais (AZERTY) pour avoir une meilleur experience en jouant.

## 3. How to build
This build is target for Linux system (especially for Ubuntu)   
Qt5 must be presented in your system (install qt5 from homepage)

### 3.1. With Makefile
```bash
# In root project
make all
# Run
make run
```

### 3.2. With CMakeLists
```bash
# In root project
mkdir build
cd build/
# In build folder
cmake ..
make
cd ..
# In root project
cp build/bin/main .
./main
```
