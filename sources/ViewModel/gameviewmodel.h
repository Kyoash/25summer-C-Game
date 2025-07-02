// gameviewmodel.h
#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#include <QObject>
#include "../model/gamemodel.h"

class GameViewModel : public QObject
{
    Q_OBJECT
public:
    explicit GameViewModel(GameModel *model, QObject *parent = nullptr);

    // 游戏控制
    void initGame(const RoleType& role); // 修改initGame接口，添加角色参数
    void startGame();

    // 玩家控制
    void setMoveLeft(bool move);
    void setMoveRight(bool move);
    void setMoveUp(bool move);
    void setMoveDown(bool move);
    void setShooting(bool shooting);
    void setSpeedShift(bool shift);
    void toggleCollisionBoxes();
    void setSpell(bool spell);

    // 游戏状态访问
    bool gameOver() const;
    bool showCollisionBoxes() const;
    int heroLife() const;

    bool speedShift() const;
    bool shooting() const;
    bool isPaused() const { return false; }

    // 游戏元素访问
    std::pair<QPixmap*, std::pair<int, int>>& getGamePixmap1();
    std::pair<QPixmap*, std::pair<int, int>>& getHero();
    std::pair<QPixmap*, std::pair<int, int>>& getBoss();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getEnemys();

    // QPixmap& getHeroPixmap();
    // std::pair<int, int> getHeroPosition();
    // QPixmap& getBossPixmap();
    // std::vector<QPixmap>& getEnemysPixmap();
    // std::pair<int, int> getBossPosition();
    // std::vector<std::pair<int, int>> getEnemysPosition(); // pending for enemy...

    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getHeroBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getBossBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getEnemyBullets(); // pending for enemy...
    //Bomb* bombs() { return m_model->bombs(); }

    // 添加状态访问接口
    int getScore() const;         // 返回当前得分
    int getHiScore() const;       // 返回当前得分
    int getLifeCount() const;     // 返回当前生命数
    int getBombCount() const;     // 返回当前炸弹数
    int getGrazeCount() const;    // 返回当前擦弹数
    float getPower() const;       // 返回当前能量值

signals:
    void updateView();
    void gameLoaded();

private:
    GameModel *m_model;

    RoleType m_selectedRole = PLAYER_REIMU;
    RoleType m_currentBoss = BOSS_EIRIN;
};

#endif // GAMEVIEWMODEL_H
