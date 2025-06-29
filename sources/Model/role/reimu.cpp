#include "reimu.h"
#include "../../common/config.h"
#include <cmath>

Reimu::Reimu() : Role(PLAYER_REIMU)
{
    // 灵梦特有属性
    m_power = 0;
    m_graze = 0;
    m_Speed = NORMAL_PLAYER_SPEED; // 玩家移动速度
}

void Reimu::shoot()
{
    // 记录射击时间间隔
    m_shootRecorderPlayer++;

    // 根据火力等级决定射击模式
    if (m_shootRecorderPlayer < PLAYER_SHOOT_INTERVAL) {
        return;
    }

    m_shootRecorderPlayer = 0;

    // 发射子弹
    bool bulletFired = false;
    for (int i = 0; i < BULLET_NUM; i++) {
        if (m_firstBullets[i].m_Free) {
            if (m_power < 2) {
                // 低火力 - 单发
                m_firstBullets[i].m_Free = false;
                m_firstBullets[i].m_X = m_X + m_Role.width() * 0.5 - PLAYER_BULLET_WIDTH * 0.5;
                m_firstBullets[i].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                m_firstBullets[i].m_SpeedY = PLAYER_BULLET_SPEED;
				m_firstBullets[i].m_SpeedX = 0;
                //m_firstBullets[i].m_Direction = UP;
                bulletFired = true;
                break;
            }
            else if (m_power < 4) {
                // 中火力 - 双发
                if (i + 1 < BULLET_NUM && m_firstBullets[i + 1].m_Free) {
                    m_firstBullets[i].m_Free = false;
                    m_firstBullets[i].m_X = m_X + m_Role.width() * 0.3 - PLAYER_BULLET_WIDTH * 0.5;
                    m_firstBullets[i].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                    m_firstBullets[i].m_SpeedY = PLAYER_BULLET_SPEED;
                    m_firstBullets[i].m_SpeedX = 0;
                    //m_firstBullets[i].m_Direction = UP;

                    m_firstBullets[i + 1].m_Free = false;
                    m_firstBullets[i + 1].m_X = m_X + m_Role.width() * 0.7 - PLAYER_BULLET_WIDTH * 0.5;
                    m_firstBullets[i + 1].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                    m_firstBullets[i + 1].m_SpeedY = PLAYER_BULLET_SPEED;
                    m_firstBullets[i + 1].m_SpeedX = 0;
                    //m_firstBullets[i + 1].m_Direction = UP;
                    bulletFired = true;
                    break;
                }
            }
            else {
                // 高火力 - 三发
                if (i + 2 < BULLET_NUM && m_firstBullets[i + 1].m_Free && m_firstBullets[i + 2].m_Free) {
                    m_firstBullets[i].m_Free = false;
                    m_firstBullets[i].m_X = m_X + m_Role.width() * 0.2 - PLAYER_BULLET_WIDTH * 0.5;
                    m_firstBullets[i].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                    m_firstBullets[i].m_SpeedY = PLAYER_BULLET_SPEED;
                    m_firstBullets[i].m_SpeedX = 0;

                    m_firstBullets[i + 1].m_Free = false;
                    m_firstBullets[i + 1].m_X = m_X + m_Role.width() * 0.5 - PLAYER_BULLET_WIDTH * 0.5;
                    m_firstBullets[i + 1].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                    m_firstBullets[i + 1].m_SpeedY = PLAYER_BULLET_SPEED;
                    m_firstBullets[i + 1].m_SpeedX = 0;

                    m_firstBullets[i + 2].m_Free = false;
                    m_firstBullets[i + 2].m_X = m_X + m_Role.width() * 0.8 - PLAYER_BULLET_WIDTH * 0.5;
                    m_firstBullets[i + 2].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                    m_firstBullets[i + 2].m_SpeedY = PLAYER_BULLET_SPEED;
                    m_firstBullets[i + 2].m_SpeedX = 0;
                    bulletFired = true;
                    break;
                }
            }
        }
    }

    // 如果未发射子弹，尝试寻找空闲子弹槽
    if (!bulletFired) {
        for (int i = 0; i < BULLET_NUM; i++) {
            if (m_firstBullets[i].m_Free) {
                m_firstBullets[i].m_Free = false;
                m_firstBullets[i].m_X = m_X + m_Role.width() * 0.5 - PLAYER_BULLET_WIDTH * 0.5;
                m_firstBullets[i].m_Y = m_Y - PLAYER_BULLET_HEIGHT;
                m_firstBullets[i].m_SpeedY = PLAYER_BULLET_SPEED;
                m_firstBullets[i].m_SpeedX = 0;
                //m_firstBullets[i].m_Direction = UP;
                break;
            }
        }
    }
}

void Reimu::updatePosition()
{
    srand(time(NULL));
    // 玩家位置由键盘控制，这里只需更新碰撞框
}

void Reimu::useSpellCard()
{
    if (m_spell > 0) {
        m_spell--;
        // 符卡效果：短时间无敌和环绕的巨大光球（可以清除弹幕）
		m_unmatched = true;
    }
}
