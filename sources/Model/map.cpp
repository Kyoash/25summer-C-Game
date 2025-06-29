#include "map.h"
#include "../Common/config.h"

Map::Map()
{
    // 初始化加载地图对象
    m_map1.load(MAP_PATH);

    // 设置地图起始坐标
    m_map1_posX = 0;
    m_map1_posY = 0;
}
