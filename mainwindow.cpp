#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
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
    //this->setMouseTracking(true);

    graphics = new QGraphicsView(this);
    graphics->setAlignment(Qt::AlignCenter);
    graphics->setMouseTracking(true);
    this->setCentralWidget(graphics);

    //Set actions icons and names Tools
    actionPensil = new QToolButton(this);
    actionPensil->setIcon(QIcon(":/ToImages/Images/pensil.png"));
    actionPensil->setIconSize(QSize(24, 24));
    actionPaintBucket = new QToolButton(this);
    actionPaintBucket->setIcon(QIcon(":/ToImages/Images/paintBucket.png"));
    actionPaintBucket->setIconSize(QSize(24, 24));
    actionText = new QToolButton(this);
    actionText->setIcon(QIcon(":/ToImages/Images/Text_icon.png"));
    actionText->setIconSize(QSize(24, 24));
    actionEraser = new QToolButton(this);
    actionEraser->setIcon(QIcon(":/ToImages/Images/Eraser.png"));
    actionEraser->setIconSize(QSize(24, 24));
    actionPipette = new QToolButton(this);
    actionPipette->setIcon(QIcon(":/ToImages/Images/pipette.png"));
    actionPipette->setIconSize(QSize(24, 24));
    actionSearch = new QToolButton(this);
    actionSearch->setIcon(QIcon(":/ToImages/Images/Search.png"));
    actionSearch->setIconSize(QSize(24, 24));

    //create widget and layout for setting tools
    QWidget *widgetTools = new QWidget();
    QHBoxLayout *layoutH = new QHBoxLayout();
    QHBoxLayout *layoutH2 = new QHBoxLayout();
    QLabel *tools = new QLabel("Tools");
    QVBoxLayout *layoutTools = new QVBoxLayout(widgetTools);

    layoutH->addWidget(actionPensil);
    layoutH->addWidget(actionPaintBucket);
    layoutH->addWidget(actionText);
    layoutH2->addWidget(actionEraser);
    layoutH2->addWidget(actionPipette);
    layoutH2->addWidget(actionSearch);

    layoutTools->addLayout(layoutH);
    layoutTools->addLayout(layoutH2);
    layoutTools->addWidget(tools);
    layoutTools->setAlignment(tools, Qt::AlignCenter | Qt::AlignBottom);
    widgetTools->setLayout(layoutTools);

    //Set actions and names Drawing
    actionEllipse= new QToolButton();
    actionEllipse->setIcon(QIcon(":/ToImages/Images/Ellipse.png"));
    actionEllipse->setIconSize(QSize(24, 24));
    actionLine = new QToolButton();
    actionLine->setIcon(QIcon(":/ToImages/Images/line.png"));
    actionLine->setIconSize(QSize(24, 24));
    actionRect = new QToolButton();
    actionRect->setIcon(QIcon(":/ToImages/Images/Rect.png"));
    actionRect->setIconSize(QSize(24, 24));

    QWidget *widgetDrawing = new QWidget();
    QHBoxLayout *layoutHD = new QHBoxLayout();
    //QHBoxLayout *layoutHD2 = new QHBoxLayout();
    QLabel *Shapes = new QLabel("Shapes");
    QVBoxLayout *layoutDrawing = new QVBoxLayout(widgetDrawing);

    layoutHD->addWidget(actionLine);
    layoutHD->addWidget(actionRect);
    layoutHD->addWidget(actionEllipse);

    layoutDrawing->addLayout(layoutHD);
    layoutDrawing->addWidget(Shapes);
    layoutDrawing->setAlignment(Shapes, Qt::AlignBottom | Qt::AlignCenter);
    widgetDrawing->setLayout(layoutDrawing);

    //Size
    QLabel *size = new QLabel("Size: ");
    size->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    spinBoxSize = new QSpinBox();
    spinBoxSize->setRange(1, 20);
    spinBoxSize->setValue(1);
    spinBoxSize->setSingleStep(1);

    sliderSize = new QSlider();
    sliderSize->setRange(1, 20);
    sliderSize->setValue(1);
    sliderSize->setSingleStep(1);
    sliderSize->setOrientation(Qt::Horizontal);
    //sliderSize->setMaximumWidth(150);

    QWidget *widgetSize = new QWidget();
    QHBoxLayout *sizeHB = new QHBoxLayout();
    QVBoxLayout *sizeVB = new QVBoxLayout();

    sizeHB->addWidget(size);
    sizeHB->addWidget(spinBoxSize);
    sizeVB->addLayout(sizeHB);
    sizeVB->addWidget(sliderSize);
    sizeVB->setAlignment(sliderSize, Qt::AlignCenter);

    widgetSize->setLayout(sizeVB);

    connect(spinBoxSize, SIGNAL(valueChanged(int)), sliderSize, SLOT(setValue(int)));
    connect(sliderSize, SIGNAL(valueChanged(int)), spinBoxSize, SLOT(setValue(int)));

    //Colors
    actionStrokeFill = new QToolButton();
    actionStrokeFill->setIconSize(QSize(48, 48));
    actionStrokeFill->setIcon(QIcon(":/ToImages/Images/Stroke_Fill.png"));
    actionStrokeFill->setCheckable(true);

    color1 = new QToolButton();
    color2 = new QToolButton();
    color1->setStyleSheet("background-color:black");
    color1->setFixedSize(24, 24);
    color2->setStyleSheet("background-color:white");
    color2->setFixedSize(24, 24);
    color1->setCheckable(true);
    color2->setCheckable(true);
    if(color1Checked)
    {
        color1->setChecked(color1Checked);
    }
    else
    {
        color2->setChecked(color2Checked);
    }
    color1Text = new QLabel("Color 1");
    color2Text = new QLabel("Color 2");

    //connect change color1 and color2
    connect(color1, SIGNAL(clicked(bool)), this, SLOT(clickColor1()));
    connect(color2, SIGNAL(clicked(bool)), this, SLOT(clickColor2()));

    //color panel
    colorBlack = new QToolButton();
    colorWhite = new QToolButton();
    colorDarkGrey = new QToolButton();
    colorGrey = new QToolButton();
    colorDarkRed = new QToolButton();
    colorRed = new QToolButton();
    colorDarkMagenta = new QToolButton();
    colorMagenta = new QToolButton();
    colorDarkYellow = new QToolButton();
    colorYellow = new QToolButton();
    colorDarkGreen = new QToolButton();
    colorGreen = new QToolButton();
    colorDarkBlue = new QToolButton();
    colorBlue = new QToolButton();
    colorDarkCyan = new QToolButton();
    colorCyan = new QToolButton();

    colorBlack->setStyleSheet("background-color:black");
    colorBlack->setFixedSize(24, 24);
    colorWhite->setStyleSheet("background-color:white");
    colorWhite->setFixedSize(24, 24);
    colorDarkGrey->setStyleSheet("background-color:darkGrey");
    colorDarkGrey->setFixedSize(24, 24);
    colorGrey->setStyleSheet("background-color:grey");
    colorGrey->setFixedSize(24, 24);
    colorDarkRed->setStyleSheet("background-color:darkRed");
    colorDarkRed->setFixedSize(24, 24);
    colorRed->setStyleSheet("background-color:red");
    colorRed->setFixedSize(24, 24);
    colorDarkMagenta->setStyleSheet("background-color:darkMagenta");
    colorDarkMagenta->setFixedSize(24, 24);
    colorMagenta->setStyleSheet("background-color:magenta");
    colorMagenta->setFixedSize(24, 24);
    colorDarkYellow->setStyleSheet("background-color:darkYellow");
    colorDarkYellow->setFixedSize(24, 24);
    colorYellow->setStyleSheet("background-color:yellow");
    colorYellow->setFixedSize(24, 24);
    colorDarkGreen->setStyleSheet("background-color:darkGreen");
    colorDarkGreen->setFixedSize(24, 24);
    colorGreen->setStyleSheet("background-color:green");
    colorGreen->setFixedSize(24, 24);
    colorDarkBlue->setStyleSheet("background-color:darkBlue");
    colorDarkBlue->setFixedSize(24, 24);
    colorBlue->setStyleSheet("background-color:blue");
    colorBlue->setFixedSize(24, 24);
    colorDarkCyan->setStyleSheet("background-color:darkCyan");
    colorDarkCyan->setFixedSize(24, 24);
    colorCyan->setStyleSheet("background-color:cyan");
    colorCyan->setFixedSize(24, 24);

    QHBoxLayout *colorLayoutDark = new QHBoxLayout();
    QHBoxLayout *colorLayoutLight = new QHBoxLayout();
    QVBoxLayout *colors = new QVBoxLayout();

    colorLayoutDark->addWidget(colorBlack);
    colorLayoutDark->addWidget(colorDarkGrey);
    colorLayoutDark->addWidget(colorDarkRed);
    colorLayoutDark->addWidget(colorDarkMagenta);
    colorLayoutDark->addWidget(colorDarkYellow);
    colorLayoutDark->addWidget(colorDarkGreen);
    colorLayoutDark->addWidget(colorDarkBlue);
    colorLayoutDark->addWidget(colorDarkCyan);

    colorLayoutLight->addWidget(colorWhite);
    colorLayoutLight->addWidget(colorGrey);
    colorLayoutLight->addWidget(colorRed);
    colorLayoutLight->addWidget(colorMagenta);
    colorLayoutLight->addWidget(colorYellow);
    colorLayoutLight->addWidget(colorGreen);
    colorLayoutLight->addWidget(colorBlue);
    colorLayoutLight->addWidget(colorCyan);

    colors->addLayout(colorLayoutDark);
    colors->addLayout(colorLayoutLight);

    QLabel *colorName = new QLabel("Colors");
    QWidget *widgetColor = new QWidget();
    QHBoxLayout *colorPanel = new QHBoxLayout();
    QVBoxLayout *colorVB = new QVBoxLayout();
    QVBoxLayout *color1Layout = new QVBoxLayout();
    QVBoxLayout *color2Layout = new QVBoxLayout();

    color1Layout->addWidget(color1);
    color1Layout->addWidget(color1Text);
    color1Layout->setAlignment(color1, Qt::AlignCenter);
    color2Layout->addWidget(color2);
    color2Layout->addWidget(color2Text);
    color2Layout->setAlignment(color2, Qt::AlignCenter);

    colorPanel->addWidget(actionStrokeFill);
    colorPanel->addLayout(color1Layout);
    colorPanel->addLayout(color2Layout);
    colorPanel->addLayout(colors);
    colorVB->addLayout(colorPanel);
    colorVB->addWidget(colorName);
    colorVB->setAlignment(colorName, Qt::AlignCenter | Qt::AlignBottom);
    widgetColor->setLayout(colorVB);

    ui->mainToolBar->addWidget(widgetTools);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(widgetDrawing);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(widgetSize);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(widgetColor);

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
                QCoreApplication::applicationDirPath(),
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
                                                                        QMessageBox::No | QMessageBox::Yes,
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

void MainWindow::clickColor1()
{
    if(!color1Checked)
    {
        color1Checked = true;
        color1->setChecked(color1Checked);
        color2Checked = false;
        color2->setChecked(color2Checked);
    }
}

void MainWindow::clickColor2()
{
    if(!color2Checked)
    {
        color1Checked = false;
        color1->setChecked(color1Checked);
        color2Checked = true;
        color2->setChecked(color2Checked);
    }
}

void MainWindow::changeColor()
{

}
