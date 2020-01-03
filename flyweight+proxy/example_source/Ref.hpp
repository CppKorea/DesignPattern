//
//  Ref.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
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









