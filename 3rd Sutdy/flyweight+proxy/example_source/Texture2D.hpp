//
//  Texture2D.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>

#include <chrono>
#include <thread>

class Texture2D
{
    
public:
    
    Texture2D(const std::string& fileName) : _fileName(fileName)
    {
        std::cout << "loading... [" << _fileName << "]" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    void draw()
    {
        std::cout << "draw [" << _fileName << "]" << std::endl;
    }
    
private:
    
    std::string _fileName;
    
};









