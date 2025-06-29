#ifndef BOSS_SEIRIN_H
#define BOSS_SEIRIN_H

#include "role.h"

class BossSeirin : public Role
{
public:
    BossSeirin();

    // ʵ���麯��
    void shoot() override;
    void updatePosition() override;

    // Boss���е���Ϊ
    void setPattern(int pattern) { m_currentPattern = pattern; }
    void SetPlayerPosition(int x, int y) {
        playerX = x;
        playerY = y;
	}

private:
    // Boss�ƶ��ٶ�
    int m_SpeedX;
    int m_SpeedY;
    // Boss��Ϊģʽ
    void pattern1(); // Բ�ε�Ļ
    void pattern2(); // ������Ļ
    void pattern3(); // ��׼��Ļ

    int m_currentPattern; // ��ǰ��Ļģʽ
    int m_moveCounter;        // �ƶ���������
    int m_pauseTimer;         // ͣ����ʱ��
    int m_patternTimer;   // ģʽ��ʱ��
    int m_targetX, m_targetY; // Ŀ��λ�ã�����ƶ���
    int m_moveLimit; // �ƶ��������ƣ������
    double m_spiralAngle; // ������Ļ�Ƕ�
    
	int playerX; // ���X���꣬������׼��Ļ
    int playerY; // ���Y���꣬������׼��Ļ(��Ҫʱ��ˢ��)
   
};

#endif // BOSS_SEIRIN_H
