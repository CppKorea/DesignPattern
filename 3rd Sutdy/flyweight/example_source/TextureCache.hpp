//
//  TextureCache.hpp
//  fly_weight
//
//  Created by mac on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <unordered_map>
#include <string>

class Sprite;

class TextureCache
{
    
public:
    
    static TextureCache& getInstance();
    Sprite* addImage(const std::string fileName);
    
private:
    
    TextureCache() = default;
    virtual ~TextureCache() = default;
    
private:
    
    std::unordered_map<std::string, Sprite*> _textures;
    
};









