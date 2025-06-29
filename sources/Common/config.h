#ifndef CONFIG_H
#define CONFIG_H

// 角色类型定义
enum RoleType {
	PLAYER_REIMU,  // 玩家
	PLAYER_MARISA, 
	BOSS_SAKURA, // 敌方Boss
	BOSS_YOUMU,
	BOSS_SEIRIN,
	BOSS_KAGUYA,
	NORMAL_ENEMY // 敌方普通敌机
};

// 所有的贴图路径配置在这里
#define REIMU_PATH ":/res/role/reimu.png" // Player 角色贴图
#define MARISA_PATH ":/res/role/marisa.png" // Player 角色贴图
#define SAKURA_PATH ":/res/role/sakura.png" // Boss 角色贴图
#define YOUMU_PATH ":/res/role/youmu.png" // Boss 角色贴图
#define SEIRIN_PATH ":/res/role/seirin.png" // Boss 角色贴图
#define KAGUYA_PATH ":/res/role/kaguya.png" // Boss 角色贴图
#define ENEMY_PATH ":/res/role/enemy.png" // 敌机贴图

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
#define PLAYER_BULLET_SPEED 10  // 玩家普通子弹移动速度

// 所有的子弹尺寸信息
#define PLAYER_BULLET_WIDTH 16 // 玩家子弹宽度
#define PLAYER_BULLET_HEIGHT 16 // 玩家子弹高度

#endif // CONFIG_H
