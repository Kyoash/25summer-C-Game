#ifndef CONFIG_H
#define CONFIG_H

#define MAP_PATH ""
#define GAME_RATE 10

// ��ɫ���Ͷ���
enum RoleType {
    PLAYER_REIMU,  // ���
    PLAYER_MARISA,
    BOSS_SAKURA, // �з�Boss
    BOSS_YOUMU,
    BOSS_EIRIN,
    BOSS_KAGUYA,
    NORMAL_ENEMY // �з���ͨ�л�
};
enum BulletType {
    DEFAULT_BULLET,
    BULLET_TYPE1,
    BULLET_TYPE2
};

// ���е���ͼ·������������
#define REIMU_PATH ":/res/role/reimu.png" // Player ��ɫ��ͼ
#define MARISA_PATH ":/res/role/marisa.png" // Player ��ɫ��ͼ
#define SAKURA_PATH ":/res/role/sakura.png" // Boss ��ɫ��ͼ
#define YOUMU_PATH ":/res/role/youmu.png" // Boss ��ɫ��ͼ
#define EIRIN_PATH ":/res/role/eirin.png" // Boss ��ɫ��ͼ
#define KAGUYA_PATH ":/res/role/kaguya.png" // Boss ��ɫ��ͼ
#define ENEMY_PATH ":/res/role/enemy.png" // �л���ͼ
#define SPELL_CIRCLE_SOURCE ":/res/ANM/ANM/etama/etama3.png"
#define ENEMY_BOSS_BULLET_1_SOURCE ":/res/ANM/ANM/etama/etama.png"
#define ENEMY_BOSS_BULLET_2_SOURCE ":/res/ANM/ANM/etama/etama6.png"

// �ӵ���ͼ·�� - ÿ����ɫ�������ӵ����ͣ���1��ʼ����
#define REIMU_BULLET1_PATH ":/res/bullet/reimu_bullet1.png"
#define REIMU_BULLET2_PATH ":/res/bullet/reimu_bullet2.png"
#define REIMU_BULLET3_PATH ":/res/bullet/reimu_bullet3.png"

#define MARISA_BULLET1_PATH ":/res/bullet/marisa_bullet1.png"
#define MARISA_BULLET2_PATH ":/res/bullet/marisa_bullet2.png"
#define MARISA_BULLET3_PATH ":/res/bullet/marisa_bullet3.png"

#define SAKURA_BULLET1_PATH ":/res/bullet/sakura_bullet1.png"
#define SAKURA_BULLET2_PATH ":/res/bullet/sakura_bullet2.png"
#define SAKURA_BULLET3_PATH ":/res/bullet/sakura_bullet3.png"

#define YOUMU_BULLET1_PATH ":/res/bullet/youmu_bullet1.png"
#define YOUMU_BULLET2_PATH ":/res/bullet/youmu_bullet2.png"
#define YOUMU_BULLET3_PATH ":/res/bullet/youmu_bullet3.png"

#define EIRIN_BULLET1_PATH ":/res/bullet/eirin_bullet1.png"
#define EIRIN_BULLET2_PATH ":/res/bullet/eirin_bullet2.png"
#define EIRIN_BULLET3_PATH ":/res/bullet/eirin_bullet3.png"

#define KAGUYA_BULLET1_PATH ":/res/bullet/kaguya_bullet1.png"
#define KAGUYA_BULLET2_PATH ":/res/bullet/kaguya_bullet2.png"
#define KAGUYA_BULLET3_PATH ":/res/bullet/kaguya_bullet3.png"

#define ENEMY_BULLET1_PATH ":/res/bullet/enemy_bullet1.png"
#define ENEMY_BULLET2_PATH ":/res/bullet/enemy_bullet2.png"
#define ENEMY_BULLET3_PATH ":/res/bullet/enemy_bullet3.png"

#define DEFAULT_BULLET_PATH ":/res/bullet/default.png"

#define ITEM_SOURCE ":/res/ANM/ANM/etama/etama2.png"
#define ASCII_SOURCE ":/res/ANM/ANM/ascii/ascii.png"
#define LOADING_SOURCE ":/res/ANM/ANM/ascii/loading.png"
#define PAUSE_SOURCE ":/res/ANM/ANM/ascii/pause.png"

#define NAME_SOURCE ":/res/ANM/ANM/front/ename.png"
#define LIFE_BOMB_SOURCE ":/res/ANM/ANM/front/front.png"

#define PAINTING_REIMU_YUKARI_SOURCE ":/res/ANM/ANM/image/loading00.png"
#define PAINTING_MARISA_ALICE_SOURCE ":/res/ANM/ANM/image/loading01.png"
#define PAINTING_REIMU_SOURCE ":/res/ANM/ANM/image/loading00h.png"
#define PAINTING_MARISA_SOURCE ":/res/ANM/ANM/image/loading01h.png"

#define PLAYER_REIMU_SOURCE ":/res/ANM/ANM/player/player00.png"
#define PLAYER_MARISA_SOURCE ":/res/ANM/ANM/player/player01.png"

#define ENEMY_SOURCE ":/res/ANM/ANM/stgenm/enemy.png"
#define BOSS_SAKUYA_SOURCE ":/res/ANM/ANM/stgenm/stg9enm_sk.png"
#define BOSS_YOUMU_SOURCE ":/res/ANM/ANM/stgenm/stg9enm_ym.png"
#define BOSS_EIRIN_SOURCE ":/res/ANM/ANM/stgenm/stg7enm.png"
#define BOSS_KAGUYA_SOURCE ":/res/ANM/ANM/stgenm/stg7enm2.png"

#define RESULT_PLAYER_SOURCE ":/res/ANM/ANM/result/result00.png"
#define RESULT_DIFFICULTY_SOURCE ":/res/ANM/ANM/result/result01.png"
#define RESULT_SCORE_SOURCE ":/res/ANM/ANM/result/result03.png"

#define REIMU_YUKARI_SELECT_SOURCE ":/res/ANM/ANM/title/sl_pltxt0.png"
#define MARISA_ALICE_SELECT_SOURCE ":/res/ANM/ANM/title/sl_pltxt1.png"
#define MENU_OPTIONS_SOURCE ":/res/ANM/ANM/title/title01.png"
#define MENU_BACKGROUND_SOURCE ":/res/ANM/ANM/title/title02.png"

#define MUSIC_SOURCE ":/res/MUSIC/th08_00.mid" // th08_00.mid ~ th08_20.mid, ����һЩ.wav ����

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
#define BOSS_BULLET_SPEED 10 // BOSS��ͨ�ӵ��ƶ��ٶ�

// ���е��ӵ��ߴ���Ϣ
#define PLAYER_BULLET_WIDTH 16 // ����ӵ����
#define PLAYER_BULLET_HEIGHT 16 // ����ӵ��߶�

#endif // CONFIG_H
