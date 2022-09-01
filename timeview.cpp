#include "timeview.h"
#include "datadisplay.h"

/*!
 * This class provides a column displaying the time a line
 * was added to a data display.
 * The actual painting is done within the data display itself.
 * \brief TimeView::TimeView
 * \param display
 */
TimeView::TimeView(DataDisplayPrivate *display)
    : QWidget(display)
{
    dataDisplay = display;
}

QSize TimeView::sizeHint() const { return QSize(dataDisplay->timeViewWidth(), 0); }

void TimeView::paintEvent(QPaintEvent *event) { dataDisplay->timeViewPaintEvent(event); }
