using namespace std;
#pragma  optimize("", off)

int main() {
    int x = 42;
    int const y = 42;
    int& z = x;
    int const& a = y;

    auto x1 = x; // int
    auto x2 = y; // int -> because we are making a copy, ignoring that we had a const
    auto x3 = z; // int -> Also making a copy, so we are ignoring the fact that we have a reference
    auto x4 = a; // int -> Same reasoning as above

    auto& x5 = x; // int&
    auto& x6 = y; // int const& -> Need to add const in order for it to be safe
    auto& x7 = z; // int&
    auto& x8 = a; // int const&

    // These are all going to be const& because we force the compiler to go that far
    auto const& x9 = x;  // int const&
    auto const& x10 = y; // int const&
    auto const& x11 = z; // int const&
    auto const& x12 = a; // int const&

    return 0;
}