#include "editorwindow.hpp"

using namespace std;

EditorWindow::EditorWindow(Game* game): GameWindow(game)
{
    const auto level1Button = new QPushButton("Carte 1", this);
    level1Button->setFont(QFont(m_fontFamily, 12));
    level1Button->setGeometry(0, 0, 160, 20);
    level1Button->move(40, 520);
    level1Button->setCursor(Qt::PointingHandCursor);
    level1Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto level2Button = new QPushButton("Carte 2", this);
    level2Button->setFont(QFont(m_fontFamily, 12));
    level2Button->setGeometry(0, 0, 200, 20);
    level2Button->move(40, 550);
    level2Button->setCursor(Qt::PointingHandCursor);
    level2Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto level3Button = new QPushButton("Carte 3", this);
    level3Button->setFont(QFont(m_fontFamily, 12));
    level3Button->setGeometry(0, 0, 200, 20);
    level3Button->move(40, 580);
    level3Button->setCursor(Qt::PointingHandCursor);
    level3Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto setTerrain1Button = new QPushButton("Appliquer fond 1", this);
    setTerrain1Button->setFont(QFont(m_fontFamily, 12));
    setTerrain1Button->setGeometry(0, 0, 200, 20);
    setTerrain1Button->move(210, 520);
    setTerrain1Button->setCursor(Qt::PointingHandCursor);
    setTerrain1Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto setTerrain2Button = new QPushButton("Appliquer fond 2", this);
    setTerrain2Button->setFont(QFont(m_fontFamily, 12));
    setTerrain2Button->setGeometry(0, 0, 200, 20);
    setTerrain2Button->move(210, 550);
    setTerrain2Button->setCursor(Qt::PointingHandCursor);
    setTerrain2Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto setTerrain3Button = new QPushButton("Appliquer fond 3", this);
    setTerrain3Button->setFont(QFont(m_fontFamily, 12));
    setTerrain3Button->setGeometry(0, 0, 200, 20);
    setTerrain3Button->move(210, 580);
    setTerrain3Button->setCursor(Qt::PointingHandCursor);
    setTerrain3Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto setTerrain4Button = new QPushButton("Appliquer fond 4", this);
    setTerrain4Button->setFont(QFont(m_fontFamily, 12));
    setTerrain4Button->setGeometry(0, 0, 200, 20);
    setTerrain4Button->move(420, 520);
    setTerrain4Button->setCursor(Qt::PointingHandCursor);
    setTerrain4Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto setTerrain5Button = new QPushButton("Appliquer fond 5", this);
    setTerrain5Button->setFont(QFont(m_fontFamily, 12));
    setTerrain5Button->setGeometry(0, 0, 200, 20);
    setTerrain5Button->move(420, 550);
    setTerrain5Button->setCursor(Qt::PointingHandCursor);
    setTerrain5Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto saveButton = new QPushButton("Sauvegarder", this);
    saveButton->setFont(QFont(m_fontFamily, 12));
    saveButton->setGeometry(0, 0, 200, 20);
    saveButton->move(420, 580);
    saveButton->setCursor(Qt::PointingHandCursor);
    saveButton->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    connect(level1Button, &QPushButton::clicked, this, [this]() { this->loadLevel(1); });
    connect(level2Button, &QPushButton::clicked, this, [this]() { this->loadLevel(2); });
    connect(level3Button, &QPushButton::clicked, this, [this]() { this->loadLevel(3); });
    connect(setTerrain1Button, &QPushButton::clicked, this, [this]() {setTerrainImage("./data/terrains/terrain_1.png");});
    connect(setTerrain2Button, &QPushButton::clicked, this, [this]() {setTerrainImage("./data/terrains/terrain_2.png");});
    connect(setTerrain3Button, &QPushButton::clicked, this, [this]() {setTerrainImage("./data/terrains/terrain_3.png");});
    connect(setTerrain4Button, &QPushButton::clicked, this, [this]() {setTerrainImage("./data/terrains/terrain_4.png");});
    connect(setTerrain5Button, &QPushButton::clicked, this, [this]() {setTerrainImage("./data/terrains/terrain_5.png");});
    connect(saveButton, &QPushButton::clicked, this, &EditorWindow::saveLevel);

    clearCache();
}

void EditorWindow::clearCache()
{
    int levelIndex = m_game->getLevelIndex();
    this->loadLevel(0);     // Passe au level 0 pour nettoyer les images
    this->loadLevel(1);
}

void EditorWindow::onPaintEvent(QPainter* painter)
{
}


void EditorWindow::mousePressEvent(QMouseEvent *event) {
    QPoint localMousePos = event->pos();  // Position locale de la souris

    int x = localMousePos.x() / CASE_SIZE;
    int y = localMousePos.y() / CASE_SIZE;

    if (x >= 0 && x < m_game->getNbCasesX() && y >= 0 && y < m_game->getNbCasesY()) {
        // Modifie la case
        if (m_game->getCase(x, y) == GROUND) {
            m_game->setCase(x, y, WALL);
        } else {
            m_game->setCase(x, y, GROUND);
        }
        update();
    }
}

void EditorWindow::loadLevel(int levelIndex) 
{
    string levelPath = GlobalSettings::levelPaths[levelIndex];
    LevelData* levelData = m_game->getLevelData();
    levelData->reloadLevelData(levelPath);

    m_game->setLevelIndex(levelIndex);
    m_game->reloadTerrain();

    // Mise à jour de la fenêtre
    reinit();
    update();
}

void EditorWindow::saveLevel() {

    ofstream file;
    file.open (GlobalSettings::levelPaths[m_game->getLevelIndex()]);

    file << m_game->getLevelData()->getTerrainImagePath() << "\n";

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (m_game->getCase(j, i) == WALL)
                file << "#"; // Ecrit un dièse pour une case WALL
            else 
                file << "."; // Ecrit un point pour une case GROUND
        }
        file << "\n"; // Nouvelle ligne après chaque ligne de la matrice
    }

    file.close();

}

void EditorWindow::setTerrainImage(std::string terrainImagePath) {
    m_game->getLevelData()->setTerrainImagePath(terrainImagePath);
    m_terrainPixmap.load(QString::fromStdString(terrainImagePath));
    update();
}