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
    QPixmap m_map2;
    QPixmap m_map3;
    QPixmap m_map4;

    // 地图X、Y轴坐标
    int m_map1_posX;
    int m_map1_posY;
    int m_map2_posX;
    int m_map2_posY;
    int m_map3_posX;
    int m_map3_posY;
    int m_map4_posX;
    int m_map4_posY;
};

#endif // MAP_H
