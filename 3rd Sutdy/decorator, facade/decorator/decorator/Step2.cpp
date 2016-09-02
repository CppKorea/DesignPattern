#include <iostream>
#include <algorithm>
#include <vector>
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

	template<typename FUNC,typename ...AS>
	void draw(FUNC func, AS&& ...as) {
		draw();
		func(as...);
	}
};

void scollText(int a,int b) {
	std::cout << "ScollText code" << std::endl;
}

int main() {
	TextField textfield(10, 10);
	textfield.draw(scollText,10,10);

	
}