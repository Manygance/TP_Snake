#ifndef JEU_HPP
#define JEU_HPP

#include <list>
#include "global_settings.hpp"
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
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    std::list<Position> snake;
    Direction dirSnake;

    Position Pos_Fruit;
    bool pause;
    bool started;
    char terrain_defaut[LIGNES][COLONNES];
    int score;

    
  public:
    Jeu();
    Jeu(const Jeu &);
    ~Jeu();
    int level;

    Jeu &operator=(const Jeu &);

    bool init();
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la case à une position donnée
    Case getCase(const Position &) const;

    // Retourne la liste des éléments du serpent en lecture seule
    const std::list<Position> &getSnake() const;

    // Indique si la case à une position donnée existe et est libre
    bool posValide(const Position &) const;

    // Modifie la direction
    void setDirection(Direction);

    void Add_Wall(Position);
    void Remove_Wall(Position);
    void Add_Fruit_Random();
    void Remove_Fruit(Position);

    void TogglePause() {
        pause = !pause;
    }

    bool GetPaused() const {
        return pause;
    }

    bool GetStarted() const {
        return started;
    }

    void setStarted() {
        started = true;
    }

    void readLevel();
    void initLevel();
    void initFruit();

    char getCase(int x, int y){
        return terrain_defaut[y][x];
    }

    void setCase(int x, int y, char c){
        terrain_defaut[y][x] = c;
    }

    std::string getLevelTxT();

    void setLevel(int level) {
        this->level = level;
    }

    Direction getDirection() const {
        return dirSnake;
    }

    int getScore() const {
        return score;
    }
};

#endif
