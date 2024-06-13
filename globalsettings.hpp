#ifndef GLOBALSETTINGS_HPP
#define GLOBALSETTINGS_HPP

#define WINDOW_ROWS 20
#define WINDOW_COL 20
#define ROWS 15
#define COLUMNS 20
#define CASE_SIZE 32

#include <iostream>
#include <string>

/// @brief Classe contenant plusieurs paramètres de base pour le jeu
class GlobalSettings {
public:
    /// @brief Chemin d'accès aux niveaux dans les fichiers
    static const std::string levelPaths[];

    /// @brief Score à atteindre pour passer au niveau suivant. Chaque indice de case correspond à un index de niveau
    static const int nextLevelConditions[];

    /// @brief Chemin d'accès aux terrains dans les fichiers
    static const std::string terrainPaths[];
};

#endif