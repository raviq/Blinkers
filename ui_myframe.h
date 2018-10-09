/********************************************************************************
** Form generated from reading UI file 'myframe.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFRAME_H
#define UI_MYFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_MyFrame
{
public:

    void setupUi(QFrame *MyFrame)
    {
        if (MyFrame->objectName().isEmpty())
            MyFrame->setObjectName(QStringLiteral("MyFrame"));
        MyFrame->resize(44, 43);
        MyFrame->setFrameShape(QFrame::StyledPanel);
        MyFrame->setFrameShadow(QFrame::Raised);

        retranslateUi(MyFrame);

        QMetaObject::connectSlotsByName(MyFrame);
    } // setupUi

    void retranslateUi(QFrame *MyFrame)
    {
        MyFrame->setWindowTitle(QApplication::translate("MyFrame", "Frame", 0));
    } // retranslateUi

};

namespace Ui {
    class MyFrame: public Ui_MyFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFRAME_H
