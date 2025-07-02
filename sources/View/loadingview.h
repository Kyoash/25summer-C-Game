#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include "../Common/config.h"

class LoadingView : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingView(const RoleType &role, QWidget *parent = nullptr);
    ~LoadingView();

    void startLoading();
    void stopLoading();

signals:
    void loadingComplete();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateLoadingIconPosition();

    QPixmap m_background;
    QPixmap m_loadingIcon;
    QTimer *m_loadingTimer;
    int m_loadingAngle = 0;
    QPoint m_loadingPosition;
    QSize m_iconSize;
};

#endif // LOADINGVIEW_H
