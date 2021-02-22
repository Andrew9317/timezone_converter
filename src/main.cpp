#include "MainForm.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainForm window;

    // window.setAttribute(Qt::WA_DeleteOnClose);
    window.setMinimumSize(350, 550);
    window.setWindowTitle("Test!");
    window.setStyleSheet(QStringLiteral("QDialog { "
                                        "border-radius: 38px; "
                                        "background: #535050; "
                                        "color: #003200; "
                                        "}"));

    window.show();

    app.exec();
}