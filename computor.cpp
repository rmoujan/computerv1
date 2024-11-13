#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void ft_error(int code)
{
    if (code == -1)
    {
        cout <<"Please enter an argument"<<endl;
    }
        exit(0);
}
void ft_output()
{
    cout<<"Reduced form: "<<endl;
    cout<<"Polynomial degree: "<<endl;
    cout<<"The solution is: "<<endl;
}

// int ft_check_coefficient()
// {
// }
// int ft_check_exponent()
// {
// }

int create_reduced_form(string str)
{
    vector<string> tokens;
    string token;
    std::istringstream ss(str);
    int flag = 0;
    while (std::getline(ss, token, ' ')) {
        if (flag == 1)
        {
            if (token == "0" || token == "1" || token == "2"
                || token == "3" || token == "4" || token == "5" 
                || token == "6" || token == "7" || token == "8" 
                || token == "9")
                {
                    cout <<"OK this is token|"<<token<<"|"<<endl;
                    tokens.push_back("-");

                }
        }
        tokens.push_back(token);
        if (token == "=")
            flag++;
    }

    for (const auto& word : tokens) {
        std::cout << word << std::endl;
    }
    return 0;
}

// int calcuk_delta()
// {
    
// }

int main(int argc, char *argv[])
{
    cout <<"argc is "<<argc<<endl;
    if (argc == 1)
        ft_error(-1);
    create_reduced_form(argv[1]);
    // cout <<argv[1]<<endl;
    //you need to check the term entered (they said that every enteris always right)
    //so we should make the reduced form:
    return 0;
}