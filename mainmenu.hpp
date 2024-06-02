//
// Created by Maný on 5/1/2024.
//

#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFontDatabase>
#include <iostream>

using namespace std;

class MainMenu final : public QWidget {
Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr) : QWidget(parent) {

        // permet de choisir aléatoirement une image de fond parmi les 5 disponibles
        int randomIndex = QRandomGenerator::global()->bounded(1, 6); // Génère un nombre entre 1 et 5 inclusivement
        QString backgroundImagePath = QString("./data/Main_Title_%1.png").arg(randomIndex);
        QPixmap bgImage(backgroundImagePath);

        if (bgImage.isNull()) {
            cerr << "Erreur lors du chargement de l'image de fond" << endl;
        } else {
            QPixmap scaledBgImage = bgImage.scaled(640, 640, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

            // Appliquer l'image de fond
            setAutoFillBackground(true);
            QPalette palette;
            palette.setBrush(QPalette::Window, QBrush(scaledBgImage));
            this->setPalette(palette);
        }

        // Charger et afficher le menubox
        QPixmap menuBox("./data/menubox.png");
        QLabel *menuBoxLabel = new QLabel(this);
        menuBoxLabel->setPixmap(menuBox);
        menuBoxLabel->setGeometry(menuBox.rect());
        menuBoxLabel->move(20, 20);

        // Charger et afficher le textbox
        QPixmap textBox("./data/textbox.png");
        QLabel *textBoxLabel = new QLabel(this);
        textBoxLabel->setPixmap(textBox);
        textBoxLabel->setGeometry(textBox.rect());
        textBoxLabel->move(0, 480);

        // Titre
        QString fontPath = "./data/font.ttf";

        // Enregistrer la police
        int fontId = QFontDatabase::addApplicationFont(fontPath);
        if (fontId == -1) {
            cerr << "Erreur lors du chargement de la police d'écriture" << endl;
            exit(1);
        }

        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
/*
        const auto title = new QLabel("Snake", this);
        title->setFont(QFont(fontFamily, 60));
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet("color: white;");

        const auto subTitle = new QLabel("by Thomas DEBELLE & Bastien JAYET", this);
        subTitle->setFont(QFont(fontFamily, 12));
        subTitle->setAlignment(Qt::AlignCenter);
        subTitle->setStyleSheet("color: white;");
*/

        // Boutons
        const auto playButton = new QPushButton("Play a map", this);
        playButton->setFont(QFont(fontFamily, 12));
        playButton->setGeometry(0, 0, 160, 20);
        playButton->move(40, 40);
        playButton->setCursor(Qt::PointingHandCursor);
        playButton->setStyleSheet(
                "QPushButton {"
                "    background-color: transparent;"
                "    border: none;"
                "    color: white;"
                "    text-align: left;"
                "    padding-left: 0px;"
                "}"
                "QPushButton:hover {"
                "    color: yellow;"
                "}"
        );

        const auto mapEditor = new QPushButton("Create a map", this);
        mapEditor->setFont(QFont(fontFamily, 12));
        mapEditor->setGeometry(0, 0, 160, 20);
        mapEditor->move(40, 70);
        mapEditor->setCursor(Qt::PointingHandCursor);
        mapEditor->setStyleSheet(
                "QPushButton {"
                "    background-color: transparent;"
                "    border: none;"
                "    color: white;"
                "    text-align: left;"
                "    padding-left: 0px;"
                "}"
                "QPushButton:hover {"
                "    color: yellow;"
                "}"
        );

        const auto exitButton = new QPushButton("Exit", this);
        exitButton->setFont(QFont(fontFamily, 12));
        exitButton->setGeometry(0, 0, 160, 20);
        exitButton->move(40, 100);
        exitButton->setCursor(Qt::PointingHandCursor);
        exitButton->setStyleSheet(
                "QPushButton {"
                "    background-color: transparent;"
                "    border: none;"
                "    color: white;"
                "    text-align: left;"
                "    padding-left: 0px;"
                "}"
                "QPushButton:hover {"
                "    color: yellow;"
                "}"
        );

        connect(playButton, &QPushButton::clicked, this, &MainMenu::playClicked);
        connect(mapEditor, &QPushButton::clicked, this, &MainMenu::createMapClicked);
        connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitClicked);
    }

signals:
    void playClicked();

    void exitClicked();

    void createMapClicked();
};


#endif //MAINMENU_HPP