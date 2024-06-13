#include "playwindow.hpp"

using namespace std;


PlayWindow::PlayWindow(Game *game) : GameWindow(game)
{
    m_notStartedText = new QLabel("Appuyer sur une touche pour commencer", this);
    m_notStartedText->setFont(QFont(m_fontFamily, 12));
    m_notStartedText->setGeometry(0, 550, 640, 20);
    m_notStartedText->setAlignment(Qt::AlignCenter);
    m_notStartedText->setStyleSheet("color: white; font-size: 16px;");
    m_notStartedText->show();

    m_scoreText = new QLabel(this);
    m_scoreText->setFont(QFont(m_fontFamily, 12));
    m_scoreText->setGeometry(0, 550, 640, 20);
    m_scoreText->setAlignment(Qt::AlignCenter);
    m_scoreText->setStyleSheet("color: white; font-size: 16px;");
    m_scoreText->hide();

    m_nextLevelText = new QLabel(this);
    m_nextLevelText->setFont(QFont(m_fontFamily, 12));
    m_nextLevelText->setGeometry(0, 570, 640, 20);
    m_nextLevelText->setAlignment(Qt::AlignCenter);
    m_nextLevelText->setStyleSheet("color: white; font-size: 16px;");
    m_nextLevelText->hide();
}

void PlayWindow::onPaintEvent(QPainter* painter)
{
    int cyclePosition = m_currentFrame % GameWindow::frameSequenceLength;
    int frameValue = cyclePosition / GameWindow::frameRepetitions;

    // Affichage du "serpent"       // TODO : supprimer les éléments relatifs à la séparation tête/corps/queue
    int x, y;
    const list<Position> &snake = m_game->getSnake();
    if (!snake.empty())
    {
        list<Position>::const_iterator itSnake;

        const Position &headPos = snake.front();

        // Pour la tête
        if (m_game->getSnakeDirection() == DOWN)
        {
            x = 1;
            y = 1;
        }
        else if (m_game->getSnakeDirection() == UP)
        {
            x = 58;
            y = 1;
        }
        else if (m_game->getSnakeDirection() == LEFT)
        {
            x = 1;
            y = 22;
        }
        else if (m_game->getSnakeDirection() == RIGHT)
        {
            x = 58;
            y = 22;
        }

        QRect sourceRect(x + 19 * frameValue, y, 17, 19);
        QRect destRect(headPos.x * CASE_SIZE, headPos.y * CASE_SIZE, 32, 32);
        painter->drawPixmap(destRect, m_pokemonPixmap, sourceRect);

        // Pour la queue
        const Position &posQueue = snake.back();
        const Position &posAvantQueue = *(++snake.rbegin());

        if (posQueue.x == posAvantQueue.x)
            if ((posQueue.y < posAvantQueue.y) && posQueue.y != 0 || (posQueue.y == 14 and posAvantQueue.y == 0))
            {
                x = 1;
                y = 1;
            }
            else if ((posQueue.y > posAvantQueue.y) && posQueue.y != 14 || (posQueue.y == 0 and posAvantQueue.y == 14))
            {
                x = 58;
                y = 1;
            }
        if (posQueue.y == posAvantQueue.y)
            if ((posQueue.x < posAvantQueue.x) && posQueue.x != 0 || (posQueue.x == 19 and posAvantQueue.x == 0))
            {
                x = 58;
                y = 22;
            }
            else if ((posQueue.x > posAvantQueue.x) && posQueue.x != 19 || (posQueue.x == 0 and posAvantQueue.x == 19))
            {
                x = 1;
                y = 22;
            }

        sourceRect = QRect(x + 19 * frameValue, y, 17, 19);
        destRect = QRect(posQueue.x * CASE_SIZE, posQueue.y * CASE_SIZE, 32, 32);
        painter->drawPixmap(destRect, m_pokemonPixmap, sourceRect);

        // Pour le corps
        for (itSnake = ++snake.begin(); itSnake != --snake.end(); itSnake++)
        {
            Position posCorps = *itSnake;
            Position posPrec = *prev(itSnake);

            if (posCorps.x == posPrec.x)
                if ((posCorps.y < posPrec.y) && posCorps.y != 0 || (posCorps.y == 14 and posPrec.y == 0))
                {
                    x = 1;
                    y = 1;
                }
                else if ((posCorps.y > posPrec.y) && posCorps.y != 14 || (posCorps.y == 0 and posPrec.y == 14))
                {
                    x = 58;
                    y = 1;
                }
            if (posCorps.y == posPrec.y)
                if ((posCorps.x < posPrec.x) && posCorps.x != 0 || (posCorps.x == 19 and posPrec.x == 0))
                {
                    x = 58;
                    y = 22;
                }
                else if ((posCorps.x > posPrec.x) && posCorps.x != 19 || (posCorps.x == 0 and posPrec.x == 19))
                {
                    x = 1;
                    y = 22;
                }

            sourceRect = QRect(x + 19 * frameValue, y, 17, 19);
            destRect = QRect(posCorps.x * CASE_SIZE, posCorps.y * CASE_SIZE, 32, 32);
            painter->drawPixmap(destRect, m_pokemonPixmap, sourceRect);
        }
    }

    // Affichage du texte
    if (!m_game->isStarted())
    {
        m_notStartedText->show();
        m_scoreText->hide();
        m_nextLevelText->hide();
    }
    else
    {
        m_notStartedText->hide();
        m_scoreText->setText("Score : " + QString::number(m_game->getScore()));
        m_scoreText->show();
        if (m_game->getLevelIndex() != 0)
        {
            m_scoreText->setGeometry(0, 530, 640, 20);
            if (m_game->getNextLevelCondition() == 0)
                m_nextLevelText->setText("Prenez les escaliers pour passer au niveau suivant !");
            else
                m_nextLevelText->setText("Il reste " + QString::number(m_game->getNextLevelCondition()) + " fruits avant le prochain niveau.");
            m_nextLevelText->show();
        }
    }
}

void PlayWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        m_game->togglePause();
        if (m_game->isPaused())
        {
            cout << "Jeu en pause" << endl;

            QLabel *label = new QLabel(this);
            label->setText("Jeu en pause");
            label->setAlignment(Qt::AlignCenter);
            label->setGeometry(0, 0, width(), height());
            label->setStyleSheet("QLabel { background-color : rgba(0, 0, 0, 100); color : white; }");
            label->show();
        }
        else
        {
            cout << "Jeu en cours" << endl;

            QList<QLabel *> labels = findChildren<QLabel *>();
            for (QLabel *label : labels)
                label->close();
        }
    }
    if (event->key() == Qt::Key_Escape)
        QCoreApplication::quit();
    if (!m_game->isStarted())
        m_game->setStarted(true);
    if (!m_game->isPaused())
    {
        if (event->key() == Qt::Key_Left and m_game->getSnakeDirection() != RIGHT)
            m_game->setSnakeDirection(LEFT);
        else if (event->key() == Qt::Key_Right and m_game->getSnakeDirection() != LEFT)
            m_game->setSnakeDirection(RIGHT);
        else if (event->key() == Qt::Key_Up and m_game->getSnakeDirection() != DOWN)
            m_game->setSnakeDirection(UP);
        else if (event->key() == Qt::Key_Down and m_game->getSnakeDirection() != UP)
            m_game->setSnakeDirection(DOWN);
    }
    else
        return;
}