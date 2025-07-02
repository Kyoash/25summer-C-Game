#include "marisa.h"
#include "../bullet/bullet.h"
#include "../../common/config.h"
#include <cmath>

Marisa::Marisa() : Role(PLAYER_MARISA), m_alternateFire(false)
{
    // 魔理沙特有属性
    m_power = 0;
    m_graze = 0;
    m_unmatched = false;
    m_Speed = NORMAL_PLAYER_SPEED; // 玩家移动速度

}
void Marisa::shoot()
{
    // 记录射击时间间隔
    m_shootRecorderPlayer++;

    // 根据火力等级决定射击模式
    if (m_shootRecorderPlayer < PLAYER_SHOOT_INTERVAL) {
        return;
    }

    m_shootRecorderPlayer = 0;

    // 发射追踪弹
    bool bulletFired = false;
    for (int i = 0; i < BULLET_NUM; i++) {
        if(m_alternateFire == false){
            if (m_secondBullets[i].m_Free) {
                if (m_power < 2) {
                    // 低火力 - 单发追踪弹
                    m_secondBullets[i].reset();  // here is a tag1 !!!!!!
                    m_secondBullets[i].m_Free = false;
                    m_secondBullets[i].m_X = m_X + m_Role.width() * 0.5 - m_secondBullets[i].m_Rect.width() * 0.5;
                    m_secondBullets[i].m_Y = m_Y - m_secondBullets[i].m_Rect.height();
                    m_secondBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                    m_secondBullets[i].m_SpeedX = 0;
                    m_secondBullets[i].setAngleLimit(M_PI / 2);
                    m_secondBullets[i].isTracking = true;
                    bulletFired = true;
                    break;
                }
                else if (m_power < 4) {
                    // 中火力 - 双发追踪弹
                    if (i + 1 < BULLET_NUM && m_secondBullets[i + 1].m_Free) {
                        m_secondBullets[i].reset();  // here is a tag1 !!!!!!
                        m_secondBullets[i].m_Free = false;
                        m_secondBullets[i].m_X = m_X + m_Role.width() * 0.3 - m_secondBullets[i].m_Rect.width() * 0.5;
                        m_secondBullets[i].m_Y = m_Y - m_secondBullets[i].m_Rect.height();
                        m_secondBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_secondBullets[i].m_SpeedX = 0;
                        m_secondBullets[i].setAngleLimit(M_PI);
                        m_secondBullets[i].isTracking = true;

                        m_secondBullets[i + 1].reset();  // here is a tag1 !!!!!!
                        m_secondBullets[i + 1].m_Free = false;
                        m_secondBullets[i + 1].m_X = m_X + m_Role.width() * 0.7 - m_secondBullets[i + 1].m_Rect.width() * 0.5;
                        m_secondBullets[i + 1].m_Y = m_Y - m_secondBullets[i + 1].m_Rect.height();
                        m_secondBullets[i + 1].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_secondBullets[i + 1].m_SpeedX = 0;
                        m_secondBullets[i + 1].setAngleLimit(M_PI);
                        m_secondBullets[i + 1].isTracking = true;
                        bulletFired = true;
                        break;
                    }
                }
                else {
                    // 高火力 - 三发追踪弹
                    if (i + 2 < BULLET_NUM && m_secondBullets[i + 1].m_Free && m_secondBullets[i + 2].m_Free) {
                        m_secondBullets[i].reset();  // here is a tag1 !!!!!!
                        m_secondBullets[i].m_Free = false;
                        m_secondBullets[i].m_X = m_X + m_Role.width() * 0.2 - m_secondBullets[i].m_Rect.width() * 0.5;
                        m_secondBullets[i].m_Y = m_Y - m_secondBullets[i].m_Rect.height();
                        m_secondBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_secondBullets[i].m_SpeedX = 0;
                        m_secondBullets[i].setAngleLimit(M_PI * 2);
                        m_secondBullets[i].isTracking = true;

                        m_secondBullets[i + 1].reset();  // here is a tag1 !!!!!!
                        m_secondBullets[i + 1].m_Free = false;
                        m_secondBullets[i + 1].m_X = m_X + m_Role.width() * 0.5 - m_secondBullets[i + 1].m_Rect.width() * 0.5;
                        m_secondBullets[i + 1].m_Y = m_Y - m_secondBullets[i + 1].m_Rect.height();
                        m_secondBullets[i + 1].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_secondBullets[i + 1].m_SpeedX = 0;
                        m_secondBullets[i + 1].setAngleLimit(M_PI * 2);
                        m_secondBullets[i + 1].isTracking = true;

                        m_secondBullets[i + 2].reset();  // here is a tag1 !!!!!!
                        m_secondBullets[i + 2].m_Free = false;
                        m_secondBullets[i + 2].m_X = m_X + m_Role.width() * 0.8 - m_secondBullets[i + 2].m_Rect.width() * 0.5;
                        m_secondBullets[i + 2].m_Y = m_Y - m_secondBullets[i + 2].m_Rect.height();
                        m_secondBullets[i + 2].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_secondBullets[i + 2].m_SpeedX = 0;
                        m_secondBullets[i + 2].setAngleLimit(M_PI * 2);
                        m_secondBullets[i + 2].isTracking = true;
                        bulletFired = true;
                        break;
                    }
                }
            }
        }else{
            if (m_firstBullets[i].m_Free) {
                if (m_power < 2) {
                    // 低火力 - 单发普通弹
                    m_firstBullets[i].m_Free = false;
                    m_firstBullets[i].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[i].m_Rect.width() * 0.5;
                    m_firstBullets[i].m_Y = m_Y - m_firstBullets[i].m_Rect.height();
                    m_firstBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                    m_firstBullets[i].m_SpeedX = 0;
                    bulletFired = true;
                    break;
                }
                else if (m_power < 4) {
                    // 中火力 - 双发普通弹
                    if (i + 1 < BULLET_NUM && m_firstBullets[i + 1].m_Free) {
                        m_firstBullets[i].m_Free = false;
                        m_firstBullets[i].m_X = m_X + m_Role.width() * 0.3 - m_firstBullets[i].m_Rect.width() * 0.5;
                        m_firstBullets[i].m_Y = m_Y - m_firstBullets[i].m_Rect.height();
                        m_firstBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_firstBullets[i].m_SpeedX = 0;

                        m_firstBullets[i + 1].m_Free = false;
                        m_firstBullets[i + 1].m_X = m_X + m_Role.width() * 0.7 - m_firstBullets[i + 1].m_Rect.width() * 0.5;
                        m_firstBullets[i + 1].m_Y = m_Y - m_firstBullets[i + 1].m_Rect.height();
                        m_firstBullets[i + 1].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_firstBullets[i + 1].m_SpeedX = 0;
                        bulletFired = true;
                        break;
                    }
                }
                else {
                    // 高火力 - 三发普通弹
                    if (i + 2 < BULLET_NUM && m_firstBullets[i + 1].m_Free && m_firstBullets[i + 2].m_Free) {
                        m_firstBullets[i].m_Free = false;
                        m_firstBullets[i].m_X = m_X + m_Role.width() * 0.2 - m_firstBullets[i].m_Rect.width() * 0.5;
                        m_firstBullets[i].m_Y = m_Y - m_firstBullets[i].m_Rect.height();
                        m_firstBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_firstBullets[i].m_SpeedX = 0;

                        m_firstBullets[i + 1].m_Free = false;
                        m_firstBullets[i + 1].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[i + 1].m_Rect.width() * 0.5;
                        m_firstBullets[i + 1].m_Y = m_Y - m_firstBullets[i + 1].m_Rect.height();
                        m_firstBullets[i + 1].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_firstBullets[i + 1].m_SpeedX = 0;

                        m_firstBullets[i + 2].m_Free = false;
                        m_firstBullets[i + 2].m_X = m_X + m_Role.width() * 0.8 - m_firstBullets[i + 2].m_Rect.width() * 0.5;
                        m_firstBullets[i + 2].m_Y = m_Y - m_firstBullets[i + 2].m_Rect.height();
                        m_firstBullets[i + 2].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                        m_firstBullets[i + 2].m_SpeedX = 0;
                        bulletFired = true;
                        break;
                    }
                }
            }
        }
    }

    // 如果未发射子弹，尝试寻找空闲子弹槽
    if (!bulletFired) {
        for (int i = 0; i < BULLET_NUM; i++) {
            if (m_secondBullets[i].m_Free) {
                m_secondBullets[i].m_Free = false;
                m_secondBullets[i].m_X = m_X + m_Role.width() * 0.5 - m_secondBullets[i].m_Rect.width() * 0.5;
                m_secondBullets[i].m_Y = m_Y - m_secondBullets[i].m_Rect.height();
                m_secondBullets[i].m_SpeedY = PLAYER_MARISA_BULLET_SPEED;
                m_secondBullets[i].m_SpeedX = 0;
                m_secondBullets[i].setAngleLimit(M_PI / 4);
                break;
            }
        }
    }else{
        // 切换射击模式
        m_alternateFire = !m_alternateFire;
    }
}

void Marisa::updatePosition()
{
    srand(time(NULL));
}

void Marisa::useSpellCard()
{
    if (m_spell > 0) {
        m_spell--;
        // 魔理沙符卡效果：发射强力追踪弹
        m_unmatched = true;

    }
}
