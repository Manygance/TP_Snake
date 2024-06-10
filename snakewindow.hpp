#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QMainWindow>
#include <QStackedWidget>

#include <iostream>

#include "jeu.hpp"
#include "sound.hpp"
#include "gamewindow.hpp"
#include "editorwindow.hpp"
#include "sound.hpp"
#include "mainmenu.hpp"

class SnakeWindow : public QMainWindow {
  Q_OBJECT

  public:
    SnakeWindow(QWidget *pParent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());

  private:
  // Events
    void paintEvent(QPaintEvent *event);
    void handlePlayClicked(int level);
    void handleExitClicked();
    void handleCreateMapClicked();

  // Attributs
    Jeu jeu;
    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;
};

#endif
