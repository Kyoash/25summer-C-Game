QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += core gui multimedia multimediawidgets

SOURCES += \
    sources/Model/bomb.cpp \
    sources/Model/gamemodel.cpp \
    sources/Model/map.cpp \
    sources/Model/role/bosseirin.cpp \
    sources/Model/role/bosskaguya.cpp \
    sources/Model/role/bosssakuya.cpp \
    sources/Model/role/bossyoumu.cpp \
    sources/Model/bullet/bullet.cpp \
    sources/Model/bullet/laser.cpp \
    sources/Model/bullet/spell.cpp \
    sources/Model/collisiondetect.cpp \
    sources/Model/item.cpp \
    sources/Model/role/marisa.cpp \
    sources/Model/role/reimu.cpp \
    sources/Model/role/role.cpp \
    sources/Model/savemanager.cpp \
    sources/Model/scoremanager.cpp \
    sources/View/gameview.cpp \
    sources/View/loadingview.cpp \
    sources/View/mainmenuview.cpp \
    sources/View/pauseview.cpp \
    sources/View/roleselectview.cpp \
    sources/View/saveview.cpp \
    sources/View/viewmanager.cpp \
    sources/ViewModel/gameviewmodel.cpp \
    sources/ViewModel/saveviewmodel.cpp \
    sources/main.cpp

HEADERS += \
    sources/Common/config.h \
    sources/Model/bomb.h \
    sources/Model/gamemodel.h \
    sources/Model/map.h \
    sources/Model/role/bosseirin.h \
    sources/Model/role/bosskaguya.h \
    sources/Model/role/bosssakuya.h \
    sources/Model/role/bossyoumu.h \
    sources/Model/bullet/bullet.h \
    sources/Model/bullet/laser.h \
    sources/Model/bullet/spell.h \
    sources/Model/collisiondetect.h \
    sources/Model/item.h \
    sources/Model/role/marisa.h \
    sources/Model/role/playerspell.h \
    sources/Model/reimu.h \
    sources/Model/role/role.h \
    sources/Model/savemanager.h \
    sources/Model/scoremanager.h \
    sources/View/gameview.h \
    sources/View/loadingview.h \
    sources/View/mainmenuview.h \
    sources/View/pauseview.h \
    sources/View/roleselectview.h \
    sources/View/saveview.h \
    sources/View/viewmanager.h \
    sources/ViewModel/gameviewmodel.h \
    sources/ViewModel/saveviewmodel.h
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc \
