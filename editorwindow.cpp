#include "editorwindow.hpp"

using namespace std;

EditorWindow::EditorWindow()
{
    // Images récupérées ici : https://rembound.com/articles/creating-a-snake-game-tutorial-with-html5
    if(!bodyVertical.load("./data/body_vertical.png") or
       !bodyHorizontal.load("./data/body_horizontal.png") or
       !bodyTopLeft.load("./data/body_top_left.png") or
       !bodyTopRight.load("./data/body_top_right.png") or
       !bodyBottomLeft.load("./data/body_bottom_left.png") or
       !bodyBottomRight.load("./data/body_bottom_right.png") or
       !headUp.load("./data/head_up.png") or
       !headDown.load("./data/head_down.png") or
       !headLeft.load("./data/head_left.png") or
       !headRight.load("./data/head_right.png") or
       !tailUp.load("./data/tail_up.png") or
       !tailDown.load("./data/tail_down.png") or
       !tailLeft.load("./data/tail_left.png") or
       !tailRight.load("./data/tail_right.png") or
       !fruit.load("./data/fruit.png") or
       !debug.load("./data/debug.png") or
       !textBox.load("./data/textbox.png"))
    {
        cerr<<"Erreur lors du chargement des images"<<endl;
        exit(1);
    }

    setLevelBackground(getLevelBackground());
    applyLevelBackground();

    QString fontPath = "./data/font.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId == -1) {
        cerr << "Erreur lors du chargement de la police d'écriture" << endl;
        exit(1);
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    const auto Maze_1_Button = new QPushButton("Carte 1", this);
    Maze_1_Button->setFont(QFont(fontFamily, 12));
    Maze_1_Button->setGeometry(0, 0, 160, 20);
    Maze_1_Button->move(40, 520);
    Maze_1_Button->setCursor(Qt::PointingHandCursor);
    Maze_1_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Maze_2_Button = new QPushButton("Carte 2", this);
    Maze_2_Button->setFont(QFont(fontFamily, 12));
    Maze_2_Button->setGeometry(0, 0, 200, 20);
    Maze_2_Button->move(40, 550);
    Maze_2_Button->setCursor(Qt::PointingHandCursor);
    Maze_2_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Maze_3_Button = new QPushButton("Carte 3", this);
    Maze_3_Button->setFont(QFont(fontFamily, 12));
    Maze_3_Button->setGeometry(0, 0, 200, 20);
    Maze_3_Button->move(40, 580);
    Maze_3_Button->setCursor(Qt::PointingHandCursor);
    Maze_3_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_1_Button = new QPushButton("Appliquer fond 1", this);
    Set_BG_1_Button->setFont(QFont(fontFamily, 12));
    Set_BG_1_Button->setGeometry(0, 0, 200, 20);
    Set_BG_1_Button->move(210, 520);
    Set_BG_1_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_1_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_2_Button = new QPushButton("Appliquer fond 2", this);
    Set_BG_2_Button->setFont(QFont(fontFamily, 12));
    Set_BG_2_Button->setGeometry(0, 0, 200, 20);
    Set_BG_2_Button->move(210, 550);
    Set_BG_2_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_2_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_3_Button = new QPushButton("Appliquer fond 3", this);
    Set_BG_3_Button->setFont(QFont(fontFamily, 12));
    Set_BG_3_Button->setGeometry(0, 0, 200, 20);
    Set_BG_3_Button->move(210, 580);
    Set_BG_3_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_3_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_4_Button = new QPushButton("Appliquer fond 4", this);
    Set_BG_4_Button->setFont(QFont(fontFamily, 12));
    Set_BG_4_Button->setGeometry(0, 0, 200, 20);
    Set_BG_4_Button->move(420, 520);
    Set_BG_4_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_4_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto Set_BG_5_Button = new QPushButton("Appliquer fond 5", this);
    Set_BG_5_Button->setFont(QFont(fontFamily, 12));
    Set_BG_5_Button->setGeometry(0, 0, 200, 20);
    Set_BG_5_Button->move(420, 550);
    Set_BG_5_Button->setCursor(Qt::PointingHandCursor);
    Set_BG_5_Button->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    const auto SaveButton = new QPushButton("Sauvegarder", this);
    SaveButton->setFont(QFont(fontFamily, 12));
    SaveButton->setGeometry(0, 0, 200, 20);
    SaveButton->move(420, 580);
    SaveButton->setCursor(Qt::PointingHandCursor);
    SaveButton->setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"
            "    border: none;"
            "    color: white;"
            "    font-size: 16px;"
            "    text-align: left;"
            "}"
            "QPushButton:hover {"
            "    color: yellow;"
            "}"
    );

    connect(Maze_1_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(1); });
    connect(Maze_2_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(2); });
    connect(Maze_3_Button, &QPushButton::clicked, this, [this]() { this->loadMaze(3); });
    connect(Set_BG_1_Button, &QPushButton::clicked, this, [this]() {setLevelBackground("./data/BG_1.png");});
    connect(Set_BG_2_Button, &QPushButton::clicked, this, [this]() {setLevelBackground("./data/BG_2.png");});
    connect(Set_BG_3_Button, &QPushButton::clicked, this, [this]() {setLevelBackground("./data/BG_3.png");});
    connect(Set_BG_4_Button, &QPushButton::clicked, this, [this]() {setLevelBackground("./data/BG_4.png");});
    connect(Set_BG_5_Button, &QPushButton::clicked, this, [this]() {setLevelBackground("./data/BG_5.png");});
    connect(SaveButton, &QPushButton::clicked, this, &EditorWindow::saveMap);

}

void EditorWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    Position pos;

    // Dessine les cases
    for (pos.y = 0; pos.y < jeu.getNbCasesY(); pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++)
            if (jeu.getCase(pos) == MUR) {
                //painter.drawPixmap(pos.x*TAILLE_CASE, pos.y*TAILLE_CASE, wall);
                QRect sourceRect(9 + 4 * 25, 163 + 4 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (jeu.getCase(pos) == FRUIT) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
                painter.drawPixmap(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, fruit);
            } else if (jeu.getCase(pos) == SOL) {
                QRect sourceRect = grid[pos];
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else
                painter.drawPixmap(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, debug);

    // Pour l'affichage au niveau de la text box
    for (pos.y = jeu.getNbCasesY(); pos.y < jeu.getNbCasesY() + 5; pos.y++)
        for (pos.x = 0; pos.x < jeu.getNbCasesX(); pos.x++) {
            if (pos.x == 0 and pos.y == 15) {
                QRect sourceRect(9 + 3 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 15) {
                QRect sourceRect(9 + 5 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0 and pos.y == 19) {
                QRect sourceRect(9 + 3 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19 and pos.y == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 19) {
                QRect sourceRect(9 + 5 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.x == 0) {
                QRect sourceRect(9 + 3 * 25, 163 + 1 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 15) {
                QRect sourceRect(9 + 4 * 25, 163 + 0 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            } else if (pos.y == 19) {
                QRect sourceRect(9 + 4 * 25, 163 + 2 * 25, 24, 24);
                QRect destRect(pos.x * TAILLE_CASE, pos.y * TAILLE_CASE, 32, 32);
                painter.drawPixmap(destRect, background, sourceRect);
            }
    }

    painter.drawPixmap(0, 480, textBox);
}

void EditorWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Space)
    {
        jeu.togglePause();
        if (jeu.isPaused())
        {
            cout<<"Jeu en pause"<<endl;

            QLabel *label = new QLabel(this);
            label->setText("Jeu en pause");
            label->setAlignment(Qt::AlignCenter);
            label->setGeometry(0, 0, width(), height());
            label->setStyleSheet("QLabel { background-color : rgba(0, 0, 0, 100); color : white; }");
            label->show();
        }
        else {
            cout << "Jeu en cours" << endl;

            QList<QLabel *> labels = findChildren<QLabel *>();
            for (QLabel *label : labels)
                label->close();
        }
    }
    if (event->key()==Qt::Key_Escape)
        QCoreApplication::quit();
    if (!jeu.isStarted())
        jeu.setStarted();
    if (!jeu.isPaused())
    {
        if (event->key()==Qt::Key_Left and jeu.getDirection()!=DROITE)
            jeu.setDirection(GAUCHE);
        else if (event->key()==Qt::Key_Right and jeu.getDirection()!=GAUCHE)
            jeu.setDirection(DROITE);
        else if (event->key()==Qt::Key_Up and jeu.getDirection()!=BAS)
            jeu.setDirection(HAUT);
        else if (event->key()==Qt::Key_Down and jeu.getDirection()!=HAUT)
            jeu.setDirection(BAS);
    }
    else
        return;
    update();
}

void EditorWindow::startEditor()
{
    jeu.loadTerrainTxt();
    jeu.initTerrain();
    initGrid();
    update();
}

void EditorWindow::mousePressEvent(QMouseEvent *event) {
    QPoint localMousePos = event->pos();  // Position locale de la souris

    int x = localMousePos.x() / TAILLE_CASE;
    int y = localMousePos.y() / TAILLE_CASE;

    if (x >= 0 && x < jeu.getNbCasesX() && y >= 0 && y < jeu.getNbCasesY()) {
        // Modifier la case
        if (jeu.getCase(x, y) == SOL) {
            jeu.setCase(x, y, MUR);
        } else {
            jeu.setCase(x, y, SOL);
        }
        update();
    }
}

void EditorWindow::loadMaze(int mazeIndex) {

    jeu.setLevel(mazeIndex);
    levelBackground = getLevelBackground();
    applyLevelBackground();
    jeu.loadTerrainTxt();
    jeu.initTerrain();
    initGrid();
    update();
}

void EditorWindow::saveMap() {

    ofstream file;
    file.open (Jeu::terrainTxtPaths[jeu.getLevelIndex()]);

    file << levelBackground << "\n";

    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (jeu.getCase(j, i) == MUR)
                file << "#"; // Écrire un point pour une case SOL
            else
                file << "."; // Écrire un dièse pour une case MUR
        }
        file << "\n"; // Nouvelle ligne après chaque ligne de la matrice
    }

    file.close();

}

std::string EditorWindow::getLevelBackground() {

    ifstream file(Jeu::terrainTxtPaths[jeu.getLevelIndex()]);
    string firstLine;
    getline(file, firstLine);
    file.close();
    return firstLine;
}

void EditorWindow::setLevelBackground(const std::string& background) {
    levelBackground = background;
    applyLevelBackground();
    update();
}

void EditorWindow::applyLevelBackground() {
    QString backgroundImagePath = QString::fromStdString(levelBackground);
    background.load(backgroundImagePath);
}

void EditorWindow::initGrid() {
        for (int y = 0; y < jeu.getNbCasesY(); ++y) {
            for (int x = 0; x < jeu.getNbCasesX(); ++x) {
                Position pos(x, y);
                int randomX = QRandomGenerator::global()->bounded(3);
                int randomY = QRandomGenerator::global()->bounded(3);
                QRect sourceRect(9 + (12 + randomX) * 25, 163 + randomY * 25, 24, 24);
                grid[pos] = sourceRect;

            }
        }
    }