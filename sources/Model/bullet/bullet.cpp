#include "bullet.h"

Bullet::Bullet(RoleType rtype, BulletType btype) :
    m_type(btype),
    role_type(rtype),
    m_X(0),
    m_Y(0),
    m_Speed(0),
    m_Free(true),
    m_SpeedX(0),
    m_SpeedY(0),
    isTracking(false),
    targetX(0),
    targetY(0),
    angleLimit(M_PI / 8), // 45度偏转限制
    m_InitSpeedX(0),
    m_InitSpeedY(0),
    angleSwift(0)
{
    // 根据角色类型和子弹类型加载贴图
    switch(role_type) {
    case PLAYER_REIMU:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(REIMU_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(REIMU_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(REIMU_BULLET3_PATH);
            break;
        }
        break;

    case PLAYER_MARISA:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(MARISA_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(MARISA_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(MARISA_BULLET3_PATH);
            break;
        }
        break;

    case BOSS_SAKUYA:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(SAKUYA_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(SAKUYA_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(SAKUYA_BULLET3_PATH);
            break;
        }
        break;

    case BOSS_YOUMU:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(YOUMU_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(YOUMU_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(YOUMU_BULLET3_PATH);
            break;
        }
        break;

    case BOSS_EIRIN:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(EIRIN_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(EIRIN_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(EIRIN_BULLET3_PATH);
            break;
        }
        break;

    case BOSS_KAGUYA:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(KAGUYA_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(KAGUYA_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(KAGUYA_BULLET3_PATH);
            break;
        }
        break;

    case NORMAL_ENEMY:
        switch(m_type) {
        case DEFAULT_BULLET:
            m_Bullet.load(ENEMY_BULLET1_PATH);
            break;
        case BULLET_TYPE1:
            m_Bullet.load(ENEMY_BULLET2_PATH);
            break;
        case BULLET_TYPE2:
            m_Bullet.load(ENEMY_BULLET3_PATH);
            break;
        }
        break;

    default:
        m_Bullet.load(DEFAULT_BULLET_PATH);
        break;
    }

    // 初始化矩形和碰撞体积
    m_Rect = QRect(m_X, m_Y, m_Bullet.width(), m_Bullet.height());
    m_collisionRect = QRect(m_X, m_Y, 0.75 * m_Bullet.width(), 0.75 * m_Bullet.height());

    // 根据角色类型设置默认速度
    if(role_type == PLAYER_REIMU) {
        m_Speed = PLAYER_REIMU_BULLET_SPEED;
    }else if(role_type == PLAYER_MARISA){
        m_Speed = PLAYER_MARISA_BULLET_SPEED;
    }

    // 记录初始速度方向
    if(role_type != PLAYER_REIMU && role_type != PLAYER_MARISA){
        m_InitSpeedX = m_SpeedX;
        m_InitSpeedY = m_SpeedY;
    }else{
        m_InitSpeedY = m_Speed;
        m_InitSpeedX = 0;
    }
    
}

void Bullet::updatePosition()
{
    // 如果子弹空闲，不需要更新
    if(m_Free) {
        return;
    }

    // 追踪子弹逻辑
    if(isTracking) {
        // 计算朝向目标的方向向量
        double dx = targetX - m_X;
        double dy = targetY - m_Y;
        double distance = sqrt(dx * dx + dy * dy);

        if(distance > 0) {
            // 计算目标方向向量
            double targetDirX = dx / distance;
            double targetDirY = dy / distance;

            // 计算当前方向向量
            double currentDirX = 0;
            double currentDirY = 0;
            double currentSpeed = sqrt(m_SpeedX * m_SpeedX + m_SpeedY * m_SpeedY);

            if(currentSpeed > 0) {
                currentDirX = m_SpeedX / currentSpeed;
                currentDirY = m_SpeedY / currentSpeed;
            } else {
                // 如果没有初始速度，使用初始速度方向
                currentDirX = m_InitSpeedX > 0 ? 1 : (m_InitSpeedX < 0 ? -1 : 0);
                currentDirY = m_InitSpeedY > 0 ? 1 : (m_InitSpeedY < 0 ? -1 : 0);
                currentSpeed = m_Speed;
            }

            // 计算当前方向与目标方向之间的角度差
            double dot = currentDirX * targetDirX + currentDirY * targetDirY;
            double cross = currentDirX * targetDirY - currentDirY * targetDirX;
            double angleDiff = atan2(cross, dot);

            // 限制偏转角度在允许范围内
            double maxAngleChange = M_PI / 180 * 2; // 每次最多偏转2度
            if(fabs(angleDiff) > maxAngleChange) {
                angleDiff = (angleDiff > 0) ? maxAngleChange : -maxAngleChange;
            }

            // 累计偏转角度
            angleSwift += fabs(angleDiff);

            // 如果累计偏转超过角度限制，则不再偏转
            if(angleSwift > angleLimit) {
                angleDiff = 0;
            }

            // 计算新的方向向量
            double newDirX = currentDirX * cos(angleDiff) - currentDirY * sin(angleDiff);
            double newDirY = currentDirX * sin(angleDiff) + currentDirY * cos(angleDiff);

            // 更新速度向量
            m_SpeedX = newDirX * currentSpeed;
            m_SpeedY = newDirY * currentSpeed;
        }
    }

    // 根据速度移动子弹
    if(m_SpeedX != 0 || m_SpeedY != 0) {
        // 使用速度向量移动
        m_X += m_SpeedX;
        m_Y += m_SpeedY;
    } else {
        // 使用单一方向速度移动
        if(role_type == PLAYER_REIMU || role_type == PLAYER_MARISA) {
            // 玩家子弹向上移动
            m_Y -= m_Speed;
        } else {
            // 敌人子弹向下移动
            m_Y += m_Speed;
        }
    }

    // 更新子弹矩形位置
    m_Rect.moveTo(m_X, m_Y);

    // 更新碰撞体积位置
    m_collisionRect.moveTo(
        m_X + (m_Bullet.width() - m_collisionRect.width()) / 2,
        m_Y + (m_Bullet.height() - m_collisionRect.height()) / 2
        );

    // 检查子弹是否超出屏幕
    if(m_Y < -m_Bullet.height() || m_Y > GAME_HEIGHT ||
        m_X < -m_Bullet.width() || m_X > GAME_WIDTH) {
        m_Free = true;
    }
}
