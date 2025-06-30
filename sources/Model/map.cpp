#include "map.h"
#include "../Common/config.h"

Map::Map()
{
    // 初始化加载地图对象
    m_map1.load(MAP_STAGE1_PATH);
    m_map2.load(MAP_STAGE2_PATH);
    m_map3.load(MAP_STAGE3_PATH);
    m_map4.load(MAP_STAGE4_PATH);

    // 设置地图起始坐标
    m_map1_posX = 0;
    m_map1_posY = 0;
    m_map2_posX = 0;
    m_map2_posY = 0;
    m_map3_posX = 0;
    m_map3_posY = 0;
    m_map4_posX = 0;
    m_map4_posY = 0;
}
