#ifndef CLOGBOOK_H
#define CLOGBOOK_H

#include <QTextEdit>
#include <QTime>

class CLogBook : public QTextEdit
{
    Q_OBJECT
private:
    QString content;

public:
    explicit CLogBook(QWidget *parent = 0) : QTextEdit(parent)
    {
        // size
        setFixedSize( width() * 0.28, height() * 0.15);
        // setting background
        QPalette FrameEditorPalette = this->palette();
        FrameEditorPalette.setColor(QPalette::Base, QColor(228, 230, 236));
        setPalette(FrameEditorPalette);
        // content
        content = QTime::currentTime().toString() + "  Starting";
        setPlainText(content);
    }

    void highlight(QColor, QColor, int);
    void log(QString cnt);

public slots:
    void recvLogSignal(QString message);

};

#endif // CLOGBOOK_H
