#include "gamemodel.h"
#include <QRandomGenerator>

void GameModel::collisionDetection()
{
    switch(m_Now_Role){
    case PLAYER_REIMU:
        switch(m_Now_Boss){
        case BOSS_SAKUYA:
            collision_reimu_sakuya();
            break;
        case BOSS_YOUMU:
            collision_reimu_youmu();
            break;
        case BOSS_EIRIN:
            collision_reimu_eirin();
            break;
        case BOSS_KAGUYA:
            collision_reimu_kaguya();
            break;
        default:
            collision_reimu_eirin();
        }
        break;
    case PLAYER_MARISA:
        switch(m_Now_Boss){
        case BOSS_SAKUYA:
            collision_marisa_sakuya();
            break;
        case BOSS_YOUMU:
            collision_marisa_youmu();
            break;
        case BOSS_EIRIN:
            collision_marisa_eirin();
            break;
        case BOSS_KAGUYA:
            collision_marisa_kaguya();
            break;
        default:
            collision_marisa_eirin();
            break;
        }
        break;
    default:
        switch(m_Now_Boss){
        case BOSS_SAKUYA:
            collision_reimu_sakuya();
            break;
        case BOSS_YOUMU:
            collision_reimu_youmu();
            break;
        case BOSS_EIRIN:
            collision_reimu_eirin();
            break;
        case BOSS_KAGUYA:
            collision_reimu_kaguya();
            break;
        default:
            collision_reimu_eirin();
            break;
        }
        break;
    }
}


void GameModel::collision_reimu_youmu(){
    // //玩家子弹与Boss碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_reimu.m_firstBullets[i].m_Free & m_boss_youmu.m_collisionRect.intersects(m_reimu.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_boss_youmu.m_life--;
    //         m_reimu.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_reimu.m_secondBullets[i].m_Free & m_boss_youmu.m_collisionRect.intersects(m_reimu.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_boss_youmu.m_life--;
    //         m_reimu.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss子弹与玩家碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_boss_youmu.m_firstBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_youmu.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_reimu.m_life--;
    //         m_boss_youmu.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_boss_youmu.m_secondBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_youmu.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_reimu.m_life--;
    //         m_boss_youmu.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss与玩家碰撞
    // if(m_boss_youmu.m_collisionRect.intersects(m_reimu.m_collisionRect))
    // {
    //     m_reimu.m_life--;
    // }
}

void GameModel::collision_reimu_sakuya(){
    // //玩家子弹与Boss碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_reimu.m_firstBullets[i].m_Free & m_boss_sakuya.m_collisionRect.intersects(m_reimu.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_boss_sakuya.m_life--;
    //         m_reimu.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_reimu.m_secondBullets[i].m_Free & m_boss_sakuya.m_collisionRect.intersects(m_reimu.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_boss_sakuya.m_life--;
    //         m_reimu.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss子弹与玩家碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_boss_sakuya.m_firstBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_sakuya.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_reimu.m_life--;
    //         m_boss_sakuya.m_firstBullets[i].m_Free = true;

    //     }
    //     if(!m_boss_sakuya.m_secondBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_sakuya.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_reimu.m_life--;
    //         m_boss_sakuya.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss与玩家碰撞
    // if(m_boss_sakuya.m_collisionRect.intersects(m_reimu.m_collisionRect))
    // {
    //     m_reimu.m_life--;
    // }
}

void GameModel::collision_reimu_kaguya(){
    //玩家子弹与Boss碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_reimu.m_firstBullets[i].m_Free & m_boss_kaguya.m_collisionRect.intersects(m_reimu.m_firstBullets[i].m_collisionRect))
        {
            m_boss_kaguya.m_life--;
            m_reimu.m_firstBullets[i].m_Free = true;
        }
        if(!m_reimu.m_secondBullets[i].m_Free & m_boss_kaguya.m_collisionRect.intersects(m_reimu.m_secondBullets[i].m_collisionRect))
        {
            m_boss_kaguya.m_life--;
            m_reimu.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss子弹与玩家碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_boss_kaguya.m_firstBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_kaguya.m_firstBullets[i].m_collisionRect))
        {
            m_reimu.m_life--;
            m_boss_kaguya.m_firstBullets[i].m_Free = true;

        }
        if(!m_boss_kaguya.m_secondBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_kaguya.m_secondBullets[i].m_collisionRect))
        {
            m_reimu.m_life--;
            m_boss_kaguya.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss与玩家碰撞
    if(m_boss_kaguya.m_collisionRect.intersects(m_reimu.m_collisionRect))
    {
        m_reimu.m_life--;
    }
}

void GameModel::collision_reimu_eirin(){
    //玩家子弹与Boss碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_reimu.m_firstBullets[i].m_Free & m_boss_eirin.m_collisionRect.intersects(m_reimu.m_firstBullets[i].m_collisionRect))
        {
            m_boss_eirin.m_life--;
            m_reimu.m_firstBullets[i].m_Free = true;
        }
        if(!m_reimu.m_secondBullets[i].m_Free & m_boss_eirin.m_collisionRect.intersects(m_reimu.m_secondBullets[i].m_collisionRect))
        {
            m_boss_eirin.m_life--;
            m_reimu.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss子弹与玩家碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_boss_eirin.m_firstBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_eirin.m_firstBullets[i].m_collisionRect))
        {
            m_reimu.m_life--;
            m_boss_eirin.m_firstBullets[i].m_Free = true;

        }
        if(!m_boss_eirin.m_secondBullets[i].m_Free & m_reimu.m_collisionRect.intersects(m_boss_eirin.m_secondBullets[i].m_collisionRect))
        {
            m_reimu.m_life--;
            m_boss_eirin.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss与玩家碰撞
    if(m_boss_eirin.m_collisionRect.intersects(m_reimu.m_collisionRect))
    {
        m_reimu.m_life--;
    }
}

void GameModel::collision_marisa_youmu(){
    // //玩家子弹与Boss碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_marisa.m_firstBullets[i].m_Free & m_boss_youmu.m_collisionRect.intersects(m_marisa.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_boss_youmu.m_life--;
    //         m_marisa.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_marisa.m_secondBullets[i].m_Free & m_boss_youmu.m_collisionRect.intersects(m_marisa.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_boss_youmu.m_life--;
    //         m_marisa.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss子弹与玩家碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_boss_youmu.m_firstBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_youmu.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_marisa.m_life--;
    //         m_boss_youmu.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_boss_youmu.m_secondBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_youmu.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_marisa.m_life--;
    //         m_boss_youmu.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss与玩家碰撞
    // if(m_boss_youmu.m_collisionRect.intersects(m_marisa.m_collisionRect))
    // {
    //     m_marisa.m_life--;
    // }
}

void GameModel::collision_marisa_sakuya(){
    // //玩家子弹与Boss碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_marisa.m_firstBullets[i].m_Free & m_boss_sakuya.m_collisionRect.intersects(m_marisa.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_boss_sakuya.m_life--;
    //         m_marisa.m_firstBullets[i].m_Free = true;
    //     }
    //     if(!m_marisa.m_secondBullets[i].m_Free & m_boss_sakuya.m_collisionRect.intersects(m_marisa.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_boss_sakuya.m_life--;
    //         m_marisa.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss子弹与玩家碰撞
    // for(int i=0;i < MAX_BULLETS;i++){
    //     if(!m_boss_sakuya.m_firstBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_sakuya.m_firstBullets[i].m_collisionRect))
    //     {
    //         m_marisa.m_life--;
    //         m_boss_sakuya.m_firstBullets[i].m_Free = true;

    //     }
    //     if(!m_boss_sakuya.m_secondBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_sakuya.m_secondBullets[i].m_collisionRect))
    //     {
    //         m_marisa.m_life--;
    //         m_boss_sakuya.m_secondBullets[i].m_Free = true;
    //     }
    // }
    // //Boss与玩家碰撞
    // if(m_boss_sakuya.m_collisionRect.intersects(m_marisa.m_collisionRect))
    // {
    //     m_marisa.m_life--;
    // }
}

void GameModel::collision_marisa_kaguya(){
    //玩家子弹与Boss碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_marisa.m_firstBullets[i].m_Free & m_boss_kaguya.m_collisionRect.intersects(m_marisa.m_firstBullets[i].m_collisionRect))
        {
            m_boss_kaguya.m_life--;
            m_marisa.m_firstBullets[i].m_Free = true;
        }
        if(!m_marisa.m_secondBullets[i].m_Free & m_boss_kaguya.m_collisionRect.intersects(m_marisa.m_secondBullets[i].m_collisionRect))
        {
            m_boss_kaguya.m_life--;
            m_marisa.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss子弹与玩家碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_boss_kaguya.m_firstBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_kaguya.m_firstBullets[i].m_collisionRect))
        {
            m_marisa.m_life--;
            m_boss_kaguya.m_firstBullets[i].m_Free = true;

        }
        if(!m_boss_kaguya.m_secondBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_kaguya.m_secondBullets[i].m_collisionRect))
        {
            m_marisa.m_life--;
            m_boss_kaguya.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss与玩家碰撞
    if(m_boss_kaguya.m_collisionRect.intersects(m_marisa.m_collisionRect))
    {
        m_marisa.m_life--;
    }
}

void GameModel::collision_marisa_eirin(){
    //玩家子弹与Boss碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_marisa.m_firstBullets[i].m_Free & m_boss_eirin.m_collisionRect.intersects(m_marisa.m_firstBullets[i].m_collisionRect))
        {
            m_boss_eirin.m_life--;
            m_marisa.m_firstBullets[i].m_Free = true;
        }
        if(!m_marisa.m_secondBullets[i].m_Free & m_boss_eirin.m_collisionRect.intersects(m_marisa.m_secondBullets[i].m_collisionRect))
        {
            m_boss_eirin.m_life--;
            m_marisa.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss子弹与玩家碰撞
    for(int i=0;i < MAX_BULLETS;i++){
        if(!m_boss_eirin.m_firstBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_eirin.m_firstBullets[i].m_collisionRect))
        {
            m_marisa.m_life--;
            m_boss_eirin.m_firstBullets[i].m_Free = true;

        }
        if(!m_boss_eirin.m_secondBullets[i].m_Free & m_marisa.m_collisionRect.intersects(m_boss_eirin.m_secondBullets[i].m_collisionRect))
        {
            m_marisa.m_life--;
            m_boss_eirin.m_secondBullets[i].m_Free = true;
        }
    }
    //Boss与玩家碰撞
    if(m_boss_eirin.m_collisionRect.intersects(m_marisa.m_collisionRect))
    {
        m_marisa.m_life--;
    }
}
