//
// Created by Maný on 6/4/2024.
//

#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP


#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QImage>
#include "jeu.hpp"

// TODO : voir si possible de faire une classe mère ?
class EditorWindow : public QMainWindow {
Q_OBJECT

protected:
    Jeu jeu;
    QPixmap fruit;
    QPixmap bodyVertical, bodyHorizontal, bodyTopLeft, bodyTopRight, bodyBottomLeft, bodyBottomRight, headUp, headDown, headLeft, headRight, tailUp, tailDown, tailLeft, tailRight;
    QPixmap background;
    QPixmap debug, textBox;
    std::string  levelBackground;

public:
    EditorWindow();
    std::string getLevelBackground();
    void setLevelBackground(const std::string& background);
    void applyLevelBackground();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void startEditor();
    void setLevel(int level) {
        this->jeu.level = level;
    }
    void mousePressEvent(QMouseEvent *event);

    QMap<Position, QRect> grid;

    void initGrid();

private slots:
    void loadMaze(int mazeIndex);
    void saveMap();

};


#endif //EDITORWINDOW_HPP
