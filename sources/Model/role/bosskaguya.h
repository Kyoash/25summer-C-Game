#ifndef BOSS_KAGUYA_H
#define BOSS_KAGUYA_H

#include "role.h"
#include "../bullet/laser.h"
#include "../../common/config.h"

class BossKaguya : public Role
{
public:
    BossKaguya();

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
    void pattern1(); // 五方向旋转普通弹幕
    void pattern2(); // 垂直激光阵（出现于屏幕边缘会平行向中间移动一段距离）+每次三发追踪弹幕
    void pattern3(); // 追踪弹幕与固定弹幕组合（十方向旋转，两者组合）

    int m_currentPattern; // 当前弹幕模式
    int m_moveCounter;    // 移动次数计数
    int m_pauseTimer;     // 停留计时器
    int m_patternTimer;   // 模式计时器
    int m_targetX, m_targetY; // 目标位置（随机移动）
    int m_moveLimit;      // 移动次数限制（随机）
    double m_spiralAngle; // 螺旋弹幕角度
    
    int playerX; // 玩家X坐标，用于瞄准弹幕
    int playerY; // 玩家Y坐标，用于瞄准弹幕
    
    // 辉夜特有属性
    bool m_isLaserActive; // 激光是否激活
    int m_laserDuration;  // 激光持续时间
    int m_laserTimer;     // 激光计时器
    Laser m_laser[MAX_LASERS]; // 辉夜激光array
    bool m_lastLaserFromLeft = false; // 上一次激光是从左边还是右边发射的
};

#endif // BOSS_KAGUYA_H
