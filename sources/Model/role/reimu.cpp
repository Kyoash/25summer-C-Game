#include "reimu.h"
#include "../../common/config.h"
#include <cmath>

Reimu::Reimu() : Role(PLAYER_REIMU)
{
    // ������������
    m_power = 0;
    m_graze = 0;
    m_Speed = NORMAL_PLAYER_SPEED; // ����ƶ��ٶ�
}

void Reimu::shoot()
{
    // ��¼���ʱ����
    m_shootRecorderPlayer++;

    // ���ݻ����ȼ��������ģʽ
    if (m_shootRecorderPlayer < PLAYER_SHOOT_INTERVAL) {
        return;
    }

    m_shootRecorderPlayer = 0;

    // �����ӵ�
    bool bulletFired = false;
    for (int i = 0; i < BULLET_NUM; i++) {
        if (m_firstBullets[i].m_Free) {
            if (m_power < 2) {
                // �ͻ��� - ����
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
                // �л��� - ˫��
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
                // �߻��� - ����
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

    // ���δ�����ӵ�������Ѱ�ҿ����ӵ���
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
    // ���λ���ɼ��̿��ƣ�����ֻ�������ײ��
}

void Reimu::useSpellCard()
{
    if (m_spell > 0) {
        m_spell--;
        // ����Ч������ʱ���޵кͻ��Ƶľ޴���򣨿��������Ļ��
		m_unmatched = true;
    }
}
