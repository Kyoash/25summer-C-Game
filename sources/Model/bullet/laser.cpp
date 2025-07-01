#include "laser.h"

Laser::Laser(RoleType type, LaserType laserType) :
    role_type(type),
    laser_type(laserType),
    m_X(0),
    m_Y(0),
    m_Free(true),
    m_angle(0),
    m_SpeedX(0),
    m_SpeedY(0),
    m_angleSpeed(0),
    targetBoss(nullptr),
    m_moveDistance(0),
    m_moveAngle(0),
    m_maxMoveDistance(0),
    m_maxMoveAngle(0)
{
    switch (role_type) {
    case PLAYER_REIMU:
        m_Laser.load(REIMU_LASER_PATH);
        break;
    case PLAYER_MARISA:
        m_Laser.load(MARISA_LASER_PATH);
        break;
    case BOSS_SAKUYA:
        m_Laser.load(SAKUYA_LASER_PATH);
        break;
    case BOSS_KAGUYA:
        m_Laser.load(KAGUYA_LASER_PATH);
        break;
    case BOSS_EIRIN:
        m_Laser.load(EIRIN_LASER_PATH);
        break;
    case BOSS_YOUMU:
        m_Laser.load(YOUMU_LASER_PATH);
        break;
    case NORMAL_ENEMY:
        m_Laser.load(ENEMY_LASER_PATH);
        break;
    default:
        m_Laser.load(DEFAULT_LASER_PATH);
        break;
    }

    // 设置纵向无限长
    if(laser_type == VERTICAL_LASER){
        m_Rect = QRect(m_X, m_Y, m_Laser.width(), GAME_HEIGHT * 3);
        m_collisionRect = QRect(m_X, m_Y, m_Laser.width() * 0.8, GAME_HEIGHT * 3);
    }else if(laser_type == HORIZONTAL_LASER){
        // 创建旋转变换
        QTransform transform;
        transform.rotate(90);
        m_Laser = m_Laser.transformed(transform);
        m_Rect = QRect(m_X, m_Y, GAME_WIDTH * 3, m_Laser.height());
        m_collisionRect = QRect(m_X, m_Y, GAME_WIDTH * 3, m_Laser.height() * 0.8);
    }else if(laser_type == ROTATION_LASER){
        m_Rect = QRect(m_X, m_Y, m_Laser.width(), GAME_HEIGHT * 3);
        m_collisionRect = QRect(m_X, m_Y, m_Laser.width() * 0.8, GAME_HEIGHT * 3);
    }
    // 设置默认移动限制
    if (m_maxMoveDistance == 0) {
        m_maxMoveDistance = GAME_WIDTH/2; // 默认移动距离限制为屏幕宽度的一半
    }
    if (m_maxMoveAngle == 0) {
        m_maxMoveAngle = M_PI / 3; // 默认旋转角度限制为120度
    }
}
    

void Laser::reset(){
    m_Free = true;
    m_X = 0;
    m_Y = 0;
    m_angle = 0;
    m_SpeedX = 0;
    m_SpeedY = 0;
    m_angleSpeed = 0;
    m_moveDistance = 0;
    m_moveAngle = 0;
    targetBoss = nullptr;
}

void Laser::updatePosition(){
    if (m_Free) return;

    // 保存旧位置用于距离计算
    int oldX = m_X;
    int oldY = m_Y;
    
    switch (laser_type) {
    case VERTICAL_LASER:
        // 垂直激光：水平移动
        m_X += m_SpeedX;
        m_moveDistance += abs(m_SpeedX);
        
        // 检查移动距离限制
        if (m_moveDistance > m_maxMoveDistance) {
            m_Free = true;
            return;
        }
        break;
    case HORIZONTAL_LASER:
        m_Y += m_SpeedY;
        m_moveDistance += abs(m_SpeedY);
        
        // 检查移动距离限制
        if (m_moveDistance > m_maxMoveDistance) {
            m_Free = true;
            return;
        }
        break;
    case ROTATION_LASER:
        if (targetBoss) {
            // 旋转激光：围绕BOSS旋转
            
            // 更新角度
            m_angle += m_angleSpeed;
            m_moveAngle += abs(m_angleSpeed);
            
            // 检查旋转角度限制
            if (m_moveAngle > m_maxMoveAngle) {
                m_Free = true;
                return;
            }
            // 计算激光位置
            int bossCenterX = targetBoss->m_X + targetBoss->m_Role.width() / 2;
            int bossCenterY = targetBoss->m_Y + targetBoss->m_Role.height() / 2;
            
            // 激光起点固定在BOSS中心
            int laserStartX = bossCenterX;
            int laserStartY = bossCenterY;
            
            // 激光方向向量
            double dirX = cos(m_angle);
            double dirY = sin(m_angle);
            
            int laserLength = GAME_HEIGHT * 3;
            int laserWidth = m_Laser.width() * 0.8;

            // 起点在 Boss 中心
            QPointF p1(bossCenterX + dirY * (laserWidth / 2), bossCenterY - dirX * (laserWidth / 2)); // 左边
            QPointF p2(bossCenterX - dirY * (laserWidth / 2), bossCenterY + dirX * (laserWidth / 2)); // 右边

            // 终点
            QPointF endCenter = QPointF(bossCenterX + dirX * laserLength, bossCenterY + dirY * laserLength);
            QPointF p3(endCenter - QPointF(dirY * (laserWidth / 2), -dirX * (laserWidth / 2))); // 终点右边
            QPointF p4(endCenter + QPointF(dirY * (laserWidth / 2), -dirX * (laserWidth / 2))); // 终点左边

            // 更新中心位置（用于贴图/绘制）
            m_X = (p1.x() + p3.x() + p2.x() + p4.x()) / 4;
            m_Y = (p1.y() + p3.y() + p2.y() + p4.y()) / 4;

            // 更新图像矩形（仍保留用于绘制）
            m_Rect = QRect(m_X - m_Laser.width() / 2, m_Y - m_Laser.height() / 2,
                           m_Laser.width(), m_Laser.height());

            // 更新碰撞多边形
            m_collisionPolygon.clear();
            m_collisionPolygon << p1 << p2 << p3 << p4;


            // 更新碰撞框：放置在激光线上
            m_Rect = QRect(m_X - m_Laser.width() / 2, m_Y - m_Laser.height() / 2, m_Laser.width(), m_Laser.height());
            m_collisionRect = QRect(m_X - m_Laser.width() / 2, m_Y - GAME_HEIGHT, m_Laser.width(), GAME_HEIGHT * 2);
        }
        break;
    default:
        break;
    }

    if (m_Y < -m_Laser.height() || m_Y > GAME_HEIGHT * 2 ||
        m_X < -m_Laser.width() || m_X > GAME_WIDTH + m_Laser.width()) {
        m_Free = true;
    }
}
