//
//  AutoreleasePool.cpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
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


AutoreleasePool& AutoreleasePool::getInstnace()
{
    static AutoreleasePool instance;
    return instance;
}


void AutoreleasePool::addObject(Ref* ref)
{
    _managedObjects.push_back(ref);
}


void AutoreleasePool::clear()
{
    std::vector<Ref*> releasings;
    releasings.swap(_managedObjects);
    for( const auto & obj : releasings )
        obj->release();
}









