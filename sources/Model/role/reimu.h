#ifndef REIMU_H
#define REIMU_H

#include "role.h"

class Reimu : public Role
{
public:
    Reimu();

    // ʵ���麯��
    void shoot() override;
    void updatePosition() override;

    // �������е�����
    void useSpellCard();

	// ��ȡ���εĻ����ȼ�
    int getPower() const { return m_power; }
    // ��ȡ���εĲ�������
    int getGraze() const { return m_graze; }
    // �������εĻ����ȼ�
    void setPower(int power) { m_power = power; }
    // �������εĲ�������
	void setGraze(int graze) { m_graze = graze; }

private:
    // �������е�����
    int m_power; // �����ȼ�
    int m_graze; // ��������
    bool m_unmatched; // �Ƿ��޵�
};

#endif // REIMU_H