#ifndef WHITESPACESCENE_H
#define WHITESPACESCENE_H

#include <QGraphicsScene>

class WhiteSpaceScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WhiteSpaceScene (qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    void printPoint(const QPoint &clickedPoint);
};

#endif // WHITESPACESCENE_H

