#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFontDatabase>
#include <QSlider>
#include <QRandomGenerator>
#include <QPixmap>
#include <iostream>

#include "sound.hpp"

class MainMenu : public QWidget {
Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

signals:
    /// @brief Lancement d'une partie
    void playClicked(int);

    /// @brief Sortie du jeu
    void exitClicked();

    /// @brief Lancement de l'éditeur de niveaux
    void createMapClicked();
    
public slots:
    /// @brief Activation/désactivation du son
    void toggleVolume() {
        volumeOn = !volumeOn;
        float volume = volumeOn ? 1.0f : 0.0f; // Volume 100% ou 0%
        setBackgroundMusicVolume(volume);
    }


private:
    bool volumeOn = true;
};



#endif //MAINMENU_HPP