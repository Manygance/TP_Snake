#include <ctime>
#include <fmod/fmod.h>

#include "snakewindow.hpp"

#include <fmod/fmod.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

    SnakeWindow window;
    window.show();

    return app.exec();
}
