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
    void paintEvent(QPaintEvent *event);  // Surcharge de la méthode paintEvent de QMainWindow
    void handlePlayClicked(int levelIndex); // Slot appelé lors du clic sur le bouton "Jouer"
    void handleExitClicked(); // Slot appelé lors du clic sur le bouton "Quitter"
    void handleCreateMapClicked(); // Slot appelé lors du clic sur le bouton "Créer une carte"

    // Attributs
    Game* m_game; // Pointeur vers le jeu en cours
    QStackedWidget *m_stackedWidget; // Widget empilé pour afficher les différentes fenêtres (menu principal, jeu, éditeur)
    MainMenu *m_mainMenu; // Widget du menu principal
};

#endif
