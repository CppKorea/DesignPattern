//
//  Ref.cpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>

#include "Ref.hpp"
#include "AutoreleasePool.hpp"

Ref::Ref() :
_referenceCount(1)
{
}


Ref::~Ref()
{
}


void Ref::retain()
{
    _referenceCount++;
}


void Ref::release()
{
    if ( _referenceCount <= 0) return ;
    
    
    _referenceCount--;
    if ( _referenceCount == 0 )
    {
        std::cout << "deleted" << std::endl;
        delete this;
    }
}


void Ref::autorelease()
{
    AutoreleasePool::getInstance().addObject(this);
}









