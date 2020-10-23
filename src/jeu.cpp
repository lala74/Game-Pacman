#include "jeu.h"

#include <assert.h>

#include <iostream>

Fantome::Fantome()
{
    posX = 0;
    posY = 0;
    dir = BAS;
}

int Fantome::getPosX() const
{
    return posX;
}

int Fantome::getPosY() const
{
    return posY;
}

void Fantome::setPosX(const int x)
{
    posX = x;
}

void Fantome::setPosY(const int y)
{
    posY = y;
}

void Fantome::setDir(const Direction d)
{
    dir = d;
}

Jeu::Jeu()
{
    terrain = NULL;
    largeur = 0;
    hauteur = 0;
    nbGomme = 0;
}

Jeu::~Jeu()
{
    if(terrain != NULL) delete[] terrain;
}

bool Jeu::init()
{
    int x, y;
    list<Fantome>::iterator itFantome;

    const char terrain_defaut[15][21] = {"####################",
                                         "#x.......##.......x#",
                                         "#.#####..##...####.#",
                                         "#........##........#",
                                         "#..x...........x...#",
                                         "#......#....#......#",
                                         "#......#...##......#",
                                         "#####..#.x..#..#####",
                                         "#......##...#......#",
                                         "#......#....#..x...#",
                                         "#...x..............#",
                                         "#..........x.......#",
                                         "#.....#......#.....#",
                                         "#x....#......#....x#",
                                         "####################"};

    largeur = 20;
    hauteur = 15;

    terrain = new Case[largeur * hauteur];

    // Initialize par d�faut le nombre de Gomme = 0 et il y a qu'un seul joueur
    nbGomme = 0;
    nomJoueur = 1;

    for(y = 0; y < hauteur; ++y)
        for(x = 0; x < largeur; ++x)
            if(terrain_defaut[y][x] == '#') {
                terrain[y * largeur + x] = MUR;
            } else if(terrain_defaut[y][x] == '.') {
                terrain[y * largeur + x] = GOMME;  // Remplacer les . par le gomme
                nbGomme++;
            } else if(terrain_defaut[y][x] == 'x')
                terrain[y * largeur + x] = BONUS;  // Remplacer les x par le Bonus de vie

    fantomes.resize(4);

    // Initialize la position et direction des fantomes
    for(itFantome = fantomes.begin(); itFantome != fantomes.end(); itFantome++) {
        do {
            x = rand() % largeur;
            y = rand() % hauteur;
        } while(terrain[y * largeur + x] != VIDE && terrain[y * largeur + x] != GOMME);

        itFantome->posX = x;
        itFantome->posY = y;
        itFantome->dir = (Direction)(rand() % 4);
    }

    // Initialize le point, point de vie et la position des 2 Pacmans
    initPacman(&pacman1);
    initPacman(&pacman2);

    return true;
}

void Jeu::initPacman(Pacman* pacman)
{
    int x, y;
    pacman->point = 0;
    pacman->pointDeVie = 5;

    // Mettre le pacman sur un gomme
    do {
        x = rand() % largeur;
        y = rand() % hauteur;
    } while(terrain[y * largeur + x] != GOMME);

    pacman->posPacmanX = x;
    pacman->posPacmanY = y;
}

void Jeu::evolue()
{
    int testX, testY;
    list<Fantome>::iterator itFantome;

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    for(itFantome = fantomes.begin(); itFantome != fantomes.end(); itFantome++) {
        testX = itFantome->posX + depX[itFantome->dir];
        testY = itFantome->posY + depY[itFantome->dir];

        if(terrain[testY * largeur + testX] != MUR) {
            itFantome->posX = testX;
            itFantome->posY = testY;
        } else
            // Changement de direction
            itFantome->dir = (Direction)(rand() % 4);
    }
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

Case Jeu::getCase(int x, int y) const
{
    assert(x >= 0 && x < largeur && y >= 0 && y < hauteur);
    return terrain[y * largeur + x];
}

void Jeu::setCase(int x, int y, Case c)
{
    terrain[y * largeur + x] = c;
}

bool Jeu::posValide(int x, int y) const
{
    return (x >= 0 && x < largeur && y >= 0 && y < hauteur && terrain[y * largeur + x] != MUR);
}

bool Jeu::deplacePacman(Pacman* pacman, Direction dir)
{
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};
    int testX, testY;

    testX = pacman->posPacmanX + depX[dir];
    testY = pacman->posPacmanY + depY[dir];

    if(posValide(testX, testY)) {
        pacman->posPacmanX = testX;
        pacman->posPacmanY = testY;
        return true;
    } else
        return false;
}

// Les gommes
int Jeu::getNbGomme() const
{
    return nbGomme;
}

void Jeu::setNbGomme(int nb)
{
    nbGomme = nb;
}

// Les joueurs
int Jeu::getNomJoueur() const
{
    return nomJoueur;
}

void Jeu::setNomJoueur(int nom)
{
    nomJoueur = nom;
}

// Classe Pacman
Jeu::Pacman::Pacman() : posPacmanX(0), posPacmanY(0), point(0), pointDeVie(5) {}

Jeu::Pacman::Pacman(int x, int y, int p, int pVie) : posPacmanX(x), posPacmanY(y), point(p), pointDeVie(pVie) {}

int Jeu::Pacman::getPacmanX() const
{
    return posPacmanX;
}

int Jeu::Pacman::getPacmanY() const
{
    return posPacmanY;
}

int Jeu::Pacman::getPoint() const
{
    return point;
}

void Jeu::Pacman::setPoint(int p)
{
    point = p;
}

int Jeu::Pacman::getPointDeVie() const
{
    return pointDeVie;
}

void Jeu::Pacman::setPointDeVie(int pVie)
{
    pointDeVie = pVie;
}
