// C++11 / C++14 lambda functions

#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;

struct OrderPairsByFirstValue {
    template <typename T>
    bool operator()(T const& lhs, T const& rhs) const {
        return lhs.first < rhs.first;
    }
};

struct Dog {


    Dog(int age, int weight)
    : m_age(age)
    , m_weight(weight)
    {}

    bool operator<(Dog const& other) const {
        return m_age < other.m_age;
    }

    bool operator==(int const age) const {
        return m_age == age;
    }
    int m_age;
    int m_weight;
};

struct SortDogsByWeightFunctor {
    bool operator()(Dog const& lhs, Dog const& rhs) const {
        return lhs.m_weight < rhs.m_weight;
    }
};

// Functor takes a weight as an argument to its constructor
// and stores that as a member variable. It uses that when 
// it wants to compare to a dog
struct FindDogByWeightFunctor {

    FindDogByWeightFunctor(int m_weight)
    : weight(m_weight) 
    {}

    bool operator()(Dog const& dog) const {
        return dog.m_weight == weight; 
    }

    int weight;
};

int main() {

    vector<pair<int, double>> v1 = {make_pair(1, 1.), make_pair(2, 2.), make_pair(3, 3.) };
    vector<pair<bool, char>> v2 = {make_pair(true, 'a'), make_pair(false, 'b')};

    sort(begin(v2), end(v2), OrderPairsByFirstValue());
    sort(begin(v2), end(v2), OrderPairsByFirstValue());

    auto lambda = [](auto const& lhs, auto const& rhs) {
        return lhs.first < rhs.first;
    };
 



    // This will use the overriden less-than operator and sort them by age
    sort(begin(v1), end(v1));

    // This will sort them by weight using the SortByWeightFunctor
    sort(begin(v1), end(v1), SortDogsByWeightFunctor());

    sort(begin(v1), end(v1), [](Dog const& lhs, Dog const&rhs) {
        return lhs.m_weight < rhs.m_weight;
    });

    find(begin(v1), end(v1), 3);

    find_if(begin(v1), end(v1), FindDogByWeightFunctor(20));

    int weight = 20;
    find_if(begin(v1), end(v1), [weight](Dog const& dog) {
        return dog.m_weight == weight;
    });


    return 0;
}