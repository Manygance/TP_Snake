#ifndef JEU_HPP
#define JEU_HPP

#include <list>
#include <iostream>
#include <iostream>
#include <fstream>
#include <cassert>

#include "globalsettings.hpp"
#include "sound.hpp"


typedef enum
{
  SOL,
  MUR,
  FRUIT,
  ESCALIER,
  DEBUG
} Case;
typedef enum
{
  GAUCHE,
  DROITE,
  HAUT,
  BAS
} Direction;

class Position
{
public:
  int x, y;
  Position();
  Position(int, int);
  bool operator==(const Position &) const;
  bool operator!=(const Position &) const;
  bool operator<(const Position &) const;
};

class Jeu
{
private:
  char terrainTxtDefault[LIGNES][COLONNES]; // TODO : trouver un moyen de supprimer (variable locale de fonction serait mieux)
  Case *terrain;
  int levelIndex;
  int NextLevelCondition;
  int largeur, hauteur; // Nombre de cases en largeur et en hauteur
  std::list<Position> snake;
  Direction dirSnake;

  Position posFruit;
  Position posStair;
  int score;

  bool paused;
  bool started;
  bool stairsAdded;

public:
  Jeu();
  Jeu(const Jeu &);
  ~Jeu();

  Jeu &operator=(const Jeu &);

  static const std::string terrainTxtPaths[];
  static const int initialFruitNextLevelCondition[];

  bool init();
  void loadTerrainTxt();
  void initTerrain();
  void initFruit();
  void addStair();

  void takeStairs();

  void evolue();

  int getLevelIndex() const;
  int getNbCasesX() const;
  int getNbCasesY() const;
  int getInitialNextLevelCondition() const;
  int getNextLevelCondition() const;
  Case getCase(const Position &) const;
  Case getCase(int, int) const;
  const std::list<Position> &getSnake() const;
  bool posValide(const Position &) const;
  bool getStairsAdded() const;

  void setDirection(Direction);
  void addRandomFruit(); // TODO : fusionner les deux fonctions en une "resetFruit"
  void removeFruit(Position);

  void setCase(int, int, Case);
  void setLevel(int);
  Direction getDirection() const;
  int getScore() const;

  void togglePause();
  bool isPaused() const;
  bool isStarted() const; // TODO : voir si encore utile ?
  void setStarted();
};

#endif
