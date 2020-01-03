//
//  TextureCache.cpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#include "TextureCache.hpp"
#include "Texture2D.hpp"

TextureCache& TextureCache::getInstance()
{
    static TextureCache instance;
    return instance;
}


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}


Texture2D* TextureCache::addImage(const std::string& fileName)
{
    Texture2D* texture = nullptr;
    auto iter = _textures.find(fileName);
    if ( iter != std::end(_textures) )
        texture = iter->second;
    else
    {
        texture = new Texture2D(fileName);
        _textures.insert( {fileName, texture} );
    }
    
    return texture;
}









