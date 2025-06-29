#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map
{
public:
    Map();//构造函数

public:
    //地图图片
    QPixmap m_map1;

    // 地图X、Y轴坐标
    int m_map1_posX;
    int m_map1_posY;
};

#endif // MAP_H
