// Move Semantics C++ 11/14
#include <utility>

using namespace std;

struct Foo {
   
   Foo() = default;
   Foo(int i )
    : i(new int(i))
    {}

    Foo(Foo const& other) {
        if(other.i != nullptr) {
            i = new int(*other.i);
        }
    }

    Foo& operator=(Foo const& other) {
        if (other.i != nullptr) {
            // i = new int(*other.i);
        }
        return *this;
    }

    // Overwriting copy operator
    Foo& operator=(Foo&& other) { // rvalue reference
        if (other.i != nullptr) {
            i = other.i;
            other.i = nullptr;
        }
        return *this;
    }

    ~Foo() {
        delete i;
        i = nullptr;
    }

     int * i = nullptr;
};

template <typename T, typename U>
bool Equals(T lhs, U rhs) {
    return lhs == rhs;
}

void FuncByValue(Foo other); // value semantics
void FuncByRef(Foo& other); // reference semantics

int ReturnPRvalue() { return 42;}

int main() {
    Foo f1;
    int i = ReturnPRvalue();
   {
       Foo f2;
       f2.i = new int(42);
       // Move treats f2 as an expiring value, we 
       // explicitly tell the compiler that f2 is going to go out of scope
       // f1 = move(f2); // xvalue

       f1 = Foo(42); // prvalue

   }
}