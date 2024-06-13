#include "game.hpp"

using namespace std;

Position::Position(){}

Position::Position(int a, int b)
{
    x=a;
    y=b;
}

bool Position::operator==(const Position &pos) const
{
    return (x==pos.x && y==pos.y);
}

bool Position::operator!=(const Position &pos) const
{
    return (x!=pos.x || y!=pos.y);
}

bool Position::operator<(const Position &pos) const
{
    return (x<pos.x || (x==pos.x && y<pos.y));
}

Game::Game(int levelIndex): m_levelIndex(levelIndex)
{
    m_terrain = nullptr;
    m_width = 0; m_height = 0;
    m_snakeDir = RIGHT;
    m_paused = false;
    m_started = false;
    m_reloaded = false;
    m_fruitPos.x = rand()%(m_width-1);
    m_fruitPos.y = rand()%(m_height-1);
    m_score = 0;
    m_levelData = nullptr;
}

Game::Game(const Game &game):m_snake(game.m_snake)
{
    m_width = game.m_width;
    m_height = game.m_height;
    m_snakeDir = game.m_snakeDir;
    m_paused = game.m_paused;
    m_reloaded = game.m_reloaded;
    m_fruitPos.x = rand()%(m_width-1);
    m_fruitPos.y = rand()%(m_height-1);
    m_levelIndex = game.m_levelIndex;
    m_score = 0;

    if (game.m_terrain!=nullptr)
    {
        m_terrain = new Case[m_width*m_height];
        for (int c=0; c<m_width*m_height; c++)
            m_terrain[c] = game.m_terrain[c];
    }
    else
        m_terrain = nullptr;

    m_levelData = nullptr;
}

Game::~Game()
{
    if (m_terrain!=nullptr)
        delete[] m_terrain;
    if (m_levelData != nullptr)
        delete m_levelData;
}

Game &Game::operator=(const Game &game)
{
    if (m_terrain!=nullptr)
        delete[] m_terrain;

    m_width = game.m_width;
    m_height = game.m_height;
    m_snakeDir = game.m_snakeDir;
    m_snake = game.m_snake;

    if (game.m_terrain!=nullptr)
    {
        m_terrain = new Case[m_width*m_height];
        for (int c=0; c<m_width*m_height; c++)
            m_terrain[c] = game.m_terrain[c];
    }
    else
        m_terrain = nullptr;
    return *this;
}

bool Game::reloadGame()
{
    // Chargement des données du niveau
    reloadLevelData();

    m_started = false;
    m_snakeDir = RIGHT;
    m_score = 0;
    m_stairsAdded = false;

    m_nextLevelCondition = GlobalSettings::nextLevelConditions[m_levelIndex];

    reloadTerrain(); // Rechargement du terrain
    resetFruit();   // Réinitialisation de la position du fruit

    int snakeLength = 5; // Longueur du serpent au début
    m_snake.clear(); // Vide la liste du serpent

    Position headPos; // Position de la tête du serpent
    headPos.x = 15;
    headPos.y = 8; 
	for (int i=0; i<snakeLength; i++)
    {
        m_snake.push_back(headPos);
        headPos.x--;
    }

    return true;
}

void Game::reloadTerrain(){

    int x, y;
    m_width = COLUMNS;
    m_height = ROWS;

    m_terrain = new Case[m_width*m_height];

    // Remplissage du terrain avec les données du niveau
    for(y=0;y<ROWS;++y)
        for(x=0;x<COLUMNS;++x)
            if (m_levelData->getTerrainTxtCase(y, x)=='#')
                m_terrain[y*m_width+x] = WALL;
            else if (m_levelData->getTerrainTxtCase(y, x)=='.')
                m_terrain[y*m_width+x] = GROUND;
            else
                m_terrain[y*m_width+x] = DEBUG;
}

void Game::update()
{
    if(m_reloaded)                 // Signal bref, supprimé à l'update. Peut être capturé par une fenêtre pour détecter un changement de niveau.
        m_reloaded = false;

    if (m_paused || !m_started) // Si pause ou jeu non démarré, on ne fait rien
    {
        return;
    }

    Position testPos;
	list<Position>::iterator snakeIt;

    // [0] droite, [1] gauche, [2] haut, [3] bas
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    testPos.x = (m_snake.front().x + depX[m_snakeDir] + m_width) % m_width;
    testPos.y = (m_snake.front().y + depY[m_snakeDir] + m_height) % m_height;


    if(m_terrain[testPos.y * m_width + testPos.x] == STAIRS && m_levelIndex != LEVEL_MAX) // Si la case est un escalier on les prend
    {
        takeStairs();
    }
    else if (isPosValid(testPos)) { // Si la case est valide, on avance
        m_snake.pop_back(); // Supprime la dernière case du serpent
        m_snake.push_front(testPos); // Ajoute une case à la tête du serpent
        if (m_terrain[testPos.y * m_width + testPos.x] == FRUIT) {
            m_snake.push_back(m_snake.back()); // Ajoute une case à la fin du serpent
            pickFruit(testPos);     // Collecte le fruit et incrémente le score
            resetFruit();           
        }
    }
    else { // Sinon, on a perdu
        reloadGame();
    }

    // Ajout des escaliers si la condition est valide
    if (!m_stairsAdded && m_levelIndex != 0 && m_nextLevelCondition <= 0)
        addStairs();
}

void Game::pickFruit(const Position& pos)
{
    m_score += 10;
    if (m_nextLevelCondition != 0)
        m_nextLevelCondition--;
    m_terrain[pos.y*m_width+pos.x] = GROUND;
    playSoundEffect("./data/Item_Sound.mp3");           // TODO : appeler plutôt dans la fenêtre
}

void Game::resetFruit() {
    bool isSnake; // Vérifie si la position du fruit est sur le serpent

    do // On cherche une position valide pour le fruit
    {
        isSnake = false;
        m_fruitPos.x = rand()%(m_width-1);
        m_fruitPos.y = rand()%(m_height-1);
        for(list<Position>::const_iterator it = m_snake.begin(); it != m_snake.end(); it++) // On vérifie que la position n'est pas sur le serpent
        {
            if(*it == m_fruitPos)
                isSnake = true;
        }
    } while (m_terrain[m_fruitPos.y*m_width+m_fruitPos.x] != GROUND || isSnake);

    m_terrain[m_fruitPos.y*m_width+m_fruitPos.x] = FRUIT;
}

void Game::takeStairs() {
    // On réinitialise le jeu pour le niveau suivant
    m_stairsAdded = false;
    loadNextLevel();
}

bool Game::hasStairsAdded() const {
    return m_stairsAdded;
}

void Game::reloadLevelData()
{
    // Réinitialisation du pointeur
    if (m_levelData != nullptr)
        delete m_levelData;
    m_levelData = nullptr;

    // Chargement des données du niveau
    string levelPath = GlobalSettings::levelPaths[m_levelIndex];           // TODO : voir si possible (et intéressant) d'éviter de passer par là pour sélectionner le niveau ?
    if(m_levelData == nullptr)
        m_levelData = new LevelData(levelPath);
    else
        m_levelData->reloadLevelData(levelPath);
}

void Game::loadNextLevel()
{
    // TODO : traiter le fait qu'on a atteint le dernier niveau
    m_started = false;
    m_reloaded = true;
    m_levelIndex++;
    reloadGame();
}

LevelData* Game::getLevelData()
{
    return m_levelData;
}

int Game::getLevelIndex() const
{
    return m_levelIndex;
}

int Game::getNbCasesX() const
{
    return m_width;
}

int Game::getNbCasesY() const
{
    return m_height;
}

Case Game::getCase(const Position &pos) const
{
    assert(pos.x>=0 && pos.x<m_width && pos.y>=0 && pos.y<m_height);
    return m_terrain[pos.y*m_width+pos.x];
}

const list<Position> &Game::getSnake() const
{
    return m_snake;
}

bool Game::isPosValid(const Position &pos) const
{
    if (pos.x>=0 && pos.x<m_width && pos.y>=0 && pos.y<m_height
        && m_terrain[pos.y*m_width+pos.x] == GROUND || m_terrain[pos.y * m_width + pos.x] == FRUIT)
    {
        list<Position>::const_iterator itSnake;
        itSnake = m_snake.begin();
        while (itSnake!=m_snake.end() && *itSnake!=pos)
            itSnake++;
        return (itSnake==m_snake.end());
    }
    else
        return false;
}

void Game::setSnakeDirection(Direction dir)
{
    m_snakeDir = dir;
}

void Game::addStairs() {

    do
    {
        m_stairsPos.x = rand()%(m_width-1);
        m_stairsPos.y = rand()%(m_height-1);
    } while (m_terrain[m_stairsPos.y*m_width+m_stairsPos.x] != GROUND and (m_terrain[m_stairsPos.y*m_width+m_stairsPos.x] != FRUIT));

    m_terrain[m_stairsPos.y*m_width+m_stairsPos.x] = STAIRS;
    m_stairsAdded = true;
}

void Game::togglePause() {
    m_paused = !m_paused;
}

bool Game::isPaused() const {
    return m_paused;
}

bool Game::isStarted() const {
    return m_started;         
}

bool Game::isReloaded() const {
    return m_reloaded;
}

void Game::setStarted(bool started) {
    m_started = started;
}

Case Game::getCase(int x, int y) const {
    return m_terrain[y*m_width+x];
}

void Game::setCase(int x, int y, Case c){
    m_terrain[y*m_width+x] = c;
}

void Game::setLevelIndex(int levelIndex) {
    m_levelIndex = levelIndex;
}

int Game::getNextLevelCondition() const {
    return m_nextLevelCondition;
}

Direction Game::getSnakeDirection() const {
    return m_snakeDir;
}

int Game::getScore() const
{
    return m_score;
}