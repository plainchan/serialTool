#include "mainwindow.h"
// version.h is generated via cmake
// if you use qmake, please cp version.h.in to version.h
#include "version.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QCoreApplication::translate("main", "CuteCom - Serial Terminal %1").arg(CuteCom_VERSION));
    parser.addHelpOption();
    QCommandLineOption sessionOption(QStringList() << "s"
                                                   << "session",
                                     QCoreApplication::translate("main", "Open a named <session>"),
                                     QCoreApplication::translate("main", "session"));
    parser.addOption(sessionOption);

    // Process the actual command line arguments given by the user
    parser.process(a);
    QString session = parser.value(sessionOption);

    MainWindow w(0, session);
    QIcon appIcon;
    appIcon.addFile(QStringLiteral(":/images/terminal.svg"));
    w.setWindowIcon(appIcon);
    w.show();

    return a.exec();
}
