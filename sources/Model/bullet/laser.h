// laser.h
#ifndef LASER_H
#define LASER_H

#include <QPixmap>
#include <QPolygonF>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <QTransform>
#include "../../common/config.h"
#include "../role/role.h"

class Laser
{
public:
    Laser(RoleType type = PLAYER_REIMU, LaserType laserType = VERTICAL_LASER);

    // 激光坐标更新
    void updatePosition();

    // set
    void setBoss(Role* boss) { targetBoss = boss; }
    void setSpeedX(double speedX) { m_SpeedX = speedX; }
    void setSpeedY(double speedY) { m_SpeedY = speedY; }
    void setAngle(double angle) { m_angle = angle; }
    void setAngleSpeed(double angleSpeed) { m_angleSpeed = angleSpeed; }
    void setMaxMoveDistance(double maxMoveDistance) { m_maxMoveDistance = maxMoveDistance; }
    void setMaxMoveAngle(double maxMoveAngle) { m_maxMoveAngle = maxMoveAngle; }

    // get
    void getPosition(int& x, int& y) const { x = m_X; y = m_Y; }
    double getAngle() const { return m_angle; }
    double getSpeedX() const { return m_SpeedX; }
    double getSpeedY() const { return m_SpeedY; }
    double getAngleSpeed() const { return m_angleSpeed; }
    bool isFree() const { return m_Free; }
    double getMoveDistance() const { return m_moveDistance; }
    double getMoveAngle() const { return m_moveAngle; }

    // 设置空闲
    void reset();

    // 获取碰撞体积
    QRect getCollisionRect() const { return m_collisionRect; }
    QPolygonF getCollisionPolygon() const { return m_collisionPolygon; }
public:
    RoleType role_type;
    LaserType laser_type;
    QPixmap m_Laser;

    int m_X, m_Y;
    QRect m_Rect;
    QRect m_collisionRect;
    QPolygonF m_Polygon;
    QPolygonF m_collisionPolygon;  // 替代 m_collisionRect 的斜向碰撞框


    bool m_Free;

    // 移动逻辑
    double m_angle;      // 当前角度
    double m_SpeedX;
    double m_SpeedY;

    double m_angleSpeed; // 每帧角度变化

    Role* targetBoss;    // 旋转中心
    // 累计移动距离/角度
    double m_moveDistance;
    double m_moveAngle;
    // 移动距离/角度上限
    double m_maxMoveDistance;
    double m_maxMoveAngle;
};

#endif // LASER_H
