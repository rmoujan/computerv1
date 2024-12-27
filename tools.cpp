#include "help.hpp"

void ft_error(int code)
{
    if (code == -1)
    {
        cout <<"Please enter an argument !!!"<<endl;
    }
    if (code == -2)
    {
        cout <<"Error : Unexpected Format !!!"<<endl;
    }
    if (code == -3)
    {
        cout <<"Error : Invalid argument !!!"<<endl;
    }
    if (code == -4)
    {
        cout <<"Error : Out of range !!!"<<endl;
    }
    if (code == -6)
    {
        cout <<"Error : The Exponenets aren't  organized !!!"<<endl;
    }
        exit(0);
}

vector<string> split_by_equal(string str)
{
    
    string token;
    vector<string> data;
    std::istringstream ss(str);

    while (std::getline(ss, token, '=')){
        data.push_back(token);
    }
    if (data.size() != 2)
        ft_error(-2);
    return (data);
}


//valid chars are: numbers  - + * =  ^ . space  X 
int check_valid_char(string str)
{
    int i = 0;
    int flag = 0;

    while(str[i])
    {
        if (str[i] == '=')
            flag++;
        if ( !((str[i]>= '0' && str[i] <= '9') || str[i] == '+' 
                || str[i] == '-' ||  str[i] == '=' 
                    || str[i] =='*' || str[i]== '^' 
                        || str[i] == 'X' || str[i] == ' ' || str[i] == '.') )
                    {
                        ft_error(-2);
                    }
        i++;
    }
    if (flag != 1)
        ft_error(-2);
    return (1);
}

vector<string> split_by_minus(string str)
{
    string token;
    vector<string> data;
    std::istringstream ss(str);

    while (std::getline(ss, token, '-'))
    {
        if (token.substr(0, 2) == "%X" || token.substr(0, 2) == "@X")
        {
            token  = token.substr(0, 1) + "1*" +token.substr(1);
        }
        else if (token.substr(0, 1) == "X")
        {
            token  = "1*" +token;
        }
        data.push_back(token);
    }
    return (data);
}

// ##############
vector<string> split_vec_by_star(vector<string> vec)
{
    string token;
    vector<string> data;

    for (string value: vec)
    {
        std::istringstream ss(value);
        while (std::getline(ss, token, '*')){
            data.push_back(token);
        }
    }
    return (data);
}


string replace_with_minus(string str) 
{

    int i = 0;
    while (str[i])
    {
        if (str[i] == '+')
        {
            str[i] = '-';
            str.insert(i + 1, 1, '@');
        }
        else if (str[i] == '-')
        {
            str.insert(i + 1, 1, '%');
        }
        i++;
    }
    return (str);
}

string remove_space(string word)
{
    word = regex_replace(word, regex(" "), "");
    return (word);

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
                if (word[i + 1] == '+')
                {
                    word[i + 1]='@';
                }
                else if (word[i + 1] == '-')
                {
                    word[i + 1]='%';
                }
        }
        i++;
    }
    return (word);
}


double get_number(string str)
{
    try {
        if (str[0] == '@')
            str[0]='+';
        else if (str[0] == '%')
            str[0] = '-';
        double num = std::stod(str);
        if (num  > 2147483647 || num < -2147483648)
            ft_error(-4);
        return (num);
    } catch (const std::invalid_argument& e) {
        ft_error(-3);
    } catch (const std::out_of_range& e) {
        ft_error(-4);
    }
    return (0);
}

void get_expo(string str)
{ 
    if (str.length() == 0 || (str.length() != 3 && str.length() != 1))
        {
            ft_error(-2);
        }
}


vector<pair<double, string>> check_format_expo_left(vector<string> data)
{
    double number;
    vector<pair<double, string>> leftAll;

    for (string str:data)
    {
        size_t pos = str.find('*');
        if (pos != string::npos) 
        {
            string result = str.substr(0, pos);
            number = get_number(result);
            result = str.substr(++pos);
            get_expo(result);
            leftAll.push_back({number, result});
        }
        else 
        {
            double numiro = get_number(str);
            leftAll.push_back({numiro, ""});
        }
    }
    return (leftAll);
}
