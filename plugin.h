#ifndef PLUGIN_H
#define PLUGIN_H

#include <QFrame>
#include <QObject>
#include <QString>

class Plugin : public QObject
{
    Q_OBJECT
public:
    typedef int (*processCmd_fp)(const QString *text, QString *new_text);

    Plugin(QObject *owner,                    /* who owns the plugin */
           QString name,                      /* name of plugin */
           QFrame *frame = nullptr,           /* Does the plugin has a UI interface? */
           processCmd_fp processCmd = nullptr /* function that injects the cmd */
    );

    ~Plugin() {}

    QObject *owner;
    QString name;
    QFrame *frame;
    processCmd_fp processCmd;

signals:
    void sendCmd(QString);
};

#endif // PLUGIN_H
