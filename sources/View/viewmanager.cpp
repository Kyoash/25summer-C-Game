#include "viewmanager.h"
// #include <iostream>
// #include "../Viewmodel/gameviewmodel.h"
#include <QKeyEvent>
#include <QMessageBox>

ViewManager::ViewManager(QWidget *parent) :
    QStackedWidget(parent),
    m_loadingView(nullptr),
    m_selectedRole(PLAYER_REIMU)
{
    // 创建主菜单
    m_mainMenuView = new MainMenuView();
    addWidget(m_mainMenuView);

    // 游戏视图将在需要时创建
    m_gameView = nullptr;

    // 创建分数视图
    m_roleSelectView = new RoleSelectView();
    addWidget(m_roleSelectView);

    // 创建暂停菜单
    m_pauseView = new PauseView();
    m_pauseView->hide();

    // 连接信号
    connect(m_mainMenuView, &MainMenuView::newGameRequested, this, &ViewManager::showRoleSelectView);
    connect(m_mainMenuView, &MainMenuView::loadRequested, this, &ViewManager::showMainMenu); // 暂不实现
    connect(m_mainMenuView, &MainMenuView::scoreRequested, this, &ViewManager::showScore);
    connect(m_mainMenuView, &MainMenuView::settingRequested, this, &ViewManager::showSettings);
    connect(m_mainMenuView, &MainMenuView::quitRequested, this, &ViewManager::quitGame);

    // 修改角色选择信号连接
    connect(m_roleSelectView, &RoleSelectView::roleReimuSelected, this, [this]() {
        m_selectedRole = PLAYER_REIMU;
        startGame();
    });
    connect(m_roleSelectView, &RoleSelectView::roleMarisaSelected, this, [this]() {
        m_selectedRole = PLAYER_MARISA;
        startGame();
    });
    connect(m_roleSelectView, &RoleSelectView::backRequested, this, &ViewManager::showMainMenu);

    // 连接角色选择信号
    connect(m_roleSelectView, &RoleSelectView::roleSelected,
            this, &ViewManager::handleRoleSelected);

    // // 连接分数视图的信号
    // connect(m_ScoreView, &ScoreView::backRequested, this, &ViewManager::showMainMenu);

    connect(m_pauseView, &PauseView::resumeRequested, this, &ViewManager::resumeGame);

    connect(m_pauseView, &PauseView::saveRequested, this, [this]() {
        if (m_pauseView->m_isSubViewOpen) return; // 防止重复打开

        m_pauseView->m_isSubViewOpen = true;
        m_saveView = new SaveView(false, this);

        connect(m_saveView, &SaveView::slotSelected, this, &ViewManager::handleSaveSlot);
        connect(m_saveView, &SaveView::backRequested, this, [this]() {
            m_saveView->deleteLater();
            m_saveView = nullptr;
            m_pauseView->m_isSubViewOpen = false; // 重置状态
            m_pauseView->show();
        });

        m_saveView->show();
    });

    connect(m_pauseView, &PauseView::loadRequested, this, [this]() {
        if (m_pauseView->m_isSubViewOpen) return; // 防止重复打开

        m_pauseView->m_isSubViewOpen = true;
        m_loadView = new SaveView(true, this);

        connect(m_loadView, &SaveView::slotSelected, this, &ViewManager::handleLoadSlot);
        connect(m_loadView, &SaveView::backRequested, this, [this]() {
            m_loadView->deleteLater();
            m_loadView = nullptr;
            m_pauseView->m_isSubViewOpen = false; // 重置状态
            m_pauseView->show();
        });

        m_loadView->show();
    });

    connect(m_pauseView, &PauseView::restartRequested, this, [this]() {
        if (m_gameView) {
            // m_gameView->viewModel()->model()->resetGame();
            // m_gameView->viewModel()->model()->startGame();
            m_pauseView->hide();
        }
    });
    connect(m_pauseView, &PauseView::backToMenuRequested, this, [this]() {
        if (m_gameView) {
            // m_gameView->viewModel()->model()->stopGame();
            showMainMenu();
            m_pauseView->hide();
        }
    });

    // 设置背景
    // setStyleSheet("background-color: #2c3e50;");

    // 显示主菜单
    setCurrentWidget(m_mainMenuView);
}

ViewManager::~ViewManager()
{
    if (m_gameView) {
        delete m_gameView;
    }
}

void ViewManager::showMainMenu()
{
    // // 如果游戏正在运行，停止它
    // if (m_gameView && !m_gameView->viewModel()->model()->gameOver()) {
    //     m_gameView->viewModel()->model()->stopGame();
    // }

    setCurrentWidget(m_mainMenuView);
}

// void ViewManager::startEasyGame()
// {
//     // 重置游戏状态
//     if (m_gameView) {
//         // 停止当前游戏
//         m_gameView->viewModel()->model()->stopGame();

//         // 重置游戏模型
//         m_gameView->viewModel()->model()->resetGame();
//     }

//     // 切换到加载界面
//     setCurrentWidget(m_loadingView);
//     m_loadingView->startLoading();
// }

void ViewManager::startGame()
{
    // 创建加载视图
    if (m_loadingView) {
        removeWidget(m_loadingView);
        delete m_loadingView;
    }
    m_loadingView = new LoadingView(m_selectedRole);
    addWidget(m_loadingView);
    setCurrentWidget(m_loadingView);
    m_loadingView->startLoading();

    // 如果游戏视图不存在，则创建
    if (!m_gameView) {
        GameModel *model = new GameModel();
        GameViewModel *viewModel = new GameViewModel(model);
        m_gameView = new GameView(viewModel);
        addWidget(m_gameView);

        // 连接加载完成信号
        connect(viewModel, &GameViewModel::gameLoaded, this, [this]() {
            // 切换到游戏视图
            setCurrentWidget(m_gameView);
            m_gameView->setFocus();

            // 停止加载动画
            if (m_loadingView) {
                m_loadingView->stopLoading();
            }
        });
    }

    // 使用选择的角色初始化游戏
    m_gameView->viewModel()->initGame(m_selectedRole);

    // 加载过程
    QTimer::singleShot(2000, m_gameView->viewModel(), [viewModel = m_gameView->viewModel()]() {
        viewModel->startGame();
    });

    // // 开始游戏（这会触发加载，完成后会发出gameLoaded信号）
    // m_gameView->viewModel()->startGame();
}

void ViewManager::keyPressEvent(QKeyEvent *event)
{
    // 在其它视图中禁止按键
    if (currentWidget() != m_gameView) {
        event->accept();
        return;
    }

    // 处理 ESC 键
    if (event->key() == Qt::Key_Escape) {
        // 在游戏视图中
        if (m_gameView && currentWidget() == m_gameView) {
            if (m_gameView && m_gameView->viewModel()->isPaused()) {
                resumeGame();
            } else {
                showPauseMenu();
            }
            event->accept();
            return;
        }

        // // 在存档选择视图中
        // else if (m_saveView && m_saveView->isVisible()) {
        //     m_saveView->deleteLater();
        //     m_saveView = nullptr;
        //     if (m_pauseView) m_pauseView->show();
        //     event->accept();
        //     return;
        // }

        // else if (m_loadView && m_loadView->isVisible()) {
        //     m_loadView->deleteLater();
        //     m_loadView = nullptr;
        //     if (m_pauseView) m_pauseView->show();
        //     event->accept();
        //     return;
        // }

        // // 在暂停菜单中
        // else if (m_pauseView && m_pauseView->isVisible()) {
        //     resumeGame();
        //     event->accept();
        //     return;
        // }

        // // 在角色选择视图中
        // else if (currentWidget() == m_roleSelectView) {
        //     showMainMenu();
        //     event->accept();
        //     return;
        // }
        // // 在主菜单中
        // else if (currentWidget() == m_mainMenuView) {
        //     // 添加确认对话框
        //     QMessageBox::StandardButton reply;
        //     reply = QMessageBox::question(
        //         this,
        //         "Quit Game",
        //         "Are you sure you want to quit?",
        //         QMessageBox::Yes | QMessageBox::No
        //         );

        //     if (reply == QMessageBox::Yes) {
        //         quitGame();
        //     }
        //     event->accept();
        //     return;
        // }
    }

    // 其他按键传递给父类处理
    QStackedWidget::keyPressEvent(event);
}

void ViewManager::showRoleSelectView()
{
    setCurrentWidget(m_roleSelectView);
}

void ViewManager::handleRoleSelected(const RoleType& role)
{
    m_selectedRole = role;
    startGame();
}

void ViewManager::showPauseMenu()
{
    if (m_gameView) {
        // m_gameView->viewModel()->model()->pauseGame();
        m_pauseView->move(
            (width() - m_pauseView->width()) / 2,
            (height() - m_pauseView->height()) / 2
            );
        m_pauseView->show();
    }
}

void ViewManager::resumeGame()
{
    if (m_gameView) {
        // m_gameView->viewModel()->model()->resumeGame();
        m_pauseView->hide();
    }
}

void ViewManager::handleSaveSlot(int slot)
{
    Q_UNUSED(slot);
    // if (m_gameView) {
    //     SaveManager::instance().saveGame(slot, m_gameView->viewModel()->model());
    //     m_saveView->refreshSaves();
    //     m_saveView->deleteLater();
    //     resumeGame();
    //     m_currentGameSlot = slot;
    // }
}

void ViewManager::handleLoadSlot(int slot)
{
    Q_UNUSED(slot);
    // if (!m_gameView) {
    //     // 如果游戏视图不存在，先创建
    //     GameModel *model = new GameModel();
    //     GameViewModel *viewModel = new GameViewModel(model);
    //     m_gameView = new GameView(viewModel);
    //     addWidget(m_gameView);

    //     // 连接游戏结束信号
    //     connect(model, &GameModel::gameStateChanged, this, [=]() {
    //         if (model->gameOver()) {
    //             model->stopGame();
    //             model->resetGame();
    //             showMainMenu();
    //         }
    //     });
    //     connect(model, &GameModel::gameOverAnimationFinished, this, [=]() {
    //         model->stopGame();
    //         model->resetGame();
    //         showMainMenu();
    //     });
    // }

    // // 尝试加载游戏
    // if (SaveManager::instance().loadGame(slot, m_gameView->viewModel()->model())) {
    //     // 加载成功后启动游戏
    //     m_gameView->viewModel()->model()->startGame();

    //     // 切换到游戏视图
    //     setCurrentWidget(m_gameView);
    //     m_currentGameSlot = slot;

    //     // 隐藏暂停菜单
    //     if (m_pauseView) {
    //         m_pauseView->hide();
    //     }
    // } else {
    //     // 加载失败处理
    //     qWarning() << "Failed to load game from slot" << slot;

    //     // 显示错误信息
    //     QMessageBox::warning(
    //         this,
    //         "Load Failed",
    //         "Failed to load saved game. The save file may be corrupted."
    //         );

    //     // 重置游戏状态
    //     m_gameView->viewModel()->model()->resetGame();
    // }

    // // 清理存档选择视图
    // if (m_loadView) {
    //     m_loadView->deleteLater();
    //     m_loadView = nullptr;
    // }
}

void ViewManager::showScore()
{
    // // 刷新分数
    // m_ScoreView->loadHighScores();
    // setCurrentWidget(m_ScoreView);
}

void ViewManager::showSettings()
{
    // 显示设置界面（暂不实现）
    showMainMenu();
}

void ViewManager::quitGame()
{
    close();
}
