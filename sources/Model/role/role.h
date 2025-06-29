#ifndef ROLE_H
#define ROLE_H

#include <QPixmap>
#include <QRect>
#include <vector>
#include "../../common/config.h"
#include "../bullet/bullet.h"

class Role
{
public:
    Role(RoleType type = PLAYER_REIMU);

    // �����ӵ�
    virtual void shoot() {};
    // ����λ��
    void setPosition(int x, int y);
    // ��������
    virtual void updatePosition() {};
    // ����״̬
    void reset();
    void resetWithoutBullets();
    // ��ȡrole����
    RoleType getType() const { return m_type; }

public:
	// ��ȡ��ɫ����
    RoleType m_type;

    // Role��Դ����
    QPixmap m_Role;

    // ����
    int m_X;
    int m_Y;

	// ���α߿�������ײ���
    QRect m_Rect;

    // ��ϻ
    Bullet m_firstBullets[MAX_BULLETS]; // ʹ���������

    // ����ֵ
    int m_life;
    int m_maxLife;
    // spell ���ܲ�
	int m_spell; 
	int m_maxSpell;

    // ��ײ���
    QRect m_collisionRect;

	// �ƶ��ٶ�
    int m_Speed;

    // ���ר������
    int m_shootRecorderPlayer; // ��������¼

    // �л�ר������
    int m_shootRecorderEnemy;

    // ���״̬��־
    bool m_Free;  // �Ƿ���У�δ��ʹ�ã�
};

#endif // PLANE_H
