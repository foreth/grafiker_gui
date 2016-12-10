#include <QtWidgets>
#include "mainwindow.h"



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Grafiker");
    window.show();

    return app.exec();
}
