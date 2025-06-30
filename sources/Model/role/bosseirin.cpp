#include "bosseirin.h"
#include "../../common/config.h"
#include <cmath>
#include <QDebug>

BossEirin::BossEirin() : Role(BOSS_EIRIN)
{
    // Boss��Ϊ���
	srand(time(NULL)); // ��ʼ�����������
    m_currentPattern = 1;
    m_patternTimer = 0;
    m_spiralAngle = 0;
    m_SpeedX = 3; // Boss�ƶ��ٶ�
    m_SpeedY = 0; // Boss��ʼ����ֱ�ƶ�
    m_pauseTimer = 0; // ͣ����ʱ��
    m_moveCounter = 0; // �ƶ���������
	m_targetX = rand() % (GAME_WIDTH - m_Role.width()); // ���Ŀ��Xλ��
	m_targetY = 150 + rand() % 100; // ���Ŀ��Yλ�ã�150-250���أ�
	m_moveLimit = rand() % 3 + 1; // ����ƶ��������ƣ�1-3�Σ�
}

void BossEirin::shoot()
{
    // ���ݵ�ǰģʽ���
    switch (m_currentPattern) {
    case 1:
        pattern1();
        break;
    case 2:
        pattern2();
        break;
    case 3:
        pattern3();
        break;
    default:
        pattern1(); // Ĭ��ʹ��ģʽ1
        break;
    }

    // ����ģʽ��ʱ��
    m_patternTimer++;
    if (m_patternTimer > 400) { // ÿ400֡�л�ģʽ
        m_patternTimer = 0;
        m_currentPattern = (m_currentPattern % 3) + 1;
    }
}

void BossEirin::updatePosition()
{
    srand(time(NULL));
    // Partten1 Boss�������ƶ�������ÿ��һ��ʱ��ͣ��һ��
    if (m_currentPattern == 1) {
        // ͣ����
        if (m_pauseTimer > 0) {
            m_pauseTimer--;
            return;
        }
        // �ƶ���
        if (m_X <= 0) {
            m_SpeedX = abs(m_SpeedX);
        }
        else if (m_X >= GAME_WIDTH - m_Role.width()) {
            m_SpeedX = -abs(m_SpeedX);
            m_moveCounter++;
        }
		// ÿ�ƶ����κ�ͣ��һ��ʱ��
        if(m_moveCounter >= m_moveLimit) {
            m_moveCounter = 0;
            m_pauseTimer = rand() % 60 + 30; // ͣ��30-90֡
			m_moveLimit = rand() % 3 + 1; // ����´��ƶ��������ƣ�1-3�Σ�
		}
        m_X += m_Speed;
        m_Rect.moveTo(m_X, m_Y);

        // ������ײ��λ��
        m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
    }
    else if (m_currentPattern >= 2) {
        // Partten23 Boss��������ƶ���ˮƽ����ȣ�����С���ȣ�ÿ�ƶ����κ���һ��λ��ͣ��һ��ʱ�䣩
        // ͣ����
        if (m_pauseTimer > 0) {
            m_pauseTimer--;
            return;
        }
        // �ƶ���
        m_moveLimit = rand() % 3 + 2; // ����ƶ��������ƣ�1-3�Σ�
        if (abs(m_X - m_targetX) > 5 || abs(m_Y - m_targetY) > 5) {
            // ��Ŀ��λ���ƶ�
            if (m_X < m_targetX) m_X += abs(m_SpeedX);
            else if (m_X > m_targetX) m_X -= abs(m_SpeedX);

            if (m_Y < m_targetY) m_Y += abs(m_SpeedY);
            else if (m_Y > m_targetY) m_Y -= abs(m_SpeedY);
        }
        else {
            // ����Ŀ��λ�ã��ƶ���������
            m_moveCounter++;

            // ÿ�ƶ����κ�ͣ��
            if (m_moveCounter >= m_moveLimit) {
                m_moveCounter = 0;
                m_pauseTimer = rand() % 60 + 30; // ͣ��30-90֡
            }
            else {
                // �����µ����Ŀ��λ��
                m_targetX = rand() % (GAME_WIDTH - m_Role.width());
                m_targetY = 150 + rand() % 100; // ����С��Χ�ƶ�
            }
        }
        // ���½�ɫ����λ��
        m_Rect.moveTo(m_X, m_Y);
        // ������ײ��λ��
        m_collisionRect.moveTo(
            m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2
        );
	}
}

void BossEirin::pattern1()
{
    // Բ�ε�Ļ
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_SHOOT_INTERVAL1) {
        return;
    }

    m_shootRecorderEnemy = 0;

    int bulletsToShoot = 12; // 12����Ļ
    double angleStep = 2 * M_PI / bulletsToShoot;

    for (int i = 0; i < bulletsToShoot; i++) {
        for (int j = 0; j < BULLET_NUM_ENEMY; j++) {
            if (m_firstBullets[j].m_Free) {
                //m_firstBullets[j].reset();
                m_firstBullets[j].m_Free = false;
                m_firstBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[j].m_Rect.width() * 0.5;
                m_firstBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[j].m_Rect.height() * 0.5;

                double angle = angleStep * i;
                m_firstBullets[j].m_SpeedX = cos(angle) * BOSS_BULLET_SPEED * 0.5;
                m_firstBullets[j].m_SpeedY = sin(angle) * BOSS_BULLET_SPEED * 0.5;
                //m_firstBullets[j].m_Direction = CUSTOM;
                break;
            }
        }
    }
}

void BossEirin::pattern2()
{
    // ������Ļ
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_SHOOT_INTERVAL2) {
        return;
    }

    m_shootRecorderEnemy = 0;

    for (int i = 0; i < BULLET_NUM_ENEMY; i++) {
        if (m_firstBullets[i].m_Free && i + 1 < BULLET_NUM && m_firstBullets[i + 1].m_Free) {
            //m_firstBullets[i].reset();
            m_firstBullets[i].m_Free = false;
            m_firstBullets[i].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[i].m_Rect.width() * 0.5;
            m_firstBullets[i].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[i].m_Rect.height() * 0.5;

            double angle = m_spiralAngle;
            m_firstBullets[i].m_SpeedX = cos(angle) * BOSS_BULLET_SPEED * 0.6;
            m_firstBullets[i].m_SpeedY = sin(angle) * BOSS_BULLET_SPEED * 0.6;

            ///m_firstBullets[i + 1].reset();
            m_firstBullets[i + 1].m_Free = false;
            m_firstBullets[i + 1].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[i + 1].m_Rect.width() * 0.5;
            m_firstBullets[i + 1].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[i + 1].m_Rect.height() * 0.5;

            m_firstBullets[i + 1].m_SpeedX = cos(angle + M_PI) * BOSS_BULLET_SPEED * 0.6;
            m_firstBullets[i + 1].m_SpeedY = sin(angle + M_PI) * BOSS_BULLET_SPEED * 0.6;
            //m_firstBullets[i].m_Direction = CUSTOM;

            m_spiralAngle += 0.2;
            if (m_spiralAngle > M_PI) {
                m_spiralAngle = 0;
            }
            break;
        }
    }
}

void BossEirin::pattern3()
{
    // ��׼��ҵĵ�Ļ
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < 20) {
        return;
    }

    m_shootRecorderEnemy = 0;

    // ���㳯����ҵĽǶ�
    double deltaX = playerX - (m_X + m_Role.width() * 0.5);
    double deltaY = playerY - (m_Y + m_Role.height() * 0.5);
    double angle = atan2(deltaY, deltaX);

    // ����3�����ε�Ļ
    for (int i = -1; i <= 1; i++) {
        for (int j = 0; j < MAX_BULLETS; j++) {
            if (m_firstBullets[j].m_Free) {
                //m_firstBullets[j].reset();
                m_firstBullets[j].m_Free = false;
                m_firstBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[j].m_Rect.width() * 0.5;
                m_firstBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[j].m_Rect.height() * 0.5;

                double bulletAngle = angle + i * 0.2;
                m_firstBullets[j].m_SpeedX = cos(bulletAngle) * BOSS_BULLET_SPEED * 0.7;
                m_firstBullets[j].m_SpeedY = sin(bulletAngle) * BOSS_BULLET_SPEED * 0.7;
                //m_firstBullets[j].m_Direction = CUSTOM;
				m_firstBullets[j].isTracking = true; // ����Ϊ׷��ģʽ
                break;
            }
        }
    }
}
