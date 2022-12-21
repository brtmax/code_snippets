#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Dog {
    Dog(int age, int weight) 
        : m_age(age)
        , m_weight(weight)
        {}

        bool operator<(Dog const& other) const {
            return m_age < other.m_age;
        }

        bool operator==(int age) const {
            return m_age == age;
        }

        int m_age;
        int m_weight;
};

struct SortByWeightFunctor {
    bool operator()(Dog const& lhs, Dog const& rhs) const {
        return lhs.m_weight < rhs.m_weight; 
    }
 
};

struct FindByWeightFunctor {

    FindByWeightFunctor(int weight)
    : m_weight(weight)
    {}

    bool operator()(Dog const& dog) const {
        return m_weight == dog.m_weight;
    }

    int m_weight;
};

template <typename T>
struct MatchFirstFunctor {
    MatchFirstFunctor(const& T) 
        : m_i(T)
        {}

        // This way we can compare at to anything that has the right
        // interface
        template <typename M>
        bool operator()(M const& pair) {
            return pair.first == m_i;
        }

        T m_i;

};


int main() {
vector<pair<int, bool>> v1 = {make_pair(1, true), make_pair(2, false)};
vector<pair<bool, float>> v2 = {make_pair(true, 1.f), make_pair(false, 2.f)};

    find_if(begin(v1), end(v1), MatchFirstFunctor<int>(2));
    find_if(begin(v2), end(v2), MatchFirstFunctor<bool>(true));



    vector<Dog> v = { Dog(3, 10), Dog(1, 40), Dog(5, 50), Dog(2, 30), Dog(4, 20)};
    sort(begin(v), end(v), SortByWeightFunctor());
    find(begin(v), end(v), 3);
    find_if(begin(v), end(v), FindByWeightFunctor(20));
    return 0;
}