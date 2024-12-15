// #include <iostream>
// #include <algorithm>
// #include <string>
// using namespace std;
// int main() {
//     std::string str = "Hello world from C++";

//     // Remove spaces from the string
//     // cout<<"begn "<<str.begin()<<endl;
//     // cout<<"end "<<str.end()<<endl;

//     str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

//     std::cout << "String without spaces: " << str << std::endl;

//     return 0;
// }


#include <iostream>
#include <unordered_map>
using namespace std;

// function prototype for display_unordered_map()
void display_unordered_map(const unordered_map<int, string> &);

int main() {

  unordered_map<int, string> student {

    {132, "Mark"},
    {143, "Chris"},
     {132, "reshe"},
  };
  
  cout << "Initial Unordered Map:\n";
  display_unordered_map(student);

//   // remove element with key: 143  
//   student.erase(143);
  
//   cout << "\nFinal Unordered Map: \n";
//   display_unordered_map(student);

  return 0;
}

// utility function to print unordered_map elements
void display_unordered_map(const unordered_map<int, string> &umap){

  for(const auto& key_value: umap) {
    int key = key_value.first;
    string value = key_value.second;
    
    cout << key << " - " << value << endl;
  }
}