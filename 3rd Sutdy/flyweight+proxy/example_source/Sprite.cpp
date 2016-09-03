//
//  Sprite.cpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#include <iostream>
#include <new> // std::nothrow

#include "Sprite.hpp"
#include "TextureCache.hpp"


Sprite::Sprite() :
_fileName(""),
_texture(nullptr)
{
//   _texture = TextureCache::getInstance().addImage(fileName);
    
    // 생성자의 문제점: 반환값이 없음.
//    if (_texture) return true;
//    return false;
}


Sprite::~Sprite()
{
    std::cout << "~Sprite()" << std::endl;
    for(auto child : _children)
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
    // self draw
    std::cout << "draw [" << _fileName << "]" << std::endl;
    for(auto& child : _children)
        child->draw();
}


void Sprite::addChild(Sprite* spr)
{
    spr->retain();
    _children.push_back(spr);
}









