//
// Created by Maný on 5/1/2024.
//

#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QImage>
#include "jeu.hpp"


class GameWindow : public QMainWindow {
Q_OBJECT

protected:
    Jeu jeu;
    QPixmap fruit;
    QPixmap bodyVertical, bodyHorizontal, bodyTopLeft, bodyTopRight, bodyBottomLeft, bodyBottomRight, headUp, headDown, headLeft, headRight, tailUp, tailDown, tailLeft, tailRight;
    QPixmap background;
    QPixmap debug, textBox;
    QLabel *notStartedText;
    QLabel *scoreText;

public:
    GameWindow(int);
    void readLevelBackground();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startGame();
    void handleTimer();

    QMap<Position, QRect> grid; // Associe chaque position de la grille à une source rect

    void initGrid();
};
#endif //GAMEWINDOW_HPP