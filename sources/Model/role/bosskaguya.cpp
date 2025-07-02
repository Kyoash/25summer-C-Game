#include "bosskaguya.h"
#include <cmath>
#include <ctime>

BossKaguya::BossKaguya() : Role(BOSS_KAGUYA)
{
    // Boss行为相关
    srand(time(NULL)); // 初始化随机数种子
    m_currentPattern = 1;
    m_patternTimer = 0;
    m_spiralAngle = 0;
    m_SpeedX = rand() % 12 + -6; // 随机速度
    m_SpeedY = rand() % 6 + -3; // 随机速度
    m_pauseTimer = 0; // 停留计时器
    m_moveCounter = 0; // 移动次数计数
    m_targetX = rand() % (GAME_WIDTH - 2 * m_collisionRect.width()) + 2* m_collisionRect.width() / 2; // 随机目标X位置
    m_targetY = 20 + m_collisionRect.height() + rand() % 100; // 随机目标Y位置（150-250像素）
    m_moveLimit = rand() % 3 + 1; // 随机移动次数限制（1-3次）

    // 辉夜特有属性
    m_isLaserActive = false;
    m_laserDuration = 0;
    m_laserTimer = 0;

    // 初始化激光数组
    for (int i = 0; i < MAX_LASERS; i++) {
        m_laser[i] = new Laser(BOSS_KAGUYA, VERTICAL_LASER);
        m_laser[i]->setMaxMoveDistance(GAME_WIDTH * 3 / 5); // 激光移动距离限制为屏幕宽度的3/5
    }

}

void BossKaguya::shoot()
{
    // 根据当前模式射击
    switch (m_currentPattern) {
    case 1:
        pattern1(); // 五方向旋转普通弹幕
        break;
    case 2:
        pattern2(); // 垂直激光阵 + 三发追踪弹幕
        break;
    case 3:
        pattern3(); // 追踪弹幕与固定弹幕组合
        break;
    default:
        pattern1(); // 默认使用模式1
        break;
    }

    // 更新模式计时器
    m_patternTimer++;
    if (m_patternTimer > 600) { // 每600帧切换模式
        m_patternTimer = 0;
        m_currentPattern = (m_currentPattern % 3) + 1;

        // 切换模式时激活激光
        if (m_currentPattern == 2) {
            m_isLaserActive = true;
            m_laserDuration = 200; // 激光持续200帧
            m_laserTimer = 0;
        }
    }

    // 更新激光计时器
    if (m_isLaserActive) {
        m_laserTimer++;
        if (m_laserTimer > m_laserDuration) {
            m_isLaserActive = false;
        }
    }
}

void BossKaguya::updatePosition()
{
    // 辉夜移动模式更复杂，不受模式限制
    // 停留期
    if (m_pauseTimer > 0) {
        m_pauseTimer--;
        return;
    }

    // 移动期
    //m_moveLimit = rand() % 3 + 1; // 随机移动次数限制（1-4次）
    if (abs(m_X - m_targetX) > 20 || abs(m_Y - m_targetY) > 20) {
        // 向目标位置移动
        if (m_X < m_targetX) m_X += abs(m_SpeedX);
        else if (m_X > m_targetX) m_X -= abs(m_SpeedX);

        if (m_Y < m_targetY) m_Y += abs(m_SpeedY);
        else if (m_Y > m_targetY) m_Y -= abs(m_SpeedY);
    } else {
        // 到达目标位置，移动次数增加
        m_moveCounter++;

        // 每移动几次后停留
        if (m_moveCounter >= m_moveLimit) {
            m_moveCounter = 0;
            m_pauseTimer = rand() % 100 + 100; // 停留100-200帧（比永琳更长）
            m_moveLimit = rand() % 3 + 1;
        } else {
            // 设置新的随机目标位置
            m_SpeedX = rand() % 10 + 5; // 随机速度
            m_SpeedY = rand() % 3 + 3; // 随机速度
            m_targetX = rand() % (GAME_WIDTH - 2 * m_collisionRect.width()) + 2* m_collisionRect.width() / 2; // 横向范围移动
            m_targetY = 20 + m_collisionRect.height() + rand() % 100; // 纵向范围更大（150-300像素）
        }
    }

    // 更新角色矩形位置
    m_Rect.moveTo(m_X, m_Y);
    // 更新碰撞框位置
    m_collisionRect.moveTo(
        m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
        m_Y + (m_Rect.height() - m_collisionRect.height()) / 2
    );

    // 更新激光位置
    for (int i = 0; i < MAX_LASERS; i++) {
        if (!m_laser[i]->isFree()) {
            m_laser[i]->updatePosition();
        }
    }
}

void BossKaguya::pattern1()
{
    // 五方向旋转普通弹幕
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_KAGUYA_SHOOT_INTERVAL1) {
        return;
    }

    m_shootRecorderEnemy = 0;

    int bulletsToShoot = 5; // 五方向
    double angleStep = 2 * M_PI / bulletsToShoot;

    for (int i = 0; i < bulletsToShoot; i++) {
        for (int j = 0; j < BULLET_NUM_ENEMY; j++) {
            if (m_firstBullets[j].m_Free) {
                m_firstBullets[j].m_Free = false;
                m_firstBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[j].m_Rect.width() * 0.5;
                m_firstBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[j].m_Rect.height() * 0.5;

                double angle = angleStep * i + m_spiralAngle;
                m_firstBullets[j].m_SpeedX = cos(angle) * BOSS_BULLET_SPEED * 0.5;
                m_firstBullets[j].m_SpeedY = sin(angle) * BOSS_BULLET_SPEED * 0.5;

                // 更新螺旋角度
                m_spiralAngle += 0.15;
                if (m_spiralAngle > 2 * M_PI) {
                    m_spiralAngle = 0;
                }
                break;
            }
        }
    }
}

void BossKaguya::pattern2()
{
    // 垂直激光阵 + 三发追踪弹幕

    // 1. 垂直激光阵（在屏幕边缘向中间移动）
    if (m_isLaserActive) {
        m_shootRecorderEnemy2++;
        if (m_shootRecorderEnemy2 % 80 == 0) { // 每80帧发射一组激光
            // 发射一侧激光，交替进行
            for (int i = 0; i < MAX_LASERS; i++) {
                if (m_laser[i]->isFree()) {
                    m_laser[i]->reset();
                    m_laser[i]->m_Free = false;
                    if (!m_lastLaserFromLeft) {
                        // 发射左侧激光
                        m_laser[i]->m_X = 0;
                        m_laser[i]->setSpeedX(4); // 向右移动
                    } else {
                        // 发射右侧激光
                        m_laser[i]->m_X = GAME_WIDTH - m_laser[i]->m_Laser.width();
                        m_laser[i]->setSpeedX(-4); // 向左移动
                    }

                    m_laser[i]->m_Y = GAME_HEIGHT / 2 - m_laser[i]->m_Laser.height() / 2;
                    m_laser[i]->laser_type = VERTICAL_LASER;

                    // 交替标志切换
                    m_lastLaserFromLeft = !m_lastLaserFromLeft;

                    break;
                }
            }
        }
    }

    // 2. 三发追踪弹幕
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_KAGUYA_SHOOT_INTERVAL2) {
        return;
    }

    m_shootRecorderEnemy = 0;

    // 发射三发追踪弹
    // 计算朝向玩家的角度
    double deltaX = playerX - (m_X + m_Role.width() * 0.5);
    double deltaY = playerY - (m_Y + m_Role.height() * 0.5);
    double angle = atan2(deltaY, deltaX);
    // 发射3发扇形弹幕
    for (int i = -1; i <= 1; i++) {
        for (int j = 0; j < BULLET_NUM_ENEMY; j++) {
            if (m_secondBullets[j].m_Free) {
                m_secondBullets[j].reset();
                m_secondBullets[j].m_Free = false;
                m_secondBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_secondBullets[j].m_Rect.width() * 0.5;
                m_secondBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_secondBullets[j].m_Rect.height() * 0.5;

                double bulletAngle = angle + i * 0.4;
                m_secondBullets[j].m_SpeedX = cos(bulletAngle) * BOSS_BULLET_SPEED * 0.7;
                m_secondBullets[j].m_SpeedY = sin(bulletAngle) * BOSS_BULLET_SPEED * 0.7;
                //m_firstBullets[j].m_Direction = CUSTOM;
                m_secondBullets[j].isTracking = true; // 设置为追踪模式
                break;
            }
        }
    }
}

void BossKaguya::pattern3()
{
    // 追踪弹幕与固定弹幕组合（十方向旋转，交叉发射）
    m_shootRecorderEnemy++;
    if (m_shootRecorderEnemy < BOSS_KAGUYA_SHOOT_INTERVAL3) { // 射击间隔调整为20帧
        return;
    }

    m_shootRecorderEnemy = 0;

    int totalBullets = 10; // 十个方向
    double angleStep = 2 * M_PI / totalBullets; // 角度间隔

    // 同时发射十个方向的子弹
    for (int i = 0; i < totalBullets; i++) {
        double angle = angleStep * i + m_spiralAngle; // 计算当前角度

        // 交叉发射：奇数索引发射追踪弹，偶数索引发射普通子弹
        if (i % 2 == 1) { // 追踪弹（奇数索引：1,3,5,7,9）
            for (int j = 0; j < BULLET_NUM_ENEMY; j++) {
                if (m_secondBullets[j].m_Free) {
                    m_secondBullets[j].reset();
                    m_secondBullets[j].m_Free = false;
                    m_secondBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_secondBullets[j].m_Rect.width() * 0.5;
                    m_secondBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_secondBullets[j].m_Rect.height() * 0.5;

                    // 设置初始速度（方向角度）
                    m_secondBullets[j].m_SpeedX = cos(angle) * BOSS_BULLET_SPEED * 0.7;
                    m_secondBullets[j].m_SpeedY = sin(angle) * BOSS_BULLET_SPEED * 0.7;

                    // 设置追踪属性
                    m_secondBullets[j].targetX = playerX;
                    m_secondBullets[j].targetY = playerY;
                    m_secondBullets[j].isTracking = true;
                    m_secondBullets[j].angleLimit = M_PI / 8; // 45度偏转限制
                    break;
                }
            }
        } else { // 普通子弹（偶数索引：0,2,4,6,8）
            for (int j = 0; j < BULLET_NUM_ENEMY; j++) {
                if (m_firstBullets[j].m_Free) {
                    m_firstBullets[j].m_Free = false;
                    m_firstBullets[j].m_X = m_X + m_Role.width() * 0.5 - m_firstBullets[j].m_Rect.width() * 0.5;
                    m_firstBullets[j].m_Y = m_Y + m_Role.height() * 0.5 - m_firstBullets[j].m_Rect.height() * 0.5;

                    // 设置固定方向速度
                    m_firstBullets[j].m_SpeedX = cos(angle) * BOSS_BULLET_SPEED * 0.7;
                    m_firstBullets[j].m_SpeedY = sin(angle) * BOSS_BULLET_SPEED * 0.7;
                    break;
                }
            }
        }
    }

    // 更新螺旋角度，使整个弹幕图案旋转
    m_spiralAngle += 0.10; // 旋转速度
    if (m_spiralAngle > 2 * M_PI) {
        m_spiralAngle = 0;
    }
}
