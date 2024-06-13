#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QLabel>

#include <iostream>
#include <fstream>

#include "game.hpp"
#include "globalsettings.hpp"


/// @brief Classe de base pour la gestion des fenêtres de jeu
class GameWindow : public QMainWindow {
Q_OBJECT

public:
    GameWindow(Game*);
    void handleTimer();
    void paintEvent(QPaintEvent*);

    void reinit();

    virtual void onPaintEvent(QPainter*) = 0;

protected:
    /// @brief Pointeur vers le jeu
    Game* m_game;
    QPixmap m_fruitPixmap, m_terrainPixmap, m_pokemonPixmap, m_stairsPixmap, m_debugPixmap, m_textBoxPixmap;

    QString m_fontFamily;           // Police d'écriture pour les textes de la fenêtre

    /// @brief Grille permettant de positionner les images des cases du sol
    QMap<Position, QRect> m_groundGrid;

    int m_currentFrame;
    static const int frameSequenceLength = 9;
    static const int frameRepetitions = 3;
};

#endif