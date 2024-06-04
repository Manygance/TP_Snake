//
// Created by Maný on 5/1/2024.
//

#include "gamewindow.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "global_settings.hpp"
#include <iostream>
#include "jeu.hpp"

using namespace std;

GameWindow::GameWindow()
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

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::handleTimer);
    timer->start(100);

    QString fontPath = "./data/font.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId == -1) {
        cerr << "Erreur lors du chargement de la police d'écriture" << endl;
        exit(1);
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    notStartedText = new QLabel("Appuyer sur une touche pour commencer", this);
    notStartedText->setFont(QFont(fontFamily, 12));
    notStartedText->setGeometry(30, 510, 480, 20);
    notStartedText->setStyleSheet("color: white; font-size: 16px;");
    notStartedText->show();

    scoreText = new QLabel(this);
    scoreText->setFont(QFont(fontFamily, 12));
    scoreText->setGeometry(30, 540, 480, 20);
    scoreText->setStyleSheet("color: white; font-size: 16px;");
    scoreText->hide();

}

void GameWindow::paintEvent(QPaintEvent *) {
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

        // Afficher la textbox





    }


    painter.drawPixmap(0, 480, textBox);

    //cout<<jeu.GetStarted()<<"  "<<jeu.getScore()<<endl;

    if (!jeu.GetStarted()) {
        notStartedText->show();
        scoreText->hide();
    } else {
        notStartedText->hide();
        scoreText->setText("Score : " + QString::number(jeu.getScore()));
        scoreText->show();

    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
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

void GameWindow::handleTimer()
{
    jeu.evolue();
    update();
}


void GameWindow::startGame()
{
    jeu.init();
    initGrid();
    update();
}

