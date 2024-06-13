#ifndef LEVELDATA_HPP
#define LEVELDATA_HPP

#include <string>
#include <fstream>

#include "globalsettings.hpp"

/// @brief Classe contenant les données de base chargée pour créer un niveau. Ce ne sont pas des données dynamiques : elles ne servent qu'à l'initialisation des classe gérant le jeu et l'affichage.
class LevelData {
public:
    /// @brief Constructeur de LevelData
    /// @param levelPath chemin vers le fichier du niveau
    LevelData(std::string);

    /// @brief Ecrase le chemin de niveau actuel et charge un nouveau niveau
    /// @param levelPath nouveau chemin du niveau
    void reloadLevelData(std::string);

    std::string getLevelPath() const;
    std::string getTerrainImagePath() const;
    void setTerrainImagePath(std::string);

    /// @brief Retourne la valeur de la case au format .txt (telle que contenue dans le fichier de level)
    /// @param y n° de ligne 
    /// @param x n° de colonne
    /// @return char
    char getTerrainTxtCase(int, int) const;
    int getNextLevelCondition() const;

private:
    std::string m_levelPath;
    std::string m_terrainImagePath;
    char m_terrainTxt[ROWS][COLUMNS];         // Représentation du terrain sous la forme de caractères       
    int m_nextLevelCondition;
};

#endif