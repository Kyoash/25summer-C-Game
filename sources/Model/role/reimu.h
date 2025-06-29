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

    // 灵梦特有的能力
    void useSpellCard();

	// 获取灵梦的火力等级
    int getPower() const { return m_power; }
    // 获取灵梦的擦弹计数
    int getGraze() const { return m_graze; }
    // 设置灵梦的火力等级
    void setPower(int power) { m_power = power; }
    // 设置灵梦的擦弹计数
	void setGraze(int graze) { m_graze = graze; }

private:
    // 灵梦特有的属性
    int m_power; // 火力等级
    int m_graze; // 擦弹计数
    bool m_unmatched; // 是否无敌
};

#endif // REIMU_H