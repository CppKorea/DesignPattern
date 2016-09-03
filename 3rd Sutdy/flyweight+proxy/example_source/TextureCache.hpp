//
//  TextureCache.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#pragma once

#include <unordered_map>
#include <string>

// 전방선언
class Texture2D;

class TextureCache
{
    
public:
    

    static TextureCache& getInstance();
    
    virtual ~TextureCache();
    Texture2D* addImage(const std::string& fileName);

private:
    
    TextureCache();
    
private:
    
    std::unordered_map<std::string, Texture2D*> _textures;
    
};









