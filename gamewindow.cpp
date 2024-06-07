#include "gamewindow.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include "globalsettings.hpp"
#include <iostream>
#include "jeu.hpp"
#include <fstream>

using namespace std;

GameWindow::GameWindow(int level)
{

    jeu.setLevel(level);

    // Images récupérées ici : https://rembound.com/articles/creating-a-snake-game-tutorial-with-html5
    if(!bodyVertical.load("./data/body_vertical.png") or
       !bodyHorizontal.load("./data/body_horizontal.png") or
       !bodyTopLeft.load("./data/body_top_left.png") or
       !bodyTopRight.load("./data/body_top_right.png") or
       !bodyBottomLeft.load("./data/body_bottom_left.png") or
       !bodyBottomRight.load("./data/body_bottom_right.png") or
       !headUp.load("./data/head_up.png") or
       !headDown.load("./data/head_down.png") or
       !headLeft.load("./data/head_left.png") or
       !headRight.load("./data/head_right.png") or
       !tailUp.load("./data/tail_up.png") or
       !tailDown.load("./data/tail_down.png") or
       !tailLeft.load("./data/tail_left.png") or
       !tailRight.load("./data/tail_right.png") or
       !textBox.load("./data/textbox.png") or
       !debug.load("./data/debug.png") or
       !fruit.load("./data/fruit.png"))
    {
        cerr<<"Erreur lors du chargement des images"<<endl;
        exit(1);
    }

    readLevelBackground();

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

void GameWindow::readLevelBackground() {
    ifstream file(terrainTxtPaths[jeu.level]);
    string firstLine;
    getline(file, firstLine);
    file.close();

    QString backgroundImagePath = QString::fromStdString(firstLine);
    background.load(backgroundImagePath);
}

void GameWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    Position pos;

    // Dessine les cases
    for (pos.y = 0; pos.y < jeu.getNbCasesY(); pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++)
            if (jeu.getCase(pos) == MUR) {
                //painter.drawPixmap(pos.x*TAILLE_CASE, pos.y*TAILLE_CASE, wall);
                QRect sourceRect(9 + 4 * 25, 163 + 4 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (jeu.getCase(pos) == FRUIT) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
                painter.drawPixmap(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, fruit);
            } else if (jeu.getCase(pos) == SOL) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else
                painter.drawPixmap(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, debug);

    // Pour l'affichage au niveau de la text box
    for (pos.y = jeu.getNbCasesY(); pos.y < jeu.getNbCasesY() + 5; pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++) {
            if (pos.x == 0 and pos.y == 15) {
                QRect sourceRect(9 + 3 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 15) {
                QRect sourceRect(9 + 5 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0 and pos.y == 19) {
                QRect sourceRect(9 + 3 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0) {
                QRect sourceRect(9 + 3 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 15) {
                QRect sourceRect(9 + 4 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 19) {
                QRect sourceRect(9 + 4 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
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
            painter.drawPixmap(posTete.x * TAILLE_CASE, posTete.y * TAILLE_CASE, headLeft);
        else if (jeu.getDirection() == 1)
            painter.drawPixmap(posTete.x * TAILLE_CASE, posTete.y * TAILLE_CASE, headRight);
        else if (jeu.getDirection() == 2)
            painter.drawPixmap(posTete.x * TAILLE_CASE, posTete.y * TAILLE_CASE, headUp);
        else if (jeu.getDirection() == 3)
            painter.drawPixmap(posTete.x * TAILLE_CASE, posTete.y * TAILLE_CASE, headDown);

        // Pour la queue
        const Position &posQueue = snake.back();
        const Position &posAvantQueue = *(++snake.rbegin());

        //cout<<"x : "<<posQueue.x<<":"<<posAvantQueue.x<<endl;
        //cout<<"y : "<<posQueue.y<<":"<<posAvantQueue.y<<endl;

        if (posQueue.x == posAvantQueue.x)
            if (posQueue.y < posAvantQueue.y)
                painter.drawPixmap(posQueue.x * TAILLE_CASE, posQueue.y * TAILLE_CASE, tailDown);
            else if (posQueue.y > posAvantQueue.y)
                painter.drawPixmap(posQueue.x * TAILLE_CASE, posQueue.y * TAILLE_CASE, tailUp);
        if (posQueue.y == posAvantQueue.y)
            if (posQueue.x < posAvantQueue.x)
                painter.drawPixmap(posQueue.x * TAILLE_CASE, posQueue.y * TAILLE_CASE, tailRight);
            else if (posQueue.x > posAvantQueue.x)
                painter.drawPixmap(posQueue.x * TAILLE_CASE, posQueue.y * TAILLE_CASE, tailLeft);


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
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyHorizontal);
                else if (posPrec.x < posCorps.x && posNext.y > posCorps.y ||
                         posNext.x < posCorps.x && posPrec.y > posCorps.y)
                    // Angle Left-Down
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyBottomLeft);
                else if (posPrec.y < posCorps.y && posNext.y > posCorps.y ||
                         posNext.y < posCorps.y && posPrec.y > posCorps.y || posPrec.x == posNext.x)
                    // Vertical
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyVertical);
                else if (posPrec.y < posCorps.y && posNext.x < posCorps.x ||
                         posNext.y < posCorps.y && posPrec.x < posCorps.x)
                    // Angle Top-Left
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyTopLeft);
                else if (posPrec.x > posCorps.x && posNext.y < posCorps.y ||
                         posNext.x > posCorps.x && posPrec.y < posCorps.y)
                    // Angle Right-Up
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyTopRight);
                else if (posPrec.y > posCorps.y && posNext.x > posCorps.x ||
                         posNext.y > posCorps.y && posPrec.x > posCorps.x)
                    // Angle Down-Right
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, bodyBottomRight);
                else
                    painter.drawPixmap(posCorps.x * TAILLE_CASE, posCorps.y * TAILLE_CASE, debug); // pour le debug
            }
        }
    }

    painter.drawPixmap(0, 480, textBox);

    //cout<<jeu.GetStarted()<<"  "<<jeu.getScore()<<endl;

    if (!jeu.isStarted()) {
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
        jeu.togglePause();
        if (jeu.isPaused())
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
    if (!jeu.isStarted())
        jeu.setStarted();
    if (!jeu.isPaused())
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

void GameWindow::initGrid() {
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

