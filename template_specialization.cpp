#include <type_traits>
using namespace std;
#pragma optimize("", off)

// tag dispatch
// SFINAE -> substitution failure is not an error

template <typename T>
bool Equals(T lhs, T rhs) {
    // Dispatch it
    return Equals(lhs, rhs, conditional_t<is_floating_point<T>::value, true_type, false_type>{});
}

template <>
bool Equals<float>(float lhs, float rhs) {
    
    // Takes floating point imprecision into account

}

template <typename T>
bool Equals(T lhs, T rhs, true_type) { // floating

    // Imprecision handling
    return true;
}

template <typename T>
bool Equals(T lhs, T rhs, false_type) { // non-floating
    return lhs == rhs;
}

int main() {
    bool b = Equals(0.42f - 0.4f, 0.02f);

    Equals(1, 1);
    return 0;
}