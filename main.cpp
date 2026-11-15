#include <QApplication>
#include "welcomewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WelcomeWindow welcome;
    welcome.resize(500, 350);
    welcome.show();

    return app.exec();
}