#include "mainmenu.hpp"

using namespace std;

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{

    // Permet de choisir aléatoirement une image de fond parmi les 5 disponibles
    int randomIndex = QRandomGenerator::global()->bounded(1, 6); // Génère un nombre entre 1 et 5 inclusivement
    QString backgroundImagePath = QString("./data/Main_Title_%1.png").arg(randomIndex);
    QPixmap bgImage(backgroundImagePath);

    if (bgImage.isNull())
    {
        cerr << "Erreur lors du chargement de l'image de fond" << endl;
    }
    else
    {
        QPixmap scaledBgImage = bgImage.scaled(640, 640, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Appliquer l'image de fond
        setAutoFillBackground(true);
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(scaledBgImage));
        this->setPalette(palette);
    }

    // Chargement et affichage du menubox
    QPixmap menuBox("./data/menubox.png");
    QLabel *menuBoxLabel = new QLabel(this);
    menuBoxLabel->setPixmap(menuBox);
    menuBoxLabel->setGeometry(menuBox.rect());
    menuBoxLabel->move(20, 20);

    // Chargement et affichage du textbox
    QPixmap textBox("./data/textbox.png");
    QLabel *textBoxLabel = new QLabel(this);
    textBoxLabel->setPixmap(textBox);
    textBoxLabel->setGeometry(textBox.rect());
    textBoxLabel->move(0, 480);

    // Enregistrement de la police
    QString fontPath = "./data/font.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId == -1)
    {
        cerr << "Erreur lors du chargement de la police d'écriture" << endl;
        exit(1);
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    const auto text_1 = new QLabel("Projet de programmation avancée", this);
    text_1->setFont(QFont(fontFamily, 12));
    text_1->setStyleSheet(
        "color: white;"
        "font-size: 16px;"
        "padding-top: 510px;"
        "padding-left: 30px;");

    const auto text_2 = new QLabel("par Thomas DEBELLE & Bastien JAYET", this);
    text_2->setFont(QFont(fontFamily, 12));
    text_2->setStyleSheet(
        "color: white;"
        "font-size: 16px;"
        "padding-top: 530px;"
        "padding-left: 30px;");

    // Boutons
    const auto playEmptyButton = new QPushButton("Carte vide", this);
    playEmptyButton->setFont(QFont(fontFamily, 12));
    playEmptyButton->setGeometry(0, 0, 160, 20);
    playEmptyButton->move(40, 40);
    playEmptyButton->setCursor(Qt::PointingHandCursor);
    playEmptyButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");

    const auto playMaze1Button = new QPushButton("Carte 1", this);
    playMaze1Button->setFont(QFont(fontFamily, 12));
    playMaze1Button->setGeometry(0, 0, 160, 20);
    playMaze1Button->move(40, 70);
    playMaze1Button->setCursor(Qt::PointingHandCursor);
    playMaze1Button->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");

    const auto playMaze2Button = new QPushButton("Carte 2", this);
    playMaze2Button->setFont(QFont(fontFamily, 12));
    playMaze2Button->setGeometry(0, 0, 160, 20);
    playMaze2Button->move(40, 100);
    playMaze2Button->setCursor(Qt::PointingHandCursor);
    playMaze2Button->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");

    const auto playMaze3Button = new QPushButton("Carte 3", this);
    playMaze3Button->setFont(QFont(fontFamily, 12));
    playMaze3Button->setGeometry(0, 0, 160, 20);
    playMaze3Button->move(40, 130);
    playMaze3Button->setCursor(Qt::PointingHandCursor);
    playMaze3Button->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");

    const auto mapEditor = new QPushButton("Modifier cartes", this);
    mapEditor->setFont(QFont(fontFamily, 12));
    mapEditor->setGeometry(0, 0, 160, 20);
    mapEditor->move(40, 160);
    mapEditor->setCursor(Qt::PointingHandCursor);
    mapEditor->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");
/* // supprimé pour le moment car le son du niveau se relance au chargement du niveau
   //si on le désactive dans le menu principal
    const auto volumeButton = new QPushButton("Son", this);
    volumeButton->setFont(QFont(fontFamily, 12));
    volumeButton->setGeometry(0, 0, 160, 20);
    volumeButton->move(40, 190);
    volumeButton->setCursor(Qt::PointingHandCursor);
    volumeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");
*/
    const auto exitButton = new QPushButton("Quitter", this);
    exitButton->setFont(QFont(fontFamily, 12));
    exitButton->setGeometry(0, 0, 160, 20);
    exitButton->move(40, 190);
    exitButton->setCursor(Qt::PointingHandCursor);
    exitButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 16px;"
        "    text-align: left;"
        "}"
        "QPushButton:hover {"
        "    color: yellow;"
        "}");

    //connect(volumeButton, &QPushButton::clicked, this, &MainMenu::toggleVolume);

    connect(playEmptyButton, &QPushButton::clicked, this, [this]()
            { this->playClicked(0); });
    connect(playMaze1Button, &QPushButton::clicked, this, [this]()
            { this->playClicked(1); });
    connect(playMaze2Button, &QPushButton::clicked, this, [this]()
            { this->playClicked(2); });
    connect(playMaze3Button, &QPushButton::clicked, this, [this]()
            { this->playClicked(3); });

    connect(mapEditor, &QPushButton::clicked, this, &MainMenu::createMapClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitClicked);
}