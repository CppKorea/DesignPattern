
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


class Decorator : public Widget {

private:
	Widget* wid;      

public:
	Decorator(Widget* w) {
		wid = w;
	}

	void draw() {
		wid->draw();
	}

	~Decorator() {
		delete wid;
	}
};


class BorderDecorator : public Decorator {

public:
	BorderDecorator(Widget* w) : Decorator(w) { }
	void draw() {
		Decorator::draw();
		cout << "   BorderDecorator" << '\n';
	}
};

class ScrollDecorator : public Decorator {
public:
	ScrollDecorator(Widget* w) : Decorator(w) { }
	void draw() {
		Decorator::draw();
		cout << "   ScrollDecorator" << '\n';
	}
};

class LolDecorator : public Decorator {
public:
	LolDecorator(Widget* w) : Decorator(w) { }
	void draw() {
		Decorator::draw();
		cout << "   LolDecorator" << '\n';
	}
};

int main(void) {

	Widget* aWidget = new LolDecorator(new LolDecorator(new LolDecorator(new BorderDecorator(
		new ScrollDecorator(
			new TextField(80, 24))))));
	aWidget->draw();
	delete aWidget;
}