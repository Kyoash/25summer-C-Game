#ifndef REIMU_H
#define REIMU_H

#include "role.h"

class Reimu : public Role
{
public:
    Reimu();

    // 实现虚函数
    void shoot() override;
    void updatePosition() override;

    // 特殊技能函数
    void useSpellCard() override;

    // 获取当前的火力值
    int getPower() const { return m_power; }
    // 获取当前的擦弹计数
    int getGraze() const { return m_graze; }
    // 设置火力值
    void setPower(int power) { m_power = power; }
    // 设置擦弹计数
    void setGraze(int graze) { m_graze = graze; }

private:
    // 角色特有属性
    int m_power;    // 火力值
    int m_graze;    // 擦弹计数
    bool m_unmatched; // 是否处于无敌状态
};

#endif // REIMU_H