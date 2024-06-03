#include <iostream>
#include <fstream>
#include <cassert>
#include "jeu.hpp"
#include "global_settings.hpp"

using namespace std;

Position::Position()
{
}

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

Jeu::Jeu()
{
    terrain = nullptr;
    largeur = 0; hauteur = 0;
    dirSnake = DROITE;
    pause = false;
    started = false;
    Pos_Fruit.x = rand()%(largeur-1);
    Pos_Fruit.y = rand()%(hauteur-1);
    char terrain_defaut[LIGNES][COLONNES]={0};
    level = LEVEL;
}

Jeu::Jeu(const Jeu &jeu):snake(jeu.snake)
{
    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;
    pause = jeu.pause;
    Pos_Fruit.x = rand()%(largeur-1);
    Pos_Fruit.y = rand()%(hauteur-1);
    level = LEVEL;
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
	int x, y;
    started = false;
    dirSnake = DROITE;

    readLevel();

	largeur = COLONNES;
	hauteur = LIGNES;



	terrain = new Case[largeur*hauteur];

	for(y=0;y<LIGNES;++y)
		for(x=0;x<COLONNES;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if (terrain_defaut[y][x]=='.')
                terrain[y*largeur+x] = SOL;
            else
                terrain[y*largeur+x] = DEBUG;


    while (terrain[Pos_Fruit.y*largeur+Pos_Fruit.x] != SOL)
    {
        Pos_Fruit.x = rand()%(largeur-1);
        Pos_Fruit.y = rand()%(hauteur-1);
    }

    terrain[Pos_Fruit.y*largeur+Pos_Fruit.x] = FRUIT;

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
    if (pause || !started) // Si pause ou jeu non démarré, on ne fait rien
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
            Remove_Fruit(posTest); // Supprime le fruit
            Add_Fruit_Random();
        }
    }
    else {
        init();
    }
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

void Jeu::Add_Wall(Position pos)
{
    terrain[pos.y*largeur+pos.x] = MUR;
}

void Jeu::Remove_Wall(Position pos)
{
    terrain[pos.y*largeur+pos.x] = SOL;
}

void Jeu::Add_Fruit_Random()
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
        Pos_Fruit.x = rand()%(largeur-1); // Crée un nouveau fruit
        Pos_Fruit.y = rand()%(hauteur-1);
        for (int i = 0; i < snake.size(); i++)
            if (Pos_Fruit == pos[i])
                IsSnake = true;
    }while (terrain[Pos_Fruit.y*largeur+Pos_Fruit.x] != SOL || IsSnake == true);

    terrain[Pos_Fruit.y*largeur+Pos_Fruit.x] = FRUIT;
}

void Jeu::Remove_Fruit(Position pos)
{
    terrain[pos.y*largeur+pos.x] = SOL;
}

void Jeu::readLevel(){

    string file_path;

    switch (level) {
        case 0:
            file_path = "level_1.txt";
            //cout << "level 1" << endl;
            break;
        case 1:
            file_path = "level_2.txt";
            //cout << "level 2" << endl;
            break;
        case 2:
            file_path = "level_3.txt";
            //cout << "level 3" << endl;
            break;
        case 3:
            file_path = "level_4.txt";
            //cout << "level 4" << endl;
            break;
        default:
            file_path = "level_1.txt";
            //cout << "default" << endl;
            break;
    }

    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        return;
    }

    char c;
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES+1; ++j) {
            if (file.get(c)) {
                this->terrain_defaut[i][j] = c;
            }
        }
    }

    file.close();
}