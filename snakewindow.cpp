#include <iostream>
#include "snakewindow.hpp"
#include "gamewindow.hpp"
#include <QMainWindow>

using namespace std;

SnakeWindow::SnakeWindow(QWidget *pParent, Qt::WindowFlags flags):QMainWindow(pParent, flags)
{
    this->setWindowTitle("Snake by Thomas and Bastien");
    this->resize(COLONNES*TAILLE_CASE, LIGNES*TAILLE_CASE);
    stackedWidget = new QStackedWidget(this);
    mainMenu = new MainMenu(this);
    stackedWidget->addWidget(mainMenu);
    stackedWidget->setCurrentWidget(mainMenu);
    setCentralWidget(stackedWidget);

    connect(mainMenu, &MainMenu::playClicked, this, &SnakeWindow::handlePlayClicked);
    connect(mainMenu, &MainMenu::exitClicked, this, &SnakeWindow::handleExitClicked);
    connect(mainMenu, &MainMenu::createMapClicked, this, &SnakeWindow::handleCreateMapClicked);

}

void SnakeWindow::handlePlayClicked() {
    cout << "Play map clicked" << endl;
    GameWindow *gameWindow = new GameWindow();
    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);
    gameWindow->startGame();
}

void SnakeWindow::handleExitClicked() {
    cout << "Exit clicked" << endl;
    QCoreApplication::quit();
}

void SnakeWindow::handleCreateMapClicked() {
    cout << "Create map clicked" << endl;
    //stackedWidget->setCurrentWidget(mapEditor);
}

