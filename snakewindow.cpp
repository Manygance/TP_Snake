#include <iostream>
#include "snakewindow.hpp"
#include "gamewindow.hpp"
#include "editorwindow.hpp"
#include <QMainWindow>
#include "sound.hpp"
#include "mainmenu.hpp"

using namespace std;

SnakeWindow::SnakeWindow(QWidget *pParent, Qt::WindowFlags flags):QMainWindow(pParent, flags)
{

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

    initializeSoundSystem();
    playBackgroundMusic("./data/Music_Title.mp3");

}

void SnakeWindow::handlePlayClicked(int level) {
    GameWindow *gameWindow = new GameWindow(level);
    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);
    gameWindow->startGame();

    stopBackgroundMusic();
    playBackgroundMusic("./data/Music_Game.mp3");
}

void SnakeWindow::handleExitClicked() {
    QCoreApplication::quit();
}

void SnakeWindow::handleCreateMapClicked() {
    EditorWindow *mapEditor = new EditorWindow();
    stackedWidget->addWidget(mapEditor);
    stackedWidget->setCurrentWidget(mapEditor);

    mapEditor->startEditor();

    stopBackgroundMusic();
    playBackgroundMusic("./data/Music_Game.mp3");
}

void SnakeWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
}

