#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>

class Scene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine, DrawEllipse, DrawRect};
    Scene(QObject* parent = 0);
    void setMode(Mode mode);
    void setBorderColor(QString color);
    void setFillColor(QString color);
    void setSizeOfBorderLine(int size);
    bool isSaved() const;
    void saved();
    void setFill(bool fillIn);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    QGraphicsRectItem* itemRect;
    QGraphicsEllipseItem* itemEllipse;

    //Color and line
    QString borderColor;
    QString fillColor;
    qreal sizeOfBorderLine = 1;

    bool save = true;
    bool _fill = false;
    Qt::GlobalColor color(int which = 0) const;
    void makeItemsControllable(bool areControllable);
};

#endif // SCENE_H
