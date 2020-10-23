#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "jeu.h"


class PacmanWindow : public QFrame
{
protected:
    Jeu jeu;
    int coef = 100;  // Coefficient des points
    QPixmap pixmapFantome, pixmapMur, pixmapCoeur, pixmapBonus, pixmapGomme, pixmapVide;
    QPixmap pixmapPacman1, pixmapPacman2, pixmapPacman1Fixe, pixmapPacman2Fixe;
    // Ajouter les Labels pour afficher le point de pacman, le nombre de fantome, le nombre des gommes restant
    QLabel* nomFantome = new QLabel();
    QLabel* nomGomme = new QLabel();
    QLabel* pointPacman1 = new QLabel();
    QLabel* pointPacman2 = new QLabel();

public:
    PacmanWindow(QWidget* pParent = 0, Qt::WindowFlags flags = 0);

    void handleTimer();
    void handleHandleTimer();  // connecte handleTimer � QTimer
    void ajoutFantome();       // ajouter un fantome
    void supprFantome();       // supprimer un fantome

    bool isCollision(Jeu::Pacman&);  // verifier la collision entre Pacman et Fantome
                                     //
    void collisionHandle();          // diminuer le point de vie chaque collision

    bool isMangerGomme(Jeu::Pacman&);  // verifier la collision entre Pacman et les Gommes
    bool isMangerBonus(Jeu::Pacman&);  // verifier la collision entre Pacman et le point de vie
    void mangerHandle();               // augmenter le point ou point de vie

    bool isGagner();      // verifier si le joueur est gagn� (manger tous les gommes)
    void gagnerHandle();  // appeler la fonction gagner

    bool isVivant(Jeu::Pacman&);  // verifier si un joueur (un pacman) est vivant

    void gagner(int, int);  // afficher le point de chaque joueur
                            // arr�ter le jeu et demander si le joueur a envie de rejoueur ou de sortir
    void perdu(int, int);   // afficher le point de chaque joueur
                            // arr�ter le jeu et demander si le joueur a envie de rejoueur ou de sortir

    void sortir();   // fermer la fen�tre PacmanWindow
    void rejouer();  // initialize le jeu et ouvrir IntroBox

    void introduction();    // IntroBox demander si le joueur veut jouer en mode seul ou � 2 joueurs
    void setUnJoueur();     // Set le jeu en mode seul
    void setDeuxJoueurs();  // Set le jeu en mode 2 joueurs

    void afficheLabel();  // Afficher tous les labels

protected:
    void paintEvent(QPaintEvent*);

    // Deplacement le PACMAN
    void keyPressEvent(QKeyEvent*);
};

class PacmanButton : public QPushButton
{
protected:
    void keyPressEvent(QKeyEvent*);

public:
    PacmanButton(QWidget* parent = 0);
};

#endif
