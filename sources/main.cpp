#include <QApplication>
#include <QResource>
#include "View/viewmanager.h"
#include "Common/config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册外部的二进制资源文件
    QResource::registerResource(GAME_RES_PATH);

    // 创建主窗口
    ViewManager viewManager;
    viewManager.setWindowTitle(GAME_TITLE);
    // viewManager.setWindowIcon(QIcon(GAME_ICON));
    viewManager.resize(VIEW_WIDTH, VIEW_HEIGHT);
    viewManager.show();

    return a.exec();
}
