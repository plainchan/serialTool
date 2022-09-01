#include <plugin.h>

Plugin::Plugin(QObject *owner, QString name, QFrame *frame, processCmd_fp processCmd)
    : owner(owner)
    , name(name)
    , frame(frame)
    , processCmd(processCmd)
{
}
