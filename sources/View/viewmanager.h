#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QStackedWidget>
#include "mainmenuview.h"
#include "gameview.h"
#include "roleselectview.h"
#include "pauseview.h"
#include "saveview.h"
#include "loadingview.h"

class ViewManager : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewManager(QWidget *parent = nullptr);
    ~ViewManager();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void showMainMenu();
    void startGame();
    void showScore();
    void showSettings();
    void quitGame();

    void showRoleSelectView();
    // 添加带角色参数的新槽函数
    void handleRoleSelected(const RoleType& role);

    void showPauseMenu();
    void handleSaveSlot(int slot);
    void handleLoadSlot(int slot);
    void resumeGame();

private:
    MainMenuView *m_mainMenuView;
    RoleSelectView *m_roleSelectView;
    LoadingView *m_loadingView;
    GameView *m_gameView;
    // ScoreView *m_scoreView; // 分数查看界面

    PauseView *m_pauseView;
    SaveView *m_saveView;
    SaveView *m_loadView;
    int m_currentGameSlot = 0;

    RoleType m_selectedRole;
};

#endif // VIEWMANAGER_H
