//
// Created by Maný on 6/4/2024.
//

#include "editorwindow.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "global_settings.hpp"
#include <iostream>
#include "jeu.hpp"
#include <QCursor>
#include <QMouseEvent>
#include <fstream>

using namespace std;

EditorWindow::EditorWindow()
{
    // Images récupérées ici : https://rembound.com/articles/creating-a-snake-game-tutorial-with-html5
    if(bodyVertical.load("./data/body_vertical.png")==false or
       bodyHorizontal.load("./data/body_horizontal.png")==false or
       bodyTopLeft.load("./data/body_top_left.png")==false or
       bodyTopRight.load("./data/body_top_right.png")==false or
       bodyBottomLeft.load("./data/body_bottom_left.png")==false or
       bodyBottomRight.load("./data/body_bottom_right.png")==false or
       headUp.load("./data/head_up.png")==false or
       headDown.load("./data/head_down.png")==false or
       headLeft.load("./data/head_left.png")==false or
       headRight.load("./data/head_right.png")==false or
       tailUp.load("./data/tail_up.png")==false or
       tailDown.load("./data/tail_down.png")==false or
       tailLeft.load("./data/tail_left.png")==false or
       tailRight.load("./data/tail_right.png")==false or
       wall.load("./data/wall.png")==false or
       fruit.load("./data/fruit.png")==false or
       floor.load("./data/floor.png")==false or
       debug.load("./data/debug.png")==false or
       textBox.load("./data/textbox.png")==false)
    {
        cerr<<"Erreur lors du chargement des images"<<endl;
        exit(1);
    }

    int randomIndex = QRandomGenerator::global()->bounded(1, 6); // Génère un nombre entre 1 et 5 inclusivement
    QString backgroundImagePath = QString("./data/BG_%1.png").arg(randomIndex);
    background.load(backgroundImagePath);

    QString fontPath = "./data/font.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId == -1) {
        cerr << "Erreur lors du chargement de la police d'écriture" << endl;
        exit(1);
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    const auto Maze_1_Button = new QPushButton("Maze 1", this);
    Maze_1_Button->setFont(QFont(fontFamily, 12));
    Maze_1_Button->setGeometry(0, 0, 160, 20);
    Maze_1_Button->move(40, 520);
    Maze_1_Button->setCursor(Qt::PointingHandCursor);
    Maze_1_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Maze_2_Button = new QPushButton("Maze 2", this);
    Maze_2_Button->setFont(QFont(fontFamily, 12));
    Maze_2_Button->setGeometry(0, 0, 200, 20);
    Maze_2_Button->move(40, 550);
    Maze_2_Button->setCursor(Qt::PointingHandCursor);
    Maze_2_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Personnalized_Button = new QPushButton("Personalized", this);
    Personnalized_Button->setFont(QFont(fontFamily, 12));
    Personnalized_Button->setGeometry(0, 0, 200, 20);
    Personnalized_Button->move(40, 580);
    Personnalized_Button->setCursor(Qt::PointingHandCursor);
    Personnalized_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_1_Button = new QPushButton("Set background 1", this);
    Set_BG_1_Button->setFont(QFont(fontFamily, 12));
    Set_BG_1_Button->setGeometry(0, 0, 200, 20);
    Set_BG_1_Button->move(210, 520);
    Set_BG_1_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_1_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_2_Button = new QPushButton("Set background 2", this);
    Set_BG_2_Button->setFont(QFont(fontFamily, 12));
    Set_BG_2_Button->setGeometry(0, 0, 200, 20);
    Set_BG_2_Button->move(210, 550);
    Set_BG_2_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_2_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_3_Button = new QPushButton("Set background 3", this);
    Set_BG_3_Button->setFont(QFont(fontFamily, 12));
    Set_BG_3_Button->setGeometry(0, 0, 200, 20);
    Set_BG_3_Button->move(210, 580);
    Set_BG_3_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_3_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_4_Button = new QPushButton("Set background 4", this);
    Set_BG_4_Button->setFont(QFont(fontFamily, 12));
    Set_BG_4_Button->setGeometry(0, 0, 200, 20);
    Set_BG_4_Button->move(420, 520);
    Set_BG_4_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_4_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_5_Button = new QPushButton("Set background 5", this);
    Set_BG_5_Button->setFont(QFont(fontFamily, 12));
    Set_BG_5_Button->setGeometry(0, 0, 200, 20);
    Set_BG_5_Button->move(420, 550);
    Set_BG_5_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_5_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto SaveButton = new QPushButton("Save", this);
    SaveButton->setFont(QFont(fontFamily, 12));
    SaveButton->setGeometry(0, 0, 200, 20);
    SaveButton->move(420, 580);
    SaveButton->setCursor(Qt::PointingHandCursor);
    SaveButton->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    connect(Maze_1_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(1); });
    connect(Maze_2_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(2); });
    connect(Personnalized_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(3); });
    connect(SaveButton, &QPushButton::clicked, this, &EditorWindow::saveMap);

}

void EditorWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    Position pos;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = wall.width();
    hauteurCase = wall.height();

    // Dessine les cases
    for (pos.y = 0; pos.y < jeu.getNbCasesY(); pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++)
            if (jeu.getCase(pos) == MUR) {
                //painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase, wall);
                QRect sourceRect(9 + 4 * 25, 163 + 4 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (jeu.getCase(pos) == FRUIT) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
                painter.drawPixmap(pos.x * largeurCase, pos.y * hauteurCase, fruit);
            } else if (jeu.getCase(pos) == SOL) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else
                painter.drawPixmap(pos.x * largeurCase, pos.y * hauteurCase, debug);

    // Pour l'affichage au niveau de la text box
    for (pos.y = jeu.getNbCasesY(); pos.y < jeu.getNbCasesY() + 5; pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++) {
            if (pos.x == 0 and pos.y == 15) {
                QRect sourceRect(9 + 3 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 15) {
                QRect sourceRect(9 + 5 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0 and pos.y == 19) {
                QRect sourceRect(9 + 3 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0) {
                QRect sourceRect(9 + 3 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 15) {
                QRect sourceRect(9 + 4 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 19) {
                QRect sourceRect(9 + 4 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * largeurCase, pos.y * hauteurCase, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            }
        }

    // Dessine le serpent
    const list<Position> &snake = jeu.getSnake();
    if (!snake.empty()) {

        list<Position>::const_iterator itSnake;

        const Position &posTete = snake.front();

        // Pour la tête
        if (jeu.getDirection() == 0)
            painter.drawPixmap(posTete.x * largeurCase, posTete.y * hauteurCase, headLeft);
        else if (jeu.getDirection() == 1)
            painter.drawPixmap(posTete.x * largeurCase, posTete.y * hauteurCase, headRight);
        else if (jeu.getDirection() == 2)
            painter.drawPixmap(posTete.x * largeurCase, posTete.y * hauteurCase, headUp);
        else if (jeu.getDirection() == 3)
            painter.drawPixmap(posTete.x * largeurCase, posTete.y * hauteurCase, headDown);

        // Pour la queue
        const Position &posQueue = snake.back();
        const Position &posAvantQueue = *(++snake.rbegin());

        //cout<<"x : "<<posQueue.x<<":"<<posAvantQueue.x<<endl;
        //cout<<"y : "<<posQueue.y<<":"<<posAvantQueue.y<<endl;

        if (posQueue.x == posAvantQueue.x)
            if (posQueue.y < posAvantQueue.y)
                painter.drawPixmap(posQueue.x * largeurCase, posQueue.y * hauteurCase, tailDown);
            else if (posQueue.y > posAvantQueue.y)
                painter.drawPixmap(posQueue.x * largeurCase, posQueue.y * hauteurCase, tailUp);
        if (posQueue.y == posAvantQueue.y)
            if (posQueue.x < posAvantQueue.x)
                painter.drawPixmap(posQueue.x * largeurCase, posQueue.y * hauteurCase, tailRight);
            else if (posQueue.x > posAvantQueue.x)
                painter.drawPixmap(posQueue.x * largeurCase, posQueue.y * hauteurCase, tailLeft);


        // Pour le corps
        if (AFFICHER_CORPS) {
            for (itSnake = ++snake.begin(); itSnake != --snake.end(); itSnake++) {
                Position posCorps = *itSnake;
                Position posNext = *next(itSnake);
                Position posPrec = *prev(itSnake);

                //cout<<"x : "<<posNext.x<<":"<<posCorps.x<<":"<<posPrec.x<<endl;
                //cout<<"y : "<<posNext.y<<":"<<posCorps.y<<":"<<posPrec.y<<endl;

                if (posPrec.x < posCorps.x && posNext.x > posCorps.x ||
                    posNext.x < posCorps.x && posPrec.x > posCorps.x || posPrec.y == posNext.y)
                    // Horizontal
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyHorizontal);
                else if (posPrec.x < posCorps.x && posNext.y > posCorps.y ||
                         posNext.x < posCorps.x && posPrec.y > posCorps.y)
                    // Angle Left-Down
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyBottomLeft);
                else if (posPrec.y < posCorps.y && posNext.y > posCorps.y ||
                         posNext.y < posCorps.y && posPrec.y > posCorps.y || posPrec.x == posNext.x)
                    // Vertical
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyVertical);
                else if (posPrec.y < posCorps.y && posNext.x < posCorps.x ||
                         posNext.y < posCorps.y && posPrec.x < posCorps.x)
                    // Angle Top-Left
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyTopLeft);
                else if (posPrec.x > posCorps.x && posNext.y < posCorps.y ||
                         posNext.x > posCorps.x && posPrec.y < posCorps.y)
                    // Angle Right-Up
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyTopRight);
                else if (posPrec.y > posCorps.y && posNext.x > posCorps.x ||
                         posNext.y > posCorps.y && posPrec.x > posCorps.x)
                    // Angle Down-Right
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, bodyBottomRight);
                else
                    painter.drawPixmap(posCorps.x * largeurCase, posCorps.y * hauteurCase, debug); // pour le debug
            }
        }
    }

    painter.drawPixmap(0, 480, textBox);
}

void EditorWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Space)
    {
        jeu.TogglePause();
        if (jeu.GetPaused())
        {
            cout<<"Jeu en pause"<<endl;

            QLabel *label = new QLabel(this);
            label->setText("Jeu en pause");
            label->setAlignment(Qt::AlignCenter);
            label->setGeometry(0, 0, width(), height());
            label->setStyleSheet("QLabel { background-color : rgba(0, 0, 0, 100); color : white; }");
            label->show();
        }
        else {
            cout << "Jeu en cours" << endl;

            QList<QLabel *> labels = findChildren<QLabel *>();
            for (QLabel *label : labels)
                label->close();
        }
    }
    if (event->key()==Qt::Key_Escape)
        QCoreApplication::quit();
    if (!jeu.GetStarted())
        jeu.setStarted();
    if (!jeu.GetPaused())
    {
        if (event->key()==Qt::Key_Left and jeu.getDirection()!=DROITE)
            jeu.setDirection(GAUCHE);
        else if (event->key()==Qt::Key_Right and jeu.getDirection()!=GAUCHE)
            jeu.setDirection(DROITE);
        else if (event->key()==Qt::Key_Up and jeu.getDirection()!=BAS)
            jeu.setDirection(HAUT);
        else if (event->key()==Qt::Key_Down and jeu.getDirection()!=HAUT)
            jeu.setDirection(BAS);
    }
    else
        return;
    update();
}

void EditorWindow::startEditor()
{
    jeu.readLevel();
    jeu.initLevel();
    initGrid();
    update();
}

void EditorWindow::mousePressEvent(QMouseEvent *event) {
    QPoint localMousePos = event->pos();  // Position locale de la souris

    int largeurCase = wall.width();
    int hauteurCase = wall.height();
    int x = localMousePos.x() / largeurCase;
    int y = localMousePos.y() / hauteurCase;

    if (x >= 0 && x < jeu.getNbCasesX() && y >= 0 && y < jeu.getNbCasesY()) {
        // Modifier la case
        if (jeu.getCase(x, y) == SOL) {
            jeu.setCase(x, y, MUR);
        } else {
            jeu.setCase(x, y, SOL);
        }
        update();
    }
}

void EditorWindow::loadMaze(int mazeIndex) {

    jeu.setLevel(mazeIndex);
    jeu.readLevel();
    jeu.initLevel();
    initGrid();
    update();

}

void EditorWindow::saveMap() {

    ofstream file;
    file.open (jeu.getLevelTxT());

    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (jeu.getCase(j, i) == MUR)
                file << "#"; // Écrire un point pour une case SOL
            else
                file << "."; // Écrire un dièse pour une case MUR
        }
        file << "\n"; // Nouvelle ligne après chaque ligne de la matrice
    }


    file.close();

}

