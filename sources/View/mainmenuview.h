// mainmenuview.h
#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>

class MainMenuView : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuView(QWidget *parent = nullptr);
    ~MainMenuView();

signals:
    void newGameRequested();
    void loadRequested();
    void scoreRequested();
    void settingRequested();
    void quitRequested();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void updateButtonSizes();

    QPushButton *m_newGameBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_scoreBtn;
    QPushButton *m_settingBtn;
    QPushButton *m_quitBtn;

    QLabel *m_rightImage;

    QPixmap m_background;
    QPixmap m_buttonNewGame;
    QPixmap m_buttonNewGameHover;
    QPixmap m_buttonLoad;
    QPixmap m_buttonLoadHover;
    QPixmap m_buttonScore;
    QPixmap m_buttonScoreHover;
    QPixmap m_buttonSetting;
    QPixmap m_buttonSettingHover;
    QPixmap m_buttonQuit;
    QPixmap m_buttonQuitHover;

    QPixmap m_imageMainMenu;
};

#endif // MAINMENUVIEW_H
