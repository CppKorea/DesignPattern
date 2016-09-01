//
//  Sprite.hpp
//  fly_weight
//
//  Created by mac on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <string>

class Sprite
{
    
public:
    
    Sprite();
    virtual ~Sprite();
    
    static Sprite* create(const std::string& fileName);
    bool initWithFile(const std::string& fileName);
    void draw();
    
private:
    
    std::string _fileName;
    
};









