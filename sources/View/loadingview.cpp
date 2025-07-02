#include "loadingview.h"
#include <QPainter>
#include <QResizeEvent>

LoadingView::LoadingView(const RoleType &role, QWidget *parent)
    : QWidget(parent)
{
    // 根据角色加载不同的背景
    if (role == PLAYER_REIMU) {
        m_background = QPixmap(":/res/reimu_paint.png");
    } else if (role == PLAYER_MARISA) {
        m_background = QPixmap(":/res/marisa_paint.png");
    } else {
        // 默认背景
        m_background = QPixmap(":/res/reimu_paint.png");
    }

    // 加载动画图标
    m_loadingIcon = QPixmap(":/res/loading.png");

    // 创建加载动画定时器
    m_loadingTimer = new QTimer(this);
    connect(m_loadingTimer, &QTimer::timeout, this, [this]() {
        m_loadingAngle = (m_loadingAngle + 10) % 360;
        update();
    });

    // 初始图标大小
    m_iconSize = QSize(100, 100); // 默认大小，会在resizeEvent中更新
}

LoadingView::~LoadingView()
{
    stopLoading();
    delete m_loadingTimer;
}

void LoadingView::startLoading()
{
    m_loadingTimer->start(50); // 每50ms更新一次
}

void LoadingView::stopLoading()
{
    m_loadingTimer->stop();
}

void LoadingView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateLoadingIconPosition();
}

void LoadingView::updateLoadingIconPosition()
{
    // 计算图标大小 - 取窗口宽度和高度的1/5作为图标大小
    int iconSize = qMin(width(), height()) / 5;
    m_iconSize = QSize(iconSize, iconSize);

    // 计算右下角1/4*1/4区域的位置
    int iconWidth = qMin(width(), height()) / 4;
    int iconHeight = qMin(width(), height()) / 4;
    int x = width() - iconWidth; // 右下1/4区域的左边界
    int y = height() - iconHeight; // 右下1/4区域的上边界

    // 居中放置
    m_loadingPosition = QPoint(
        x + (iconWidth - iconWidth) / 2, // 在右下1/4区域内居中
        y + (iconHeight - iconHeight) / 2
        );
}

void LoadingView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景 - 缩放以填充整个窗口
    if (!m_background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), m_background.scaled(
                                                        width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation
                                                        ));
    }

    // 绘制旋转的加载图标
    if (!m_loadingIcon.isNull()) {
        // 缩放加载图标
        QPixmap scaledIcon = m_loadingIcon.scaled(
            m_iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation
            );

        painter.save();

        // 计算旋转中心（图标中心）
        QPoint center = QPoint(
            m_loadingPosition.x() + m_iconSize.width() / 2,
            m_loadingPosition.y() + m_iconSize.height() / 2
            );

        // 平移到中心点并旋转
        painter.translate(center);
        painter.rotate(m_loadingAngle);

        // 绘制图标（以中心为基准）
        painter.drawPixmap(
            -scaledIcon.width() / 2,
            -scaledIcon.height() / 2,
            scaledIcon
            );

        painter.restore();
    }
}
