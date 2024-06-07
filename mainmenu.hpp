#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFontDatabase>
#include <QSlider>
#include <iostream>
#include "sound.hpp"

using namespace std;

class MainMenu : public QWidget {       // TODO : ajouter tout partout en final ?
Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);

public slots:
    void playClicked(int);          // TODO : si ça marche pas, repasser en signals:
    void exitClicked();
    void createMapClicked();
    void toggleVolume();

private:
    bool volumeOn = true;
};



#endif //MAINMENU_HPP