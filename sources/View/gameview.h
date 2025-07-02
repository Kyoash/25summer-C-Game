#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QPainter>
#include "../ViewModel/gameviewmodel.h"

class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(GameViewModel *viewModel, QWidget *parent = nullptr);
    ~GameView();

    GameViewModel* viewModel() const { return m_gameViewModel; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    // 状态显示相关资源
    QPixmap m_gameBg;
    QPixmap m_scoreIcon;
    QPixmap m_hiScoreIcon;
    QPixmap m_lifeIcon;
    QPixmap m_bombIcon;
    QPixmap m_grazeIcon;
    QPixmap m_powerIcon;
    QPixmap m_watermarkIcon;
    QPixmap m_lifeNumIcon;
    QPixmap m_bombNumIcon;

    // 区域划分
    QRect m_leftArea;
    QRect m_rightArea;

    // 右侧子区域
    QVector<QRect> m_rightSections;

    // 计算缩放比例
    float calculateScaleFactor(const QRect& area, int originalWidth, int originalHeight) const;

    GameViewModel *m_gameViewModel;
};

#endif // GAMEVIEW_H
