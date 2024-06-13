#include "snakewindow.hpp"

using namespace std;

SnakeWindow::SnakeWindow(QWidget *pParent, Qt::WindowFlags flags):QMainWindow(pParent, flags)
{

    // Initialisation de la fenêtre
    this->setWindowTitle("Snake by Thomas and Bastien");
    this->setFixedSize(WINDOW_COL*CASE_SIZE, WINDOW_ROWS*CASE_SIZE);

    // Creation du menu principal et ajout au stacked widget
    m_stackedWidget = new QStackedWidget(this);
    m_mainMenu = new MainMenu(this);
    m_stackedWidget->addWidget(m_mainMenu);
    m_stackedWidget->setCurrentWidget(m_mainMenu);
    setCentralWidget(m_stackedWidget);

    // Connexion des signaux du menu principal
    connect(m_mainMenu, &MainMenu::playClicked, this, &SnakeWindow::handlePlayClicked);
    connect(m_mainMenu, &MainMenu::exitClicked, this, &SnakeWindow::handleExitClicked);
    connect(m_mainMenu, &MainMenu::createMapClicked, this, &SnakeWindow::handleCreateMapClicked);

    // Initialisation du système de son
    initializeSoundSystem();
    playBackgroundMusic("./data/Music_Title.mp3");

}

SnakeWindow::~SnakeWindow() {
    if(m_game != nullptr)
        delete m_game;
}

void SnakeWindow::handlePlayClicked(int level) {
    m_game = new Game(level);
    m_game->reloadGame();

    PlayWindow *playWindow = new PlayWindow(m_game);
    m_stackedWidget->addWidget(playWindow);
    m_stackedWidget->setCurrentWidget(playWindow);
    playWindow->reinit();
    playWindow->update();

    stopBackgroundMusic();
    playBackgroundMusic("./data/Music_Game.mp3");
}

void SnakeWindow::handleExitClicked() {
    QCoreApplication::quit();
}

void SnakeWindow::handleCreateMapClicked() {
    m_game = new Game(1);
    m_game->reloadGame();

    EditorWindow *editorWindow = new EditorWindow(m_game);
    m_stackedWidget->addWidget(editorWindow);
    m_stackedWidget->setCurrentWidget(editorWindow);
    editorWindow->reinit();
    editorWindow->update();

    stopBackgroundMusic();
    playBackgroundMusic("./data/Music_Game.mp3");
}

void SnakeWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
}

