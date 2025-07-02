// mainmenuview.cpp
#include "mainmenuview.h"
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QStyle>

MainMenuView::MainMenuView(QWidget *parent) : QWidget(parent)
{
    // 加载所有图片资源
    m_background = QPixmap(":/res/bg.png");
    m_imageMainMenu = QPixmap(":/res/title.png");

    m_buttonNewGame = QPixmap(":/res/start.png");
    m_buttonNewGameHover = QPixmap(":/res/start.png");
    m_buttonLoad = QPixmap(":/res/start.png");
    m_buttonLoadHover = QPixmap(":/res/start.png");
    m_buttonScore = QPixmap(":/res/start.png");
    m_buttonScoreHover = QPixmap(":/res/start.png");
    m_buttonSetting = QPixmap(":/res/start.png");
    m_buttonSettingHover = QPixmap(":/res/start.png");
    m_buttonQuit = QPixmap(":/res/quit.png");
    m_buttonQuitHover = QPixmap(":/res/quit.png");

    // 主水平布局：左侧按钮区 + 右侧图片区
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // === 左侧按钮区域 ===
    QWidget *leftPanel = new QWidget(this);
    leftPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *buttonLayout = new QVBoxLayout(leftPanel);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(20); // 按钮垂直间距

    // 创建按钮
    m_newGameBtn = new QPushButton(leftPanel);
    m_newGameBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_loadBtn = new QPushButton(leftPanel);
    m_loadBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_scoreBtn = new QPushButton(leftPanel);
    m_scoreBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_settingBtn = new QPushButton(leftPanel);
    m_settingBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_quitBtn = new QPushButton(leftPanel);
    m_quitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 添加到布局
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_newGameBtn, 0, Qt::AlignCenter);
    buttonLayout->addWidget(m_loadBtn, 0, Qt::AlignCenter);
    buttonLayout->addWidget(m_scoreBtn, 0, Qt::AlignCenter);
    buttonLayout->addWidget(m_settingBtn, 0, Qt::AlignCenter);
    buttonLayout->addWidget(m_quitBtn, 0, Qt::AlignCenter);
    buttonLayout->addStretch(1);

    // === 右侧图片区域 ===
    m_rightImage = new QLabel(this);
    m_rightImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_rightImage->setAlignment(Qt::AlignCenter);
    m_rightImage->setScaledContents(true);

    if (!m_imageMainMenu.isNull()) {
        m_rightImage->setPixmap(m_imageMainMenu);
    }

    // === 添加到主布局 ===
    mainLayout->addWidget(leftPanel, 1); // 左侧占1份空间
    mainLayout->addWidget(m_rightImage, 1); // 右侧占1份空间

    // 连接信号
    connect(m_newGameBtn, &QPushButton::clicked, this, &MainMenuView::newGameRequested);
    connect(m_loadBtn, &QPushButton::clicked, this, &MainMenuView::loadRequested);
    connect(m_scoreBtn, &QPushButton::clicked, this, &MainMenuView::scoreRequested);
    connect(m_settingBtn, &QPushButton::clicked, this, &MainMenuView::settingRequested);
    connect(m_quitBtn, &QPushButton::clicked, this, &MainMenuView::quitRequested);

    // 初始更新按钮大小
    updateButtonSizes();
}

MainMenuView::~MainMenuView()
{
    // 清理资源
}

void MainMenuView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateButtonSizes();
}

void MainMenuView::updateButtonSizes()
{
    // 计算统一按钮高度（基于窗口高度的比例）
    int commonHeight = height() / 10;
    if (commonHeight < 30) commonHeight = 30; // 最小高度
    if (commonHeight > 80) commonHeight = 80; // 最大高度

    // 计算每个按钮的宽度（基于各自图片的宽高比）
    int newGameWidth = commonHeight;
    int loadWidth = commonHeight;
    int scoreWidth = commonHeight;
    int settingWidth = commonHeight;
    int quitWidth = commonHeight;

    // 如果图片有效，根据图片宽高比计算宽度
    if (!m_buttonNewGame.isNull() && m_buttonNewGame.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonNewGame.width()) / m_buttonNewGame.height();
        newGameWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    if (!m_buttonLoad.isNull() && m_buttonLoad.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonLoad.width()) / m_buttonLoad.height();
        loadWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    if (!m_buttonScore.isNull() && m_buttonScore.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonScore.width()) / m_buttonScore.height();
        scoreWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    if (!m_buttonSetting.isNull() && m_buttonSetting.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonSetting.width()) / m_buttonSetting.height();
        settingWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    if (!m_buttonQuit.isNull() && m_buttonQuit.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonQuit.width()) / m_buttonQuit.height();
        quitWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    // 设置按钮固定大小（高度相同，宽度根据图片宽高比）
    m_newGameBtn->setFixedSize(newGameWidth, commonHeight);
    m_loadBtn->setFixedSize(loadWidth, commonHeight);
    m_scoreBtn->setFixedSize(scoreWidth, commonHeight);
    m_settingBtn->setFixedSize(settingWidth, commonHeight);
    m_quitBtn->setFixedSize(quitWidth, commonHeight);

    // 更新按钮样式
    QString buttonStyle = "QPushButton {"
                          "  border: none;"
                          "  background-color: transparent;"
                          "}";

    QString hoverStyle = "QPushButton:hover {"
                         "  background-color: transparent;"
                         "}";

    m_newGameBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_loadBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_scoreBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_settingBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_quitBtn->setStyleSheet(buttonStyle + hoverStyle);

    // 设置按钮图标（缩放后的图片）
    auto setButtonIcon = [commonHeight](QPushButton* button, const QPixmap& pixmap,
                                        const QPixmap& hoverPixmap, int width) {
        if (pixmap.isNull()) return;

        QIcon icon;
        icon.addPixmap(pixmap.scaled(width, commonHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Normal);

        if (!hoverPixmap.isNull()) {
            icon.addPixmap(hoverPixmap.scaled(width, commonHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Active);
        }

        button->setIcon(icon);
        button->setIconSize(QSize(width, commonHeight));
    };

    setButtonIcon(m_newGameBtn, m_buttonNewGame, m_buttonNewGameHover, newGameWidth);
    setButtonIcon(m_loadBtn, m_buttonLoad, m_buttonLoadHover, loadWidth);
    setButtonIcon(m_scoreBtn, m_buttonScore, m_buttonScoreHover, scoreWidth);
    setButtonIcon(m_settingBtn, m_buttonSetting, m_buttonSettingHover, settingWidth);
    setButtonIcon(m_quitBtn, m_buttonQuit, m_buttonQuitHover, quitWidth);
}

void MainMenuView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景图（保持宽高比，填充整个窗口）
    if (!m_background.isNull()) {
        QPixmap scaledBg = m_background.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPoint bgPos((width() - scaledBg.width()) / 2, (height() - scaledBg.height()) / 2);
        painter.drawPixmap(bgPos, scaledBg);
    }

    // 绘制半透明覆盖层（增强按钮可见性）
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
}
