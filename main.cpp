#include <QApplication>
#include "noughtscrosseswidget.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("://styles/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    app.setStyleSheet(styleSheet);

    Widget w;
    w.show();
    return app.exec();
}
