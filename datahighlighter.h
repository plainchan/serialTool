#ifndef DATAHIGHLIGHTER_H
#define DATAHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class DataHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum Formats { HEX };

    DataHighlighter(QTextDocument *parent = nullptr);
    void setSearchString(const QString &search);
    void setCharFormat(QTextCharFormat *format, Formats type);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    QRegExp *m_pattern_time;
    QTextCharFormat m_format_time;
    QRegExp *m_pattern_bytes;
    QTextCharFormat m_format_bytes;
    QRegExp *m_pattern_ctrl;
    QTextCharFormat m_format_ctrl;
    QRegExp *m_pattern_hex;
    QTextCharFormat m_format_hex;
    QTextCharFormat m_format_search;

    QString m_searchString;
};

#endif // DATAHIGHLIGHTER_H
