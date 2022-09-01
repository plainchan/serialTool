#include "datahighlighter.h"

DataHighlighter::DataHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    m_format_time.setForeground(Qt::darkGreen);
    m_pattern_time = new QRegExp("\\d{2,2}:\\d{2,2}:\\d{2,2}:\\d{3,3} ");
    m_format_bytes.setForeground(QColor(120, 180, 200));
    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(10);
    m_format_bytes.setFont(font);
    m_pattern_bytes = new QRegExp("^\\d{8} ");
    m_format_ctrl.setForeground(Qt::darkRed);
    m_format_ctrl.setFontWeight(QFont::Bold);
    m_pattern_ctrl = new QRegExp("[\\x240A\\x240D\\x21E5]");
    font = QFont("Monospace");
    font.setStyleHint(QFont::Courier);
    font.setPointSize(10);
    m_format_hex.setFont(font);
    m_format_hex.setForeground(Qt::darkMagenta);
    m_pattern_hex = new QRegExp("<0x[\\da-f]{2}>");
    m_format_search.setBackground(QColor(230, 230, 180));
    m_format_search.setForeground(QColor(50, 50, 180));
}

void DataHighlighter::setSearchString(const QString &search)
{
    m_searchString = search;
    rehighlight();
}

void DataHighlighter::setCharFormat(QTextCharFormat *format, DataHighlighter::Formats type)
{
    Q_UNUSED(format)
    switch (type) {
    case Formats::HEX:
        // m_format_hex = format;
        break;
    default:
        break;
    }
}

void DataHighlighter::highlightBlock(const QString &text)
{
    if (text.isEmpty())
        return;
    int index = m_pattern_time->indexIn(text);
    if (index >= 0)
        setFormat(index, m_pattern_time->matchedLength(), m_format_time);

    index = m_pattern_bytes->indexIn(text);
    if (index >= 0)
        setFormat(index, m_pattern_bytes->matchedLength(), m_format_bytes);

    index = m_pattern_ctrl->indexIn(text, 0);
    while (index >= 0) {
        setFormat(index, 1, m_format_ctrl);
        index = m_pattern_ctrl->indexIn(text, index + 1);
    }

    index = m_pattern_hex->indexIn(text, 0);
    int l = 0;
    while (index >= 0) {
        l = m_pattern_hex->matchedLength();
        setFormat(index, l, m_format_hex);
        index = m_pattern_hex->indexIn(text, index + l);
    }

    if (m_searchString.isEmpty())
        return;

    const int length = m_searchString.length();
    index = text.indexOf(m_searchString, 0, Qt::CaseInsensitive);
    while (index >= 0) {
        setFormat(index, length, m_format_search);
        index = text.indexOf(m_searchString, index + length, Qt::CaseInsensitive);
    }
}
