#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include <QWidget>
class DataDisplayPrivate;

class TimeView : public QWidget
{
    Q_OBJECT
public:
    explicit TimeView(DataDisplayPrivate *display);

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    DataDisplayPrivate *dataDisplay;
};

#endif // TIMEVIEW_H
