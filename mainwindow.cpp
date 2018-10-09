#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, int numberFrames) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    numFrames = numberFrames;
    ui->setupUi(this);
    statusBar()->setSizeGripEnabled(true);
    setFixedSize(maximumSize());
    setWindowTitle("Autonomous Threaded Observers (Percepts: Colors)");

    // starting time
     start = QDateTime::currentMSecsSinceEpoch();

    loadGUI();
}

//================================================================================================

void MainWindow::loadGUI()
{
    pheno = new CLogBook** [numFrames];
    btnLearn = new QPushButton("Learn");
    btnQuit = new QPushButton("Quit");

    connect(btnLearn, SIGNAL(clicked()), this, SLOT(On_LearnButtonClicked()));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(On_quiButtonClicked()));

    checkBox = new QCheckBox("Faces");
    connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(showFaces()));

    checkBox1 = new QCheckBox("Observations");
    connect(checkBox1, SIGNAL(toggled(bool)), this, SLOT(showCores()));

    checkBox2 = new QCheckBox("Actions");
    connect(checkBox2, SIGNAL(toggled(bool)), this, SLOT(showActions()));

    QHBoxLayout *top = new QHBoxLayout;
    QHBoxLayout *middle = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;

    m_hAgent = (double*) malloc(numFrames * sizeof(double));

    for ( int i = 0 ; i < numFrames ; i++ )
    {
         QGroupBox* formGroupBox = new QGroupBox("Agent " + QString::number(i) );
         layout[i] = new QFormLayout;

         frame[i] = new MyFrame(this);

         QHBoxLayout *blinkerLayout = new QHBoxLayout;
         blinkerLayout->addStretch();
         blinkerLayout->addWidget(frame[i]); // the colorful tile;
         blinkerLayout->addStretch();

         /*
         // init the H value and its label
         m_hAgent[i] = 0.0;
         m_hAgentLabel = new QLabel("  H = " + QString::number(m_hAgent[i]));
         blinkerLayout->addWidget(m_hAgentLabel);
        */
         // adding the blinker tile and the label

         layout[i]->addItem(blinkerLayout);
         layout[i]->addRow(new QLabel(""));


         QFormLayout* actionsLayout = new QFormLayout;
         actionsGroupBox[i] = new QGroupBox("Internal generative model of actions");


         actionsLayout->addRow(new QLabel("   Time  \t " + QString::number(i) + "'s action"));
         FrameEditor[i] = new CLogBook;
         actionsLayout->addRow(FrameEditor[i]);

         QFormLayout* observationsLayout = new QFormLayout;
         observationsGroupBox[i] = new QGroupBox("Observations of others' faces");

         pheno[i] = new CLogBook* [numFrames];

         for (int j = 0 ; j < numFrames ; j++)
         {
                 //if ( j != i ) // reomved, allowing the agent to observe itself too.
                //{
                     pheno[i][j] = new CLogBook;
                     QString name = QString::number(i) + "'s observations of " + QString::number(j) + "'s face" ;
                     QLabel *nameLabel = new QLabel(name);
                     qDebug() << nameLabel->font();
                     QFont f( "Lucida Grande", 12, QFont::Normal);
                     nameLabel->setFont(f);
                     observationsLayout->addRow(nameLabel);
                     observationsLayout->addRow(pheno[i][j]);
                 //}
         }


         actionsGroupBox[i]->setLayout(actionsLayout);
         layout[i]->addRow(actionsGroupBox[i]);

         layout[i]->addRow(new QLabel(""));

         observationsGroupBox[i]->setLayout(observationsLayout);
         layout[i]->addRow(observationsGroupBox[i]);

         formGroupBox->setLayout(layout[i]);
         middle->addWidget(formGroupBox);
    }

    btnLayout->addStretch();
    btnLayout->addWidget(checkBox);
    btnLayout->addWidget(checkBox2);
    btnLayout->addWidget(checkBox1);

    btnLayout->addWidget(btnLearn);
    btnLayout->addWidget(btnQuit);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(top);
    mainLayout->addLayout(middle);
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(btnLayout);
    centralWidget()->setLayout(mainLayout);

//=== Setting Threads ======================================================================================
    /* A QThread should be used much like a regular thread instance: prepare an object (QObject) class with all your desired
     * functionality in it. Then create a new QThread instance, push the QObject onto it using moveToThread(QThread*) of the QObject
     * instance and call start() on the QThread instance. That’s all. You set up the proper signal/slot connections to make it quit
     * properly and such, and that’s all. https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/ */

    for (int i = 0 ; i < numFrames ; i++)
    {
        // The thread and the worker are created in the constructor so it is always safe to delete them.
        thread[i] = new QThread();
        worker[i] = new Worker(frame[i], FrameEditor[i], i);

        QObject::connect(frame[i], SIGNAL(frameColorChanged(QColor, int)), this, SLOT(updateFrameEditor(QColor, int)));

        worker[i]->moveToThread(thread[i]);
        // hooks up the error message signal from the worker to an error processing function in the main thread.
        connect(worker[i], SIGNAL(error(QString)), this, SLOT(errorString(QString)));

        // connects the thread’s started() signal to the processing() slot in the worker, causing it to start.
        connect(thread[i], SIGNAL(started()), worker[i], SLOT(process()));

        /* Then the clean-up: when the worker instance emits finished(), as we did in the example, it will signal the thread to quit, i.e.
         * shut down. We then mark the worker instance using the same finished() signal for deletion. Finally, to prevent nasty crashes
         * because the thread hasn’t fully shut down yet when it is deleted, we connect the finished() of the thread (not the worker!)
         * to its own deleteLater() slot. This will cause the thread to be deleted only after it has fully shut down.  */

        connect(worker[i], SIGNAL(finished()), thread[i], SLOT(quit()));
        connect(worker[i], SIGNAL(finished()), worker[i], SLOT(deleteLater()));
        connect(thread[i], SIGNAL(finished()), thread[i], SLOT(deleteLater()));

        thread[i]->start();
    }

    checkBox->setChecked(false);
    checkBox1->setChecked(false);
    checkBox2->setChecked(false);

    for (int i = 0 ; i < numFrames ; i++)
    {
        frame[i]->setVisible(false);
        observationsGroupBox[i]->setVisible(false);
        actionsGroupBox[i]->setVisible(false);
    }

}

//================================================================================================
void MainWindow::errorString(QString s)
{
    qDebug() << this->QObject::thread()->currentThreadId() << ": Error :" << s;
}
//================================================================================================

// A slot is called when a signal connected to it is emitted
// i: indexed of the currently updated frame
void MainWindow::updateFrameEditor(QColor color, int i)
{
    // Get current time
  //  QString timeString = QTime::currentTime().toString();

    // Returns the number of milliseconds since 1970-01-01T00:00:00 Universal Coordinated Time.
     QString t = QString::number(QDateTime::currentMSecsSinceEpoch() - start);

     qDebug() << t << endl ;

    // TODO unify below
    FrameEditor[i]->recvLogSignal(t + "\t" + color.name() );
    FrameEditor[i]->highlight(QColor(228, 230, 236), QColor(0,0,0), 255);

    //FrameEditor[i]->highlight(QColor(133, 99, 99));

    for (int j = 0 ; j < numFrames ; j++)
       if ( j != i )
       {
          pheno[j][i]->recvLogSignal(t); //timeString);// + "\t" + color.name() );
          pheno[j][i]->highlight(QColor(0,0,0), color, 150);
       }
}
//================================================================================================

void MainWindow::showFaces()
{
    for (int i = 0 ; i < numFrames ; i++)
      frame[i]->setVisible(checkBox->isChecked());
}

void MainWindow::showCores()
{
    for (int i = 0 ; i < numFrames ; i++)
         observationsGroupBox[i]->setVisible(checkBox1->isChecked());
}

void MainWindow::showActions()
{
    for (int i = 0 ; i < numFrames ; i++)
        actionsGroupBox[i]->setVisible(checkBox2->isChecked());
}

//================================================================================================

void MainWindow::On_LearnButtonClicked()
{
    qDebug() << "LearnButton Clicked";
}
//================================================================================================

void MainWindow::On_quiButtonClicked()
{
    qDebug() << "CancelButton Clicked. Quitting.";
    qApp->exit();
}

//================================================================================================

MainWindow::~MainWindow()
{
    for(int i = 0 ; i < numFrames ; i++)
        delete [] pheno[i];
    delete [] pheno;

    delete ui;
}
