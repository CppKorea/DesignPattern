//
//  main.cpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>
#include <chrono>
using namespace std;

#include "Sprite.hpp"
#include "TextureCache.hpp"
#include "AutoreleasePool.hpp"

int main()
{
    auto root = Sprite::create("pelvis.png");
    root->retain();
    
    auto spr = Sprite::create("head.png");
    root->addChild(spr);
    
    for(int i = 0 ; i < 2 ; ++ i)
    {
        auto spr = Sprite::create("arm.png");
        root->addChild(spr);
    }
    for(int i = 0 ; i < 2 ; ++ i)
    {
        auto spr = Sprite::create("leg.png");
        root->addChild(spr);
    }
    
    auto start = chrono::high_resolution_clock::now();
    
    // game loop
    while( true )
    {
        if ( root ) root->draw();
        
        // 1초 후 제거
        auto curr = chrono::high_resolution_clock::now();
        if (root &&
            (chrono::duration_cast<chrono::milliseconds>(curr - start)).count() > 1000)
        {
            root->release();
            root = nullptr;
        }
        
        AutoreleasePool::getInstance().clear();
    }
}









