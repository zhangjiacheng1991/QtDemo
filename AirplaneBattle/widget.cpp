#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTime>
#include <QObject>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initScene();
    initdata();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initScene()
{
    m_scene = new QGraphicsScene(0,0,m_width,m_height,this);
    m_background = new QGraphicsItemGroup();
    m_bullets = new QGraphicsItemGroup();
    m_enemys =  new QGraphicsItemGroup();
    m_scene->addItem(m_background);
    m_scene->addItem(m_bullets);
    m_scene->addItem(m_enemys);
    ui->graphicsView->setScene(m_scene);
    initBackground();
}

void Widget::initBackground()
{
    QPixmap image =  QPixmap(":/img/background1.jpg");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(image,m_background);
    QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(image,m_background);
    item2->setPos(QPoint(0,-m_height));
    item->setPos(QPoint(0,0));
    m_background->addToGroup(item);
    m_background->addToGroup(item2);
}

void Widget::initdata()
{
    setFocusPolicy(Qt::StrongFocus);
    //飞机移动
    connect(ui->graphicsView,&QWGraphicsView::keyBoardPressed,this,&Widget::onKeyBoardPressed);
    connect(ui->graphicsView,&QWGraphicsView::mouseMoved,this,&Widget::onMouseMove);
    //发射子弹
    connect(&m_createBullet,&QTimer::timeout,this,&Widget::onCreateBullet);
    m_createBullet.start(100);
    //刷新地图
    connect(&m_updata,&QTimer::timeout,this,&Widget::onUpdata);
    m_updata.start(10);
    //创建敌机
    connect(&m_createEnemy,&QTimer::timeout,this,&Widget::onCreateEnemy);
    m_createEnemy.start((10 - m_level)* 50);
    m_airplane = new QGraphicsPixmapItem(QPixmap(":/img/airplane1.png"));
    m_airplane->setPos(251,384);
    m_scene->addItem(m_airplane);
}

void Widget::gameOver()
{
    m_createEnemy.stop();
    m_createBullet.stop();
    m_updata.stop();
    m_scene->clear();
    disconnect(&m_createBullet,&QTimer::timeout,this,&Widget::onCreateBullet);
    disconnect(ui->graphicsView,&QWGraphicsView::keyBoardPressed,this,&Widget::onKeyBoardPressed);
    disconnect(ui->graphicsView,&QWGraphicsView::mouseMoved,this,&Widget::onMouseMove);
    initScene();
}

void Widget::onUpdata()
{
    removeOutItem();
    colliding();
    if(m_background->y() >= m_height)
    {
        m_background->setY(0);
    }
    m_background->setY(m_background->y() + 1);
    m_enemys->setY(m_enemys->y()+ m_level + 1);
    m_bullets->setY(m_bullets->y() - 4);
}

void Widget::onCreateEnemy()
{
    qsrand(QTime::currentTime().msec());
    for(int i = 0 ; i <  qrand() % 10; i++)
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(":/img/enemy1.png"));
        //        qsrand(QTime::currentTime().msec());
        item->setData(0,qrand()%10 +m_level);
        int x = qrand()%512;
        item->setPos(x,0);
        m_enemys->addToGroup(item);

    }
}

void Widget::onKeyBoardPressed(QKeyEvent event)
{
    if(event.key() == Qt::Key_Left)
    {
        m_airplane->setX(m_airplane->x() - m_airplaneMoveSpeed);
    }
    else if(event.key() == Qt::Key_Right)
    {
        m_airplane->setX(m_airplane->x() + m_airplaneMoveSpeed);
    }
    else if(event.key() == Qt::Key_Down)
    {
        m_airplane->setY(m_airplane->y() + m_airplaneMoveSpeed);
    }
    else if(event.key() == Qt::Key_Up)
    {
        m_airplane->setY(m_airplane->y() - m_airplaneMoveSpeed);
    }
}

void Widget::onMouseMove(QMouseEvent event)
{
    m_airplane->setPos(event.pos());
}

void Widget::onCreateBullet()
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(":/img/bullet1.png"));
    item->setPos(m_airplane->x() + m_airplane->pixmap().width()/2,m_airplane->y());
    m_bullets->addToGroup(item);
}

void Widget::colliding()
{
    //是否击中敌机
    foreach(QGraphicsItem * bullet , m_bullets->childItems())
    {
        QList<QGraphicsItem *> list = bullet->collidingItems();
        if(list.isEmpty())continue;
        foreach(QGraphicsItem * enemy , list)
        {
            if(enemy->parentItem() == m_enemys)
            {
                m_enemys->removeFromGroup(enemy);
                delete enemy;
                m_bullets->removeFromGroup(bullet);
                delete bullet;
                break;
            }
        }
    }
    //英雄碰撞检测
    foreach(QGraphicsItem * item , m_airplane->collidingItems())
    {

        if(item->parentItem() == m_enemys)
        {
            gameOver();
        }

    }
}

    void Widget::removeOutItem()
    {
        foreach(QGraphicsItem * item , m_bullets->childItems())
        {
            if(item->y() <= 0)
            {
                m_bullets->removeFromGroup(item);
                delete item;
            }
        }
        foreach(QGraphicsItem * item , m_enemys->childItems())
        {
            if(item->y() >= m_height)
            {
                m_enemys->removeFromGroup(item);
                delete item;
            }
        }
    }

