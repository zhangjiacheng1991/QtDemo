#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initScene();
    void initBackground();
    void initdata();
    void gameOver();
    void GameBegin(int level);
private:
    void onUpdata();
    void onCreateEnemy();
    void onKeyBoardPressed(QKeyEvent event);
    void onMouseMove(QMouseEvent event);
    void onCreateBullet();
    void colliding();
    void removeOutItem();
private:
    Ui::Widget *ui;
    QGraphicsScene* m_scene;
    QGraphicsItemGroup* m_background;
    QGraphicsItemGroup* m_bullets;
    QGraphicsItemGroup* m_enemys;
    QGraphicsPixmapItem* m_airplane;
    QTimer m_updata;
    QTimer m_createEnemy;
    QTimer m_createBullet;
    int m_level{0};
    int m_airplaneMoveSpeed{10};
    int pressCurr{0};
    int pressBefore{0};
    int m_width{512};
    int m_height{768};
};
#endif // WIDGET_H
