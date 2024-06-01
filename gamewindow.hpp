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
    QPixmap floor, wall, fruit;
    QPixmap bodyVertical, bodyHorizontal, bodyTopLeft, bodyTopRight, bodyBottomLeft, bodyBottomRight, headUp, headDown, headLeft, headRight, tailUp, tailDown, tailLeft, tailRight;
    QPixmap BG_1;
    QPixmap debug, textBox;
    QPixmap player_1;

    int frame_number = 0;
    int frame_direction = 1;

public:
    GameWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startGame();
    void Clicked_Add_Wall();
    void Clicked_Remove_Wall();
    void handleTimer();

    QMap<Position, QRect> grid; // Associer chaque position de la grille à une source rect

    void initGrid() {
        for (int y = 0; y < jeu.getNbCasesY(); ++y) {
            for (int x = 0; x < jeu.getNbCasesX(); ++x) {
                Position pos(x, y);
                if (jeu.getCase(pos) != MUR ) {
                    int randomX = QRandomGenerator::global()->bounded(3);
                    int randomY = QRandomGenerator::global()->bounded(3);
                    QRect sourceRect(9 + (12 + randomX) * 25, 163 + randomY * 25, 24, 24);
                    grid[pos] = sourceRect;
                }
            }
        }
    }
};
#endif //GAMEWINDOW_HPP