#include "role.h"

Role::Role(RoleType type) :
    m_type(type),
    m_X(0),
    m_Y(0),
    m_life(1),  // 默认值，后面会根据类型覆盖
    m_maxLife(1), // 默认值，后面会根据类型覆盖
    m_spell(0),
    m_maxSpell(0),
    m_shootRecorderPlayer(0),
    m_Speed(0),
    m_shootRecorderEnemy(0),
    m_Free(true)
{

    // 加载角色贴图
    switch (m_type) {
    case PLAYER_REIMU:
        m_Role.load(REIMU_PATH);
        break;
    case PLAYER_MARISA:
        m_Role.load(MARISA_PATH);
        break;
    case BOSS_SAKURA:
        m_Role.load(SAKURA_PATH);
        break;
    case BOSS_YOUMU:
        m_Role.load(YOUMU_PATH);
        break;
    case BOSS_EIRIN:
        m_Role.load(EIRIN_PATH);
        break;
    case BOSS_KAGUYA:
        m_Role.load(KAGUYA_PATH);
        break;
    case NORMAL_ENEMY:
        m_Role.load(ENEMY_PATH);
        break;
    default:
        // 未知类型，使用默认贴图
        m_Role.load(REIMU_PATH); // 默认使用Reimu贴图
        break;
    }


    // 根据角色类型设置不同的属性
    switch (m_type) {
    case PLAYER_REIMU:
    case PLAYER_MARISA:
        // 玩家角色 3条生命，位于屏幕下方中间
        m_maxLife = MAX_PLAYER_LIFE;
        m_life = INIT_PLAYER_LIFE;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = GAME_HEIGHT - m_Role.height() - 50; // 离底部50像素
        m_spell = INIT_PLAYER_SPELL; // 初始符卡槽为空
        m_maxSpell = MAX_PLAYER_SPELL; // 玩家有3个符卡槽
        m_Free = false; // 玩家初始为非空闲状态
        break;

    case BOSS_SAKURA:
    case BOSS_YOUMU:
    case BOSS_EIRIN:
    case BOSS_KAGUYA:
        // Boss角色 - 更多生命值，位于屏幕上方中间
        m_maxLife = BOSS_LIFE; // Boss有80条生命
        m_life = m_maxLife;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = 200; // 离顶部200像素
        m_Free = false; // Boss初始为非空闲状态
        break;

    case NORMAL_ENEMY:
        // 普通敌机 - 1条生命，位置由生成时决定
        m_X = 0;
        m_Y = 0;
        m_life = ENEMY_LIFE;
        m_maxLife = ENEMY_LIFE;
        m_Speed = ENEMY_SPEED;
        m_Free = true; // 敌机初始为空闲状态
        break;

    default:
        // 未知类型，使用默认值
        break;
    }

    // 初始化贴图坐标大小
    m_Rect.setWidth(m_Role.width());
    m_Rect.setHeight(m_Role.height());
    m_Rect.moveTo(m_X, m_Y);

    // 初始化碰撞矩形
    // 对于Boss使用更大的碰撞框
    if (m_type >= BOSS_SAKURA && m_type <= BOSS_KAGUYA) {
        m_collisionRect.setWidth(BOSS_COLLISION_WIDTH);
        m_collisionRect.setHeight(BOSS_COLLISION_HEIGHT);
    }
    else if (m_type < BOSS_SAKURA) {
        m_collisionRect.setWidth(ROLE_COLLISION_WIDTH);
        m_collisionRect.setHeight(ROLE_COLLISION_HEIGHT);
    }
    else {
        m_collisionRect.setWidth(ENEMY_COLLISION_WIDTH);
        m_collisionRect.setHeight(ENEMY_COLLISION_HEIGHT);
    }
    m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
        m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);

    // 初始化子弹
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_firstBullets[i] = Bullet(m_type, DEFAULT_BULLET);
    }
    for (int i = 0; i < MAX_BULLETS; i++){
        m_secondBullets[i] = Bullet(m_type, DEFAULT_BULLET);
        m_secondBullets[i].isTracking = true;
    }
}

void Role::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X, m_Y);
    // 更新碰撞框位置
    m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
        m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
}

void Role::reset()
{
    // 根据角色类型重置状态
    switch (m_type) {
    case PLAYER_REIMU:
    case PLAYER_MARISA:
        m_life = INIT_PLAYER_LIFE;
        m_spell = INIT_PLAYER_SPELL;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = GAME_HEIGHT - m_Role.height() - 50;
        m_Rect.moveTo(m_X, m_Y);
        m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
        break;

    case BOSS_SAKURA:
    case BOSS_YOUMU:
    case BOSS_EIRIN:
    case BOSS_KAGUYA:
        m_life = BOSS_LIFE;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = 200;
        m_Rect.moveTo(m_X, m_Y);
        m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
            m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
        break;

    case NORMAL_ENEMY:
        m_life = ENEMY_LIFE;
        m_Free = true;
        break;
    }

    // 重置子弹
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_firstBullets[i].m_Free = true;
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_secondBullets[i].m_Free = true;
    }
}

void Role::resetWithoutBullets()
{
    if (m_type == NORMAL_ENEMY) {
        m_Free = true;
        m_life = ENEMY_LIFE;
        m_shootRecorderEnemy = 0;
        m_X = 0;
        m_Y = 0;
    }
}
