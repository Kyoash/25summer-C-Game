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
    //初始化追踪弹目标刷新计数器
    Count_Bullets_Refresh = 0;
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
    m_paused = false;
    //初始化角色及关卡数
    m_Now_Role = role;
    m_Now_Boss = BOSS_EIRIN;
    m_Stage = 1;
    m_enemyRecorder = 0;
    //初始化追踪弹目标刷新计数器
    Count_Bullets_Refresh = 0;
}

void GameModel::updateGameState()
{
    updatePositions();
    collisionDetection();
    emit updateView();
}

void GameModel::updatePositions()
{
    //更新追踪弹目标刷新计数器
    Count_Bullets_Refresh++;
    if (Count_Bullets_Refresh >= updateTargetRate)
        Count_Bullets_Refresh = 0;
    // 根据加速状态选择移动速度
    int currentSpeed = m_speedShift ? SHIFTED_PLAYER_SPEED : NORMAL_PLAYER_SPEED;

    // 追踪弹目标
    int Now_Role_x;
    int Now_Role_y;
    int Now_Boss_x;
    int Now_Boss_y;

    // 确定当前操纵角色位置
    // 发射子弹
    int x_temp,y_temp;
    switch(m_Now_Role){
    case PLAYER_REIMU:
        m_reimu.shoot();
        x_temp = m_reimu.m_X;
        y_temp = m_reimu.m_Y;
        Now_Role_x = m_reimu.m_X;
        Now_Role_y = m_reimu.m_Y;
        break;
    case PLAYER_MARISA:
        m_marisa.shoot();
        x_temp = m_marisa.m_X;
        y_temp = m_marisa.m_Y;
        Now_Role_x = m_marisa.m_X;
        Now_Role_y = m_marisa.m_Y;
        break;
    default:
        m_reimu.shoot();
        x_temp = m_reimu.m_X;
        y_temp = m_reimu.m_Y;
        Now_Role_x = m_reimu.m_X;
        Now_Role_y = m_reimu.m_Y;
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
            m_marisa.setPosition(x_temp, y_temp);
            break;
        default:
            m_reimu.setPosition(x_temp, y_temp);
            break;
        }
    }

    // 更新Boss子弹位置，更新boss位置，发射子弹
    switch(m_Now_Boss){
    /*
    case BOSS_SAKUYA:
        m_boss_sakuya.SetPlayerPosition(Now_Role_x,Now_Role_y);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_boss_sakuya.m_firstBullets[i].m_Free) {
                m_boss_sakuya.m_firstBullets[i].updatePosition();
                // m_boss_sakuya.m_firstBullets[i].m_Free = checkBulletsOut(m_boss_sakuya.m_firstBullets[i].m_X,m_boss_sakuya.m_firstBullets[i].m_Y,m_boss_sakuya.m_firstBullets[i].m_Rect.width(),m_boss_sakuya.m_firstBullets[i].m_Rect.height());
            }
            if (!m_boss_sakuya.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_boss_sakuya.m_secondBullets[i].targetX = Now_Role_x;
                    m_boss_sakuya.m_secondBullets[i].targetY = Now_Role_y;
                }
                m_boss_sakuya.m_secondBullets[i].updatePosition();
                // m_boss_sakuya.m_secondBullets[i].m_Free = checkBulletsOut(m_boss_sakuya.m_secondBullets[i].m_X,m_boss_sakuya.m_secondBullets[i].m_Y,m_boss_sakuya.m_secondtBullets[i].m_Rect.width(),m_boss_sakuya.m_secondBullets[i].m_Rect.height());
            }
        }
        m_boss_sakuya.updatePosition();
        m_boss_sakuya.shoot();
        Now_Boss_x = m_boss_sakuya.m_X;
        Now_Boss_y = m_boss_sakuya.m_Y;
        break;
    case BOSS_YOUMU:
        m_boss_youmu.SetPlayerPosition(Now_Role_x,Now_Role_y);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_boss_youmu.m_firstBullets[i].m_Free) {
                m_boss_youmu.m_firstBullets[i].updatePosition();
                // m_boss_youmu.m_firstBullets[i].m_Free = checkBulletsOut(m_boss_youmu.m_firstBullets[i].m_X,m_boss_youmu.m_firstBullets[i].m_Y,m_boss_youmu.m_firstBullets[i].m_Rect.width(),m_boss_youmu.m_firstBullets[i].m_Rect.height());
            }
            if (!m_boss_youmu.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_boss_youmu.m_secondBullets[i].targetX = Now_Role_x;
                    m_boss_youmu.m_secondBullets[i].targetY = Now_Role_y;
                }
                m_boss_youmu.m_secondBullets[i].updatePosition();
                // m_boss_youmu.m_secondBullets[i].m_Free = checkBulletsOut(m_boss_youmu.m_secondBullets[i].m_X,m_boss_youmu.m_secondBullets[i].m_Y,m_boss_youmu.m_secondtBullets[i].m_Rect.width(),m_boss_youmu.m_secondBullets[i].m_Rect.height());
            }
        }
        m_boss_youmu.updatePosition();
        m_boss_youmu.shoot();
        Now_Boss_x = m_boss_youmu.m_X;
        Now_Boss_y = m_boss_youmu.m_Y;
        break;
*/
    case BOSS_EIRIN:
        m_boss_eirin.SetPlayerPosition(Now_Role_x,Now_Role_y);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_boss_eirin.m_firstBullets[i].m_Free) {
                m_boss_eirin.m_firstBullets[i].updatePosition();
                // m_boss_eirin.m_firstBullets[i].m_Free = checkBulletsOut(m_boss_eirin.m_firstBullets[i].m_X,m_boss_eirin.m_firstBullets[i].m_Y,m_boss_eirin.m_firstBullets[i].m_Rect.width(),m_boss_eirin.m_firstBullets[i].m_Rect.height());
            }
            if (!m_boss_eirin.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_boss_eirin.m_secondBullets[i].targetX = Now_Role_x;
                    m_boss_eirin.m_secondBullets[i].targetY = Now_Role_y;
                }
                m_boss_eirin.m_secondBullets[i].updatePosition();
                // m_boss_eirin.m_secondBullets[i].m_Free = checkBulletsOut(m_boss_eirin.m_secondBullets[i].m_X,m_boss_eirin.m_secondBullets[i].m_Y,m_boss_eirin.m_secondtBullets[i].m_Rect.width(),m_boss_eirin.m_secondBullets[i].m_Rect.height());
            }
        }
        m_boss_eirin.updatePosition();
        m_boss_eirin.shoot();
        Now_Boss_x = m_boss_eirin.m_X;
        Now_Boss_y = m_boss_eirin.m_Y;
        break;
    case BOSS_KAGUYA:
        m_boss_kaguya.SetPlayerPosition(Now_Role_x,Now_Role_y);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_boss_kaguya.m_firstBullets[i].m_Free) {
                m_boss_kaguya.m_firstBullets[i].updatePosition();
                // m_boss_kaguya.m_firstBullets[i].m_Free = checkBulletsOut(m_boss_kaguya.m_firstBullets[i].m_X,m_boss_kaguya.m_firstBullets[i].m_Y,m_boss_kaguya.m_firstBullets[i].m_Rect.width(),m_boss_kaguya.m_firstBullets[i].m_Rect.height());
            }
            if (!m_boss_kaguya.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_boss_kaguya.m_secondBullets[i].targetX = Now_Role_x;
                    m_boss_kaguya.m_secondBullets[i].targetY = Now_Role_y;
                }
                m_boss_kaguya.m_secondBullets[i].updatePosition();
                // m_boss_kaguya.m_secondBullets[i].m_Free = checkBulletsOut(m_boss_kaguya.m_secondBullets[i].m_X,m_boss_kaguya.m_secondBullets[i].m_Y,m_boss_kaguya.m_secondtBullets[i].m_Rect.width(),m_boss_kaguya.m_secondBullets[i].m_Rect.height());
            }
        }
        m_boss_kaguya.updatePosition();
        m_boss_kaguya.shoot();
        Now_Boss_x = m_boss_kaguya.m_X;
        Now_Boss_y = m_boss_kaguya.m_Y;
        break;
    default:
        m_boss_eirin.SetPlayerPosition(Now_Role_x,Now_Role_y);
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_boss_eirin.m_firstBullets[i].m_Free) {
                m_boss_eirin.m_firstBullets[i].updatePosition();
                // m_boss_eirin.m_firstBullets[i].m_Free = checkBulletsOut(m_boss_eirin.m_firstBullets[i].m_X,m_boss_eirin.m_firstBullets[i].m_Y,m_boss_eirin.m_firstBullets[i].m_Rect.width(),m_boss_eirin.m_firstBullets[i].m_Rect.height());
            }
            if (!m_boss_eirin.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_boss_eirin.m_secondBullets[i].targetX = Now_Role_x;
                    m_boss_eirin.m_secondBullets[i].targetY = Now_Role_y;
                }
                m_boss_eirin.m_secondBullets[i].updatePosition();
                // m_boss_eirin.m_secondBullets[i].m_Free = checkBulletsOut(m_boss_eirin.m_secondBullets[i].m_X,m_boss_eirin.m_secondBullets[i].m_Y,m_boss_eirin.m_secondtBullets[i].m_Rect.width(),m_boss_eirin.m_secondBullets[i].m_Rect.height());
            }
        }
        m_boss_eirin.updatePosition();
        m_boss_eirin.shoot();
        Now_Boss_x = m_boss_eirin.m_X;
        Now_Boss_y = m_boss_eirin.m_Y;
        break;
    }

    // 更新自机子弹位置
    switch(m_Now_Role){
    case PLAYER_REIMU:
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_reimu.m_firstBullets[i].m_Free) {
                m_reimu.m_firstBullets[i].updatePosition();
                // m_reimu.m_firstBullets[i].m_Free = checkBulletsOut(m_reimu.m_firstBullets[i].m_X,m_reimu.m_firstBullets[i].m_Y,m_reimu.m_firstBullets[i].m_Rect.width(),m_reimu.m_firstBullets[i].m_Rect.height());
            }
            if (!m_reimu.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_reimu.m_secondBullets[i].targetX = Now_Boss_x;
                    m_reimu.m_secondBullets[i].targetY = Now_Boss_y;
                }
                m_reimu.m_secondBullets[i].updatePosition();
                // m_reimu.m_secondBullets[i].m_Free = checkBulletsOut(m_reimu.m_secondBullets[i].m_X,m_reimu.m_secondBullets[i].m_Y,m_reimu.m_secondtBullets[i].m_Rect.width(),m_reimu.m_secondBullets[i].m_Rect.height());
            }
        }
        break;
    case PLAYER_MARISA:
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_marisa.m_firstBullets[i].m_Free) {
                m_marisa.m_firstBullets[i].updatePosition();
                // m_marisa.m_firstBullets[i].m_Free = checkBulletsOut(m_marisa.m_firstBullets[i].m_X,m_marisa.m_firstBullets[i].m_Y,m_marisa.m_firstBullets[i].m_Rect.width(),m_marisa.m_firstBullets[i].m_Rect.height());
            }
            if (!m_marisa.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_marisa.m_secondBullets[i].targetX = Now_Boss_x;
                    m_marisa.m_secondBullets[i].targetY = Now_Boss_y;
                }
                m_marisa.m_secondBullets[i].updatePosition();
                // m_marisa.m_secondBullets[i].m_Free = checkBulletsOut(m_marisa.m_secondBullets[i].m_X,m_marisa.m_secondBullets[i].m_Y,m_marisa.m_secondtBullets[i].m_Rect.width(),m_marisa.m_secondBullets[i].m_Rect.height());
            }
        }
        break;
    default:
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!m_reimu.m_firstBullets[i].m_Free) {
                m_reimu.m_firstBullets[i].updatePosition();
                // m_reimu.m_firstBullets[i].m_Free = checkBulletsOut(m_reimu.m_firstBullets[i].m_X,m_reimu.m_firstBullets[i].m_Y,m_reimu.m_firstBullets[i].m_Rect.width(),m_reimu.m_firstBullets[i].m_Rect.height());
            }
            if (!m_reimu.m_secondBullets[i].m_Free) {
                if(Count_Bullets_Refresh == 0){
                    m_reimu.m_secondBullets[i].targetX = Now_Boss_x;
                    m_reimu.m_secondBullets[i].targetY = Now_Boss_y;
                }
                m_reimu.m_secondBullets[i].updatePosition();
                // m_reimu.m_secondBullets[i].m_Free = checkBulletsOut(m_reimu.m_secondBullets[i].m_X,m_reimu.m_secondBullets[i].m_Y,m_reimu.m_secondtBullets[i].m_Rect.width(),m_reimu.m_secondBullets[i].m_Rect.height());
            }
        }
        break;
    }


    // 更新爆炸效果

}

void GameModel::changeStage(int next_stage){
    m_gameTimer.stop();
    int life_temp;
    switch(m_Now_Role){
    case PLAYER_REIMU:
        life_temp = m_reimu.m_life;
        break;
    case PLAYER_MARISA:
        life_temp = m_marisa.m_life;
        break;
    default:
        life_temp = m_reimu.m_life;
        break;
    }

    resetRoles();

    switch(m_Now_Role){
    case PLAYER_REIMU:
        m_reimu.m_life = life_temp;
        break;
    case PLAYER_MARISA:
        m_marisa.m_life = life_temp;
        break;
    default:
        m_reimu.m_life = life_temp;
        break;
    }

    switch(next_stage){
    case 1:
        m_Now_Boss = BOSS_EIRIN;
        break;
    case 2:
        m_Now_Boss = BOSS_KAGUYA;
        break;
    case 3:
        m_Now_Boss = BOSS_YOUMU;
        break;
    case 4:
        m_Now_Boss = BOSS_SAKUYA;
        break;
    default:
        m_Now_Boss = BOSS_EIRIN;
        break;
    }
}

void GameModel::pauseGame()
{
    if (!m_paused) {
        m_gameTimer.stop();
        m_paused = true;
        emit gamePaused(true);
    }
}

void GameModel::resumeGame()
{
    if (m_paused) {
        m_gameTimer.start(GAME_RATE);
        m_paused = false;
        emit gamePaused(false);
    }
}

void GameModel::resetRoles(){
    m_reimu.reset();
    m_marisa.reset();
    m_boss_eirin.reset();
    m_boss_kaguya.reset();
    //m_boss_youmu.reset();
    //m_boss_sakuya.reset();
}

void GameModel::resetGame(){
    m_gameTimer.stop();
    resetRoles();
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
    //初始化追踪弹目标刷新计数器
    Count_Bullets_Refresh = 0;
}

