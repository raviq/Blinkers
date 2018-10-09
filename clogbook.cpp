#include "clogbook.h"


void CLogBook::log(QString cnt)
{
    content = cnt + "\n" + toPlainText();
    setPlainText(content);
}

// Highlights upper line of ClobBook using 'color'
void CLogBook::highlight(QColor fcolor, QColor bcolor, int alpha)
{
   QTextEdit::ExtraSelection highlight;
   highlight.cursor = textCursor();
   highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
   QColor abcolor = QColor(bcolor);
   abcolor.setAlpha(alpha); // Int alpha is specified in the range 0-25
   highlight.format.setBackground(abcolor);
   highlight.format.setForeground(fcolor);

   QList<QTextEdit::ExtraSelection> extras;
   extras << highlight;
   setExtraSelections(extras);
}


void CLogBook::recvLogSignal(QString message)
{
    log(message);
}
