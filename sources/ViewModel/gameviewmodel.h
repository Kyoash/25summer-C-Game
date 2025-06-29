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
    void initGame() {}
    void startGame() {}

    // 玩家控制
    void setMoveLeft(bool move);
    void setMoveRight(bool move);
    void setMoveDown(bool move);
    void setShooting(bool shooting);
    void setSpeedShift(bool shift);
    void toggleCollisionBoxes();

    // 游戏状态访问
    bool gameOver() const;
    bool showCollisionBoxes() const;
    int heroLife() const;

    bool speedShift() const;
    bool shooting() const;

    // 游戏元素访问
    QPixmap& getGamePixmap1();
    QPixmap& getHeroPixmap();
    std::pair<int, int> getHeroPosition();
    QPixmap& getBossPixmap();
    std::vector<QPixmap>& getEnemysPixmap();
    std::pair<int, int> getBossPosition();
    std::vector<std::pair<int, int>> getEnemysPosition(); // pending for enemy...
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getHeroBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getBossBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& getEnemyBullets(); // pending for enemy...
    //Bomb* bombs() { return m_model->bombs(); }

signals:
    void updateView();

private:
    GameModel *m_model;
};

#endif // GAMEVIEWMODEL_H
