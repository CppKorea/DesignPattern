#pragma once
#include <iostream>
#include <conio.h>

#include "./FrameBuffer.h"

namespace Pattern
{

    class ConsoleScreen
    {
    public:

        void clear()
        {
            // Windows CMD
            //std::system("cls");
        }

        template <u32 Width, u32 Height>
        void render(const FrameBuffer<Width, Height>& _buffer)
        {
            using namespace std;
            this->clear();

            cout << "Rendering... " << Width << ", " << Height << endl;

            cout << hex << uppercase ;
            // Row-based access
            for (auto y = 0; y < Height; ++y) {
                for (auto x = 0; x < Width; ++x) {
                    cout << _buffer[{x, y}] << ' ';
                }
                cout << '\n';
            }
            /*
            // Column-based access
            for (auto x = 0; x < Width; ++x) {
                for (auto y = 0; y < Height; ++y) {
                    cout << _buffer[{x, y}] << ' ';
                }
                cout << '\n';
            }
            */
            cout << dec << endl;
        }

    };


    template <u32 Width, u32 Height>
    ConsoleScreen& operator << (ConsoleScreen& _out, 
                                const FrameBuffer<Width, Height>& _buffer)
    {
        _out.render(_buffer);
        return _out;
    }

}// namespace Pattern

