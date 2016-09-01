//
//  TextureCache.cpp
//  fly_weight
//
//  Created by mac on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#include "TextureCache.hpp"
#include "Sprite.hpp"


TextureCache& TextureCache::getInstance()
{
    static TextureCache instance;
    return instance;
}


Sprite* TextureCache::addImage(const std::string fileName)
{
    Sprite* texture = nullptr;
    auto iter = _textures.find(fileName);
    if ( iter != std::end(_textures) )
        texture = iter->second;
    if ( !texture )
    {
        cout << "loading... [" << fileName << "]" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        
        texture = new Sprite();
        _textures.insert( {fileName, texture} );
    }
    
    return texture;
}









