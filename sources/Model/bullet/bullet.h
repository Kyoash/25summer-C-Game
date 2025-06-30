// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QPixmap>
#include <QRect>
#include "../../Common/config.h"

class Bullet
{
public:
    Bullet(RoleType type = PLAYER_REIMU, BulletType btype = DEFAULT_BULLET);

    // 更新子弹坐标
    void updatePosition();

    // 获取子弹类型
    BulletType getType() const { return m_type; }

    void setAngleLimit(double limit) { angleLimit = limit; }

public:
    // 子弹类型
    BulletType m_type;
    // 子弹所属的角色类型
    RoleType role_type;

    // 子弹资源对象
    QPixmap m_Bullet;

    // 子弹坐标
    int m_X;
    int m_Y;

    // 子弹移动速度
    int m_Speed;

    // 子弹是否闲置
    bool m_Free;

    // 子弹的矩形边框
    QRect m_Rect;

    // 碰撞体积
    QRect m_collisionRect;

    // 子弹速度属性
    int m_SpeedX;
    int m_SpeedY;

    // 是否追踪
    bool isTracking;
    // 目标位置
    int targetX;
    int targetY;
    // 追踪角度上限(子弹在追踪过程中最多偏转多少)
    double angleLimit = M_PI / 8;
    // 初速度得到初角度
    int m_InitSpeedX;
    int m_InitSpeedY;
    // 当前偏转角度
    double angleSwift;

};

#endif // BULLET_H

