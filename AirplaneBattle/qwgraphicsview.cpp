#include "qwgraphicsview.h"

QWGraphicsView::QWGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void QWGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyBoardPressed(*event);
    QGraphicsView::keyPressEvent(event);
}

void QWGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    emit keyBoardReleased(*event);
    QGraphicsView::keyReleaseEvent(event);
}

void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(*event);
    QGraphicsView::mouseMoveEvent(event);
}
