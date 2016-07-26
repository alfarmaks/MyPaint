#ifndef SCENEFORDRAWING_H
#define SCENEFORDRAWING_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>

class sceneForDrawing : public QGraphicsView
{
public:
    explicit sceneForDrawing()
    {
        this->setAlignment(Qt::AlignCenter);
        this->setMouseTracking(true);
        this->resize(800, 550);
    }
    ~sceneForDrawing();

public:
    void mouseMoveEvent(QMouseEvent *ev)
    {
        x = ev->pos().x();
        y = ev->pos().y();
    }
private:
    int x, y;

signals:
    QString currentPosition()
    {
        return QString("%1, %2").arg(x).arg(y);
    }
};

#endif // SCENEFORDRAWING_H
