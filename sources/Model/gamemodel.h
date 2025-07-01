#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "../Common/config.h"
#include "role/role.h"
#include "role/reimu.h"
#include "role/marisa.h"
#include "role/bossyoumu.h"
#include "role/bosseirin.h"
#include "role/bosskaguya.h"
#include "role/bosssakuya.h"
#include "bullet/bullet.h"
#include "bullet/laser.h"
#include "bullet/spell.h"
#include "bomb.h"
#include "item.h"
#include "map.h"
#include "scoremanager.h"
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class GameModel : public QObject
{
    Q_OBJECT
public:
    GameModel(QObject *parent = nullptr);
    ~GameModel();

    // 游戏状态
    bool gameOver() const { return m_gameOver; }
    bool showCollisionBoxes() const { return m_showCollisionBoxes; }
    bool paused() const { return m_paused; }

    // 游戏元素访问
    Map& map() { return m_map; }
    Reimu& reimu() { return m_reimu; }
    Marisa& marisa() { return m_marisa; };
    BossYoumu& bossyoumu() { return m_boss_youmu; };
    BossSakuya& bosssakuya() { return m_boss_sakuya; };
    BossKaguya& bosskaguya() { return m_boss_kaguya; };
    BossEirin& bosseirin() { return m_boss_eirin; }
    RoleType& Now_Role() { return m_Now_Role; }
    RoleType& Now_Boss() { return m_Now_Boss; }
    int& Stage() { return m_Stage; }
    int& enemyRecorder() { return m_enemyRecorder; }

    // 游戏控制
    void initGame(RoleType role);
    void startGame();
    void pauseGame();//暂停游戏
    void resumeGame();//继续游戏
    void changeStage(int next_stage);//更换关卡

    //玩家控制
    void setMoveLeft(bool move) { m_moveLeft = move; }
    void setMoveRight(bool move) { m_moveRight = move; }
    void setMoveUp(bool move) { m_moveUp = move; }
    void setMoveDown(bool move) { m_moveDown = move; }
    void setShooting(bool shooting) { m_shooting = shooting; }
    void setSpeedShift(bool shift) { m_speedShift = shift; }
    void setSpell(bool spell) { m_spell = spell; }

signals:
    void updateView();
    void gamePaused(bool isPaused);

public slots:
    void updateGameState();

private:
    //刷新各个元素
    void updatePositions();
    //碰撞检测
    void collisionDetection();
    void collision_reimu_youmu();
    void collision_reimu_sakuya();
    void collision_reimu_kaguya();
    void collision_reimu_eirin();
    void collision_marisa_youmu();
    void collision_marisa_sakuya();
    void collision_marisa_kaguya();
    void collision_marisa_eirin();

    // 游戏元素
    Map m_map;
    Reimu m_reimu;
    Marisa m_marisa;
    BossYoumu m_boss_youmu;
    BossSakuya m_boss_sakuya;
    BossKaguya m_boss_kaguya;
    BossEirin m_boss_eirin;
    RoleType m_Now_Role = PLAYER_REIMU;
    RoleType m_Now_Boss = BOSS_EIRIN;
    int m_Stage = 1;//关卡
    int m_enemyRecorder = 0;//分数

    // 游戏状态
    bool m_gameOver = false;//游戏结束
    bool m_showCollisionBoxes = false;//显示碰撞箱
    bool m_paused = false;//游戏暂停

    // 控制状态
    bool m_moveLeft = false;
    bool m_moveRight = false;
    bool m_moveUp = false;
    bool m_moveDown = false;
    bool m_shooting = false;
    bool m_speedShift = false;
    bool m_spell = false;

    // 计时器
    QTimer m_gameTimer;
};

#endif // GAMEMODEL_H
