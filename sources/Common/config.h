#ifndef CONFIG_H
#define CONFIG_H

// ��ɫ���Ͷ���
enum RoleType {
	PLAYER_REIMU,  // ���
	PLAYER_MARISA, 
	BOSS_SAKURA, // �з�Boss
	BOSS_YOUMU,
	BOSS_SEIRIN,
	BOSS_KAGUYA,
	NORMAL_ENEMY // �з���ͨ�л�
};

// ���е���ͼ·������������
#define REIMU_PATH ":/res/role/reimu.png" // Player ��ɫ��ͼ
#define MARISA_PATH ":/res/role/marisa.png" // Player ��ɫ��ͼ
#define SAKURA_PATH ":/res/role/sakura.png" // Boss ��ɫ��ͼ
#define YOUMU_PATH ":/res/role/youmu.png" // Boss ��ɫ��ͼ
#define SEIRIN_PATH ":/res/role/seirin.png" // Boss ��ɫ��ͼ
#define KAGUYA_PATH ":/res/role/kaguya.png" // Boss ��ɫ��ͼ
#define ENEMY_PATH ":/res/role/enemy.png" // �л���ͼ

// ��Ϸ��ͼ����
#define GAME_WIDTH 600  // ��Ϸ���ڿ��
#define GAME_HEIGHT 800 // ��Ϸ���ڸ߶�
#define GAME_TITLE "������ҹ��" // ����

// ��ɫ��ײ�ߴ�����
#define ROLE_COLLISION_WIDTH 48   // ��ɫ���
#define ROLE_COLLISION_HEIGHT 64 // ��ɫ�߶�

// Player/Enemy �ӵ����
#define MAX_BULLETS 200 // ����ӵ���������
#define BULLET_NUM 60   // PLAYER��ϻ���ӵ�����
#define BULLET_NUM_ENEMY 120 // ENEMY��ϻ���ӵ�����

// Player��ֵ����
#define INIT_PLAYER_LIFE 3  // �Ի���ʼ����ֵ
#define INIT_PLAYER_SPELL 3 // �Ի���ʼ������
#define MAX_PLAYER_LIFE 8 // �Ի��������ֵ
#define MAX_PLAYER_SPELL 8 // �Ի���������
#define PLAYER_SHOOT_INTERVAL 10 // �Ի�������

// Boss��ײ�ߴ�����
#define BOSS_COLLISION_WIDTH 144 // Boss��ײ���ο��
#define BOSS_COLLISION_HEIGHT 192 // Boss��ײ���θ߶�

// Boss��ֵ����
#define BOSS_LIFE 80 // Boss��ʼ����ֵ
#define BOSS_SHOOT_INTERVAL1 15 // Bossһ�׶�������
#define BOSS_SHOOT_INTERVAL2 5 // Boss���׶�������
#define BOSS_SHOOT_INTERVAL3 10 // Boss���׶�������

// �л��������� 
#define ENEMY_SPEED 4  // �л��ƶ��ٶ�
#define ENEMY_NUM   20  // �л�������
#define ENEMY_INTERVAL  100  // �л�����ʱ����
#define ENEMY_LIFE 2 // �л�����ֵ

// �л���ײ�ߴ�����
#define ENEMY_COLLISION_WIDTH 48 // �л���ײ���ο��
#define ENEMY_COLLISION_HEIGHT 64 // �л���ײ���θ߶�

// ���е��ƶ��ٶ���Ϣ
#define SHIFTED_PLAYER_SPEED 8 // ��Ҽ����ƶ��ٶ�
#define NORMAL_PLAYER_SPEED 4 // �����ͨ�ƶ��ٶ�
#define PLAYER_BULLET_SPEED 10  // �����ͨ�ӵ��ƶ��ٶ�

// ���е��ӵ��ߴ���Ϣ
#define PLAYER_BULLET_WIDTH 16 // ����ӵ����
#define PLAYER_BULLET_HEIGHT 16 // ����ӵ��߶�

#endif // CONFIG_H
