//
//  Sprite.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
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
    void addChild(Sprite* spr);

private:
    
    std::vector<Sprite*> _children;
    std::string _fileName;
    Texture2D* _texture;
    
};









