#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QMainWindow>
#include <QStackedWidget>
#include "jeu.hpp"
#include "mainmenu.hpp"
#include "sound.hpp"

class SnakeWindow : public QMainWindow {

    Q_OBJECT

  protected:
    Jeu jeu;
    QPixmap BG_Title_1, BG_Title_2;

    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;

  public:
    SnakeWindow(QWidget *pParent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());

  protected:
    void paintEvent(QPaintEvent *event);

    void handlePlayClicked(int level);
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
