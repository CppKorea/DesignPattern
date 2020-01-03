#include <iostream>


using namespace std;


class Widget {

public:
	virtual void draw() = 0;
	virtual ~Widget() {}
};


class TextField : public Widget {

private:
	int width, height;

public:
	TextField(int w, int h) {
		width = w;
		height = h;
	}

	void draw() {
		cout << "TextField: " << width << ", " << height << '\n';
	}
};


int main() {
	TextField textfield(10, 10);
	textfield.draw();
}