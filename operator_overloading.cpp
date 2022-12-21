// Operator overloading best practices
// Fast advanced operator overloading
// Reference file to be expanded soon

#include <iostream>
#include <string>
#include <list>
using namespace std;

struct Channel {
    string Name;
    int Frequency;

    Channel(string name, int frequency) {
        Name = name;
        Frequency = frequency;
    }

    // Promise compiler that this function will not change member ressources
    // Need to override == operator in order to use .remove
    bool operator==(const Channel& channel) const {
        return this->Name == channel.Name;
    }
};

// Overriding <<
ostream& operator<<(ostream& COUT, Channel& channel) {

    COUT << "Name: " << channel.Name << endl;
    COUT << "Frequency: " << channel.Frequency << endl;
    // Return so that we can use it back to back
    return COUT; 
}

struct MyCollection {
    list<Channel> myChannels;

    void operator+=(Channel& channel) {
        this->myChannels.push_back(channel);
    }
    void operator-=(Channel& channel) {
        this->myChannels.remove(channel);
    }
};

ostream& operator<<(ostream& COUT, MyCollection& myCollection) {
    for (Channel ch : myCollection.myChannels) {
        COUT << ch << endl;
    }
    return COUT;
}

int main() {
    Channel c1 = Channel("channel_1", 42);
    Channel c2 = Channel("chanel_2", 314);

    MyCollection myCollection;
    myCollection += c1;
    myCollection += c2;
    myCollection -= c2;

    cout << myCollection;

    cin.get();
}