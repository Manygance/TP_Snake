#include <iostream>
#include "snakewindow.hpp"
#include "gamewindow.hpp"
#include <QMainWindow>
#include "sound.hpp"

using namespace std;

SnakeWindow::SnakeWindow(QWidget *pParent, Qt::WindowFlags flags):QMainWindow(pParent, flags)
{

    initializeSoundSystem();
    playBackgroundMusic("./data/Music_Title.mp3");

    this->setWindowTitle("Snake by Thomas and Bastien");
    this->setFixedSize(COLONNES_FENETRE*TAILLE_CASE, LIGNES_FENETRE*TAILLE_CASE);

    stackedWidget = new QStackedWidget(this);
    mainMenu = new MainMenu(this);
    stackedWidget->addWidget(mainMenu);
    stackedWidget->setCurrentWidget(mainMenu);
    setCentralWidget(stackedWidget);

    connect(mainMenu, &MainMenu::playClicked, this, &SnakeWindow::handlePlayClicked);
    connect(mainMenu, &MainMenu::exitClicked, this, &SnakeWindow::handleExitClicked);
    connect(mainMenu, &MainMenu::createMapClicked, this, &SnakeWindow::handleCreateMapClicked);


}

void SnakeWindow::handlePlayClicked(int level) {
    //cout << "Play map clicked" << endl;
    GameWindow *gameWindow = new GameWindow();
    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);

    stopBackgroundMusic();
    playBackgroundMusic("./data/Music_Game.mp3");

    gameWindow->setLevel(level);
    gameWindow->startGame();
}

void SnakeWindow::handleExitClicked() {
    //cout << "Exit clicked" << endl;
    QCoreApplication::quit();
}

void SnakeWindow::handleCreateMapClicked() {
    //cout << "Create map clicked" << endl;
    //stackedWidget->setCurrentWidget(mapEditor);
}

void SnakeWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
}

