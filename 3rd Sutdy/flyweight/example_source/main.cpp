//
//  ex00.cpp
//  fly_weight
//
//  Created by mac on 2016. 9. 2..
//  Copyright © 2016년 realtrick. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

// ex01

class Sprite
{
    
public:
    
    Sprite(const std::string& fileName)
    {
        _fileName = fileName;
        
        cout << "loading texture... " << _fileName << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    void draw()
    {
        cout << "draw " << _fileName  << endl;
    }
    
private:
    
    std::string _fileName;
    
};

int main()
{
    vector<Sprite*> imgs;
    imgs.push_back(new Sprite("rock.png"));
    imgs.push_back(new Sprite("rock.png"));
    imgs.push_back(new Sprite("grass.png"));
    
    for(auto& img : imgs)
        img->draw();
}

// ex02

// 기존의 문제: 불필요한 로딩시간이 걸린다.
// 해결: 중복을 제거
// cocos2d-x의 구현

//#include "Sprite.hpp"
//#include "TextureCache.hpp"
//
//int main()
//{
//    std::vector<Sprite*> renderer;
//    renderer.push_back(Sprite::create("rock.png"));
//    renderer.push_back(Sprite::create("rock.png"));
//    renderer.push_back(Sprite::create("rock.png"));
//    renderer.push_back(Sprite::create("rock.png"));
//    renderer.push_back(Sprite::create("grass.png"));
//    renderer.push_back(Sprite::create("grass.png"));
//    renderer.push_back(Sprite::create("grass.png"));
//   
//    for(auto& obj : renderer)
//    {
//        obj->draw();
//    }
//}








