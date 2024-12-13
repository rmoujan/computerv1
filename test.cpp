#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main() {
    std::string str = "Hello world from C++";

    // Remove spaces from the string
    // cout<<"begn "<<str.begin()<<endl;
    // cout<<"end "<<str.end()<<endl;

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    std::cout << "String without spaces: " << str << std::endl;

    return 0;
}
