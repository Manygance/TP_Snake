#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QMainWindow>
#include <QStackedWidget>

#include <iostream>

#include "game.hpp"
#include "sound.hpp"
#include "playwindow.hpp"
#include "editorwindow.hpp"
#include "sound.hpp"
#include "mainmenu.hpp"

/// @brief Fenêtre principale du jeu, créée au lancement du programme.
class SnakeWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Constructeur de la fenêtre principale
    /// @param pParent Widget parent de la fenêtre
    /// @param flags Flags pour la création de la fenêtre
    SnakeWindow(QWidget *pParent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~SnakeWindow();

private:
    // Events
    void paintEvent(QPaintEvent *event);
    void handlePlayClicked(int levelIndex);
    void handleExitClicked();
    void handleCreateMapClicked();

    // Attributs
    Game* m_game;
    QStackedWidget *m_stackedWidget;
    MainMenu *m_mainMenu;
};

#endif
