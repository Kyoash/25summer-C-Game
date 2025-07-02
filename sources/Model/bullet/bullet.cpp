#include "bullet.h"

Bullet::Bullet(RoleType rtype, BulletType btype) :
    m_type(btype),
    role_type(rtype),

    m_Free(true),
    m_SpeedY(rtype >= BOSS_SAKUYA ? 10 : -10),
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

    // 记录初始速度方向
    if(role_type != PLAYER_REIMU && role_type != PLAYER_MARISA){
        m_InitSpeedX = m_SpeedX;
        m_InitSpeedY = m_SpeedY;
    }else{
        m_InitSpeedY = m_SpeedY;
        m_InitSpeedX = 0;
    }

    zhuizongnow = 0;
    maxzhuizong = 80;
    zhuizongwancheng = false;

}

void Bullet::updatePosition()
{
    // 如果子弹空闲，不需要更新
    if(m_Free) {
        zhuizongnow = 0;
        zhuizongwancheng = false;
        return;
    }

    // 追踪子弹逻辑
    if(isTracking && !zhuizongwancheng) {
        if(m_SpeedX < 1e-3 && m_SpeedX > (-1) * 1e-3){
            m_SpeedX = 0.1;
        }
        if(m_SpeedY < 1e-3 && m_SpeedY > (-1) * 1e-3){
            m_SpeedY = 0.1;
        }
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
            double currentSpeed = sqrt(double(m_SpeedX * m_SpeedX + m_SpeedY * m_SpeedY));

            // // // // ???把这一段删了追踪弹打不出来？？？ tag2!!!
            // // if (currentSpeed < 1e-2 && currentSpeed > -1e-2) {
            // //     currentSpeed = m_Speed; // 默认速度
            // //     if (abs(currentSpeed) < 1e-2) currentSpeed = -10; // 避免0
            // //     m_SpeedX = m_InitSpeedX != 0 ? m_InitSpeedX : 0;
            // //     m_SpeedY = m_InitSpeedY != 0 ? m_InitSpeedY : currentSpeed;
            // // }
            // if(currentSpeed == 0){
            //     m_SpeedX = -3;
            //     m_SpeedY = 4;
            //     currentSpeed = 5;
            // }

            currentDirX = m_SpeedX / currentSpeed;
            currentDirY = m_SpeedY / currentSpeed;

            // 计算当前方向与目标方向之间的角度差
            // 替换现有的角度差计算
            double angleCurrent;
            double angleTarget;
            if(currentDirX == 0){
                if(currentDirY < 0){
                    angleCurrent = - M_PI / 2;
                }else{
                    angleCurrent = M_PI / 2;
                }
            }else{
                angleCurrent = atan2(currentDirY, currentDirX);
            }
            if(targetDirX == 0){
                if(targetDirY < 0){
                    angleTarget = - M_PI / 2;
                }else{
                    angleTarget = M_PI / 2;
                }
            }else{
                angleTarget = atan2(targetDirY, targetDirX);
            }

            double angleDiff = angleTarget - angleCurrent;

            // 将角度差标准化到[-π, π]范围内
            while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
            while (angleDiff < -M_PI) angleDiff += 2 * M_PI;

            // 限制偏转角度在允许范围内

            //double maxAngleChange = M_PI / 180 * 50; // 每次最多偏转10度
            //if(fabs(angleDiff) > maxAngleChange) {
            //    angleDiff = (angleDiff > 0) ? maxAngleChange : -maxAngleChange;
            //}

            /*
            // 累计偏转角度
            angleSwift += fabs(angleDiff);

            // 如果累计偏转超过角度限制，则不再偏转
            if(angleSwift > angleLimit) {
                isTracking = false;
            }
            */
            // 计算新的方向向量
            double newDirX = currentDirX * cos(angleDiff) - currentDirY * sin(angleDiff);
            double newDirY = currentDirX * sin(angleDiff) + currentDirY * cos(angleDiff);
            // 归一化新方向（避免精度累积)
            double len = sqrt(newDirX * newDirX + newDirY * newDirY);
            if (len != 1.0) {
                newDirX /= len;
                newDirY /= len;
            }
            // 更新速度向量
            m_SpeedX = newDirX * currentSpeed  ;
            m_SpeedY = newDirY * currentSpeed  ;
        }
        zhuizongnow++;
    }
    if(zhuizongnow >= maxzhuizong){
        zhuizongwancheng = true;
    }
    // 基于距离判断是否完成追踪
    // double distanceToTarget = sqrt(pow(targetX - m_X, 2) + pow(targetY - m_Y, 2));
    // if (distanceToTarget < 50 || zhuizongnow >= maxzhuizong) {
    //     zhuizongwancheng = true;
    // }

    // 根据速度移动子弹
    if(m_SpeedX != 0 || m_SpeedY != 0) {
        // 使用速度向量移动
        m_X += m_SpeedX;
        m_Y += m_SpeedY;
    } else {
        // 使用单一方向速度移动
        if(role_type == PLAYER_REIMU || role_type == PLAYER_MARISA) {
            // 玩家子弹向上移动
            m_Y += m_Speed;
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
    if(m_Y < 0 || m_Y > (GAME_HEIGHT - m_collisionRect.height()) ||
        m_X < 0 || m_X > (GAME_WIDTH - m_collisionRect.width())) {
        m_Free = true;
    }
}

void Bullet::reset()
{
    isTracking = false;
    zhuizongnow = 0;
    zhuizongwancheng = false;
}
