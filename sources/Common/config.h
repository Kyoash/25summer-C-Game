#ifndef CONFIG_H
#define CONFIG_H

// ½ĒÉ«ĄąŠĶ¶ØŅå
enum RoleType {
    PLAYER_REIMU,  // ē©å®¶
    PLAYER_MARISA,
    BOSS_SAKUYA, // ęę¹Boss
    BOSS_YOUMU,
    BOSS_EIRIN,
    BOSS_KAGUYA,
    NORMAL_ENEMY // ęę¹ę®éęęŗ
};
enum BulletType {
    DEFAULT_BULLET,
    BULLET_TYPE1,
    BULLET_TYPE2
};
enum LaserType {
    ROTATION_LASER,
    HORIZONTAL_LASER,
    VERTICAL_LASER
};

#define GAME_RATE 10
// ęęēč““å¾č·Æå¾éē½®åØčæé
#define MAP_STAGE1_PATH ":/res/map/stagemap1.png"
#define MAP_STAGE2_PATH ":/res/map/stagemap2.png"
#define MAP_STAGE3_PATH ":/res/map/stagemap3.png"
#define MAP_STAGE4_PATH ":/res/map/stagemap4.png"
#define REIMU_PATH ":/res/role/reimu.png" // Player č§č²č““å¾
#define MARISA_PATH ":/res/role/marisa.png" // Player č§č²č““å¾
#define SAKUYA_PATH ":/res/role/sakuya.png" // Boss č§č²č““å¾
#define YOUMU_PATH ":/res/role/youmu.png" // Boss č§č²č““å¾
#define EIRIN_PATH ":/res/role/eirin.png" // Boss č§č²č““å¾
#define KAGUYA_PATH ":/res/role/kaguya.png" // Boss č§č²č““å¾
#define ENEMY_PATH ":/res/role/enemy.png" // ęęŗč““å¾
#define SPELL_CIRCLE_SOURCE ":/res/ANM/ANM/etama/etama3.png"
#define ENEMY_BOSS_BULLET_1_SOURCE ":/res/ANM/ANM/etama/etama.png"
#define ENEMY_BOSS_BULLET_2_SOURCE ":/res/ANM/ANM/etama/etama6.png"

// å­å¼¹č““å¾č·Æå¾ - ęÆäøŖč§č²ęäøē§å­å¼¹ē±»åļ¼ä»1å¼å§č®”ę°
#define REIMU_BULLET1_PATH ":/res/bullet/reimu_bullet1.png"
#define REIMU_BULLET2_PATH ":/res/bullet/reimu_bullet2.png"
#define REIMU_BULLET3_PATH ":/res/bullet/reimu_bullet3.png"

#define MARISA_BULLET1_PATH ":/res/bullet/marisa_bullet1.png"
#define MARISA_BULLET2_PATH ":/res/bullet/marisa_bullet2.png"
#define MARISA_BULLET3_PATH ":/res/bullet/marisa_bullet3.png"

#define SAKUYA_BULLET1_PATH ":/res/bullet/sakuya_bullet1.png"
#define SAKUYA_BULLET2_PATH ":/res/bullet/sakuya_bullet2.png"
#define SAKUYA_BULLET3_PATH ":/res/bullet/sakuya_bullet3.png"

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
// ęæåč““å¾č·Æå¾
#define REIMU_LASER_PATH ":/res/bullet/reimu_laser.png"
#define MARISA_LASER_PATH ":/res/bullet/marisa_laser.png"
#define SAKUYA_LASER_PATH ":/res/bullet/sakuya_laser.png"
#define YOUMU_LASER_PATH ":/res/bullet/youmu_laser.png"
#define EIRIN_LASER_PATH ":/res/bullet/eirin_laser.png"
#define KAGUYA_LASER_PATH ":/res/bullet/kaguya_laser.png"
#define ENEMY_LASER_PATH ":/res/bullet/enemy_laser.png"
#define DEFAULT_LASER_PATH ":/res/bullet/default_laser.png"

// å¶ä»č““å¾č·Æå¾

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

#define MUSIC_SOURCE ":/res/MUSIC/th08_00.mid" // th08_00.mid ~ th08_20.mid, čæęäøäŗ.wav ęē„

// ęøøęå°å¾éē½®
#define GAME_WIDTH 600  // ęøøęēŖå£å®½åŗ¦
#define GAME_HEIGHT 900 // ęøøęēŖå£é«åŗ¦
#define GAME_TITLE "äøę¹ę°øå¤ę" // ę é¢

// č§č²ē¢°ęå°ŗåÆøéē½®
#define ROLE_COLLISION_WIDTH 48   // č§č²å®½åŗ¦
#define ROLE_COLLISION_HEIGHT 64 // č§č²é«åŗ¦

// Player/Enemy å­å¼¹ēøå³
#define MAX_BULLETS 200 // ęå¤§å­å¼¹ę°ééē½®
#define BULLET_NUM 60   // PLAYERå¼¹å£äø­å­å¼¹ę»ę°
#define BULLET_NUM_ENEMY 120 // ENEMYå¼¹å£äø­å­å¼¹ę»ę°

// Playerę°å¼éē½®
#define INIT_PLAYER_LIFE 3  // čŖęŗåå§ēå½å¼
#define INIT_PLAYER_SPELL 3 // čŖęŗåå§ē¬¦å”ę§½
#define MAX_PLAYER_LIFE 8 // čŖęŗęå¤§ēå½å¼
#define MAX_PLAYER_SPELL 8 // čŖęŗęå¤§ē¬¦å”ę§½
#define PLAYER_SHOOT_INTERVAL 10 // čŖęŗå°å»é“é

// Bossē¢°ęå°ŗåÆøéē½®
#define BOSS_COLLISION_WIDTH 144 // Bossē¢°ęē©å½¢å®½åŗ¦
#define BOSS_COLLISION_HEIGHT 192 // Bossē¢°ęē©å½¢é«åŗ¦

// Bossę°å¼éē½®
#define BOSS_LIFE 80 // Bossåå§ēå½å¼
#define BOSS_SHOOT_INTERVAL1 15 // Bossäøé¶ę®µå°å»é“é
#define BOSS_SHOOT_INTERVAL2 5 // Bossäŗé¶ę®µå°å»é“é
#define BOSS_SHOOT_INTERVAL3 10 // Bossäøé¶ę®µå°å»é“é
#define BOSS_KAGUYA_SHOOT_INTERVAL1 10 // Boss Kaguya äøé¶ę®µå°å»é“é
#define BOSS_KAGUYA_SHOOT_INTERVAL2 8 // Boss Kaguya äŗé¶ę®µå°å»é“é
#define BOSS_KAGUYA_SHOOT_INTERVAL3 12 // Boss Kaguya äøé¶ę®µå°å»é“é

// ęęŗéē½®ę°ę® 
#define ENEMY_SPEED 4  // ęęŗē§»åØéåŗ¦
#define ENEMY_NUM   20  // ęęŗę»ę°é
#define ENEMY_INTERVAL  100  // ęęŗåŗåŗę¶é“é“é
#define ENEMY_LIFE 2 // ęęŗēå½å¼

// ęęŗē¢°ęå°ŗåÆøéē½®
#define ENEMY_COLLISION_WIDTH 48 // ęęŗē¢°ęē©å½¢å®½åŗ¦
#define ENEMY_COLLISION_HEIGHT 64 // ęęŗē¢°ęē©å½¢é«åŗ¦

// ęęēē§»åØéåŗ¦äæ”ęÆ
#define SHIFTED_PLAYER_SPEED 8 // ē©å®¶å éē§»åØéåŗ¦
#define NORMAL_PLAYER_SPEED 4 // ē©å®¶ę®éē§»åØéåŗ¦
#define PLAYER_REIMU_BULLET_SPEED 10 // ē©å®¶Reimuå­å¼¹ē§»åØéåŗ¦
#define PLAYER_MARISA_BULLET_SPEED 8 // ē©å®¶Marisaå­å¼¹ē§»åØéåŗ¦
#define BOSS_BULLET_SPEED 10 // BOSSę®éå­å¼¹ē§»åØéåŗ¦

// ęęēå­å¼¹å°ŗåÆøäæ”ęÆ
#define PLAYER_BULLET_WIDTH 16 // ē©å®¶å­å¼¹å®½åŗ¦
#define PLAYER_BULLET_HEIGHT 16 // ē©å®¶å­å¼¹é«åŗ¦

// ęæåäæ”ęÆ
#define MAX_LASERS 16 // ęå¤§ęæåę°é

#endif // CONFIG_H
