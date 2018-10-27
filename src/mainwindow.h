#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myqtextedit.h"
#include "myframe.h"
#include "clogbook.h"
#include "worker.h"
#include "myqtextedit.h"

#include <QMainWindow>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <qDebug>
#include <Qtime>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QString>
#include <QTextEdit>
#include <QPalette>
#include <QString>
#include <QCheckBox>
#include <iostream>


#define MAX_FRAMES 50

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, int numberFrames = 2);
    ~MainWindow();
    void loadGUI();

private slots:
     // A slot is called when a signal connected to it is emitted
     void errorString(QString);
     void On_LearnButtonClicked();
     void On_quiButtonClicked();

//public slots:
     void updateFrameEditor(QColor, int);
     void showFaces();
     void showCores();
     void showActions();


private:
    // GUI
    int numFrames;
    Ui::MainWindow *ui;

    MyFrame *frame[MAX_FRAMES];
    // TODO unify both FrameEditor and pheno? in the loops
    CLogBook *FrameEditor[MAX_FRAMES];
    CLogBook *** pheno;  // recorded observations of the others.
    QGroupBox* observationsGroupBox[MAX_FRAMES];
    QGroupBox* actionsGroupBox[MAX_FRAMES];

    QFormLayout *layout[MAX_FRAMES];


    QPushButton *btnQuit;
    QPushButton *btnLearn;
    QCheckBox *checkBox;
    QCheckBox *checkBox1;
    QCheckBox *checkBox2;

    QThread *thread[MAX_FRAMES];
    Worker *worker[MAX_FRAMES];

    QLabel* m_hAgentLabel;
    double* m_hAgent;

    qint64 start;

};


#endif // MAINWINDOW_H
