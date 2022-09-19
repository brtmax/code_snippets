#include <utility>
using namespace std;
// For future reference

// Rule of 5 -> Formerly rule of 3
struct Foo {

    // special member functions

    Foo() = default; // Default constructor
    Foo(Foo const& other) = default; // Copy constructor
    Foo& operator=(Foo const& other) = default;  // Copy assignment operator
    Foo(Foo&& other) = default; // Move constructor
    Foo& operator=(Foo&& other) = default; // Move assignment operator
    ~Foo() = default; // Destructor
};

int main() {

}