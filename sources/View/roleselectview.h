// roleselectview.h
#ifndef ROLESELECTVIEW_H
#define ROLESELECTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QLabel> // 添加QLabel头文件
#include "../Common/config.h"

class RoleSelectView : public QWidget
{
    Q_OBJECT
public:
    explicit RoleSelectView(QWidget *parent = nullptr);
    ~RoleSelectView();

signals:
    void roleReimuSelected();
    void roleMarisaSelected();
    void backRequested();
    void roleSelected(const RoleType& role);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void updateButtonSizes();

    QPushButton *m_roleReimuBtn;
    QPushButton *m_roleMarisaBtn;
    QPushButton *m_backBtn;
    QLabel *m_titleLabel; // 添加标题标签

    QPixmap m_background;
    QPixmap m_titleImage; // 添加标题图片
    QPixmap m_buttonReimu;
    QPixmap m_buttonReimuHover;
    QPixmap m_buttonMarisa;
    QPixmap m_buttonMarisaHover;
    QPixmap m_buttonBack;
    QPixmap m_buttonBackHover;
};

#endif // ROLESELECTVIEW_H
