#ifndef SAVEVIEW_H
#define SAVEVIEW_H

#include <QWidget>
#include <QVector>
// #include "../model/savemanager.h"

class SaveView : public QWidget
{
    Q_OBJECT
public:
    explicit SaveView(bool forLoad, QWidget *parent = nullptr);

    void refreshSaves();

protected:
    void keyPressEvent(QKeyEvent *event) override;  // 添加键盘事件处理

signals:
    void slotSelected(int slot);
    void backRequested();

private:
    bool m_forLoad; // true: 加载模式, false: 保存模式
};

#endif // SAVEVIEW_H
