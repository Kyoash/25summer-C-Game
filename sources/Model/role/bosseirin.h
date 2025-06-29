#ifndef BOSS_SEIRIN_H
#define BOSS_SEIRIN_H

#include "role.h"

class BossSeirin : public Role
{
public:
    BossSeirin();

    // 实现虚函数
    void shoot() override;
    void updatePosition() override;

    // Boss特有的行为
    void setPattern(int pattern) { m_currentPattern = pattern; }
    void SetPlayerPosition(int x, int y) {
        playerX = x;
        playerY = y;
	}

private:
    // Boss移动速度
    int m_SpeedX;
    int m_SpeedY;
    // Boss行为模式
    void pattern1(); // 圆形弹幕
    void pattern2(); // 螺旋弹幕
    void pattern3(); // 瞄准弹幕

    int m_currentPattern; // 当前弹幕模式
    int m_moveCounter;        // 移动次数计数
    int m_pauseTimer;         // 停留计时器
    int m_patternTimer;   // 模式计时器
    int m_targetX, m_targetY; // 目标位置（随机移动）
    int m_moveLimit; // 移动次数限制（随机）
    double m_spiralAngle; // 螺旋弹幕角度
    
	int playerX; // 玩家X坐标，用于瞄准弹幕
    int playerY; // 玩家Y坐标，用于瞄准弹幕(需要时刻刷新)
   
};

#endif // BOSS_SEIRIN_H
