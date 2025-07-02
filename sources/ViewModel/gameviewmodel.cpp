#include "gameviewmodel.h"

// 静态变量用于返回引用（避免返回临时变量）
static std::pair<QPixmap*, std::pair<int, int>> dummyPixmapPair(nullptr, {0,0});
static std::vector<std::pair<QPixmap*, std::pair<int, int>>> dummyVector;

static std::pair<QPixmap*, std::pair<int, int>> gamePixmap1Pair(nullptr, {0,0});
static std::pair<QPixmap*, std::pair<int, int>> heroPair(nullptr, {0,0});
static std::pair<QPixmap*, std::pair<int, int>> bossPair(nullptr, {0,0});
std::vector<std::pair<QPixmap*, std::pair<int, int>>> heroBulletsVector;
std::vector<std::pair<QPixmap*, std::pair<int, int>>> bossBulletsVector;



GameViewModel::GameViewModel(GameModel *model, QObject *parent)
    : QObject(parent), m_model(model)
{
    // 构造函数初始化
    connect(m_model, &GameModel::updateView, this, &GameViewModel::updateView);
}

// 游戏控制
void GameViewModel::initGame(const RoleType& role) {
    switch(role) {
    case PLAYER_REIMU:
        m_selectedRole = PLAYER_REIMU;
        break;
    case PLAYER_MARISA:
        m_selectedRole = PLAYER_MARISA;
        break;
    default:
        m_selectedRole = PLAYER_REIMU;
        break;
    }
    m_model->initGame(m_selectedRole);
}

void GameViewModel::startGame() {
    m_model->startGame();
    emit gameLoaded();
}

// 玩家控制
void GameViewModel::setMoveLeft(bool move) { m_model->setMoveLeft(move); }
void GameViewModel::setMoveRight(bool move) { m_model->setMoveRight(move); }
void GameViewModel::setMoveUp(bool move) { m_model->setMoveUp(move); }
void GameViewModel::setMoveDown(bool move) { m_model->setMoveDown(move); }
void GameViewModel::setShooting(bool shooting) { m_model->setShooting(shooting); }
void GameViewModel::setSpeedShift(bool shift) { m_model->setSpeedShift(shift); }
void GameViewModel::setSpell(bool spell) { m_model->setSpell(spell); }
void GameViewModel::toggleCollisionBoxes() { }

// 游戏状态访问
bool GameViewModel::gameOver() const { return false; }
bool GameViewModel::showCollisionBoxes() const { return false; }
int GameViewModel::heroLife() const { return 0; }
bool GameViewModel::speedShift() const { return false; }
bool GameViewModel::shooting() const { return false; }

// 游戏元素访问
std::pair<QPixmap*, std::pair<int, int>>& GameViewModel::getGamePixmap1() {
    gamePixmap1Pair = std::make_pair(&(m_model->map().m_map1),
                                     std::make_pair(m_model->map().m_map1_posX, m_model->map().m_map1_posY));
    return gamePixmap1Pair;
}

std::pair<QPixmap*, std::pair<int, int>>& GameViewModel::getHero() {
    switch(m_model->Now_Role()) {
    case PLAYER_REIMU:
        heroPair = std::make_pair(&(m_model->reimu().m_Role),
                                  std::make_pair(m_model->reimu().m_X, m_model->reimu().m_Y));
        break;
    case PLAYER_MARISA:
        heroPair = std::make_pair(&(m_model->marisa().m_Role),
                                  std::make_pair(m_model->marisa().m_X, m_model->marisa().m_Y));
        break;
    default:
        return dummyPixmapPair;
        break;
    }

    return heroPair;
}

std::pair<QPixmap*, std::pair<int, int>>& GameViewModel::getBoss() {
    switch(m_model->Now_Boss()) {
    case BOSS_EIRIN:
        bossPair = std::make_pair(&(m_model->bosseirin().m_Role),
                                  std::make_pair(m_model->bosseirin().m_X, m_model->bosseirin().m_Y));
        break;
    case BOSS_KAGUYA:
        bossPair = std::make_pair(&(m_model->bosskaguya().m_Role),
                                  std::make_pair(m_model->bosskaguya().m_X, m_model->bosskaguya().m_Y));
        break;
    // case BOSS_SAKUYA:
    //     bossPair = std::make_pair(&(m_model->bosssakuya().m_Role),
    //                               std::make_pair(m_model->bosssakuya().m_X, m_model->bosssakuya().m_Y));
    //     break;
    // case BOSS_YOUMU:
    //     bossPair = std::make_pair(&(m_model->bossyoumu().m_Role),
    //                               std::make_pair(m_model->bossyoumu().m_X, m_model->bossyoumu().m_Y));
    //     break;
    default:
        return dummyPixmapPair;
        break;
    }

    return bossPair;
}

std::vector<std::pair<QPixmap*, std::pair<int, int>>>& GameViewModel::getEnemys() {
    return dummyVector;
}

std::vector<std::pair<QPixmap*, std::pair<int, int>>>& GameViewModel::getHeroBullets() {
    heroBulletsVector.clear();
    std::pair<QPixmap*, std::pair<int, int>> tmp_pair;
    switch(m_model->Now_Role()) {
    case PLAYER_REIMU:
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->reimu().m_firstBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->reimu().m_firstBullets[i].m_Bullet),
                                          std::make_pair(m_model->reimu().m_firstBullets[i].m_X,
                                                         m_model->reimu().m_firstBullets[i].m_Y));
                heroBulletsVector.push_back(tmp_pair);
            }
        }
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->reimu().m_secondBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->reimu().m_secondBullets[i].m_Bullet),
                                          std::make_pair(m_model->reimu().m_secondBullets[i].m_X,
                                                         m_model->reimu().m_secondBullets[i].m_Y));
                heroBulletsVector.push_back(tmp_pair);
            }
        }

        break;
    case PLAYER_MARISA:
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->marisa().m_firstBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->marisa().m_firstBullets[i].m_Bullet),
                                          std::make_pair(m_model->marisa().m_firstBullets[i].m_X,
                                                         m_model->marisa().m_firstBullets[i].m_Y));
                heroBulletsVector.push_back(tmp_pair);
            }
        }
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->marisa().m_secondBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->marisa().m_secondBullets[i].m_Bullet),
                                          std::make_pair(m_model->marisa().m_secondBullets[i].m_X,
                                                         m_model->marisa().m_secondBullets[i].m_Y));
                heroBulletsVector.push_back(tmp_pair);
            }
        }
        break;
    default:
        return dummyVector;
        break;
    }

    return heroBulletsVector;
}

std::vector<std::pair<QPixmap*, std::pair<int, int>>>& GameViewModel::getBossBullets() {
    bossBulletsVector.clear();
    std::pair<QPixmap*, std::pair<int, int>> tmp_pair;
    switch(m_model->Now_Boss()) {
    case BOSS_EIRIN:
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->bosseirin().m_firstBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->bosseirin().m_firstBullets[i].m_Bullet),
                                          std::make_pair(m_model->bosseirin().m_firstBullets[i].m_X,
                                                         m_model->bosseirin().m_firstBullets[i].m_Y));
                bossBulletsVector.push_back(tmp_pair);
            }
        }
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->bosseirin().m_secondBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->bosseirin().m_secondBullets[i].m_Bullet),
                                          std::make_pair(m_model->bosseirin().m_secondBullets[i].m_X,
                                                         m_model->bosseirin().m_secondBullets[i].m_Y));
                bossBulletsVector.push_back(tmp_pair);
            }
        }

        break;
    case BOSS_KAGUYA:
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->bosskaguya().m_firstBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->bosskaguya().m_firstBullets[i].m_Bullet),
                                          std::make_pair(m_model->bosskaguya().m_firstBullets[i].m_X,
                                                         m_model->bosskaguya().m_firstBullets[i].m_Y));
                bossBulletsVector.push_back(tmp_pair);
            }
        }
        for(int i = 0; i < MAX_BULLETS; i++)
        {
            if(!m_model->bosskaguya().m_secondBullets[i].m_Free){
                tmp_pair = std::make_pair(&(m_model->bosskaguya().m_secondBullets[i].m_Bullet),
                                          std::make_pair(m_model->bosskaguya().m_secondBullets[i].m_X,
                                                         m_model->bosskaguya().m_secondBullets[i].m_Y));
                bossBulletsVector.push_back(tmp_pair);
            }
        }
        break;
    default:
        return dummyVector;
        break;
    }

    return bossBulletsVector;
}

std::vector<std::pair<QPixmap*, std::pair<int, int>>>& GameViewModel::getEnemyBullets() {
    return dummyVector;
}

// 实现状态接口（占位实现）
int GameViewModel::getScore() const { return 114514; }
int GameViewModel::getHiScore() const { return 1919810; } // 返回最高分
int GameViewModel::getLifeCount() const {
    switch(m_model->Now_Role()) {
    case PLAYER_REIMU:
        return m_model->reimu().m_life;
        break;
    case PLAYER_MARISA:
        return m_model->marisa().m_life;
        break;
    default:
        return 6;
        break;
    }
}

int GameViewModel::getBombCount() const {
    switch(m_model->Now_Role()) {
    case PLAYER_REIMU:
        return m_model->reimu().m_spell;
        break;
    case PLAYER_MARISA:
        return m_model->marisa().m_spell;
        break;
    default:
        return 7;
        break;
    }
}
int GameViewModel::getGrazeCount() const { return 114; }
float GameViewModel::getPower() const { return 5.14f; }
