#ifndef PAUSEVIEW_H
#define PAUSEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class PauseView : public QWidget
{
    Q_OBJECT
public:
    explicit PauseView(QWidget *parent = nullptr);

    bool m_isSubViewOpen = false;

protected:
    void keyPressEvent(QKeyEvent *event) override;  // 添加键盘事件处理

signals:
    void backToMenuRequested();
    void saveRequested();
    void restartRequested();
    void loadRequested();
    void resumeRequested();

private:
    QPushButton *m_backToMenuBtn;
    QPushButton *m_saveBtn;
    QPushButton *m_restartBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_resumeBtn;

};

#endif // PAUSEVIEW_H
