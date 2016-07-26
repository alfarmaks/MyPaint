#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QLabel>
#include <QIcon>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QString>
#include <QTransform>
#include <QCursor>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setMovable(false);
    this->setMouseTracking(true);

    graphics = new QGraphicsView(this);
    graphics->setAlignment(Qt::AlignCenter);
    graphics->setMouseTracking(true);
    this->setCentralWidget(graphics);

    //Set actions icons and names
    actionPensil = new QToolButton(this);
    actionPensil->setIcon(QIcon(":/ToImages/Images/pensil.png"));
    actionPaintBucket = new QToolButton(this);
    actionPaintBucket->setIcon(QIcon(":/ToImages/Images/paintBucket.png"));
    actionText = new QToolButton(this);
    actionText->setIcon(QIcon(":/ToImages/Images/Text_icon.png"));
    actionEraser = new QToolButton(this);
    actionEraser->setIcon(QIcon(":/ToImages/Images/Eraser.png"));
    actionPipette = new QToolButton(this);
    actionPipette->setIcon(QIcon(":/ToImages/Images/pipette.png"));
    actionSearch = new QToolButton(this);
    actionSearch->setIcon(QIcon(":/ToImages/Images/Search.png"));

    QWidget *widgetTools = new QWidget();
    QHBoxLayout *layoutH = new QHBoxLayout();
    QHBoxLayout *layoutH2 = new QHBoxLayout();
    QLabel *tools = new QLabel();
    QVBoxLayout *layoutTools = new QVBoxLayout(widgetTools);

    layoutH->addWidget(actionPensil);
    layoutH->addWidget(actionPaintBucket);
    layoutH->addWidget(actionText);
    layoutH2->addWidget(actionEraser);
    layoutH2->addWidget(actionPipette);
    layoutH2->addWidget(actionSearch);
    tools->setText("Tools");

    layoutTools->addLayout(layoutH);
    layoutTools->addLayout(layoutH2);
    layoutTools->addWidget(tools);
    layoutTools->setAlignment(tools, Qt::AlignCenter);
    widgetTools->setLayout(layoutTools);


    ui->mainToolBar->addWidget(widgetTools);
    ui->mainToolBar->addSeparator();

    //set shortcut for action from menubar
    ui->actionNew->setShortcut(QString("Ctrl+N"));
    ui->actionExit->setShortcut(QString("Ctrl+Q"));
    ui->actionOpen->setShortcut(QString("Ctrl+O"));
    ui->actionSave->setShortcut(QString("Ctrl+S"));
    ui->actionSave_as->setShortcut(QString("Ctrl+Shift+S"));
    ui->actionAbout->setShortcut(QString("F1"));

    //set signals and slots
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutInfo()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveImage()));
    connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(saveAsImage()));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newLayout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkFileFormat(QFileInfo checkSuffix)
{
    QList<QString> listOfFormats;
    listOfFormats<<"bmp"<<"jpg"<<"png"<<"jpeg";
    QString suffix = checkSuffix.suffix();

    if (listOfFormats.contains(suffix))
    {
        return true;
    }
    return false;
}

void MainWindow::ErrorFileFormat(QString suffix)
{
    QMessageBox msgBox;
    msgBox.setText("Incorrect format!");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setInformativeText("You chose incorrect image format");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDetailedText(QString(tr("1)You choose %1 format!\n2)You can choose only bmp, jpeg, jpg, or png files format!")).arg(suffix));
    msgBox.exec();
}

void MainWindow::openFile()
{

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "/home",
                tr("All files (*.*);;PNG files (*.png);;JPEG files (*.jpeg | *.jpg);;BMP files (*.bmp)")
                );
    if(!fileName.isEmpty())
    {
        QFileInfo checkSuffix(fileName);
        if (checkFileFormat(checkSuffix))
        {
            QImage image(fileName);

            if(image.isNull())
            {
                QMessageBox::information(this,"Image Viewer","Error Displaying image");
                return;
            }
            else
            {
                save = false;
                QGraphicsScene *scene = new QGraphicsScene();
                graphics = new QGraphicsView(scene);
                graphics->setAlignment(Qt::AlignCenter);
                this->setCentralWidget(graphics);
                this->resize(image.width()+25, image.height()+ui->mainToolBar->height()+ui->menuBar->height()+ui->statusBar->height()+25);
                scene->addPixmap(QPixmap::fromImage(image));
                //scene->addItem(item);
            }
        }
        else
        {
            ErrorFileFormat(checkSuffix.suffix());
        }

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    QTransform t;
    t.scale(1, 1);
    t.translate(0, -ui->menuBar->height()-ui->mainToolBar->height());
    QPoint pos = ev->pos()*t;
    if(pos.x() <= graphics->width() && pos.y() <= graphics->height() && pos.x() >= 0 && pos.y() >= 0)
    {
        ui->statusBar->showMessage(QString("%1, %2").arg(pos.x()).arg(pos.y()));
    }
}

void MainWindow::aboutInfo()
{
    About about;
    about.exec();
}

void MainWindow::saveFile(QFileInfo checkSuffix)
{
    if (checkFileFormat(checkSuffix))
    {
        QPixmap pixMap = graphics->grab();
        pixMap.save(filePath);
        save = true;
    }
    else
    {
        filePath = "";
        ErrorFileFormat(checkSuffix.suffix());
    }
}

void MainWindow::saveImage()
{
    if(!save)
    {
        if(!filePath.isEmpty())
        {
            QFileInfo checkSuffix(filePath);
            saveFile(checkSuffix);
        }
        else
        {
            filePath = QFileDialog::getSaveFileName(this,
                                                    tr("Save image"),
                                                    QCoreApplication::applicationDirPath(),
                                                    "JPEG files (*.jpeg | *.jpg);;PNG files (*.png);;BMP files (*.bmp)" );
            if(!filePath.isEmpty())
            {
                QFileInfo checkSuffix(filePath);
                saveFile(checkSuffix);
            }
        }

    }
}

void MainWindow::saveAsImage()
{
    filePath = QFileDialog::getSaveFileName(this,
                                            tr("Save image"),
                                            QCoreApplication::applicationDirPath(),
                                            "JPEG files (*.jpeg | *.jpg);;PNG files (*.png);;BMP files (*.bmp)" );
    if(!filePath.isEmpty())
    {
        QFileInfo checkSuffix(filePath);
        saveFile(checkSuffix);
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(!save){
        QMessageBox::StandardButton result = QMessageBox::question( this, "MyPaint",
                                                                        tr("You don't save your work.\nDo you want to save your work?\n"),
                                                                        QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
        if (result != QMessageBox::Yes)
        {
            event->accept();
        }
        else
        {
            saveAsImage();
            event->accept();
        }
    }
    else
    {
        QMessageBox::StandardButton result = QMessageBox::question( this, "MyPaint",
                                                                        tr("Are you sure?\n"),
                                                                        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
        if (result != QMessageBox::Yes)
        {
            event->ignore();
        }
        else
        {
            event->accept();
        }
    }
}

void MainWindow::newLayout()
{
    if(!save){
        QMessageBox::StandardButton result = QMessageBox::question( this, "MyPaint",
                                                                        tr("You don't save your work.\nDo you want to save your work?\n"),
                                                                        QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
        if (result == QMessageBox::Yes)
        {
            saveAsImage();
        }
    }
    graphics = new QGraphicsView(this);
    graphics->setAlignment(Qt::AlignCenter);
    graphics->setMouseTracking(true);
    this->setCentralWidget(graphics);
    save = true;
}
