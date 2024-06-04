//
// Created by Maný on 6/4/2024.
//

#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP


#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QImage>
#include "jeu.hpp"

class EditorWindow : public QMainWindow {
Q_OBJECT

protected:
    Jeu jeu;
    QPixmap floor, wall, fruit;
    QPixmap bodyVertical, bodyHorizontal, bodyTopLeft, bodyTopRight, bodyBottomLeft, bodyBottomRight, headUp, headDown, headLeft, headRight, tailUp, tailDown, tailLeft, tailRight;
    QPixmap background;
    QPixmap debug, textBox;

public:
    EditorWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startEditor();
    void handleTimer();
    void setLevel(int level) {
        this->jeu.level = level;
    }

    QMap<Position, QRect> grid;

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


signals:
    void showLevel(int);


};


#endif //EDITORWINDOW_HPP
