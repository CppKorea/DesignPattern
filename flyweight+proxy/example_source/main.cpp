//
//  Texture2D.hpp
//  flyweight, proxy pattern
//
//  Created by mac on 2016. 9. 3..
//  Copyright © 2016년 남준현. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

/*
#include "Texture2D.hpp"
#include "TextureCache.hpp"

int main()
{
    vector<Texture2D*> textures;
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("rock.png"));
    textures.push_back(TextureCache::getInstance().addImage("grass.png"));
    textures.push_back(TextureCache::getInstance().addImage("metal.png"));
    
    for( auto& texture : textures )
        texture->draw();
}

// 의도: 속성이 동일한 객체가 다수 생성된다면, 하나의 객체를 공유해서 사용하자.
// 적용: 동일한 속성을 찾고, 한 곳에서 모아서 관리.

*/


//class Sprite
//{
//public:
//    Sprite() { cout << "Sprite()" << endl; }
//    ~Sprite() { cout << "~Sprite()" << endl; }
//    void draw() { cout << "draw" << endl; }
//};
//
//
//template <typename T>
//class Ptr
//{
//    
//public:
//    
//    Ptr(T* p = nullptr) : _data(p)
//    {
//        
//    }
//    
//    ~Ptr()
//    {
//        delete _data;
//    }
//    
//    T* operator->() { return _data; }
//    T& operator*() { return &_data; }
//    
//private:
//    
//    T* _data;
//    
//};
//
//template <typename T>
//class SharedPtr
//{
//public:
//    
//    SharedPtr(T* p = nullptr) : _data(p)
//    {
//        _ref = new int(1);
//    }
//    
//    SharedPtr(const SharedPtr& copy)
//    {
//        _data = copy._data;
//        _ref = copy._ref;
//        
//        (*_ref) ++;
//        
//        cout << "ref: " << *_ref << endl;
//    }
//    
//    ~SharedPtr()
//    {
//        (*_ref)--;
//        cout << "ref: " << *_ref << endl;
//        if ( *_ref == 0 )
//        {
//            delete _data;
//            delete _ref;
//        }
//    }
//    
//    T* operator->() { return _data; }
//    T& operator*() { return &_data; }
//    
//private:
//    
//    T* _data;
//    int* _ref;
//    
//};
//
//
//int main()
//{
//    SharedPtr<Sprite> spr = new Sprite();
//    spr->draw();
//    SharedPtr<Sprite> spr2 = spr;
//}


#include <chrono>
#include <thread>

#include "Sprite.hpp"
#include "AutoreleasePool.hpp"

int main()
{
    auto scene = Sprite::create("empty.png");
    for(int i = 0 ; i < 2 ; ++ i )
    {
        auto spr = Sprite::create("rock.ng");
        scene->addChild(spr);
    }
    for(int i = 0 ; i < 2 ; ++ i )
    {
        auto spr = Sprite::create("grass.png");
        scene->addChild(spr);
    }
    scene->retain();
    
    auto start = chrono::high_resolution_clock::now();

    // game loop
    while ( true )
    {
        if ( scene ) scene->draw();
        
        // 1초 후 발생하는 event
        auto curr = chrono::high_resolution_clock::now();
        auto interval = chrono::duration_cast<chrono::seconds>(curr - start);
        if ( scene && interval.count() > 1 )
        {
            scene->release();
            scene = nullptr;
        }
        
        AutoreleasePool::getInstnace().clear();
    }
}











