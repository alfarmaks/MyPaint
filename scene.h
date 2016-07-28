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
    bool saved() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Mode sceneMode;
    QPointF origPoint;
    QGraphicsLineItem* itemToDraw;
    QString borderColor;
    QString fillColor;
    bool save = true;
    void makeItemsControllable(bool areControllable);
};

#endif // SCENE_H
