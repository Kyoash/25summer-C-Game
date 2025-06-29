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
#include "collisiondetect.h"
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

    // 游戏元素访问
    Map& map() { return m_map; }
    Reimu& reimu() { return m_reimu; }
    BossEirin& bosseirin() { return m_boss_eirin; }

    // 游戏控制
    void initGame();
    void startGame();

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

public slots:
    void updateGameState();

private:
    void updatePositions();

    // 游戏元素
    Map m_map;
    Reimu m_reimu;
    BossEirin m_boss_eirin;

    // 游戏状态
    bool m_gameOver = false;
    bool m_showCollisionBoxes = false;

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
