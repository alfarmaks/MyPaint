#include "scene.h"

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    itemToDraw = 0;
    itemRect = 0;
    itemEllipse = 0;
}

void Scene::setMode(Mode mode){
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine || mode == DrawEllipse || mode == DrawRect){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject){
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }
    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::makeItemsControllable(bool areControllable){
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine || sceneMode == DrawRect || sceneMode == DrawEllipse)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine)
    {
        if(!itemToDraw)
        {
            itemToDraw = new QGraphicsLineItem();
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(color(0), sizeOfBorderLine, Qt::SolidLine));
            itemToDraw->setPos(origPoint);
        }
        itemToDraw->setLine(0, 0,
                            event->scenePos().x() - origPoint.x(),
                            event->scenePos().y() - origPoint.y());
        save = false;
    }
    else if(sceneMode == DrawRect)
    {
        if(!itemRect)
        {
            itemRect = new QGraphicsRectItem();
            this->addItem(itemRect);
            itemRect->setPen(QPen(color(0), sizeOfBorderLine, Qt::SolidLine));
            itemRect->setPos(origPoint);
        }
        if(_fill)
        {
            itemRect->setBrush(color(1));
        }
        itemRect->setRect(0,0,
                          event->scenePos().x() - origPoint.x(),
                          event->scenePos().y() - origPoint.y());
        save = false;
    }
    else if(sceneMode == DrawEllipse)
    {
        if(!itemEllipse)
        {
            itemEllipse = new QGraphicsEllipseItem();
            this->addItem(itemEllipse);
            itemEllipse->setPen(QPen(color(0), sizeOfBorderLine, Qt::SolidLine));
            itemEllipse->setPos(origPoint);
        }
        if(_fill)
        {
            itemEllipse->setBrush(color(1));
        }
        itemEllipse->setRect(0,0,
                          event->scenePos().x() - origPoint.x(),
                          event->scenePos().y() - origPoint.y());
        save = false;
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    itemRect = 0;
    itemEllipse = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else
        QGraphicsScene::keyPressEvent(event);
}

void Scene::setBorderColor(QString color)
{
    borderColor = color;
}

void Scene::setFillColor(QString color)
{
    fillColor = color;
}

bool Scene::isSaved() const
{
    return save;
}

void Scene::saved()
{
    save = true;
}

void Scene::setSizeOfBorderLine(int size)
{
    sizeOfBorderLine = static_cast<qreal>(size);
}

Qt::GlobalColor Scene::color(int which) const
{
    QString color;
    if(which == 0)
    {
        color = borderColor;
    }
    else
    {
        color = fillColor;
    }

    //return color
    if(color == "black")
    {
        return Qt::black;
    }
    else if(color == "white")
    {
        return Qt::white;
    }
    else if(color == "darkGray")
    {
        return Qt::darkGray;
    }
    else if (color == "gray")
    {
        return Qt::gray;
    }
    else if(color == "darkRed")
    {
        return Qt::darkRed;
    }
    else if(color == "red")
    {
        return Qt::red;
    }
    else if(color == "darkMagenta")
    {
        return Qt::darkMagenta;
    }
    else if(color == "magenta")
    {
        return Qt::magenta;
    }
    else if(color == "darkYellow")
    {
        return Qt::darkYellow;
    }
    else if(color == "yellow")
    {
        return Qt::yellow;
    }
    else if(color == "darkGreen")
    {
        return Qt::darkGreen;
    }
    else if(color == "green")
    {
        return Qt::green;
    }
    else if(color == "darkBlue")
    {
        return Qt::darkBlue;
    }
    else if(color == "blue")
    {
        return Qt::blue;
    }
    else if(color == "darkCyan")
    {
        return Qt::darkCyan;
    }
    else if(color == "cyan")
    {
        return Qt::cyan;
    }
}

void Scene::setFill(bool fillIn)
{
    _fill = fillIn;
}
