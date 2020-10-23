#ifndef _JEU_H_
#define _JEU_H_

#include <list>
using namespace std;

typedef enum { VIDE, MUR, GOMME, BONUS } Case;  // Ajouter 2 characteritiques de Case (GOMME, BONUS de vie)
typedef enum { GAUCHE, DROITE, HAUT, BAS } Direction;

class Jeu;

class Fantome
{
    friend class Jeu;

protected:
    int posX, posY;
    Direction dir;

public:
    Fantome();
    int getPosX() const;
    int getPosY() const;
    void setPosX(const int);
    void setPosY(const int);

    void setDir(const Direction);
};

class Jeu
{
    // Classe imbriqu� Pacman
public:
    class Pacman
    {
        friend class Jeu;

    protected:
        int posPacmanX, posPacmanY;
        int point;       // les gommes mang�es
        int pointDeVie;  // les points de vie restant
    public:
        // Constructeur
        Pacman();
        Pacman(int, int, int, int);

        // Retourne la position de Pacman
        int getPacmanX() const;
        int getPacmanY() const;

        // Retourne le point
        int getPoint() const;
        void setPoint(int);

        // Retourne le point de vie
        int getPointDeVie() const;
        void setPointDeVie(int);
    };

protected:
    Case* terrain;
    int largeur, hauteur;  // Nombre de cases en largeur et en hauteur

    int nbGomme;    // Nombre les gommes restants sur la carte
    int nomJoueur;  // Nombre de joueur

public:
    list<Fantome> fantomes;

public:
    // Initialize 2 pacmans
    Pacman pacman1;
    Pacman pacman2;

    Jeu();
    Jeu(const Jeu&) = delete;
    ~Jeu();

    Jeu& operator=(const Jeu&) = delete;

    bool init();
    void initPacman(Pacman*);  // Initialize la position initiale de pacman

    // Deplacement les fantomes
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la case � une position donn�e
    Case getCase(int, int) const;
    void setCase(int, int, Case);

    // Retourne le nombre de gomme restant
    int getNbGomme() const;
    void setNbGomme(int);

    // Retourne le nombre de Joueur
    int getNomJoueur() const;
    void setNomJoueur(int);

    // Indique si la case � une position donn�e existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // D�place Pacman dans une direction (si la case � atteindre est valide)
    bool deplacePacman(Pacman*, Direction);
};

#endif
