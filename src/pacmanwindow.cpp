#include "pacmanwindow.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool is_handle_timer_is_running = false;  // V�rifier si le handleTimer est entrain d'�tre connect� avec QTimer
                                          // Eviter de dupliquer la connection entre handleTimer et QTimer
                                          // (ca va augmenter la vitesse du jeu)

PacmanWindow::PacmanWindow(QWidget* pParent, Qt::WindowFlags flags) : QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if(pixmapPacman1.load("./data/1pacmanRIGHT.bmp") == false) {
        cout << "Impossible d'ouvrir pacman.png" << endl;
        exit(-1);
    }

    if(pixmapPacman2.load("./data/2pacmanRIGHT.bmp") == false) {
        cout << "Impossible d'ouvrir pacman.png" << endl;
        exit(-1);
    }

    if(pixmapPacman1Fixe.load("./data/1pacmanRIGHT.bmp") == false) {
        cout << "Impossible d'ouvrir pacman.png" << endl;
        exit(-1);
    }

    if(pixmapPacman2Fixe.load("./data/2pacmanRIGHT.bmp") == false) {
        cout << "Impossible d'ouvrir pacman.png" << endl;
        exit(-1);
    }

    if(pixmapFantome.load("./data/fantome.bmp") == false) {
        cout << "Impossible d'ouvrir fantome.bmp" << endl;
        exit(-1);
    }

    if(pixmapMur.load("./data/mur.bmp") == false) {
        cout << "Impossible d'ouvrir mur.bmp" << endl;
        exit(-1);
    }

    if(pixmapCoeur.load("./data/coeur.bmp") == false) {
        cout << "Impossible d'ouvrir coeur.bmp" << endl;
        exit(-1);
    }

    if(pixmapBonus.load("./data/bonus.bmp") == false) {
        cout << "Impossible d'ouvrir bonus.bmp" << endl;
        exit(-1);
    }

    if(pixmapGomme.load("./data/gomme.bmp") == false) {
        cout << "Impossible d'ouvrir gomme.bmp" << endl;
        exit(-1);
    }

    if(pixmapVide.load("./data/vide.bmp") == false) {
        cout << "Impossible d'ouvrir vide.bmp" << endl;
        exit(-1);
    }

    jeu.init();

    // Afficher IntroBox
    introduction();

    //  Ajout button "Ajout Fantome"
    PacmanButton* btn_ajout = new PacmanButton(this);
    btn_ajout->setFixedSize(100, 20);
    btn_ajout->setText("Ajout Fantome");
    btn_ajout->move(10, 10);
    connect(btn_ajout, &PacmanButton::clicked, this, &PacmanWindow::ajoutFantome);

    //  Ajout button "Suppr Fantome"
    PacmanButton* btn_suppr = new PacmanButton(this);
    btn_suppr->setFixedSize(100, 20);
    btn_suppr->setText("Suppr Fantome");
    btn_suppr->move(120, 10);
    connect(btn_suppr, &PacmanButton::clicked, this, &PacmanWindow::supprFantome);

    //  Ajout Label nomFantome
    nomFantome = new QLabel(this);
    nomFantome->setGeometry(QRect(QPoint(70, 45), QSize(130, 30)));
    nomFantome->setFont(QFont("Arial", 18));
    //  Ajout Label nomGomme
    nomGomme = new QLabel(this);
    nomGomme->setGeometry(QRect(QPoint(150, 45), QSize(130, 30)));
    nomGomme->setFont(QFont("Arial", 18));
    //  Ajout Label pointPacman1
    pointPacman1 = new QLabel(this);
    pointPacman1->setGeometry(QRect(QPoint(290, 5), QSize(130, 30)));
    pointPacman1->setFont(QFont("Arial", 18));
    //  Ajout Label pointPacman2
    pointPacman2 = new QLabel(this);
    pointPacman2->setGeometry(QRect(QPoint(290, 45), QSize(130, 30)));
    pointPacman2->setFont(QFont("Arial", 18));

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    //  Ralonger la fen�tre du jeu
    resize(jeu.getNbCasesX() * largeurCase, jeu.getNbCasesY() * hauteurCase + 80);
}

void PacmanWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for(y = 0; y < jeu.getNbCasesY(); y++)
        for(x = 0; x < jeu.getNbCasesX(); x++)
            if(jeu.getCase(x, y) == MUR)
                painter.drawPixmap(x * largeurCase, y * hauteurCase + 80, pixmapMur);
            else if(jeu.getCase(x, y) == GOMME)
                painter.drawPixmap(x * largeurCase, y * hauteurCase + 80, pixmapGomme);
            else if(jeu.getCase(x, y) == BONUS)
                painter.drawPixmap(x * largeurCase, y * hauteurCase + 80, pixmapBonus);
            else if(jeu.getCase(x, y) == VIDE)
                painter.drawPixmap(x * largeurCase, y * hauteurCase + 80, pixmapVide);

    // Dessine les fantomes
    for(itFantome = jeu.fantomes.begin(); itFantome != jeu.fantomes.end(); itFantome++)
        painter.drawPixmap(itFantome->getPosX() * largeurCase, itFantome->getPosY() * hauteurCase + 80, pixmapFantome);

    // Dessine Pacman 1
    if(isVivant(jeu.pacman1))
        painter.drawPixmap(
            jeu.pacman1.getPacmanX() * largeurCase, jeu.pacman1.getPacmanY() * hauteurCase + 80, pixmapPacman1);
    // Dessine Pacman 2
    if(jeu.getNomJoueur() == 2)
        if(isVivant(jeu.pacman2))
            painter.drawPixmap(
                jeu.pacman2.getPacmanX() * largeurCase, jeu.pacman2.getPacmanY() * hauteurCase + 80, pixmapPacman2);

    // Dessine Coeur Pacman 1
    for(int i = 1; i <= jeu.pacman1.getPointDeVie(); i++) painter.drawPixmap(400 + 40 * (i - 1), 5, pixmapCoeur);
    // Dessine Coeur Pacman 2
    if(jeu.getNomJoueur() == 2)
        for(int i = 1; i <= jeu.pacman2.getPointDeVie(); i++) painter.drawPixmap(400 + 40 * (i - 1), 45, pixmapCoeur);

    // Dessine Point Pacman 1
    painter.drawPixmap(250, 5, pixmapPacman1Fixe);
    // Dessine Point Pacman 2
    if(jeu.getNomJoueur() == 2) painter.drawPixmap(250, 45, pixmapPacman2Fixe);
    // Dessine Nombre Fantome
    painter.drawPixmap(30, 40, pixmapFantome);
    // Dessine Nombre Gomme
    painter.drawPixmap(110, 40, pixmapGomme);
}

void PacmanWindow::keyPressEvent(QKeyEvent* event)
{
    if(isVivant(jeu.pacman1)) {  // Verifier si le joueur est vivant
                                 // Si il est mort, il ne peut d�placer le pacman
        if(event->key() == Qt::Key_Left) {
            jeu.deplacePacman(&jeu.pacman1, GAUCHE);
            pixmapPacman1.load("./data/1pacmanLEFT.bmp");
        } else if(event->key() == Qt::Key_Right) {
            jeu.deplacePacman(&jeu.pacman1, DROITE);
            pixmapPacman1.load("./data/1pacmanRIGHT.bmp");
        } else if(event->key() == Qt::Key_Up) {
            jeu.deplacePacman(&jeu.pacman1, HAUT);
            pixmapPacman1.load("./data/1pacmanUP.bmp");
        } else if(event->key() == Qt::Key_Down) {
            jeu.deplacePacman(&jeu.pacman1, BAS);
            pixmapPacman1.load("./data/1pacmanDOWN.bmp");
        }
        update();
    }

    if(isVivant(jeu.pacman2)) {      // Verifier si le joueur est vivant
                                     // Si il est mort, il ne peut d�placer le pacman
        if(jeu.getNomJoueur() == 2)  // Si il y a 2 joueurs
        {
            if(event->key() == Qt::Key_Q) {
                jeu.deplacePacman(&jeu.pacman2, GAUCHE);
                pixmapPacman2.load("./data/2pacmanLEFT.bmp");
            } else if(event->key() == Qt::Key_D) {
                jeu.deplacePacman(&jeu.pacman2, DROITE);
                pixmapPacman2.load("./data/2pacmanRIGHT.bmp");
            } else if(event->key() == Qt::Key_Z) {
                jeu.deplacePacman(&jeu.pacman2, HAUT);
                pixmapPacman2.load("./data/2pacmanUP.bmp");
            } else if(event->key() == Qt::Key_S) {
                jeu.deplacePacman(&jeu.pacman2, BAS);
                pixmapPacman2.load("./data/2pacmanDOWN.bmp");
            }
        }
        update();
    }
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    collisionHandle();
    mangerHandle();
    gagnerHandle();
    afficheLabel();

    update();
}

void PacmanWindow::ajoutFantome()
{
    Fantome f;
    int x, y;
    Direction dir;
    // Initialize random position et direction
    do {
        x = rand() % jeu.getNbCasesX();
        y = rand() % jeu.getNbCasesY();
    } while(jeu.getCase(x, y) != VIDE && jeu.getCase(x, y) != GOMME);
    dir = (Direction)(rand() % 4);
    // Set position et direction pour la Fantome
    f.setPosX(x);
    f.setPosY(y);
    f.setDir(dir);
    jeu.fantomes.push_back(f);
}

void PacmanWindow::supprFantome()
{
    if(!jeu.fantomes.empty()) jeu.fantomes.pop_back();
}

// Collision
bool PacmanWindow::isCollision(Jeu::Pacman& pacman)
{
    int pacman_x, pacman_y;
    list<Fantome>::iterator itFantome;

    pacman_x = pacman.getPacmanX();
    pacman_y = pacman.getPacmanY();
    for(itFantome = jeu.fantomes.begin(); itFantome != jeu.fantomes.end(); itFantome++) {
        if(pacman_x == itFantome->getPosX() && pacman_y == itFantome->getPosY()) return true;
    }
    return false;
}

void PacmanWindow::collisionHandle()
{
    string message;
    ostringstream point;
    QString msg;
    if(isCollision(jeu.pacman1)) {
        if(jeu.pacman1.getPointDeVie() > 1) {
            jeu.pacman1.setPointDeVie(jeu.pacman1.getPointDeVie() - 1);
        } else {
            jeu.pacman1.setPointDeVie(0);
        }
    }
    if(jeu.getNomJoueur() == 2)
        if(isCollision(jeu.pacman2)) {
            if(jeu.pacman2.getPointDeVie() > 1) {
                jeu.pacman2.setPointDeVie(jeu.pacman2.getPointDeVie() - 1);
            } else {
                jeu.pacman2.setPointDeVie(0);
            }
        }

    // Perdu si le jeu est en mode seul et le joueur est mort
    if(jeu.getNomJoueur() == 1 && isVivant(jeu.pacman1) == false) perdu(jeu.pacman1.getPoint(), jeu.pacman2.getPoint());

    // Perdu si le jeu est en mode 2 joueurs et tout les 2 joueurs sont morts
    if(isVivant(jeu.pacman1) == false && isVivant(jeu.pacman2) == false)
        perdu(jeu.pacman1.getPoint(), jeu.pacman2.getPoint());
}

// Manger Handle
bool PacmanWindow::isMangerGomme(Jeu::Pacman& pacman)
{
    if(jeu.getCase(pacman.getPacmanX(), pacman.getPacmanY()) == GOMME)
        return true;
    else
        return false;
}

bool PacmanWindow::isMangerBonus(Jeu::Pacman& pacman)
{
    if(jeu.getCase(pacman.getPacmanX(), pacman.getPacmanY()) == BONUS)
        return true;
    else
        return false;
}

void PacmanWindow::mangerHandle()
{
    if(isMangerGomme(jeu.pacman1)) {
        jeu.setCase(jeu.pacman1.getPacmanX(), jeu.pacman1.getPacmanY(), VIDE);
        jeu.setNbGomme(jeu.getNbGomme() - 1);
        jeu.pacman1.setPoint(jeu.pacman1.getPoint() + 1);
    } else if(jeu.getNomJoueur() == 2) {
        if(isMangerGomme(jeu.pacman2)) {
            jeu.setCase(jeu.pacman2.getPacmanX(), jeu.pacman2.getPacmanY(), VIDE);
            jeu.setNbGomme(jeu.getNbGomme() - 1);
            jeu.pacman2.setPoint(jeu.pacman2.getPoint() + 1);
        }
    }

    if(isMangerBonus(jeu.pacman1)) {
        jeu.setCase(jeu.pacman1.getPacmanX(), jeu.pacman1.getPacmanY(), VIDE);
        jeu.pacman1.setPoint(jeu.pacman1.getPoint() + 5);  // 1 bonus  = 5 gommes
        if(jeu.pacman1.getPointDeVie() < 5)                // limit du point de vie = 5
            jeu.pacman1.setPointDeVie(jeu.pacman1.getPointDeVie() + 1);
    } else if(jeu.getNomJoueur() == 2) {
        if(isMangerBonus(jeu.pacman2)) {
            jeu.setCase(jeu.pacman2.getPacmanX(), jeu.pacman2.getPacmanY(), VIDE);
            jeu.pacman2.setPoint(jeu.pacman2.getPoint() + 5);  // limit du point de vie = 5
            if(jeu.pacman2.getPointDeVie() < 5) jeu.pacman2.setPointDeVie(jeu.pacman2.getPointDeVie() + 1);
        }
    }
}

// Gagner Handle
bool PacmanWindow::isGagner()
{
    if(jeu.getNbGomme() > 0)
        return false;
    else
        return true;
}

void PacmanWindow::gagnerHandle()
{
    if(isGagner()) gagner(jeu.pacman1.getPoint(), jeu.pacman2.getPoint());
}

bool PacmanWindow::isVivant(Jeu::Pacman& pacman)
{
    if(pacman.getPointDeVie() == 0)
        return false;
    else
        return true;
}
// Gestion des taches du jeu
void PacmanWindow::gagner(int p1, int p2)
{
    string message;
    ostringstream point1, point2;
    QString msg;
    point1 << p1 * 100;
    point2 << p2 * 100;
    if(jeu.getNomJoueur() == 1)
        message = "Vous avez gagne " + point1.str() + " points";
    else if(jeu.getNomJoueur() == 2)
        message = "Pacman 1 a gagne " + point1.str() + " points\nPacman 2 a gagne " + point2.str() + " points";

    msg = QString::fromLocal8Bit(message.c_str());

    QMessageBox gagnerBox;
    gagnerBox.setText("Felicitations ! YOLO");
    gagnerBox.setInformativeText(msg);

    QPushButton* btn_rejouer = gagnerBox.addButton("Rejouer", QMessageBox::AcceptRole);
    connect(btn_rejouer, &QPushButton::clicked, this, &PacmanWindow::rejouer);

    QPushButton* btn_sortir = gagnerBox.addButton("Sortir", QMessageBox::AcceptRole);
    connect(btn_sortir, &QPushButton::clicked, this, &PacmanWindow::sortir);

    gagnerBox.exec();
}

void PacmanWindow::perdu(int p1, int p2)
{
    string message;
    ostringstream point1, point2;
    QString msg;
    point1 << p1 * coef;
    point2 << p2 * coef;
    if(jeu.getNomJoueur() == 1)
        message = "Vous etes gagne " + point1.str() + " points";
    else if(jeu.getNomJoueur() == 2)
        message = "Pacman 1 a gagne " + point1.str() + " points\nPacman 2 a gagne " + point2.str() + " points";
    msg = QString::fromLocal8Bit(message.c_str());

    QMessageBox perduBox;
    perduBox.setText("Vous etes perdu !");
    perduBox.setInformativeText(msg);

    QPushButton* btn_rejouer = perduBox.addButton("Rejouer", QMessageBox::AcceptRole);
    connect(btn_rejouer, &QPushButton::clicked, this, &PacmanWindow::rejouer);

    QPushButton* btn_sortir = perduBox.addButton("Sortir", QMessageBox::AcceptRole);
    connect(btn_sortir, &QPushButton::clicked, this, &PacmanWindow::sortir);

    perduBox.exec();
}

void PacmanWindow::sortir()
{
    this->close();
}

void PacmanWindow::rejouer()
{
    jeu.init();

    introduction();
}

void PacmanWindow::introduction()
{
    QMessageBox introBox;
    introBox.setText("Joueur 1: les fleches\nJoueur 2: ZSQD");

    QPushButton* btn_un = introBox.addButton("1 joueur", QMessageBox::AcceptRole);
    connect(btn_un, &QPushButton::clicked, this, &PacmanWindow::setUnJoueur);

    QPushButton* btn_deux = introBox.addButton("2 joueurs", QMessageBox::AcceptRole);
    connect(btn_deux, &QPushButton::clicked, this, &PacmanWindow::setDeuxJoueurs);

    introBox.exec();
}

// Set le jeu en mode seul
void PacmanWindow::setUnJoueur()
{
    cout << "Vous avez choisi le mode 1 joueur" << endl;
    jeu.setNomJoueur(1);
    if(!is_handle_timer_is_running)  // Assurer qu'on n'a pas connecter handleTimer avec QTimer plusieurs fois
    {
        handleHandleTimer();
        is_handle_timer_is_running = true;
    }
}

void PacmanWindow::setDeuxJoueurs()
{
    cout << "Vous avez choisi le mode detruire le friendship" << endl;
    jeu.setNomJoueur(2);
    if(!is_handle_timer_is_running) {
        handleHandleTimer();
        is_handle_timer_is_running = true;
    }
}

// Handler of handleTimer
void PacmanWindow::handleHandleTimer()
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PacmanWindow::handleTimer);
    timer->start(100);
}

// LABEL
void PacmanWindow::afficheLabel()
{
    nomFantome->setText(QString(("x " + to_string(jeu.fantomes.size())).c_str()));
    nomFantome->show();

    nomGomme->setText(QString(("x " + to_string(jeu.getNbGomme())).c_str()));
    nomGomme->show();

    // Label pour le pacman 1
    pointPacman1->setText(QString((": " + to_string(jeu.pacman1.getPoint() * coef)).c_str()));
    pointPacman1->show();

    // Label pour le pacman 2
    if(jeu.getNomJoueur() == 2) {
        pointPacman2->setText(QString((": " + to_string(jeu.pacman2.getPoint() * coef)).c_str()));
        pointPacman2->show();
    }
}

// Classe PacmanButton
PacmanButton::PacmanButton(QWidget* parent) : QPushButton(parent) {}

void PacmanButton::keyPressEvent(QKeyEvent* e)
{
    if(parent() != NULL) QCoreApplication::sendEvent(parent(), e);
}
