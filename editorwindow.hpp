#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP

#include "gamewindow.hpp"

class EditorWindow : public GameWindow {
Q_OBJECT

public:
    EditorWindow(Game*);
    void mousePressEvent(QMouseEvent *event);

    virtual void onPaintEvent(QPainter*) override;

private:
    void clearCache();

private slots:
    void loadLevel(int levelIndex);
    void saveLevel();
    void setTerrainImage(std::string);
};


#endif //EDITORWINDOW_HPP
