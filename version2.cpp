#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

void ft_error(int code)
{
    if (code == -1)
    {
        cout <<"Please enter an argument"<<endl;
    }
    if (code == -2)
    {
        cout <<"Error : Unexpected Format !!!"<<endl;
    }
    if (code == -3)
    {
        cout <<"Error : Invalid argument"<<endl;
    }
    if (code == -4)
    {
        cout <<"Error : Out of range"<<endl;
    }
    if (code == -5)
    {
        cout <<"Error : Out of range"<<endl;
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

// int create_reduced_form(string str)
// {
//     vector<string> tokens;
//     string token;
//     std::istringstream ss(str);
//     int flag = 0;
//     while (std::getline(ss, token, ' ')) {
//         if (flag == 1)
//         {
//             if (token == "0" || token == "1" || token == "2"
//                 || token == "3" || token == "4" || token == "5" 
//                 || token == "6" || token == "7" || token == "8" 
//                 || token == "9")
//                 {
//                     cout <<"OK this is token|"<<token<<"|"<<endl;
//                     tokens.push_back("-");

//                 }
//         }
//         tokens.push_back(token);
//         if (token == "=")
//             flag++;
//     }

//     for (const auto& word : tokens) {
//         std::cout << word << std::endl;
//     }
//     return 0;
// }

void split_by_space(string str)
{

    vector<string> tokens;
    string token;
    map<string, float> equation;
    
        std::istringstream tt(str);
        while (tt >> token) {
            cout<<"|"<<token<<"|"<<endl;
            tokens.push_back(token);
        }
    // std::cout << "Size of the vector: " << tokens.size() << std::endl;
}

vector<string> split_by_equal(string str)
{
    
    string token;
    vector<string> data;
    std::istringstream ss(str);

    while (std::getline(ss, token, '=')){
        // cout<<"|"<<token<<"|"<<endl;
        data.push_back(token);
    }

    if (data.size() != 2)
        ft_error(-2);

    // cout <<"SIZE OF VECTOR IS "<<data.size()<<endl;
    return (data);
}

//valid chars are: numbers / - + * =  ^ . space / X / 
int check_valid_char(string str)
{
    int i = 0;
    int flag = 0;
    // cout <<"Test check valid char"<<endl;
    while(str[i])
    {
        if (str[i] == '=')
            flag++;
        if ( !((str[i]>= '0' && str[i] <= '9') || str[i] == '+' 
                || str[i] == '-' ||  str[i] == '=' 
                    || str[i] =='*' || str[i]== '^' 
                        || str[i] == 'X' || str[i] == ' ' || str[i] == '.') )
                    {
                        // cout <<"|Inside check valid "<<str[i]<<"|"<<endl;
                        ft_error(-2);
                    }
        i++;
    }
    if (flag != 1)
        ft_error(-2);
    // cout <<"after while"<<endl;
    return (1);
}

vector<string> split_by_minus(string str)
{
    string token;
    vector<string> data;
    std::istringstream ss(str);
    cout<<"Split by MINUS"<<std::endl;
    while (std::getline(ss, token, '-')){
        cout<<"|"<<token<<"|"<<endl;
        data.push_back(token);
    }
    return data;
}


vector<string> split_vec_by_star(vector<string> vec)
{
    string token;
    vector<string> data;
    for (string value: vec)
    {
        std::istringstream ss(value);
        cout<<"Split The Vector by STAR"<<std::endl;
        while (std::getline(ss, token, '*')){
            cout<<"|"<<token<<"|"<<endl;
            data.push_back(token);
        }
    }
    cout <<" ********** After spliting by star :: "<<endl;
    cout <<"size of vector "<<data.size();
    cout <<"------------------------"<<endl;
    for (string value:data)
    {
        cout <<"|"<<value<<"|"<<endl;
    }
    cout <<"-----------------------------"<<endl;
    cout <<"Size of the original vec is "<<vec.size()<<endl;
    //hadi ila zedtha , u ll nor handle the bonus
    // if (vec.size() * 2 != data.size() && vec.size() != 1)
    // {
    //     ft_error(-2);
    // }
    cout <<"FINAL "<<endl;
    return data;
}


string replace_with_minus(string str) {

    int i = 0;
    while (str[i])
    {
        if (str[i] == '+')
        {
            str[i] = '-';
        }
        i++;
    }
    return str;
}

string remove_space(string word)
{
    word = regex_replace(word, regex(" "), "");
    return word;

}

string flag_sign(string word)
{
    int i = 1;

    if (word[0] == '+')
        word[0] = '@';
    else if (word[0] == '-')
        word[0] = '%';
    
    while(word[i])
    {
        if (word[i] == '=')
        {
            // cout <<"==========|"<<word[i]<<"| and |"<<word[i + 1]<<"|"<<endl;
                if (word[i + 1] == '+')
                {
                    // cout <<"=== et +++ "<<endl;
                    word[i + 1]='@';
                }
                else if (word[i + 1] == '-')
                {
                    // cout <<"=== et --- "<<endl;
                    word[i + 1]='%';
                }
        }
        i++;
    }
    return word;
}

void combine_all(vector<string> leftTokens, vector<string> rightTokens)
{
    //store duplicate keys and unsorted :
    std::vector<std::pair<int, std::string>> all;

    std::vector<string> first;
    std::vector<string> second;

    // split_vec_by_star(leftTokens);
    // split_vec_by_star(rightTokens);


}

double get_number(string str)
{
    try {
        if (str[0] == '@')
            str[0]='+';
        else if (str[0] == '%')
            str[0] = '-';
        double num = std::stod(str); // Attempt to convert
        std::cout << "Integer: " << num << std::endl;
        return num;
    } catch (const std::invalid_argument& e) {
        ft_error(-3);
    } catch (const std::out_of_range& e) {
        ft_error(-4);
    }
    return (0);
}

string get_expo(string str)
{
    cout <<"----------- Start Handling the expo ------------ "<<endl;
    cout<<"length of str is "<<str.length()<<endl;
    if (str.length() == 0)
        {
            ft_error(-2);
        }
    else if (str != "X^0" && str != "X^1" && str != "X^2" && str != "X^3" && str != "X")
    {
        ft_error(-2);
    }
    return "";
}
//take the number jsk each the end of string or reach the star.
//WESLT HENA 
void check_format_expo_left(vector<string> data)
{
    int i = 0;
    double number;
    // int key, 
    // string expo;
    //should check the 4 cases :
    // 1 case :
    for (string str:data)
    {
        cout <<"[ First String: "<<str<<endl;
        size_t pos = str.find('*');
        // if this is true, then am expecting two strings , first is number , second if expo.
        if (pos != string::npos) {
            // Extract substring up to the delimiter
            string result = str.substr(0, pos);
            number = get_number(result);
            cout << "Substring before *: " << result << endl;
            result = str.substr(++pos);
            cout << "Substring after  *: " << result<<" and length of str is "<<result.length()<< endl;
            get_expo(result);
        }
        else {
            //there is no star, that's mean , should check if the input is a nbr or expo
            std::cout << "Delimiter not found!" << endl;
            }
    }
}

int main(int argc, char *argv[])
{
    // cout <<"argc is "<<argc<<endl;
    // cout <<"BEFORE argv is "<<argv[1]<<endl;
    if (argc == 1)
        ft_error(-1);
     check_valid_char(argv[1]);
    string word = remove_space(argv[1]);
    cout <<"******* Word after remove spaces |"<<word<<endl;
    //then flagi beginne d equation if there is a sign and after =.
    string strr = flag_sign(word);
    // cout <<"** after flag sign" <<strr<<endl;
    string newStr = replace_with_minus(strr);
    // cout <<"AFTER argv is "<<newStr<<endl;

    vector<string> data;
    vector<string> leftTokens;
    vector<string> rightTokens;

    data = split_by_equal(newStr);
    leftTokens = split_by_minus(data[0]);
    // cout <<"size of leftTokens is "<<leftTokens.size()<<endl;
    // cout <<"LEFTTOKENS "<<endl;
    // for (string value:leftTokens)
    // {
    //     cout <<"{"<<value[0]<<"}"<<endl;
    // }
    check_format_expo_left(leftTokens);
    // cout<<"*********** Second str "<<endl;
    // rightTokens = split_by_minus(data[1]);
    // combine_all(leftTokens, rightTokens);
    // cout <<"Original string" <<argv[1]<<endl;
    return 0;
}
