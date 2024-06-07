#ifndef JEU_HPP
#define JEU_HPP

#include <list>
#include "globalsettings.hpp"
#include <iostream>

typedef enum {SOL, MUR, FRUIT, DEBUG} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Position
{
  public:
    int x, y;
    Position();
    Position(int,int);
    bool operator==(const Position &) const;
    bool operator!=(const Position &) const;
    bool operator<(const Position &) const;
};

class Jeu
{
  private:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    std::list<Position> snake;
    Direction dirSnake;

    Position posFruit;
    bool paused;
    bool started;
    char terrainTxtDefault[LIGNES][COLONNES];       // TODO : trouver un moyen de supprimer (variable locale de fonction serait mieux)
    int score;

  public:
    Jeu();
    Jeu(const Jeu &);
    ~Jeu();
    int level;

    Jeu &operator=(const Jeu &);

    bool init();
    void loadTerrainTxt();
    void initTerrain();
    void initFruit();

    void evolue();

    int getNbCasesX() const;
    int getNbCasesY() const;
    Case getCase(const Position &) const;
    Case getCase(int, int) const;
    const std::list<Position> &getSnake() const;
    bool posValide(const Position &) const;

    void setDirection(Direction);
    void addRandomFruit();          // TODO : fusionner les deux fonctions en une "resetFruit"
    void removeFruit(Position);

    
    void setCase(int, int, Case);
    void setLevel(int);    
    Direction getDirection() const;
    int getScore() const;

    void togglePause();
    bool isPaused() const;
    bool isStarted() const;       // TODO : voir si encore utile ?
    void setStarted();
};

#endif
