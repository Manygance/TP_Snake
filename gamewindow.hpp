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

#include "jeu.hpp"
#include "globalsettings.hpp"


class GameWindow : public QMainWindow {
Q_OBJECT

protected:
    Jeu jeu;
    QPixmap fruit;
    QPixmap bodyVertical, bodyHorizontal, bodyTopLeft, bodyTopRight, bodyBottomLeft, bodyBottomRight, headUp, headDown, headLeft, headRight, tailUp, tailDown, tailLeft, tailRight;
    QPixmap background, pokemon;
    QPixmap debug, textBox;
    QLabel *notStartedText;
    QLabel *scoreText;
    int frame;
    const int SEQUENCE_LENGTH = 9;
    const int REPETITIONS = 3;

public:
    GameWindow(int);
    void readLevelBackground();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startGame();
    void handleTimer();

    QMap<Position, QRect> grid;

    void initGrid();
};
#endif //GAMEWINDOW_HPP