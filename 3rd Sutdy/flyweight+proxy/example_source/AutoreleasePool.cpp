//
//  AutoreleasePool.cpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include "AutoreleasePool.hpp"
#include "Ref.hpp"

AutoreleasePool::AutoreleasePool()
{
    _managedObjects.reserve(150);
}


AutoreleasePool::~AutoreleasePool()
{
    _managedObjects.clear();
}


AutoreleasePool& AutoreleasePool::getInstance()
{
    static AutoreleasePool instance;
    return instance;
}


void AutoreleasePool::addObject(Ref* object)
{
    _managedObjects.push_back(object);
}


void AutoreleasePool::clear()
{
    std::vector<Ref*> releasings;
    releasings.swap(_managedObjects);
    for(const auto& obj : releasings)
        obj->release();
}









