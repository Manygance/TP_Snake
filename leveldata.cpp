#include "leveldata.hpp"

using namespace std;

LevelData::LevelData(string path)
{
    reloadLevelData(path);
}

void LevelData::reloadLevelData(string path)
{
    // Lecture du chemin de l'image de fond
    string firstLine;
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        return;
    }

    getline(file, firstLine);           // Lecture de la première ligne du fichier
    m_terrainImagePath = firstLine;


    // Lecture des données du terrain
    string line;
    for (int i = 0; i < ROWS; ++i) {
        getline(file, line);
        for (int j = 0; j < line.size(); ++j) {
            m_terrainTxt[i][j] = line[j];
        }
    }

    file.close();
}

string LevelData::getLevelPath() const
{
    return m_levelPath;
}

string LevelData::getTerrainImagePath() const
{
    return m_terrainImagePath;
}

void LevelData::setTerrainImagePath(string terrainImagePath)
{
    m_terrainImagePath = terrainImagePath;
}

char LevelData::getTerrainTxtCase(int y, int x) const
{
    return m_terrainTxt[y][x];      // TODO : ajouter une sécurité
}

int LevelData::getNextLevelCondition() const
{
    return m_nextLevelCondition;
}