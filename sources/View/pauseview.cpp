#include "pauseview.h"

#include <QApplication>
#include <QLabel>
#include <QKeyEvent>

PauseView::PauseView(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(400, 400);

    QWidget *container = new QWidget(this);
    container->setStyleSheet(
        "background-color: rgba(50, 50, 50, 220);"
        "border-radius: 10px;"
        "border: 2px solid #3498db;"
        );
    container->setFixedSize(380, 380);
    container->move(10, 10);

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 30, 30, 30);

    // 标题
    QLabel *title = new QLabel("PAUSED", container);
    title->setStyleSheet("color: #e74c3c; font-size: 28px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // 按钮样式
    QString buttonStyle =
        "QPushButton {"
        "  background-color: #3498db;"
        "  color: white;"
        "  font-size: 18px;"
        "  padding: 10px;"
        "  border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2980b9;"
        "}";

    // 创建按钮
    m_resumeBtn = new QPushButton("Resume", container);
    m_resumeBtn->setStyleSheet(buttonStyle);
    layout->addWidget(m_resumeBtn);

    m_saveBtn = new QPushButton("Save Game", container);
    m_saveBtn->setStyleSheet(buttonStyle);
    layout->addWidget(m_saveBtn);

    m_loadBtn = new QPushButton("Load Game", container);
    m_loadBtn->setStyleSheet(buttonStyle);
    layout->addWidget(m_loadBtn);

    m_restartBtn = new QPushButton("Restart Game", container);
    m_restartBtn->setStyleSheet(buttonStyle);
    layout->addWidget(m_restartBtn);

    m_backToMenuBtn = new QPushButton("Back to Menu", container);
    m_backToMenuBtn->setStyleSheet(buttonStyle);
    layout->addWidget(m_backToMenuBtn);

    // 连接信号
    connect(m_resumeBtn, &QPushButton::clicked, this, &PauseView::resumeRequested);
    connect(m_saveBtn, &QPushButton::clicked, this, &PauseView::saveRequested);
    connect(m_loadBtn, &QPushButton::clicked, this, &PauseView::loadRequested);
    connect(m_restartBtn, &QPushButton::clicked, this, &PauseView::restartRequested);
    connect(m_backToMenuBtn, &QPushButton::clicked, this, &PauseView::backToMenuRequested);
}

void PauseView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && !m_isSubViewOpen) {
        emit resumeRequested();
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}
