#include "demo2048.h"
#include <time.h>
#include <QFile>
#include <QDataStream>

Demo2048::Demo2048(QObject *parent) : QObject(parent)
{
    srand(time(0));
    QFile file("score.dat");
    bool result = file.open(QIODevice::ReadOnly);
    if(result)
    {
        QDataStream steam(&file);
        steam >> m_bestScore >> m_topStep;
        file.close();
    }
    else
    {
        m_topStep = 0;
        m_bestScore = 0;
    }
}

void Demo2048::start()
{
    //初始化当前数据
    initGame();
}

void Demo2048::move(Demo2048::MoveDirection direction)
{
    added(direction);
}

int Demo2048::score()
{
    return m_score;
}

int Demo2048::step()
{
    return m_step;
}

int Demo2048::bestScore()
{
    return m_bestScore;
}

int Demo2048::topStep()
{
    return m_topStep;
}

void Demo2048::added(Demo2048::MoveDirection direction)
{
    if(direction == MoveLeft)
    {
        for(int i = 0;i < ROW; i++)
        {
            int preIndex = i*COLUMN;
            int nextIndex = preIndex +1;
            while(nextIndex >= (i+1)*COLUMN) {
                if(m_curPanel[preIndex] == 0)
                {
                    preIndex ++;
                    nextIndex = preIndex + 1;
                    continue;
                }
                if(m_curPanel[nextIndex] == 0)
                {
                    nextIndex++;
                    continue;
                }
                if(m_curPanel[preIndex] == m_curPanel[nextIndex])
                {
                    m_curPanel[nextIndex] += m_curPanel[preIndex];
                    preIndex = nextIndex;
                    nextIndex = preIndex + 1;
                }
            }
        }
    }
    if(direction == MoveRight)
    {
        for(int i = 0;i < ROW; i++)
        {
            int preIndex = (i+1)*COLUMN -1;
            int nextIndex = preIndex - 1;
            while(nextIndex < i*COLUMN) {
                if(m_curPanel[preIndex] == 0)
                {
                    preIndex --;
                    nextIndex = preIndex - 1;
                    continue;
                }
                if(m_curPanel[nextIndex] == 0)
                {
                    nextIndex--;
                    continue;
                }
                if(m_curPanel[preIndex] == m_curPanel[nextIndex])
                {
                    m_curPanel[nextIndex] += m_curPanel[preIndex];
                    preIndex = nextIndex;
                    nextIndex = preIndex - 1;
                }
            }
        }
    }
    if(direction == MoveUp)
    {
        for(int i = 0;i < COLUMN; i++)
        {
            int preIndex = (i+1)*ROW + 4;
            int nextIndex = preIndex - 1;
            while(nextIndex < i*COLUMN) {
                if(m_curPanel[preIndex] == 0)
                {
                    preIndex --;
                    nextIndex = preIndex - 1;
                    continue;
                }
                if(m_curPanel[nextIndex] == 0)
                {
                    nextIndex--;
                    continue;
                }
                if(m_curPanel[preIndex] == m_curPanel[nextIndex])
                {
                    m_curPanel[nextIndex] += m_curPanel[preIndex];
                    preIndex = nextIndex;
                    nextIndex = preIndex - 1;
                }
            }
        }
    }
}

void Demo2048::moved(Demo2048::MoveDirection direction)
{
    if(direction == MoveUp)
    {
        for(int i = 0; i < ROW; i++)
        {
            QVector<int> temp;
            for(int j = 0; j < COLUMN; j++)
            {
                int val = data[i][j];
                if( val != 0)
                {
                    temp.append(val);
                }
            }
            for(int j = 0; j < COLUMN; j++)
            {
                if(j < temp.size())
                {
                    data[i][j] = temp[j];
                }
                data[i][j] = 0;
            }
        }
    }
    if(direction == MoveDown)
    {
        for(int i = 0; i < ROW; i++)
        {
            QVector<int> temp;
            for(int j = 0; j < COLUMN; j++)
            {
                int val = data[i][COLUMN-j-1];
                if( val != 0)
                {
                    temp.append(val);
                }
            }
            for(int j = COLUMN -1; j >= 0; j++)
            {
                if(temp.size() > 0)
                {
                    data[i][j] = temp.last();
                    temp.pop_back();
                }
                data[i][j] = 0;
            }
        }
    }
}

void Demo2048::initGame()
{
    m_curPanel.clear();
    m_steps.clear();
    m_resteps.clear();
    m_score = 0;
    m_step = 0;
    int firstNum = rand()%16;
    int secondNum = rand()%16;
    while(firstNum == secondNum)
    {
        secondNum = rand()%16;
    }
    m_curPanel.resize(16);
    m_curPanel.fill(0,16);
    m_curPanel[firstNum] = 2;
    m_curPanel[secondNum] = 2;
}
