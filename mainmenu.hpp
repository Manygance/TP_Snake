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

using namespace std;

class MainMenu : public QWidget {       // TODO : ajouter tout partout en final ?
Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

signals:
    void playClicked(int);
    void exitClicked();
    void createMapClicked();
    
public slots:
    void toggleVolume() {
        volumeOn = !volumeOn;
        float volume = volumeOn ? 1.0f : 0.0f; // Volume 100% ou 0%
        setBackgroundMusicVolume(volume);
    }


private:
    bool volumeOn = true;
};



#endif //MAINMENU_HPP