#include "gamemodel.h"
#include <QRandomGenerator>

GameModel::GameModel(QObject *parent) : QObject(parent)
{
    connect(&m_gameTimer, &QTimer::timeout, this, &GameModel::updateGameState);
    // 初始化控制状态
    m_moveLeft = false;
    m_moveRight = false;
    m_moveUp = false;
    m_moveDown = false;
    m_shooting = false;
    m_speedShift = false;
    m_spell = false;
    //初始化角色及关卡数
    m_Now_Role = PLAYER_REIMU;
    m_Now_Boss = BOSS_EIRIN;
    m_Stage = 1;
    m_enemyRecorder = 0;
}

GameModel::~GameModel() {}

void GameModel::startGame()
{
    m_gameTimer.start(GAME_RATE);
}

void GameModel::initGame(RoleType role)
{
    //游戏状态
    m_gameOver = false;
    m_showCollisionBoxes = false;
    //初始化角色及关卡数
    m_Now_Role = role;
    m_Now_Boss = BOSS_EIRIN;
    m_Stage = 1;
    m_enemyRecorder = 0;
}

void GameModel::updateGameState()
{
    updatePositions();
    emit updateView();
}

void GameModel::updatePositions()
{
    // 根据加速状态选择移动速度
    int currentSpeed = m_speedShift ? SHIFTED_PLAYER_SPEED : NORMAL_PLAYER_SPEED;

    // 确定当前操纵角色
    // 发射子弹
    int x_temp,y_temp;
    switch(m_Now_Role){
    case PLAYER_REIMU:
        m_reimu.shoot();
        x_temp = m_reimu.m_X;
        y_temp = m_reimu.m_Y;
        break;
    case PLAYER_MARISA:
        m_marisa.shoot();
        x_temp = m_marisa.m_X;
        y_temp = m_marisa.m_Y;
        break;
    default:
        m_reimu.shoot();
        x_temp = m_reimu.m_X;
        y_temp = m_reimu.m_Y;
        break;
    }

    // 添加键盘控制的角色移动
    bool positionChanged = false;
    if (m_moveLeft) {
        x_temp -= currentSpeed;
        if (x_temp < 0) x_temp = 0;
        positionChanged = true;
    }
    if (m_moveRight) {
        x_temp += currentSpeed;
        // 限制不能越过游戏区域边界
        if (x_temp > GAME_WIDTH - m_reimu.m_Rect.width()) {
            x_temp = GAME_WIDTH - m_reimu.m_Rect.width();
        }
        positionChanged = true;
    }
    if (m_moveUp) {
        y_temp -= currentSpeed;
        if (y_temp < 0) y_temp = 0;
        positionChanged = true;
    }
    if (m_moveDown) {
        y_temp += currentSpeed;
        if (y_temp > GAME_HEIGHT - m_reimu.m_Rect.height()) {
            y_temp = GAME_HEIGHT - m_reimu.m_Rect.height();
        }
        positionChanged = true;
    }

    // 更新位置
    if (positionChanged) {
        switch(m_Now_Role){
        case PLAYER_REIMU:
            m_reimu.setPosition(x_temp, y_temp);
            break;
        case PLAYER_MARISA:
            m_reimu.setPosition(x_temp, y_temp);
            break;
        default:
            m_reimu.setPosition(x_temp, y_temp);
            break;
        }
    }

    // 更新自机子弹位置

    // 更新敌机位置和子弹
    switch(m_Now_Boss){
    case BOSS_SAKURA:
        m_boss_sakuya.updatePosition();
        m_boss_sakuya.shoot();
        break;
    case BOSS_YOUMU:
        m_boss_youmu.updatePosition();
        m_boss_youmu.shoot();
        break;
    case BOSS_EIRIN:
        m_boss_eirin.updatePosition();
        m_boss_eirin.shoot();
        break;
    case BOSS_KAGUYA:
        m_boss_kaguya.updatePosition();
        m_boss_kaguya.shoot();
        break;
    default:
        m_boss_eirin.updatePosition();
        m_boss_eirin.shoot();
        break;
    }


    // 更新爆炸效果

}
