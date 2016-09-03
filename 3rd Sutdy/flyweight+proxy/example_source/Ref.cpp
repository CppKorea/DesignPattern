//
//  Ref.cpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

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
    if ( _referenceCount <= 0 ) return ; // assert or throw
    
    _referenceCount--;
    
    if ( _referenceCount == 0)
        delete this;
}


void Ref::autorelease()
{
    AutoreleasePool::getInstnace().addObject(this);
}









