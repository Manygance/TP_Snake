#ifndef PLAYWINDOW_HPP
#define PLAYWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <iostream>
#include <fstream>

#include "gamewindow.hpp"
#include "globalsettings.hpp"


class PlayWindow : public GameWindow {
Q_OBJECT

public:
    PlayWindow(Game*);
    void keyPressEvent(QKeyEvent*);

    virtual void onPaintEvent(QPainter*) override;

private:
    QLabel* m_notStartedText;
    QLabel* m_scoreText;
    QLabel* m_nextLevelText;
};
#endif