//
// Created by Maný on 5/1/2024.
//

#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"


class GameWindow : public QMainWindow {
Q_OBJECT

protected:
    Jeu jeu;
    QPixmap pixmapCorps, pixmapTete, pixmapMur, pixmapFruit;


public:
    GameWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startGame();
    void Clicked_Add_Wall();
    void Clicked_Remove_Wall();
    void handleTimer();

};
#endif //GAMEWINDOW_HPP