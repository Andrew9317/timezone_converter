#include <QApplication>
#include "MainForm.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainForm window;
    window.show();

    app.exec();
}