//
//  Texture2D.h
//  flyweight+proxy
//
//  Created by 남준현 on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class Texture2D
{
    
public:
    
    explicit Texture2D(const std::string& fileName)
    {
        std::cout << "loading ... [" << fileName << "]" <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
};