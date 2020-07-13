#ifndef DEMO2048_H
#define DEMO2048_H

#include <QObject>
#include <QVector>




const int ROW = 4;
const int COLUMN = 4;
class Demo2048 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int score READ score)
    Q_PROPERTY(int step READ step)
    Q_PROPERTY(int bestScore READ bestScore)
    Q_PROPERTY(int topStep READ topStep)
    enum MoveDirection{
        MoveLeft=0,MoveRight,MoveDown,MoveUp
    };
    Q_ENUM(MoveDirection)
public:
    explicit Demo2048(QObject *parent = nullptr);
    Q_INVOKABLE void start();
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void reBack();
    Q_INVOKABLE void move(MoveDirection direction);
    int score();
    int step();
    int bestScore();
    int topStep();
signals:

private:
    void added(MoveDirection direction);//根据方向将数据加在一起
    void moved(MoveDirection direction);
    void initGame();

private:
    int m_score{};
    int m_step{};
    int m_bestScore{};
    int m_topStep{};
    int data[ROW][COLUMN];
    typedef   QVector<int> Panel;
    Panel m_curPanel{};
    QVector<Panel> m_steps;
    QVector<Panel> m_resteps;
    bool m_addedstatus{false};
};

#endif // DEMO2048_H
