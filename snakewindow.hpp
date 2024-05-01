#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QMainWindow>
#include <QStackedWidget>
#include "jeu.hpp"
#include "mainmenu.hpp"

class SnakeWindow : public QMainWindow {

    Q_OBJECT

  protected:
    Jeu jeu;
    QPixmap pixmapCorps, pixmapTete, pixmapMur, pixmapFruit;

    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;

  public:
    SnakeWindow(QWidget *pParent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());

  protected:
    /*
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void Clicked_Add_Wall();
    void Clicked_Remove_Wall();
    void handleTimer();
     */

    void handlePlayClicked();
    void handleExitClicked();
    void handleCreateMapClicked();
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
