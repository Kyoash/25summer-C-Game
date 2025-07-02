#include "roleselectview.h"
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QStyle>

RoleSelectView::RoleSelectView(QWidget *parent) : QWidget(parent)
{
    // 加载所有图片资源
    m_background = QPixmap(":/res/map/stg6bg3.png");
    m_titleImage = QPixmap(":/res/sl_player.png");

    // 角色选择按钮图片
    m_buttonReimu = QPixmap(":/res/reimu.png");
    m_buttonReimuHover = QPixmap(":/res/reimu.png");
    m_buttonMarisa = QPixmap(":/res/marisa.png");
    m_buttonMarisaHover = QPixmap(":/res/marisa.png");
    m_buttonBack = QPixmap(":/res/quit.png");
    m_buttonBackHover = QPixmap(":/res/quit.png");

    // 主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 添加顶部弹性空间 - 创建标题与顶部的距离
    mainLayout->addStretch(1);

    // === 标题区域 ===
    m_titleLabel = new QLabel(this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignCenter);

    // 添加标题下方的间距 - 创建标题与按钮之间的距离
    mainLayout->addSpacing(30);

    // === 角色选择按钮区域 ===
    QWidget *charactersPanel = new QWidget(this);
    charactersPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *charactersLayout = new QVBoxLayout(charactersPanel);
    charactersLayout->setAlignment(Qt::AlignCenter);
    charactersLayout->setSpacing(40);

    // 创建角色选择按钮
    m_roleReimuBtn = new QPushButton(charactersPanel);
    m_roleReimuBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_roleMarisaBtn = new QPushButton(charactersPanel);
    m_roleMarisaBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 在按钮区域内部添加弹性空间，使按钮垂直居中
    charactersLayout->addStretch(1);
    charactersLayout->addWidget(m_roleReimuBtn, 0, Qt::AlignCenter);
    charactersLayout->addWidget(m_roleMarisaBtn, 0, Qt::AlignCenter);
    charactersLayout->addStretch(1);

    mainLayout->addWidget(charactersPanel, 1);
    mainLayout->addSpacing(50);

    // === 返回按钮区域 ===
    QWidget *backPanel = new QWidget(this);
    backPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout *backLayout = new QHBoxLayout(backPanel);
    backLayout->setAlignment(Qt::AlignCenter);

    m_backBtn = new QPushButton(backPanel);
    m_backBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    backLayout->addWidget(m_backBtn, 0, Qt::AlignCenter);
    mainLayout->addWidget(backPanel);

    // 添加底部弹性空间 - 创建底部留白
    mainLayout->addStretch(1);

    // 连接信号
    connect(m_roleReimuBtn, &QPushButton::clicked, this, [this]() {
        emit roleReimuSelected();
        emit roleSelected(PLAYER_REIMU);
    });
    connect(m_roleMarisaBtn, &QPushButton::clicked, this, [this]() {
        emit roleMarisaSelected();
        emit roleSelected(PLAYER_MARISA);
    });
    connect(m_backBtn, &QPushButton::clicked, this, &RoleSelectView::backRequested);

    // 初始更新按钮大小
    updateButtonSizes();
}

RoleSelectView::~RoleSelectView()
{
    // 清理资源
}

void RoleSelectView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateButtonSizes();
}

void RoleSelectView::updateButtonSizes()
{
    // 计算统一按钮高度（基于窗口高度的比例）
    int commonHeight = height() / 8;
    if (commonHeight < 30) commonHeight = 30;
    if (commonHeight > 80) commonHeight = 80;

    // 更新标题图片大小
    if (!m_titleImage.isNull()) {
        // 标题高度为窗口高度的1/8
        int titleHeight = height() / 8;
        int titleWidth = titleHeight * 2; // 宽高比约为2:1

        // 根据实际图片宽高比调整
        if (m_titleImage.height() > 0) {
            double aspectRatio = static_cast<double>(m_titleImage.width()) / m_titleImage.height();
            titleWidth = static_cast<int>(titleHeight * aspectRatio);
        }

        QPixmap scaledTitle = m_titleImage.scaled(
            titleWidth, titleHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_titleLabel->setPixmap(scaledTitle);
    }

    // 计算每个按钮的宽度（基于各自图片的宽高比）
    int reimuWidth = 2 * commonHeight;
    int marisaWidth = 2 * commonHeight;
    int backWidth = commonHeight;

    if (!m_buttonReimu.isNull() && m_buttonReimu.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonReimu.width()) / m_buttonReimu.height();
        reimuWidth = static_cast<int>(2 * commonHeight * aspectRatio);
    }

    if (!m_buttonMarisa.isNull() && m_buttonMarisa.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonMarisa.width()) / m_buttonMarisa.height();
        marisaWidth = static_cast<int>(2 * commonHeight * aspectRatio);
    }

    if (!m_buttonBack.isNull() && m_buttonBack.height() > 0) {
        double aspectRatio = static_cast<double>(m_buttonBack.width()) / m_buttonBack.height();
        backWidth = static_cast<int>(commonHeight * aspectRatio);
    }

    // 设置按钮固定大小
    m_roleReimuBtn->setFixedSize(reimuWidth, 2 * commonHeight);
    m_roleMarisaBtn->setFixedSize(marisaWidth, 2 * commonHeight);
    m_backBtn->setFixedSize(backWidth, commonHeight);

    // 更新按钮样式
    QString buttonStyle = "QPushButton {"
                          "  border: none;"
                          "  background-color: transparent;"
                          "}";

    QString hoverStyle = "QPushButton:hover {"
                         "  background-color: transparent;"
                         "}";

    m_roleReimuBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_roleMarisaBtn->setStyleSheet(buttonStyle + hoverStyle);
    m_backBtn->setStyleSheet(buttonStyle + hoverStyle);

    // 设置按钮图标
    auto setButtonIcon = [commonHeight](QPushButton* button, const QPixmap& pixmap,
                                        const QPixmap& hoverPixmap, int width) {
        if (pixmap.isNull()) return;

        QIcon icon;
        icon.addPixmap(pixmap.scaled(width, 2 * commonHeight, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation), QIcon::Normal);

        if (!hoverPixmap.isNull()) {
            icon.addPixmap(hoverPixmap.scaled(width, 2 * commonHeight, Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation), QIcon::Active);
        }

        button->setIcon(icon);
        button->setIconSize(QSize(width, 2 * commonHeight));
    };

    auto setBackButtonIcon = [commonHeight](QPushButton* button, const QPixmap& pixmap,
                                            const QPixmap& hoverPixmap, int width) {
        if (pixmap.isNull()) return;

        QIcon icon;
        icon.addPixmap(pixmap.scaled(width, commonHeight, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation), QIcon::Normal);

        if (!hoverPixmap.isNull()) {
            icon.addPixmap(hoverPixmap.scaled(width, commonHeight, Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation), QIcon::Active);
        }

        button->setIcon(icon);
        button->setIconSize(QSize(width, commonHeight));
    };

    setButtonIcon(m_roleReimuBtn, m_buttonReimu, m_buttonReimuHover, reimuWidth);
    setButtonIcon(m_roleMarisaBtn, m_buttonMarisa, m_buttonMarisaHover, marisaWidth);
    setBackButtonIcon(m_backBtn, m_buttonBack, m_buttonBackHover, backWidth);
}

void RoleSelectView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景图
    if (!m_background.isNull()) {
        QPixmap scaledBg = m_background.scaled(size(), Qt::KeepAspectRatioByExpanding,
                                               Qt::SmoothTransformation);
        QPoint bgPos((width() - scaledBg.width()) / 2, (height() - scaledBg.height()) / 2);
        painter.drawPixmap(bgPos, scaledBg);
    }

    // 绘制半透明覆盖层
    painter.setBrush(QColor(0, 0, 0, 100));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
}
