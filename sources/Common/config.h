// #ifndef CONFIG_H
// #define CONFIG_H

// /********** 游戏配置数据 **********/
// #define GAME_WIDTH  (768 * 1)  // 宽度
// #define GAME_HEIGHT (768 * 1)  // 高度
// #define RIGHT_PANEL_WIDTH (256 * 1) // 右侧面板宽度
// #define PLAY_AREA_WIDTH (512 * 1)  // 游戏区域宽度
// #define GAME_TITLE "DongFangYongYe" // 标题

// #define GAME_RES_PATH  "./DongFang.rcc" // rcc文件路径

// #define GAME_ICON  ""

// // /********** 地图配置数据 **********/
// // #define MAP_PATH  "" // 地图图片路径
// // #define MAP_PATH_PANEL  "" // 地图图片路径
// // #define MAP_SCROLL_SPEED 2  // 地图滚动速度

// // #define GAME_RATE  10   // 刷新间隔，帧率 单位毫秒

// // /********** 飞机配置数据 **********/
// // #define HERO_PATH ""

// // /********** 子弹配置数据 **********/
// // #define BULLET_PATH ""   // 子弹图片路径
// // #define BULLET_SPEED 10  // 子弹移动速度

// // #define MAX_BULLETS 200 // 最大子弹数量配置
// // #define BULLET_NUM 50   // 弹匣中子弹总数
// // #define BULLET_INTERVAL 10 // 发射子弹时间间隔

// // /********** 敌机配置数据 **********/
// // #define ENEMY_PATH  ""  // 敌机资源图片
// // #define ENEMY_SPEED 4  // 敌机移动速度
// // #define ENEMY_NUM   20  // 敌机总数量
// // #define ENEMY_INTERVAL  100  // 敌机出场时间间隔
// // #define ENEMY_LIFE 3 // 敌机生命值

// // // 敌机子弹配置
// // #define ENEMY_BULLET_PATH ""   // 敌机子弹图片路径
// // #define ENEMY_BULLET_SPEED 3    // 敌机子弹速度
// // #define ENEMY_BULLET_NUM   200  // 敌机子弹总数量
// // #define ENEMY_SHOOT_INTERVAL 80 // 敌机发射子弹时间间隔

// // // 血条配置
// // #define HERO_LIFE 30  // 自机初始生命值
// // #define LIFE_BAR_WIDTH 200 // 血条宽度
// // #define LIFE_BAR_HEIGHT 20 // 血条高度

// // // 碰撞体积配置
// // #define HERO_COLLISION_WIDTH 10
// // #define HERO_COLLISION_HEIGHT 10
// // #define ENEMY_COLLISION_WIDTH 100
// // #define ENEMY_COLLISION_HEIGHT 100
// // #define BULLET_COLLISION_WIDTH 20
// // #define BULLET_COLLISION_HEIGHT 20
// // #define ENEMY_BULLET_COLLISION_WIDTH 20
// // #define ENEMY_BULLET_COLLISION_HEIGHT 20

// // /********** 爆炸配置数据 **********/
// // #define BOMB_PATH  ""   // 爆炸资源图片
// // #define BOMB_NUM  20     // 爆炸数量
// // #define BOMB_MAX  7      // 爆炸图片最大索引
// // #define BOMB_INTERVAL 20   // 爆炸切图时间间隔

// // /********** 音效配置数据 **********/
// // #define SOUND_BACKGROUND ""
// // #define SOUND_BOMB ""
// // #define SOUND_HIT  ""
// // #define SOUND_GAMEOVER ""

// // #define NORMAL_SPEED 8
// // #define SHIFTED_SPEED 4

// // // 调试模式配置
// // #define DEBUG_COLLISION_BOX 1 // 1为开启碰撞框显示，0为关闭

// // // 分数文件路径
// // #define SCORE_FILE ""

// // // 飞机类型定义
// // enum PlaneType {
// //     HERO_PLANE,
// //     ENEMY_PLANE
// // };

// // // 子弹类型定义
// // enum BulletType {
// //     HERO_BULLET,
// //     ENEMY_BULLET
// // };

// #define SPELL_CIRCLE_SOURCE ":/res/ANM/ANM/etama/etama3.png"
// #define ENEMY_BOSS_BULLET_1_SOURCE ":/res/ANM/ANM/etama/etama.png"
// #define ENEMY_BOSS_BULLET_2_SOURCE ":/res/ANM/ANM/etama/etama6.png"

// #define ITEM_SOURCE ":/res/ANM/ANM/etama/etama2.png"
// #define ASCII_SOURCE ":/res/ANM/ANM/ascii/ascii.png"
// #define LOADING_SOURCE ":/res/ANM/ANM/ascii/loading.png"
// #define PAUSE_SOURCE ":/res/ANM/ANM/ascii/pause.png"

// #define NAME_SOURCE ":/res/ANM/ANM/front/ename.png"
// #define LIFE_BOMB_SOURCE ":/res/ANM/ANM/front/front.png"

// #define PAINTING_REIMU_YUKARI_SOURCE ":/res/ANM/ANM/image/loading00.png"
// #define PAINTING_MARISA_ALICE_SOURCE ":/res/ANM/ANM/image/loading01.png"
// #define PAINTING_REIMU_SOURCE ":/res/ANM/ANM/image/loading00h.png"
// #define PAINTING_MARISA_SOURCE ":/res/ANM/ANM/image/loading01h.png"

// #define PLAYER_REIMU_SOURCE ":/res/ANM/ANM/player/player00.png"
// #define PLAYER_MARISA_SOURCE ":/res/ANM/ANM/player/player01.png"

// #define ENEMY_SOURCE ":/res/ANM/ANM/stgenm/enemy.png"
// #define BOSS_SAKUYA_SOURCE ":/res/ANM/ANM/stgenm/stg9enm_sk.png"
// #define BOSS_YOUMU_SOURCE ":/res/ANM/ANM/stgenm/stg9enm_ym.png"
// #define BOSS_EIRIN_SOURCE ":/res/ANM/ANM/stgenm/stg7enm.png"
// #define BOSS_KAGUYA_SOURCE ":/res/ANM/ANM/stgenm/stg7enm2.png"

// #define RESULT_PLAYER_SOURCE ":/res/ANM/ANM/result/result00.png"
// #define RESULT_DIFFICULTY_SOURCE ":/res/ANM/ANM/result/result01.png"
// #define RESULT_SCORE_SOURCE ":/res/ANM/ANM/result/result03.png"

// #define REIMU_YUKARI_SELECT_SOURCE ":/res/ANM/ANM/title/sl_pltxt0.png"
// #define MARISA_ALICE_SELECT_SOURCE ":/res/ANM/ANM/title/sl_pltxt1.png"
// #define MENU_OPTIONS_SOURCE ":/res/ANM/ANM/title/title01.png"
// #define MENU_BACKGROUND_SOURCE ":/res/ANM/ANM/title/title02.png"

// #define MUSIC_SOURCE ":/res/MUSIC/th08_00.mid" // th08_00.mid ~ th08_20.mid, 还有一些.wav 暂略

// #endif // CONFIG_H


#ifndef CONFIG_H
#define CONFIG_H

#define GAME_RATE 10

// 角色类型定义
enum RoleType {
    PLAYER_REIMU,  // 玩家
    PLAYER_MARISA,
    BOSS_SAKUYA, // 敌方Boss
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
enum LaserType {
    ROTATION_LASER,
    HORIZONTAL_LASER,
    VERTICAL_LASER
};

// 所有的贴图路径配置在这里
#define MAP_STAGE1_PATH ":/res/map/stagemap1.png"
#define MAP_STAGE2_PATH ":/res/map/stagemap2.png"
#define MAP_STAGE3_PATH ":/res/map/stagemap3.png"
#define MAP_STAGE4_PATH ":/res/map/stagemap4.png"
#define REIMU_PATH ":/res/role/reimu.png" // Player 角色贴图
#define MARISA_PATH ":/res/role/marisa.png" // Player 角色贴图
#define SAKUYA_PATH ":/res/role/sakuya.png" // Boss 角色贴图
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
// 激光贴图路径
#define REIMU_LASER_PATH ":/res/bullet/reimu_laser.png"
#define MARISA_LASER_PATH ":/res/bullet/marisa_laser.png"
#define SAKUYA_LASER_PATH ":/res/bullet/sakuya_laser.png"
#define YOUMU_LASER_PATH ":/res/bullet/youmu_laser.png"
#define EIRIN_LASER_PATH ":/res/bullet/eirin_laser.png"
#define KAGUYA_LASER_PATH ":/res/bullet/kaguya_laser.png"
#define ENEMY_LASER_PATH ":/res/bullet/enemy_laser.png"
#define DEFAULT_LASER_PATH ":/res/bullet/default_laser.png"

// 其他贴图路径

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
#define GAME_WIDTH 576  // 游戏窗口宽度
#define GAME_HEIGHT 864 // 游戏窗口高度
#define GAME_TITLE "东方永夜抄" // 标题

// 角色碰撞尺寸配置
#define ROLE_COLLISION_WIDTH 20   // 角色宽度
#define ROLE_COLLISION_HEIGHT 30 // 角色高度

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
#define BOSS_KAGUYA_SHOOT_INTERVAL1 15 // Boss Kaguya 一阶段射击间隔
#define BOSS_KAGUYA_SHOOT_INTERVAL2 8 // Boss Kaguya 二阶段射击间隔
#define BOSS_KAGUYA_SHOOT_INTERVAL3 15 // Boss Kaguya 三阶段射击间隔

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
#define PLAYER_REIMU_BULLET_SPEED (-10) // 玩家Reimu子弹移动速度
#define PLAYER_MARISA_BULLET_SPEED (-8) // 玩家Marisa子弹移动速度
#define BOSS_BULLET_SPEED 7 // BOSS普通子弹移动速度

// 所有的子弹尺寸信息
#define PLAYER_BULLET_WIDTH 16 // 玩家子弹宽度
#define PLAYER_BULLET_HEIGHT 16 // 玩家子弹高度

// 激光信息
#define MAX_LASERS 16 // 最大激光数量

// temp
#define GAME_RES_PATH  "./DongFang.rcc" // rcc文件路径
#define VIEW_WIDTH 768  // 游戏窗口宽度
#define VIEW_HEIGHT 768 // 游戏窗口高度

#endif // CONFIG_H
