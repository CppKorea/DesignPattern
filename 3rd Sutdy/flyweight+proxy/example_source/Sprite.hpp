//
//  Sprite.hpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "Ref.hpp"

class Texture2D;

class Sprite : public Ref
{
    
public:
    
    Sprite();
    virtual ~Sprite();
    
    static Sprite* create(const std::string& fileName);
    bool initWithFile(const std::string& fileName);
    
    void draw();
    void addChild(Sprite* object);
    
private:
    
    std::vector<Sprite*> _children;
    std::string _fileName;
    Texture2D* _texture;
    
};









