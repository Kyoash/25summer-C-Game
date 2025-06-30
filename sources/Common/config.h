#ifndef CONFIG_H
#define CONFIG_H

#define MAP_PATH ""
#define GAME_RATE 10

// 角色类型定义
enum RoleType {
    PLAYER_REIMU,  // 玩家
    PLAYER_MARISA,
    BOSS_SAKURA, // 敌方Boss
    BOSS_YOUMU,
    BOSS_EIRIN,
    BOSS_KAGUYA,
    NORMAL_ENEMY // 敌方普通敌机
};
enum BulletType {
    DEFAULT_BULLET,
    BULLET_TYPE1,
    BULLET_TYPE2
};

// 所有的贴图路径配置在这里
#define REIMU_PATH ":/res/role/reimu.png" // Player 角色贴图
#define MARISA_PATH ":/res/role/marisa.png" // Player 角色贴图
#define SAKURA_PATH ":/res/role/sakura.png" // Boss 角色贴图
#define YOUMU_PATH ":/res/role/youmu.png" // Boss 角色贴图
#define EIRIN_PATH ":/res/role/eirin.png" // Boss 角色贴图
#define KAGUYA_PATH ":/res/role/kaguya.png" // Boss 角色贴图
#define ENEMY_PATH ":/res/role/enemy.png" // 敌机贴图
#define SPELL_CIRCLE_SOURCE ":/res/ANM/ANM/etama/etama3.png"
#define ENEMY_BOSS_BULLET_1_SOURCE ":/res/ANM/ANM/etama/etama.png"
#define ENEMY_BOSS_BULLET_2_SOURCE ":/res/ANM/ANM/etama/etama6.png"

// 子弹贴图路径 - 每个角色有三种子弹类型，从1开始计数
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

#define MUSIC_SOURCE ":/res/MUSIC/th08_00.mid" // th08_00.mid ~ th08_20.mid, 还有一些.wav 暂略

// 游戏地图配置
#define GAME_WIDTH 600  // 游戏窗口宽度
#define GAME_HEIGHT 800 // 游戏窗口高度
#define GAME_TITLE "东方永夜抄" // 标题

// 角色碰撞尺寸配置
#define ROLE_COLLISION_WIDTH 48   // 角色宽度
#define ROLE_COLLISION_HEIGHT 64 // 角色高度

// Player/Enemy 子弹相关
#define MAX_BULLETS 200 // 最大子弹数量配置
#define BULLET_NUM 60   // PLAYER弹匣中子弹总数
#define BULLET_NUM_ENEMY 120 // ENEMY弹匣中子弹总数

// Player数值配置
#define INIT_PLAYER_LIFE 3  // 自机初始生命值
#define INIT_PLAYER_SPELL 3 // 自机初始符卡槽
#define MAX_PLAYER_LIFE 8 // 自机最大生命值
#define MAX_PLAYER_SPELL 8 // 自机最大符卡槽
#define PLAYER_SHOOT_INTERVAL 10 // 自机射击间隔

// Boss碰撞尺寸配置
#define BOSS_COLLISION_WIDTH 144 // Boss碰撞矩形宽度
#define BOSS_COLLISION_HEIGHT 192 // Boss碰撞矩形高度

// Boss数值配置
#define BOSS_LIFE 80 // Boss初始生命值
#define BOSS_SHOOT_INTERVAL1 15 // Boss一阶段射击间隔
#define BOSS_SHOOT_INTERVAL2 5 // Boss二阶段射击间隔
#define BOSS_SHOOT_INTERVAL3 10 // Boss三阶段射击间隔

// 敌机配置数据 
#define ENEMY_SPEED 4  // 敌机移动速度
#define ENEMY_NUM   20  // 敌机总数量
#define ENEMY_INTERVAL  100  // 敌机出场时间间隔
#define ENEMY_LIFE 2 // 敌机生命值

// 敌机碰撞尺寸配置
#define ENEMY_COLLISION_WIDTH 48 // 敌机碰撞矩形宽度
#define ENEMY_COLLISION_HEIGHT 64 // 敌机碰撞矩形高度

// 所有的移动速度信息
#define SHIFTED_PLAYER_SPEED 8 // 玩家加速移动速度
#define NORMAL_PLAYER_SPEED 4 // 玩家普通移动速度
#define PLAYER_REIMU_BULLET_SPEED 10 // 玩家Reimu子弹移动速度
#define PLAYER_MARISA_BULLET_SPEED 8 // 玩家Marisa子弹移动速度
#define BOSS_BULLET_SPEED 10 // BOSS普通子弹移动速度

// 所有的子弹尺寸信息
#define PLAYER_BULLET_WIDTH 16 // 玩家子弹宽度
#define PLAYER_BULLET_HEIGHT 16 // 玩家子弹高度

#endif // CONFIG_H
