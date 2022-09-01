#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include "ui_searchpanel.h"
#include <QTextDocument>

class SearchPanel : public QWidget, private Ui::SearchPanel
{
    Q_OBJECT

public:
    explicit SearchPanel(QWidget *parent = nullptr);
    void showPanel(bool setVisible);
    void setPatternFound(bool patternFound);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void closing();
    void findNext(QString searchText, QTextDocument::FindFlags);
    void textEntered(QString searchText);

private:
    /*!
     * \brief m_original_format
     */
    QString m_original_format;
};

#endif // SEARCHPANEL_H
