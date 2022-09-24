#include <vector>
using namespace std;
#pragma optimize("", off)

struct Shape {
    virtual Shape* Clone() = 0;
    virtual ~Shape() = default;
};

template <typename T>
struct ShapeCRTP : public Shape { //curiously recurring template pattern
    virtual Shape* Clone() override { return new T(*static_cast<T*>this)); }
}; 

// Inherit from ShapeCRTP which is templated on our type
struct Square : public ShapeCRTP<Square> {
    Square* Clone() { return new Square(*this); }
    int x = 1;
};

struct Rectangle : public ShapeCRTP<Rectangle> {
    int x = 1;
    int y = 2;
};

int main() {
    vector<Shape*> v;
    v.push_back(new Square);
    v.push_back(new Rectangle);

    for (auto s : v) {
        Shape* c = s->Clone();
    }
}