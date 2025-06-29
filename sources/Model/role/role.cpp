#include "role.h"

Role::Role(RoleType type) :
    m_type(type),
    m_X(0),
    m_Y(0),
    m_life(1),  // Ĭ��ֵ�������������͸���
    m_maxLife(1), // Ĭ��ֵ�������������͸���
    m_spell(0),
    m_maxSpell(0),
    m_shootRecorderPlayer(0),
    m_Speed(0),
    m_shootRecorderEnemy(0),
    m_Free(true)
{

    // ���ؽ�ɫ��ͼ
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
    case BOSS_SEIRIN:
        m_Role.load(SEIRIN_PATH);
        break;
    case BOSS_KAGUYA:
        m_Role.load(KAGUYA_PATH);
        break;
    case NORMAL_ENEMY:
        m_Role.load(ENEMY_PATH);
        break;
    default:
        // δ֪���ͣ�ʹ��Ĭ����ͼ
        m_Role.load(REIMU_PATH); // Ĭ��ʹ��Reimu��ͼ
        break;
    }


    // ���ݽ�ɫ�������ò�ͬ������
    switch (m_type) {
    case PLAYER_REIMU:
    case PLAYER_MARISA:
        // ��ҽ�ɫ 3��������λ����Ļ�·��м�
        m_maxLife = MAX_PLAYER_LIFE;
        m_life = INIT_PLAYER_LIFE;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = GAME_HEIGHT - m_Role.height() - 50; // ��ײ�50����
        m_spell = INIT_PLAYER_SPELL; // ��ʼ������Ϊ��
        m_maxSpell = MAX_PLAYER_SPELL; // �����3��������
        m_Free = false; // ��ҳ�ʼΪ�ǿ���״̬
        break;

    case BOSS_SAKURA:
    case BOSS_YOUMU:
    case BOSS_SEIRIN:
    case BOSS_KAGUYA:
        // Boss��ɫ - ��������ֵ��λ����Ļ�Ϸ��м�
        m_maxLife = BOSS_LIFE; // Boss��80������
        m_life = m_maxLife;
        m_X = GAME_WIDTH * 0.5 - m_Role.width() * 0.5;
        m_Y = 200; // �붥��200����
        m_Free = false; // Boss��ʼΪ�ǿ���״̬
        break;

    case NORMAL_ENEMY:
        // ��ͨ�л� - 1��������λ��������ʱ����
        m_X = 0;
        m_Y = 0;
        m_life = ENEMY_LIFE;
        m_maxLife = ENEMY_LIFE;
        m_Speed = ENEMY_SPEED;
        m_Free = true; // �л���ʼΪ����״̬
        break;

    default:
        // δ֪���ͣ�ʹ��Ĭ��ֵ
        break;
    }

    // ��ʼ����ͼ�����С
    m_Rect.setWidth(m_Role.width());
    m_Rect.setHeight(m_Role.height());
    m_Rect.moveTo(m_X, m_Y);

    // ��ʼ����ײ����
    // ����Bossʹ�ø������ײ��
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

    // ��ʼ���ӵ�
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_firstBullets[i] = Bullet(m_type);
    }
}

void Role::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X, m_Y);
    // ������ײ��λ��
    m_collisionRect.moveTo(m_X + (m_Rect.width() - m_collisionRect.width()) / 2,
        m_Y + (m_Rect.height() - m_collisionRect.height()) / 2);
}

void Role::reset()
{
    // ���ݽ�ɫ��������״̬
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
    case BOSS_SEIRIN:
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

    // �����ӵ�
    for (int i = 0; i < MAX_BULLETS; i++) {
        m_firstBullets[i].m_Free = true;
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
