//
//  TextureCache.hpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <unordered_map>
#include <string>

class Texture2D;

class TextureCache
{
    
public:
    
    static TextureCache& getInstance();
    Texture2D* addImage(const std::string& fileName);
    
    virtual ~TextureCache() = default;
    
private:

    TextureCache() = default;
    
private:
    
    std::unordered_map<std::string, Texture2D*> _textures;
    
};








