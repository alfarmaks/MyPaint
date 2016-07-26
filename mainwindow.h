#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolButton>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QFileInfo>

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
    QToolButton *actionPensil;
    QToolButton *actionPaintBucket;
    QToolButton *actionText;
    QToolButton *actionEraser;
    QToolButton *actionPipette;
    QToolButton *actionSearch;
    QGraphicsView *graphics;


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

};

#endif // MAINWINDOW_H
