#include "searchpanel.h"
#include <QKeyEvent>

SearchPanel::SearchPanel(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    le_searchText->setPlaceholderText(tr("with no selection, search is started at end of text"));
    connect(btn_close, &QToolButton::clicked, [=]() {
        emit closing();
        showPanel(false);
    });
    connect(btn_next, &QToolButton::clicked, [=]() { emit findNext(le_searchText->text(), nullptr); });
    connect(btn_prev, &QToolButton::clicked,
            [=]() { emit findNext(le_searchText->text(), QTextDocument::FindBackward); });
    installEventFilter(this);
    le_searchText->installEventFilter(this);
    m_original_format = le_searchText->styleSheet();
}

/*!
 * Shows and hides the search panel
 * \brief SearchPanel::showPanel
 * \param visible
 */
void SearchPanel::showPanel(bool visible)
{
    if (!visible) {
        hide();
    } else {
        le_searchText->setFocus();
        if (!le_searchText->text().isEmpty())
            le_searchText->selectAll();
        if (isVisible())
            return;
        setVisible(true);
    }
}

/*!
 * Changes appearance of the font to indicate if
 * the search pattern is found or not
 * \brief SearchPanel::setFound
 * \param patternFound
 */
void SearchPanel::setPatternFound(bool patternFound)
{
    le_searchText->setStyleSheet(((patternFound) ? m_original_format : QStringLiteral("color: red;")));
}

bool SearchPanel::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_F3 && !le_searchText->text().isEmpty()) {
            if (ke->modifiers() == Qt::NoModifier) {
                emit findNext(le_searchText->text(), nullptr);
            } else if (ke->modifiers() == Qt::ShiftModifier) {
                emit findNext(le_searchText->text(), QTextDocument::FindBackward);
            }
        } else if (ke->modifiers() == Qt::NoModifier) {
            if (ke->key() == Qt::Key_Escape) {
                showPanel(false);
                return true;
            } else if (obj == le_searchText) {
                if (ke->key() == Qt::Key_Return) {
                    emit textEntered(le_searchText->text());
                }
            }
        }
    } else {
        return QWidget::eventFilter(obj, event);
    }
    return false;
}
