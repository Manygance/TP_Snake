#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <iostream>
#include <iostream>
#include <fstream>
#include <cassert>

#include "leveldata.hpp"
#include "globalsettings.hpp"
#include "sound.hpp"

/// @brief Enumération définissant un type de case dans l'espace de jeu.
typedef enum
{
    GROUND,
    WALL,
    FRUIT,
    STAIRS,
    DEBUG
} Case;

/// @brief Enumération définissant une direction dans l'espace de jeu.
typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;

/// @brief Classe définissant une position dans l'espace de jeu.
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


/// @brief Classe gérant le comportement du jeu.
class Game
{
public:
    Game(int);
    Game(const Game &);
    ~Game();

    Game &operator=(const Game &);

    /// Fonctions générales rechargeant le jeu
    bool reloadGame();
    void reloadTerrain();

    // Fonctions de gestion du terrain
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Fonctions de contrôle du jeu
    void update();
    void togglePause();
    bool isPaused() const;
    bool isStarted() const;
    void setStarted(bool);
    bool isReloaded() const;

    // Fonctions de gestion des éléments de jeu
    void addStairs();
    void pickFruit(const Position &);
    void resetFruit();
    void takeStairs();
    bool hasStairsAdded() const;
    int getScore() const;

    Case getCase(const Position &) const;
    Case getCase(int, int) const;
    void setCase(int, int, Case);
    bool isPosValid(const Position &) const;

    // Fonctions de contrôle du "snake"
    const std::list<Position> &getSnake() const;
    Direction getSnakeDirection() const;
    void setSnakeDirection(Direction);

    // Fonctions de gestion du niveau et du score
    void reloadLevelData();               // TODO : à réaliser dans les windows, et passer un pointeur en argument du game ?
    void loadNextLevel();
    LevelData* getLevelData();
    int getLevelIndex() const;
    void setLevelIndex(int);
    int getNextLevelCondition() const;

private:
    // Variables de gestion des niveaux
    LevelData* m_levelData;
    int m_levelIndex;
    int m_nextLevelCondition;           // Valeur représentant la condition pour l'apparition du niveau suivant. Ce score est décrémenté à chaque fois qu'un fruit est ramassé. Lorsqu'il atteint 0, l'escalier apparaît.
    
    // Variables du terrain
    Case *m_terrain;
    int m_width, m_height; // Nombre de cases en largeur et en hauteur
    
    // Variables du "snake"
    std::list<Position> m_snake;
    Direction m_snakeDir;

    // Variables des éléments du jeu
    Position m_fruitPos;
    Position m_stairsPos;
    
    // Variables d'état du jeu
    int m_score;
    bool m_paused;
    bool m_started;
    bool m_reloaded;
    bool m_stairsAdded;

};

#endif
