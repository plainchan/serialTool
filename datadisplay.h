#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>

class TimeView;
class SearchPanel;
class DataDisplayPrivate;
class QAction;
class DataHighlighter;

class DataDisplay : public QWidget
{
    Q_OBJECT

    struct DisplayLine {
        QString data;
        QString trailer;
    };

public:
    explicit DataDisplay(QWidget *parent = nullptr);

    void clear();

    void setReadOnly(bool readonly);

    void setUndoRedoEnabled(bool enabled);

    void startSearch();

    void displayData(const QByteArray &data);

    void setDisplayTime(bool displayTime);

    void setDisplayHex(bool displayHex);

    void setDisplayCtrlCharacters(bool displayCtrlCharacters);

    void setLinebreakChar(const QString &chars);

    QTextDocument *getTextDocument();

private:
    void find(const QString &, QTextDocument::FindFlags);
    void insertSpaces(QString &data, int step = 1);
    bool formatHexData(const QByteArray &inData);
    void constructDisplayLine(const QByteArray &inData);
    void setupTextFormats();

    DataDisplayPrivate *m_dataDisplay;

    SearchPanel *m_searchPanel;

    int m_searchAreaHeight;

    /**
     * @brief m_timestamp
     */
    QTime m_timestamp;

    /**
     * @brief m_hexBytes
     */
    quint64 m_hexBytes;

    /**
     * In case the last printed hex line
     * contained less than 16 bytes,
     * The line's raw content will be stored
     * here so it can be reprinted in the next round
     * @brief m_hexLeftOver
     */
    QByteArray *m_hexLeftOver;

    /**
     * Data is displayed as hexadecimal values.
     * @brief m_displayHex
     */
    bool m_displayHex;

    /**
     * Ctrl characters like LF and Tabs are visualized
     * with symbols
     * @brief m_displayCtrlCharacters
     */
    bool m_displayCtrlCharacters;

    /**
     * defines characters at which a new line is generated.
     */
    char m_linebreakChar;

    /**
     * The container to store multiple formated
     * lines before beeing printed
     * @brief m_data
     */
    QList<DisplayLine> m_data;

    bool m_previous_ended_with_nl;

    QTextCharFormat *m_format_data;
    QTextCharFormat *m_format_hex;
    QTextCharFormat *m_format_ascii;

    QVector<QTime> *m_timestamps;
    DataHighlighter *m_highlighter;
    bool m_redisplay;
    QTimer m_bufferingIncomingDataTimer;

private slots:
    void displayDataFromBuffer(void);
};

class DataDisplayPrivate : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit DataDisplayPrivate(DataDisplay *parent = nullptr);

    void timeViewPaintEvent(QPaintEvent *event);

    int timeViewWidth();

    void setTimestampFormat(const QString &timestampFormat);

    void setTimeFormat(QTextCharFormat *format_time);

    QVector<QTime> *timestamps();

    void setDisplayTime(bool displayTime);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void updateTimeView(const QRect &, int);

private:
    QTextCharFormat *m_format_time;

    /**
     * @brief m_timestampFormat
     */
    QString m_timestampFormat;

    int m_time_width;
    TimeView *m_timeView;
    QVector<QTime> *m_timestamps;
};

#endif // DATADISPLAY_H
