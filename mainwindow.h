#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolButton>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QFileInfo>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

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

    //QToolButtons for panel tools
    QToolButton *actionPensil;
    QToolButton *actionPaintBucket;
    QToolButton *actionText;
    QToolButton *actionEraser;
    QToolButton *actionPipette;
    QToolButton *actionSearch;

    //QToolButtons for panel Drawing
    QToolButton *actionLine;
    QToolButton *actionRect;
    QToolButton *actionEllipse;
    QGraphicsView *graphics;

    //panel Colors
    QToolButton *color1;
    QLabel *color1Text;
    QToolButton *color2;
    QLabel *color2Text;
    bool color1Checked = true;
    bool color2Checked = false;
    QToolButton *actionStrokeFill;

    QToolButton *colorBlack;
    QToolButton *colorWhite;
    QToolButton *colorDarkGrey;
    QToolButton *colorGrey;
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

    void mouseMoveEvent(QMouseEvent *ev);
    void closeEvent (QCloseEvent *event);
    void saveFile(QFileInfo checkSuffix);
    void ErrorFileFormat(QString suffix);
    bool checkFileFormat(QFileInfo checkSuffix);

private slots:
    void openFile();
    void aboutInfo();
    void saveImage();
    void saveAsImage();
    void newLayout();
    void clickColor1();
    void clickColor2();
    void changeColor();

};

#endif // MAINWINDOW_H
