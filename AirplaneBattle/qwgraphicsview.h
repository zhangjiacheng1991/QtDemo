#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QWGraphicsView(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void keyBoardPressed(QKeyEvent event);
    void keyBoardReleased(QKeyEvent event);
    void mouseMoved(QMouseEvent event);
};

#endif // QWGRAPHICSVIEW_H
