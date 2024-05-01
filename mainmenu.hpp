//
// Created by Maný on 5/1/2024.
//

#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainMenu final : public QWidget {
Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr) : QWidget(parent) {
        const auto layoutH = new QHBoxLayout(this);
        const auto layoutV = new QVBoxLayout;

        // Title
        const auto title = new QLabel("Snake", this);
        title->setStyleSheet("font-size: 70px;");
        title->setAlignment(Qt::AlignCenter);
        const auto subTitle = new QLabel("by Thomas DEBELLE & Bastien JAYET", this);
        subTitle->setStyleSheet("font-size: 24px;");
        subTitle->setAlignment(Qt::AlignCenter);

        // Buttons
        const auto playButton = new QPushButton("Play a map", this);
        playButton->setStyleSheet("padding-left: 20px; padding-right: 20px;");
        const auto mapEditor = new QPushButton("Create a map", this);
        mapEditor->setStyleSheet("padding-left: 20px; padding-right: 20px;");
        const auto exitButton = new QPushButton("Exit", this);
        exitButton->setStyleSheet("padding-left: 20px; padding-right: 20px;");

        layoutV->addStretch();
        layoutV->addWidget(title);
        layoutV->addWidget(subTitle);
        layoutV->addStretch();
        layoutV->addWidget(playButton);
        layoutV->addWidget(mapEditor);
        layoutV->addWidget(exitButton);
        layoutV->addStretch();

        layoutH->addStretch();
        layoutH->addLayout(layoutV);
        layoutH->addStretch();

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