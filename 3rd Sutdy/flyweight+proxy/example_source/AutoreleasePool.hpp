//
//  AutoreleasePool.hpp
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <vector>

class Ref;

class AutoreleasePool
{
    
public:
    
    static AutoreleasePool& getInstance();
    
    virtual ~AutoreleasePool();
    
    void addObject(Ref* object);
    void clear();
    
private:
    
    AutoreleasePool();
    std::vector<Ref*> _managedObjects;
    
};









