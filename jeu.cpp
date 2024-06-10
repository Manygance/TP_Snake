#include "jeu.hpp"

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

const std::string Jeu::terrainTxtPaths[] = {"level_1.txt", "level_2.txt", "level_3.txt", "level_4.txt"};        // Initialisation du tableau de niveaux

Jeu::Jeu()
{
    terrain = nullptr;
    largeur = 0; hauteur = 0;
    dirSnake = DROITE;
    paused = false;
    started = false;
    posFruit.x = rand()%(largeur-1);
    posFruit.y = rand()%(hauteur-1);
    char terrain_defaut[LIGNES][COLONNES]={0};
    levelIndex = LEVEL;
    score = 0;
}

Jeu::Jeu(const Jeu &jeu):snake(jeu.snake)
{
    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;
    paused = jeu.paused;
    posFruit.x = rand()%(largeur-1);
    posFruit.y = rand()%(hauteur-1);
    levelIndex = LEVEL;
    score = 0;

    char terrain_defaut[LIGNES][COLONNES]={0};
    
    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
}

Jeu::~Jeu()
{
    if (terrain!=nullptr)
        delete[] terrain;
}

Jeu &Jeu::operator=(const Jeu &jeu)
{
    if (terrain!=nullptr)
        delete[] terrain;

    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;
    snake = jeu.snake;

    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
    return *this;
}

bool Jeu::init()
{

    started = false;
    dirSnake = DROITE;
    score = 0;

    loadTerrainTxt();
    initTerrain();
    initFruit();

    int longueurSerpent = 5;
    snake.clear();

    Position posTete;
    posTete.x = 15;
    posTete.y = 8; 
	for (int i=0; i<longueurSerpent; i++)
    {
        snake.push_back(posTete);
        posTete.x--;
    }

    return true;
}

void Jeu::evolue()
{
    if (paused || !started) // Si pause ou jeu non démarré, on ne fait rien
    {
        return;
    }

    Position posTest;
	list<Position>::iterator itSnake;

    // [0] droite, [1] gauche, [2] haut, [3] bas
    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    posTest.x = (snake.front().x + depX[dirSnake] + largeur) % largeur;
    posTest.y = (snake.front().y + depY[dirSnake] + hauteur) % hauteur;

    //cout << "posTest.x: " << posTest.x << " posTest.y: " << posTest.y << endl;

    if (posValide(posTest)) {
        snake.pop_back();
        snake.push_front(posTest);
        if (terrain[posTest.y * largeur + posTest.x] == FRUIT) {
            snake.push_back(snake.back()); // Ajoute une case à la fin du serpent
            removeFruit(posTest); // Supprime le fruit
            addRandomFruit();
        }
    }
    else {
        init();
    }
}

int Jeu::getLevelIndex() const
{
    return levelIndex;
}

int Jeu::getNbCasesX() const
{
    return largeur;
}

int Jeu::getNbCasesY() const
{
    return hauteur;
}

Case Jeu::getCase(const Position &pos) const
{
    assert(pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur);
    return terrain[pos.y*largeur+pos.x];
}

const list<Position> &Jeu::getSnake() const
{
    return snake;
}

bool Jeu::posValide(const Position &pos) const
{
    if (pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur
        && terrain[pos.y*largeur+pos.x] == SOL || terrain[pos.y * largeur + pos.x] == FRUIT)
    {
        list<Position>::const_iterator itSnake;
        itSnake = snake.begin();
        while (itSnake!=snake.end() && *itSnake!=pos)
            itSnake++;
        return (itSnake==snake.end());
    }
    else
        return false;
}

void Jeu::setDirection(Direction dir)
{
    dirSnake = dir;
}

void Jeu::addRandomFruit()
{

    list<Position>::const_iterator itSnake;
    itSnake = snake.begin();

    Position pos[snake.size()];
    int idex = 0;
    bool IsSnake = false;

    while (itSnake!=snake.end())
    {
        pos[idex] = *itSnake;
        idex++;
        itSnake++;
    }

    do{
        IsSnake = false;
        posFruit.x = rand()%(largeur-1); // Crée un nouveau fruit
        posFruit.y = rand()%(hauteur-1);
        for (int i = 0; i < snake.size(); i++)
            if (posFruit == pos[i])
                IsSnake = true;
    }while (terrain[posFruit.y*largeur+posFruit.x] != SOL || IsSnake == true);

    terrain[posFruit.y*largeur+posFruit.x] = FRUIT;
}

void Jeu::removeFruit(Position pos)
{
    score += 10;
    terrain[pos.y*largeur+pos.x] = SOL;
    playBackgroundMusic("./data/Item_Sound.mp3");           // TODO : ne pas mettre en playBackgroundMusic (sinon coupure)
}

void Jeu::loadTerrainTxt(){

    ifstream file(Jeu::terrainTxtPaths[levelIndex]);

    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        return;
    }

    string line;

    getline(file, line); // lire la première ligne et l'ignore

    for (int i = 0; i < LIGNES; ++i) {
        getline(file, line);
        for (int j = 0; j < line.size(); ++j) {
            this->terrainTxtDefault[i][j] = line[j];
        }
    }

    file.close();
}

void Jeu::initTerrain(){

    int x, y;
    largeur = COLONNES;
    hauteur = LIGNES;

    terrain = new Case[largeur*hauteur];

    for(y=0;y<LIGNES;++y)
        for(x=0;x<COLONNES;++x)
            if (terrainTxtDefault[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if (terrainTxtDefault[y][x]=='.')
                terrain[y*largeur+x] = SOL;
            else
                terrain[y*largeur+x] = DEBUG;
}

void Jeu::initFruit(){

    while (terrain[posFruit.y*largeur+posFruit.x] != SOL)
    {
        posFruit.x = rand()%(largeur-1);
        posFruit.y = rand()%(hauteur-1);
    }

    terrain[posFruit.y*largeur+posFruit.x] = FRUIT;

}

void Jeu::togglePause() {
    paused = !paused;
}

bool Jeu::isPaused() const {
    return paused;
}

bool Jeu::isStarted() const {
    return started;         
}

void Jeu::setStarted() {
    started = true;
}

Case Jeu::getCase(int x, int y) const {
    return terrain[y*largeur+x];
}

void Jeu::setCase(int x, int y, Case c){
    terrain[y*largeur+x] = c;
}

void Jeu::setLevel(int level) {
    this->levelIndex = level;
}

Direction Jeu::getDirection() const {
    return dirSnake;
}

int Jeu::getScore() const
{
    return score;
}

