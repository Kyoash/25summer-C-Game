#include "saveview.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QDateTime>
#include <QKeyEvent>

SaveView::SaveView(bool forLoad, QWidget *parent)
    : QWidget(parent), m_forLoad(forLoad)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(600, 600);

    QWidget *container = new QWidget(this);
    container->setStyleSheet(
        "background-color: rgba(50, 50, 50, 220);"
        "border-radius: 10px;"
        "border: 2px solid #3498db;"
        );
    container->setFixedSize(580, 580);
    container->move(10, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout(container);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 标题
    QString titleText = m_forLoad ? "LOAD GAME" : "SAVE GAME";
    QLabel *title = new QLabel(titleText, container);
    title->setStyleSheet("color: #e74c3c; font-size: 28px; font-weight: bold;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // 滚动区域
    QScrollArea *scrollArea = new QScrollArea(container);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: transparent; border: none;");

    QWidget *scrollContent = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(scrollContent);
    gridLayout->setSpacing(10);

    // 添加存档槽位
    for (int i = 1; i <= 20; i++) {
        QWidget *slotWidget = new QWidget(scrollContent);
        slotWidget->setStyleSheet(
            "background-color: rgba(100, 100, 100, 150);"
            "border-radius: 5px;"
            "border: 1px solid #7f8c8d;"
            );
        slotWidget->setFixedHeight(80);

        QHBoxLayout *slotLayout = new QHBoxLayout(slotWidget);
        slotLayout->setContentsMargins(10, 5, 10, 5);

        QLabel *slotLabel = new QLabel(QString("Slot %1").arg(i), slotWidget);
        slotLabel->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");

        QLabel *infoLabel = new QLabel("Empty", slotWidget);
        infoLabel->setStyleSheet("color: #bdc3c7; font-size: 14px;");
        infoLabel->setObjectName(QString("info_%1").arg(i));

        QPushButton *actionButton = new QPushButton(
            m_forLoad ? "Load" : "Save",
            slotWidget
            );
        actionButton->setStyleSheet(
            "QPushButton {"
            "  background-color: #2ecc71;"
            "  color: white;"
            "  font-size: 14px;"
            "  padding: 5px 10px;"
            "  border-radius: 3px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #27ae60;"
            "}"
            );
        actionButton->setProperty("slot", i);

        slotLayout->addWidget(slotLabel);
        slotLayout->addWidget(infoLabel, 1);
        slotLayout->addWidget(actionButton);

        gridLayout->addWidget(slotWidget, (i-1)/2, (i-1)%2);

        connect(actionButton, &QPushButton::clicked, this, [this, i]() {
            emit slotSelected(i);
        });
    }

    scrollContent->setLayout(gridLayout);
    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea, 1);

    // 返回按钮
    QPushButton *backButton = new QPushButton("Back", container);
    backButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #e74c3c;"
        "  color: white;"
        "  font-size: 18px;"
        "  padding: 10px 20px;"
        "  border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #c0392b;"
        "}"
        );
    mainLayout->addWidget(backButton, 0, Qt::AlignCenter);

    connect(backButton, &QPushButton::clicked, this, &SaveView::backRequested);

    // 刷新存档信息
    refreshSaves();
}

void SaveView::refreshSaves()
{
    // QVector<SaveManager::SaveInfo> saves = SaveManager::instance().getSaveList();

    // for (const SaveManager::SaveInfo &info : saves) {
    //     QLabel *infoLabel = findChild<QLabel*>(QString("info_%1").arg(info.slot));
    //     if (infoLabel) {
    //         if (info.score == 0 && info.heroLife == 0) {
    //             infoLabel->setText("Empty");
    //             infoLabel->setStyleSheet("color: #bdc3c7; font-size: 14px;");
    //         } else {
    //             QString text = QString("Score: %1 | Life: %2\n%3")
    //             .arg(info.score, 6, 10, QChar('0'))
    //                 .arg(info.heroLife)
    //                 .arg(info.timestamp);
    //             infoLabel->setText(text);
    //             infoLabel->setStyleSheet("color: white; font-size: 14px;");
    //         }
    //     }
    // }
}

void SaveView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit backRequested();
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}
