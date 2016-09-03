//
//  AutoreleasePool.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#pragma once

#include <vector>

class Ref;

class AutoreleasePool
{
    
public:
    
    static AutoreleasePool& getInstnace();
    
    virtual ~AutoreleasePool();
    
    void addObject(Ref* ref);
    void clear();

private:
    
    AutoreleasePool();
    
private:
    
    std::vector<Ref*> _managedObjects;
    
};









