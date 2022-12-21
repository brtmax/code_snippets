// Perfect forwarding
#include <vector>

using namespace std;

struct Foo {
    Foo() = default;
    Foo(int i, bool b, float f)
    : m_i(i)
    , m_b(b)
    , m_f(f)
    {}

    int m_i;
    bool m_b;
    float m_f;
    // ... potentially a lot of other member variables
};

int main() {
    vector<int> v1;
    {
        Foo f1(1, true, 2.f);
        v1.push_back(v1); // Make a copy
        v1.push_back(move(v1)); // 
        v1.push_back(Foo(1, true, 2.f));

        v1.emplace_back(1, true, 2.f);
    }
    return 0;
}