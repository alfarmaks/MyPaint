#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"
#include <QMainWindow>
#include <QAction>
#include <QToolButton>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QFileInfo>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QSignalMapper>
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool save = true;
    QString filePath;
    Ui::MainWindow *ui;

    QGraphicsView *graphics;
    Scene* scene;

    //QToolButtons for panel tools
    QToolButton *actionPensil;
    QToolButton *actionPaintBucket;
    QToolButton *actionText;
    QToolButton *actionEraser;
    QToolButton *actionPipette;

    //QToolButtons for panel Drawing
    QToolButton *actionLine;
    QToolButton *actionRect;
    QToolButton *actionEllipse;
    QToolButton *actionSelect;

    //panel Colors
    QToolButton *color1;
    QLabel *color1Text;
    QToolButton *color2;
    QLabel *color2Text;
    bool color1Checked = true;
    bool color2Checked = false;
    bool fillButton = false;
    QToolButton *actionStrokeFill;

    QToolButton *colorBlack;
    QToolButton *colorWhite;
    QToolButton *colorDarkGray;
    QToolButton *colorGray;
    QToolButton *colorDarkRed;
    QToolButton *colorRed;
    QToolButton *colorDarkMagenta;
    QToolButton *colorMagenta;
    QToolButton *colorDarkYellow;
    QToolButton *colorYellow;
    QToolButton *colorDarkGreen;
    QToolButton *colorGreen;
    QToolButton *colorDarkBlue;
    QToolButton *colorBlue;
    QToolButton *colorDarkCyan;
    QToolButton *colorCyan;

    //Size
    QSpinBox *spinBoxSize;
    QSlider *sliderSize;

    QSignalMapper *colorMapper;
    QSignalMapper *drawingMapper;

    void createActions();
    void createConnections();
    void mouseMoveEvent(QMouseEvent *ev);
    void closeEvent (QCloseEvent *event);
    void saveFile(QFileInfo checkSuffix);
    void ErrorFileFormat(QString suffix);
    bool checkFileFormat(QFileInfo checkSuffix);
    void wheelEvent(QWheelEvent *event);

private slots:
    void openFile();
    void aboutInfo();
    void saveImage();
    void saveAsImage();
    void newLayout();
    void clickColor1();
    void clickColor2();
    void clicked(const QString &color);
    void actionDrawingClicked(int mode);
    void setValueSpinBox(int value);
    void setValueSlider(int value);
    void BorderOrFill();
};

#endif // MAINWINDOW_H
