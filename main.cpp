#include <ctime>
#include "snakewindow.hpp"

using namespace std;

/*
 * TODO : MODIFIER UN MENU PAUSE
 * TODO : MODIFIER LE MENU PRINCIPAL POUR AVOIR PLUSIEURS NIVEAUX
 * TODO : MODIFIER LE MENU PRINCIPAL POUR AVOIR UN MENU DE CREATION DE MAP
 * TODO : MODIFIER LE MENU PRINCIPAL POUR AVOIR UN MENU OPTION
 * TODO : REDIMENTIONNER LA FENETRE DE JEU
 * TODO : LIRE LE NIVEAU DEPUIS UN FICHIER TEXTE
 * TODO : AJOUTER UN SCORE
 * TODO : AJOUTER UN MENU DE FIN DE PARTIE
 * TODO : AJOUTER UNE CONDITION DE FIN
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

    SnakeWindow wnd;
    wnd.show();

    return app.exec();
}
