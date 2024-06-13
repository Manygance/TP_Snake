#include "gamewindow.hpp"

using namespace std;

GameWindow::GameWindow(Game *game) : m_game(game)
{
    // Chargement des ressources de base        # TODO : basculer tous les chemins dans globalsettings
    if (!m_textBoxPixmap.load("./data/textbox.png") ||
        !m_debugPixmap.load("./data/debug.png") ||
        !m_fruitPixmap.load("./data/fruit.png") ||
        !m_pokemonPixmap.load("./data/pokemon.png") ||
        !m_stairsPixmap.load("./data/stairs.png"))
    {
        cerr << "Erreur lors du chargement des images de base." << endl;
        exit(1);
    }
    
    // Initialisation des polices d'écriture
    QString fontPath = "./data/font.ttf";           // TODO : déplacer dans les globalsettings
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId == -1)
    {
        cerr << "Erreur lors du chargement de la police d'écriture." << endl;
        exit(1);
    }
    m_fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    // Lancement du timer
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::handleTimer);
    timer->start(100);
    m_currentFrame = 0;
}

void GameWindow::handleTimer()
{
    if(m_game->isReloaded())
    {
        reinit();
    }

    m_game->update();
    update();           // Mise à jour de la fenêtre Qt
}

void GameWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    Position pos;

    /**/
    // Affichage du terrain (cases)
    // TODO : définir les positions des rects dans les globalsettings
    for (pos.y = 0; pos.y < m_game->getNbCasesY(); pos.y++)
        for (pos.x = 0; pos.x < m_game->getNbCasesX(); pos.x++)
            if (m_game->getCase(pos) == WALL)
            {
                QRect sourceRect(9 + 4 * 25, 163 + 4 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (m_game->getCase(pos) == FRUIT)
            {
                QRect sourceRect = m_groundGrid[pos];
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
                painter.drawPixmap(pos.x * CASE_SIZE, pos.y * CASE_SIZE, m_fruitPixmap);
            }
            else if (m_game->getCase(pos) == GROUND)
            {
                QRect sourceRect = m_groundGrid[pos];
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (m_game->getCase(pos) == STAIRS)
            {
                QRect sourceRect(0, 0, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_stairsPixmap, sourceRect);
            }
            else
            {
                painter.drawPixmap(pos.x * CASE_SIZE, pos.y * CASE_SIZE, m_debugPixmap);
            }

    // Affichage du fond de la boîte de texte
    for (pos.y = m_game->getNbCasesY(); pos.y < m_game->getNbCasesY() + 5; pos.y++)
        for (pos.x = 0; pos.x < m_game->getNbCasesX(); pos.x++)
        {
            if (pos.x == 0 and pos.y == 15)
            {
                QRect sourceRect(9 + 3 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.x == 19 and pos.y == 15)
            {
                QRect sourceRect(9 + 5 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.x == 0 and pos.y == 19)
            {
                QRect sourceRect(9 + 3 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.x == 19 and pos.y == 19)
            {
                QRect sourceRect(9 + 5 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.x == 19)
            {
                QRect sourceRect(9 + 5 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.x == 0)
            {
                QRect sourceRect(9 + 3 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.y == 15)
            {
                QRect sourceRect(9 + 4 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
            else if (pos.y == 19)
            {
                QRect sourceRect(9 + 4 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * CASE_SIZE, pos.y * CASE_SIZE, 32, 32);
                painter.drawPixmap(destRect, m_terrainPixmap, sourceRect);
            }
        }

    // Affichage de la zone de texte
    painter.drawPixmap(0, 480, m_textBoxPixmap);


    // Appel du comportement spécifique pour l'héritage
    onPaintEvent(&painter);
    m_currentFrame++;
}

void GameWindow::reinit()
{
    // Chargement de l'image pour le terrain
    QString terrainImagePath = QString::fromStdString(m_game->getLevelData()->getTerrainImagePath());
    m_terrainPixmap.load(terrainImagePath);

    // Construction de la grille
    for (int y = 0; y < m_game->getNbCasesY(); ++y)
    {
        for (int x = 0; x < m_game->getNbCasesX(); ++x)
        {
            Position pos(x, y);
            if (m_game->getCase(pos) != WALL)
            {
                int randomX = QRandomGenerator::global()->bounded(3);
                int randomY = QRandomGenerator::global()->bounded(3);
                QRect sourceRect(9 + (12 + randomX) * 25, 163 + randomY * 25, 24, 24);
                m_groundGrid[pos] = sourceRect;
            }
        }
    }
}