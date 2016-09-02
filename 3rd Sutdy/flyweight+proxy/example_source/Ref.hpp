//
//  Ref.hpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

class Ref
{
    
public:
    
    Ref();
    virtual ~Ref();
    
    void retain();
    void release();
    void autorelease();
    
private:
    
    unsigned int _referenceCount;
    
};









