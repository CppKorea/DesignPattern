//
//  Sprite.cpp
//  fly_weight
//
//  Created by mac on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Sprite.hpp"
#include "TextureCache.hpp"


Sprite::Sprite() :
_fileName("")
{}


Sprite::~Sprite()
{}


Sprite* Sprite::create(const std::string& fileName)
{
    auto ret = new (std::nothrow) Sprite();
    if ( ret && ret->initWithFile(fileName) )
    {
        return ret;
    }
    delete ret;
    return nullptr;
}


bool Sprite::initWithFile(const std::string& fileName)
{
    _fileName = fileName;
    
    Sprite* texture = TextureCache::getInstance().addImage(fileName);
    if ( texture ) return true;
    else return false;
}


void Sprite::draw()
{
    cout << "draw [" << _fileName << "]" << endl;
}









