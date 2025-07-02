#include <algorithm>

#include "gameview.h"
#include <QKeyEvent>
#include <QIcon>

#include "../Common/config.h"

#define MAIN_ICON_HEIGHT_RATIO 0.8f   // 主图标高度占区域高度的比例
#define SUB_ICON_HEIGHT_RATIO 1.0f   // 小图标高度相对于主图标高度的比例

GameView::GameView(GameViewModel *viewModel, QWidget *parent)
    : QWidget(parent), m_gameViewModel(viewModel)
{
    setFixedSize(VIEW_WIDTH, VIEW_HEIGHT);
    setWindowTitle(GAME_TITLE);
    // setWindowIcon(QIcon(GAME_ICON));
    setFocusPolicy(Qt::StrongFocus);

    // 连接视图模型的更新信号到视图的重绘
    connect(m_gameViewModel, &GameViewModel::updateView, this, [this]() {
        update();  // 触发重绘
    });

    // 连接游戏加载完成信号(Debug)
    connect(m_gameViewModel, &GameViewModel::gameLoaded, this, [this]() {
        // 这里可以添加游戏加载完成后的处理
        qDebug() << "Game loaded, view ready";
    });

    // 加载资源
    m_gameBg = QPixmap(":/res/game_bg.png");
    m_scoreIcon = QPixmap(":/res/score.png");
    m_hiScoreIcon = QPixmap(":/res/hiscore.png");
    m_lifeIcon = QPixmap(":/res/life.png");
    m_bombIcon = QPixmap(":/res/bomb.png");
    m_grazeIcon = QPixmap(":/res/graze.png");
    m_powerIcon = QPixmap(":/res/power.png");
    m_watermarkIcon = QPixmap(":/res/watermark.png");
    m_lifeNumIcon = QPixmap(":/res/item/life_num.png");
    m_bombNumIcon = QPixmap(":/res/item/bomb_num.png");
}

GameView::~GameView() {}

void GameView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // 计算左右区域
    int totalWidth = width();
    int totalHeight = height();

    // 左侧游戏区域 (2/3宽度)
    m_leftArea = QRect(0, 0, totalWidth * 2 / 3, totalHeight);

    // 右侧状态区域 (1/3宽度)
    m_rightArea = QRect(totalWidth * 2 / 3, 0, totalWidth / 3, totalHeight);

    // 划分右侧区域 (11个部分)
    m_rightSections.clear();
    int sectionHeight = totalHeight / 20; // 基本单位高度

    // 0: 1/20 空区域（新增）
    m_rightSections << QRect(m_rightArea.left(), 0, m_rightArea.width(), sectionHeight);

    // 1: 1/20: Score
    m_rightSections << QRect(m_rightArea.left(), sectionHeight, m_rightArea.width(), sectionHeight);

    // 2: 1/20: HiScore
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 2, m_rightArea.width(), sectionHeight);

    // 3: 1/20: 空区域
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 3, m_rightArea.width(), sectionHeight);

    // 4: 1/20: Life
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 4, m_rightArea.width(), sectionHeight);

    // 5: 1/20: Bomb
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 5, m_rightArea.width(), sectionHeight);

    // 6: 1/20: 空区域
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 6, m_rightArea.width(), sectionHeight);

    // 7: 1/20: Power
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 7, m_rightArea.width(), sectionHeight);

    // 8: 1/20: Graze
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 8, m_rightArea.width(), sectionHeight);

    // 9: 1/20: 空区域
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 9, m_rightArea.width(), sectionHeight);

    // 10: 10/20: 水印区域 (占10个单位高度)
    m_rightSections << QRect(m_rightArea.left(), sectionHeight * 10, m_rightArea.width(), sectionHeight * 10);
}


float GameView::calculateScaleFactor(const QRect& area, int originalWidth, int originalHeight) const
{
    float widthScale = static_cast<float>(area.width()) / originalWidth;
    float heightScale = static_cast<float>(area.height()) / originalHeight;
    return qMin(widthScale, heightScale);
}

void GameView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 1. 绘制背景 - 整个窗口
    if (!m_gameBg.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), m_gameBg.scaled(
                                                        width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation
                                                        ));
    }

    // 计算左右区域
    int totalWidth = width();
    int totalHeight = height();

    // 左侧游戏区域 (2/3宽度)
    QRect leftArea(0, 0, totalWidth * 2 / 3, totalHeight);

    // 右侧状态区域 (1/3宽度)
    QRect rightArea(totalWidth * 2 / 3, 0, totalWidth / 3, totalHeight);

    // === 绘制左侧游戏区域 ===
    painter.save();
    painter.setClipRect(leftArea);

    // 获取游戏元素
    std::pair<QPixmap*, std::pair<int, int>>& gamePixmap1 = m_gameViewModel->getGamePixmap1();
    std::pair<QPixmap*, std::pair<int, int>>& hero = m_gameViewModel->getHero();
    std::pair<QPixmap*, std::pair<int, int>>& boss = m_gameViewModel->getBoss();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& enemys = m_gameViewModel->getEnemys();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& heroBullets = m_gameViewModel->getHeroBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& bossBullets = m_gameViewModel->getBossBullets();
    std::vector<std::pair<QPixmap*, std::pair<int, int>>>& enemyBullets = m_gameViewModel->getEnemyBullets();

    // 计算缩放比例 - 基于原始游戏尺寸
    float scaleX = static_cast<float>(leftArea.width()) / GAME_WIDTH;
    float scaleY = static_cast<float>(leftArea.height()) / GAME_HEIGHT;
    float scale = qMin(scaleX, scaleY);

    // 绘制 gamePixmap1
    if (gamePixmap1.first && !gamePixmap1.first->isNull()) {
        QPixmap scaledPixmap = gamePixmap1.first->scaled(
            gamePixmap1.first->width() * scale,
            gamePixmap1.first->height() * scale,
            Qt::KeepAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            leftArea.left() + gamePixmap1.second.first * scale,
            leftArea.top() + gamePixmap1.second.second * scale,
            scaledPixmap
            );
    }

    // 绘制 hero
    if (hero.first && !hero.first->isNull()) {
        QPixmap scaledPixmap = hero.first->scaled(
            hero.first->width() * scale,
            hero.first->height() * scale,
            Qt::KeepAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            leftArea.left() + hero.second.first * scale,
            leftArea.top() + hero.second.second * scale,
            scaledPixmap
            );
    }

    // 绘制 boss
    if (boss.first && !boss.first->isNull()) {
        QPixmap scaledPixmap = boss.first->scaled(
            boss.first->width() * scale,
            boss.first->height() * scale,
            Qt::KeepAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            leftArea.left() + boss.second.first * scale,
            leftArea.top() + boss.second.second * scale,
            scaledPixmap
            );
    }

    // // 绘制 enemys
    // for (auto& enemy : enemys) {
    //     if (enemy.first && !enemy.first->isNull()) {
    //         QPixmap scaledPixmap = enemy.first->scaled(
    //             enemy.first->width() * scale,
    //             enemy.first->height() * scale,
    //             Qt::KeepAspectRatio, Qt::SmoothTransformation
    //             );
    //         painter.drawPixmap(
    //             leftArea.left() + enemy.second.first * scale,
    //             leftArea.top() + enemy.second.second * scale,
    //             scaledPixmap
    //             );
    //     }
    // }

    // 绘制 heroBullets
    for (auto& heroBullet : heroBullets) {
        if (heroBullet.first && !heroBullet.first->isNull()) {
            QPixmap scaledPixmap = heroBullet.first->scaled(
                heroBullet.first->width() * scale,
                heroBullet.first->height() * scale,
                Qt::KeepAspectRatio, Qt::SmoothTransformation
                );
            painter.drawPixmap(
                leftArea.left() + heroBullet.second.first * scale,
                leftArea.top() + heroBullet.second.second * scale,
                scaledPixmap
                );
        }
    }

    // 绘制 bossBullets
    for (auto& bossBullet : bossBullets) {
        if (bossBullet.first && !bossBullet.first->isNull()) {
            QPixmap scaledPixmap = bossBullet.first->scaled(
                bossBullet.first->width() * scale,
                bossBullet.first->height() * scale,
                Qt::KeepAspectRatio, Qt::SmoothTransformation
                );
            painter.drawPixmap(
                leftArea.left() + bossBullet.second.first * scale,
                leftArea.top() + bossBullet.second.second * scale,
                scaledPixmap
                );
        }
    }

    // // 绘制 enemyBullets
    // for (auto& enemyBullet : enemyBullets) {
    //     if (enemyBullet.first && !enemyBullet.first->isNull()) {
    //         QPixmap scaledPixmap = enemyBullet.first->scaled(
    //             enemyBullet.first->width() * scale,
    //             enemyBullet.first->height() * scale,
    //             Qt::KeepAspectRatio, Qt::SmoothTransformation
    //             );
    //         painter.drawPixmap(
    //             leftArea.left() + enemyBullet.second.first * scale,
    //             leftArea.top() + enemyBullet.second.second * scale,
    //             scaledPixmap
    //             );
    //     }
    // }

    painter.restore();

    // === 绘制右侧状态区域 ===

    // 绘制半透明背景
    painter.setBrush(QColor(0, 0, 0, 0));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rightArea);

    // 划分右侧区域 (11个部分)
    QVector<QRect> rightSections;
    int sectionHeight = totalHeight / 20; // 基本单位高度

    // 0: 1/20 空区域（新增）
    rightSections << QRect(rightArea.left(), 0, rightArea.width(), sectionHeight);

    // 1: 1/20: Score
    rightSections << QRect(rightArea.left(), sectionHeight, rightArea.width(), sectionHeight);

    // 2: 1/20: HiScore
    rightSections << QRect(rightArea.left(), sectionHeight * 2, rightArea.width(), sectionHeight);

    // 3: 1/20: 空区域
    rightSections << QRect(rightArea.left(), sectionHeight * 3, rightArea.width(), sectionHeight);

    // 4: 1/20: Life
    rightSections << QRect(rightArea.left(), sectionHeight * 4, rightArea.width(), sectionHeight);

    // 5: 1/20: Bomb
    rightSections << QRect(rightArea.left(), sectionHeight * 5, rightArea.width(), sectionHeight);

    // 6: 1/20: 空区域
    rightSections << QRect(rightArea.left(), sectionHeight * 6, rightArea.width(), sectionHeight);

    // 7: 1/20: Power
    rightSections << QRect(rightArea.left(), sectionHeight * 7, rightArea.width(), sectionHeight);

    // 8: 1/20: Graze
    rightSections << QRect(rightArea.left(), sectionHeight * 8, rightArea.width(), sectionHeight);

    // 9: 1/20: 空区域
    rightSections << QRect(rightArea.left(), sectionHeight * 9, rightArea.width(), sectionHeight);

    // 10: 10/20: 水印区域 (占10个单位高度)
    rightSections << QRect(rightArea.left(), sectionHeight * 10, rightArea.width(), sectionHeight * 10);

    // 绘制分隔线
    painter.setPen(QPen(QColor(100, 100, 100, 100), 1));
    for (int i = 1; i < rightSections.size(); i++) {
        int y = rightSections[i].top();
        painter.drawLine(rightArea.left(), y, rightArea.right(), y);
    }

    // 设置文本样式
    QFont font("Sylfaen", 24);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // 计算得分和最高分区域的最大图标宽度
    int maxIconWidth = 0;

    // 计算得分区域图标宽度
    if (!m_scoreIcon.isNull()) {
        QRect rect = rightSections[1]; // Score区域
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int iconWidth = mainIconHeight * m_scoreIcon.width() / m_scoreIcon.height();
        maxIconWidth = qMax(maxIconWidth, iconWidth);
    }

    // 计算最高分区域图标宽度
    if (!m_hiScoreIcon.isNull()) {
        QRect rect = rightSections[2]; // HiScore区域
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int iconWidth = mainIconHeight * m_hiScoreIcon.width() / m_hiScoreIcon.height();
        maxIconWidth = qMax(maxIconWidth, iconWidth);
    }

    // === 绘制得分区域 ===
    if (!m_scoreIcon.isNull()) {
        QRect rect = rightSections[1]; // Score区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算图标宽度（保持宽高比）
        int iconWidth = mainIconHeight * m_scoreIcon.width() / m_scoreIcon.height();

        // 绘制图标（垂直居中）
        QPixmap scaledIcon = m_scoreIcon.scaled(
            iconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 绘制得分值 (8位数字，不足补0)
        QString score = QString("%1").arg(m_gameViewModel->getScore(), 8, 10, QChar('0'));
        QRect textRect = rect.adjusted(maxIconWidth + padding * 2 / 4, 0, -padding / 4, 0);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, score);
    }

    // === 绘制最高分区域 ===
    if (!m_hiScoreIcon.isNull()) {
        QRect rect = rightSections[2]; // HiScore区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算图标宽度（保持宽高比）
        int iconWidth = mainIconHeight * m_hiScoreIcon.width() / m_hiScoreIcon.height();

        // 绘制图标（垂直居中）
        QPixmap scaledIcon = m_hiScoreIcon.scaled(
            iconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 绘制最高分值 (8位数字，不足补0)
        QString hiScore = QString("%1").arg(m_gameViewModel->getHiScore(), 8, 10, QChar('0'));
        QRect textRect = rect.adjusted(maxIconWidth + padding * 2 / 4, 0, -padding / 4, 0);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, hiScore);
    }

    // === 绘制生命区域 ===
    if (!m_lifeIcon.isNull() && !m_lifeNumIcon.isNull()) {
        QRect rect = rightSections[4]; // Life区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算主图标宽度（保持宽高比）
        int mainIconWidth = mainIconHeight * m_lifeIcon.width() / m_lifeIcon.height();

        // 绘制生命图标（垂直居中）
        QPixmap scaledIcon = m_lifeIcon.scaled(
            mainIconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 计算小图标高度（主图标高度的比例）
        int subIconHeight = mainIconHeight * SUB_ICON_HEIGHT_RATIO;

        // 计算可用空间
        int availableWidth = std::min(static_cast<int>(0.64 * rect.width() - padding / 4), rect.width() - mainIconWidth - padding * 3 / 4);
        int maxIcons = 8; // 最多8个图标

        // 计算每个小图标的理想大小
        int subIconSize = std::min(
            availableWidth / maxIcons,
            subIconHeight
            );

        // 确保图标大小合理
        subIconSize = std::max(subIconSize, 10); // 最小10像素

        int lifeCount = std::min(m_gameViewModel->getLifeCount(), maxIcons);

        // 计算起始位置（垂直居中）
        int startX = rect.left() + std::max(static_cast<int>(0.36 * rect.width()), padding / 4 + mainIconWidth + padding / 4);
        int y = rect.top() + (rect.height() - subIconSize) / 2;

        // 绘制生命数量图标（单行，最多8个）
        for (int i = 0; i < lifeCount; i++) {
            int x = startX + i * subIconSize;

            painter.drawPixmap(
                x, y,
                subIconSize, subIconSize,
                m_lifeNumIcon
                );
        }
    }

    // === 绘制炸弹区域 ===
    if (!m_bombIcon.isNull() && !m_bombNumIcon.isNull()) {
        QRect rect = rightSections[5]; // Bomb区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算主图标宽度（保持宽高比）
        int mainIconWidth = mainIconHeight * m_bombIcon.width() / m_bombIcon.height();

        // 绘制炸弹图标（垂直居中）
        QPixmap scaledIcon = m_bombIcon.scaled(
            mainIconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 计算小图标高度（主图标高度的比例）
        int subIconHeight = mainIconHeight * SUB_ICON_HEIGHT_RATIO;

        // 计算可用空间
        int availableWidth = std::min(static_cast<int>(0.64 * rect.width() - padding / 4), rect.width() - mainIconWidth - padding * 3 / 4);
        int maxIcons = 8; // 最多8个图标

        // 计算每个小图标的理想大小
        int subIconSize = std::min(
            availableWidth / maxIcons,
            subIconHeight
            );

        // 确保图标大小合理
        subIconSize = std::max(subIconSize, 10); // 最小10像素

        int bombCount = std::min(m_gameViewModel->getBombCount(), maxIcons);

        // 计算起始位置（垂直居中）
        int startX = rect.left() + std::max(static_cast<int>(0.36 * rect.width()), padding / 4 + mainIconWidth + padding / 4);
        int y = rect.top() + (rect.height() - subIconSize) / 2;

        // 绘制炸弹数量图标（单行，最多8个）
        for (int i = 0; i < bombCount; i++) {
            int x = startX + i * subIconSize;

            painter.drawPixmap(
                x, y,
                subIconSize, subIconSize,
                m_bombNumIcon
                );
        }
    }

    // === 绘制能量区域 ===
    if (!m_powerIcon.isNull()) {
        QRect rect = rightSections[7]; // Power区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算图标宽度（保持宽高比）
        int iconWidth = mainIconHeight * m_powerIcon.width() / m_powerIcon.height();

        // 绘制能量图标（垂直居中）
        QPixmap scaledIcon = m_powerIcon.scaled(
            iconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 绘制能量值 (3位浮点数)
        QString power = QString("%1").arg(m_gameViewModel->getPower(), 0, 'f', 2);
        QRect textRect = rect.adjusted(iconWidth + padding * 2 / 4, 0, -padding / 4, 0);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, power);
    }

    // === 绘制擦弹区域 ===
    if (!m_grazeIcon.isNull()) {
        QRect rect = rightSections[8]; // Graze区域

        // 计算主图标高度（区域高度的比例）
        int mainIconHeight = rect.height() * MAIN_ICON_HEIGHT_RATIO;
        int padding = (rect.height() - mainIconHeight) / 2;

        // 计算图标宽度（保持宽高比）
        int iconWidth = mainIconHeight * m_grazeIcon.width() / m_grazeIcon.height();

        // 绘制擦弹图标（垂直居中）
        QPixmap scaledIcon = m_grazeIcon.scaled(
            iconWidth, mainIconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation
            );
        painter.drawPixmap(
            rect.left() + padding / 4,
            rect.top() + padding,
            scaledIcon
            );

        // 绘制擦弹值 (4位数字，不足补0)
        QString graze = QString("%1").arg(m_gameViewModel->getGrazeCount(), 4, 10, QChar('0'));
        QRect textRect = rect.adjusted(iconWidth + padding * 2 / 4, 0, -padding / 4, 0);
        painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignHCenter, graze);
    }

    // === 绘制水印区域 ===
    if (!m_watermarkIcon.isNull()) {
        QRect rect = rightSections[10]; // 水印区域

        // 计算缩放比例 - 宽度为区域宽度的0.9倍
        float scaleFactor = static_cast<float>(rect.width() * 0.9f) / m_watermarkIcon.width();
        int scaledWidth = static_cast<int>(m_watermarkIcon.width() * scaleFactor);
        int scaledHeight = static_cast<int>(m_watermarkIcon.height() * scaleFactor);

        // 创建缩放后的水印图像
        QPixmap scaledWatermark = m_watermarkIcon.scaled(
            scaledWidth, scaledHeight,
            Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 计算居中位置
        int x = rect.left() + (rect.width() - scaledWidth) / 2;
        int y = rect.top() + (rect.height() - scaledHeight) / 2;

        // 居中绘制水印
        painter.drawPixmap(x, y, scaledWatermark);
    }
}










void GameView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        m_gameViewModel->setMoveLeft(true);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        m_gameViewModel->setMoveRight(true);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        m_gameViewModel->setMoveUp(true);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        m_gameViewModel->setMoveDown(true);
        break;
    case Qt::Key_Z:
        m_gameViewModel->setShooting(true);
        break;
    case Qt::Key_Shift:
        m_gameViewModel->setSpeedShift(true);
        break;
    case Qt::Key_X:
        m_gameViewModel->setSpell(true);
        break;
    case Qt::Key_M:
        m_gameViewModel->toggleCollisionBoxes();
        update();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        m_gameViewModel->setMoveLeft(false);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        m_gameViewModel->setMoveRight(false);
        break;
    case Qt::Key_Up:
    case Qt::Key_W:
        m_gameViewModel->setMoveUp(false);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        m_gameViewModel->setMoveDown(false);
        break;
    case Qt::Key_Z:
        m_gameViewModel->setShooting(false);
        break;
    case Qt::Key_X:
        m_gameViewModel->setSpell(false);
        break;
    case Qt::Key_Shift:
        m_gameViewModel->setSpeedShift(false);
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}
