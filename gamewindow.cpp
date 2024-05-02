//
// Created by Maný on 5/1/2024.
//

#include "gamewindow.hpp"
#include <QPainter>
#include <QTimer>
#include "global_settings.hpp"
#include <iostream>
#include "jeu.hpp"

using namespace std;

GameWindow::GameWindow()
{
    int largeurCase, hauteurCase;

    if (pixmapCorps.load("./data/snake_corps.png")==false)
    {
        cout<<"Impossible d'ouvrir snake_corps.png"<<endl;
        exit(-1);
    }

    if (pixmapTete.load("./data/snake_tete.png")==false)
    {
        cout<<"Impossible d'ouvrir snake_tete.png"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    if (pixmapFruit.load("./data/fruit.png")==false)
    {
        cout<<"Impossible d'ouvrir fruit.png"<<endl;
        exit(-1);
    }

    jeu.init();

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::handleTimer);
    timer->start(100);

}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    Position pos;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for (pos.y=0;pos.y<jeu.getNbCasesY();pos.y++)
        for (pos.x=0;pos.x<jeu.getNbCasesX();pos.x++)
            if (jeu.getCase(pos)==MUR)
                painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase+TAILLE_BANDEAU*DEBUG, pixmapMur);
            else if (jeu.getCase(pos)==FRUIT)
                painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase+TAILLE_BANDEAU*DEBUG, pixmapFruit);



    // Dessine le serpent
    const list<Position> &snake = jeu.getSnake();
    if (!snake.empty())
    {
        list<Position>::const_iterator itSnake;
        const Position &posTete = snake.front();
        painter.drawPixmap(posTete.x*largeurCase, posTete.y*hauteurCase+TAILLE_BANDEAU*DEBUG, pixmapTete);

        for (itSnake=++snake.begin(); itSnake!=snake.end(); itSnake++)
            painter.drawPixmap(itSnake->x*largeurCase, itSnake->y*hauteurCase+TAILLE_BANDEAU*DEBUG, pixmapCorps);
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
        if (event->key()==Qt::Key_Left)
            jeu.setDirection(GAUCHE);
        else if (event->key()==Qt::Key_Right)
            jeu.setDirection(DROITE);
        else if (event->key()==Qt::Key_Up)
            jeu.setDirection(HAUT);
        else if (event->key()==Qt::Key_Down)
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

void GameWindow::Clicked_Add_Wall()
{
    cout<<"Ajout mur"<<endl;
    Position pos(rand()%(jeu.getNbCasesX()-1), rand()%(jeu.getNbCasesY()-1));

    while (jeu.getCase(pos)!=VIDE)
    {
        pos.x = rand()%(jeu.getNbCasesX()-1);
        pos.y = rand()%(jeu.getNbCasesY()-1);
    }

    //cout<<"Position mur : "<<pos.x<<" "<<pos.y<<endl;
    jeu.Add_Wall(pos);
}

void GameWindow::Clicked_Remove_Wall()
{
    cout<<"Suppression mur"<<endl;
    Position pos(rand()%(jeu.getNbCasesX()-1), rand()%(jeu.getNbCasesY()-1));;

    while (jeu.getCase(pos)!=MUR)
    {
        pos.x = rand()%(jeu.getNbCasesX()-1);
        pos.y = rand()%(jeu.getNbCasesY()-1);
    }
    //cout<<"Position vide : "<<pos.x<<" "<<pos.y<<endl;
    jeu.Remove_Wall(pos);
}

void GameWindow::startGame()
{
    jeu.init();
    update();
}