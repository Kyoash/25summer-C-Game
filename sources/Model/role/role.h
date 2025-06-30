#ifndef ROLE_H
#define ROLE_H

#include <QPixmap>
#include <QRect>
#include <vector>
#include "../../common/config.h"
#include "../bullet/bullet.h"

class Role
{
public:
    Role(RoleType type = PLAYER_REIMU);

    // 发射子弹
    virtual void shoot() {};
    // 设置位置
    void setPosition(int x, int y);
    // 更新坐标
    virtual void updatePosition() {};
    // 重置状态
    void reset();
    void resetWithoutBullets();
    // 获取role类型
    RoleType getType() const { return m_type; }
    // 使用技能
    virtual void useSpellCard() {};

public:
	// 获取角色类型
    RoleType m_type;

    // Role资源对象
    QPixmap m_Role;

    // 坐标
    int m_X;
    int m_Y;

	// 矩形边框，用于碰撞检测
    QRect m_Rect;

    // 弹匣
    Bullet m_firstBullets[MAX_BULLETS]; // 使用最大数量
    // 追踪弹夹
    Bullet m_secondBullets[MAX_BULLETS]; 

    // 生命值
    int m_life;
    int m_maxLife;
    // spell 技能槽
	int m_spell; 
	int m_maxSpell;

    // 碰撞体积
    QRect m_collisionRect;

	// 移动速度
    int m_Speed;

    // 玩家专用属性
    int m_shootRecorderPlayer; // 发射间隔记录

    // 敌机专用属性
    int m_shootRecorderEnemy;

    // 添加状态标志
    bool m_Free;  // 是否空闲（未被使用）
};

#endif // ROLE_H
