//
//  Sprite.cpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>
#include <new> // std::nothrow

#include "Sprite.hpp"
#include "Texture2D.hpp"
#include "TextureCache.hpp"


Sprite::Sprite() :
_fileName(""),
_texture(nullptr)
{
}


Sprite::~Sprite()
{
    for(auto& child : _children)
        child->release();
}


Sprite* Sprite::create(const std::string& fileName)
{
    auto ret = new (std::nothrow) Sprite();
    if ( ret && ret->initWithFile(fileName) )
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}


bool Sprite::initWithFile(const std::string& fileName)
{
    _fileName = fileName;
    _texture = TextureCache::getInstance().addImage(fileName);
    
    if ( _texture ) return true;
    return false;
}


void Sprite::draw()
{
    // draw self
    std::cout << "draw [" << _fileName << "]" << std::endl;
    for( auto& child : _children )
        child->draw();
}


void Sprite::addChild(Sprite* object)
{
    object->retain();
    _children.push_back(object);
}








