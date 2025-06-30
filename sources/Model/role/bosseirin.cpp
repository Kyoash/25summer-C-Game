#include "bosseirin.h"
#include "../../common/config.h"
#include <cmath>
#include <QDebug>

BossEirin::BossEirin() : Role(BOSS_EIRIN)
{
    // Boss行为相关
	srand(time(NULL)); // 初始化随机数种子
    m_currentPattern = 1;
    m_patternTimer = 0;
    m_spiralAngle = 0;
    m_SpeedX = 3; // Boss移动速度
    m_SpeedY = 0; // Boss初始不垂直移动
    m_pauseTimer = 0; // 停留计时器
    m_moveCounter = 0; // 移动次数计数
	m_targetX = rand() % (GAME_WIDTH - m_Role.width()); // 随机目标X位置
	m_targetY = 150 + rand() % 100; // 随机目标Y位置（150-250像素）
	m_moveLimit = rand() % 3 + 1; // 随机移动次数限制（1-3次）
}

void BossEirin::shoot()
{
    // 根据当前模式射击
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
        pattern1(); // 默认使用模式1
        break;
    }

    // 更新模式计时器
    m_patternTimer++;
    if (m_patternTimer > 400) { // 每400帧切换模式
        m_patternTimer = 0;
        m_currentPattern = (m_currentPattern % 3) + 1;
    }
}

void BossEirin::updatePosition()
{
    srand(time(NULL));
    // Partten1 Boss简单左右移动，并且每隔一段时间停留一会
    if (m_currentPattern == 1) {
        // 停留期
        if (m_pauseTimer > 0) {
            m_pauseTimer--;
            return;
        }
        // 移动期
        if (m_X <= 0) {
            m_SpeedX = abs(m_SpeedX);
        }
        else if (m_X >= GAME_WIDTH - m_Role.width()) {
            m_SpeedX = -abs(m_SpeedX);
            m_moveCounter++;
        }
		// 每移动几次后停留一段时间
        if(m_moveCounter >= m_moveLimit) {
            m_moveCounter = 0;
            m_pauseTimer = rand() % 60 + 30; // 停留30-90帧
			m_moveLimit = rand() % 3 + 1; // 随机下次移动次数限制（1-3次）
		}
        m_X += m_Speed;
        m_Rect.moveTo(m_X, m_Y);

        // 更新碰撞框位置
        m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
    }
    else if (m_currentPattern >= 2) {
        // Partten23 Boss随机方向移动（水平大幅度，纵向小幅度，每移动三次后在一个位置停留一段时间）
        // 停留期
        if (m_pauseTimer > 0) {
            m_pauseTimer--;
            return;
        }
        // 移动期
        m_moveLimit = rand() % 3 + 2; // 随机移动次数限制（1-3次）
        if (abs(m_X - m_targetX) > 5 || abs(m_Y - m_targetY) > 5) {
            // 向目标位置移动
            if (m_X < m_targetX) m_X += abs(m_SpeedX);
            else if (m_X > m_targetX) m_X -= abs(m_SpeedX);

            if (m_Y < m_targetY) m_Y += abs(m_SpeedY);
            else if (m_Y > m_targetY) m_Y -= abs(m_SpeedY);
        }
        else {
            // 到达目标位置，移动次数增加
            m_moveCounter++;

            // 每移动三次后停留
            if (m_moveCounter >= m_moveLimit) {
                m_moveCounter = 0;
                m_pauseTimer = rand() % 60 + 30; // 停留30-90帧
            }
            else {
                // 设置新的随机目标位置
                m_targetX = rand() % (GAME_WIDTH - m_Role.width());
                m_targetY = 150 + rand() % 100; // 纵向小范围移动
            }
        }
        // 更新角色矩形位置
        m_Rect.moveTo(m_X, m_Y);
        // 更新碰撞框位置
        m_collisionRect.moveTo(
            m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2
        );
	}
}

void BossEirin::pattern1()
{
    // 圆形弹幕
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_SHOOT_INTERVAL1) {
        return;
    }

    m_shootRecorderEnemy = 0;

    int bulletsToShoot = 12; // 12方向弹幕
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
    // 螺旋弹幕
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
    // 瞄准玩家的弹幕
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < 20) {
        return;
    }

    m_shootRecorderEnemy = 0;

    // 计算朝向玩家的角度
    double deltaX = playerX - (m_X + m_Role.width() * 0.5);
    double deltaY = playerY - (m_Y + m_Role.height() * 0.5);
    double angle = atan2(deltaY, deltaX);

    // 发射3发扇形弹幕
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
				m_firstBullets[j].isTracking = true; // 设置为追踪模式
                break;
            }
        }
    }
}
