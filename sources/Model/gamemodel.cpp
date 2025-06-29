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
}

GameModel::~GameModel() {}

void GameModel::startGame()
{
    m_gameTimer.start(GAME_RATE);
}

void GameModel::initGame()
{
    m_gameOver = false;
    m_showCollisionBoxes = false;

}

void GameModel::updateGameState()
{
    updatePositions();
    emit updateView();
}

void GameModel::updatePositions()
{
    // 根据加速状态选择移动速度
    int currentSpeed = m_speedShift ? SHIFTED_SPEED : NORMAL_SPEED;

    // 添加键盘控制的飞机移动
    bool positionChanged = false;
    if (m_moveLeft) {
        m_reimu.m_X -= currentSpeed;
        if (m_reimu.m_X < 0) m_reimu.m_X = 0;
        positionChanged = true;
    }
    if (m_moveRight) {
        m_reimu.m_X += currentSpeed;
        // 限制不能越过游戏区域边界
        if (m_reimu.m_X > PLAY_AREA_WIDTH - m_hero.m_Rect.width()) {
            m_reimu.m_X = PLAY_AREA_WIDTH - m_hero.m_Rect.width();
        }
        positionChanged = true;
    }
    if (m_moveUp) {
        m_reimu.m_Y -= currentSpeed;
        if (m_reimu.m_Y < 0) m_reimu.m_Y = 0;
        positionChanged = true;
    }
    if (m_moveDown) {
        m_reimu.m_Y += currentSpeed;
        if (m_reimu.m_Y > GAME_HEIGHT - m_reimu.m_Rect.height()) {
            m_reimu.m_Y = GAME_HEIGHT - m_reimu.m_Rect.height();
        }
        positionChanged = true;
    }

    // 更新位置
    if (positionChanged) {
        m_reimu.setPosition(m_reimu.m_X, m_reimu.m_Y);
    }

    // 发射子弹

    // 更新自机子弹位置

    // 更新敌机位置和子弹

    // 更新爆炸效果

}
