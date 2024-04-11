#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"

class SnakeWindow : public QFrame
{
  protected:
    Jeu jeu;
    QPixmap pixmapCorps, pixmapTete, pixmapMur, pixmapFruit;

  public:
    SnakeWindow(QWidget *pParent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());
    void handleTimer();

  protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void Clicked_Add_Wall();
    void Clicked_Remove_Wall();
};

class CustomPushButton : public QPushButton
{
    public:
    CustomPushButton(QWidget *pParent=nullptr):QPushButton(pParent){}

    void keyPressEvent(QKeyEvent *e)
    {
        if (parent()!=nullptr)
            QCoreApplication::sendEvent(parent(), e);
    }
};

#endif
