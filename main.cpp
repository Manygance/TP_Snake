#include <ctime>
#include "snakewindow.hpp"

#include <fmod/fmod.h>

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

    FMOD_SYSTEM *system;
    FMOD_SOUND *soundHihat;
    FMOD_RESULT result;

    result = FMOD_System_Create(&system);
    if (result!=FMOD_OK)
    {
        cout<<"A"<<result<<endl;
        return -1;
    }
    result = FMOD_System_Init(system, 8, FMOD_INIT_NORMAL, nullptr);
    if (result!=FMOD_OK)
    {
        cout<<"B"<<result<<endl;
        return -1;
    }
    result = FMOD_System_CreateSound(system, "./data/Music_Menu.mp3", FMOD_SOFTWARE, nullptr, &soundHihat);
    if (result!=FMOD_OK)
    {
        cout<<"Cannot create sound. Error"<<result<<endl;
        return -1;
    }
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, soundHihat, 0, NULL);
    if (result!=FMOD_OK)
    {
        cout<<"C"<<result<<endl;
        return -1;
    }

    return app.exec();
}
