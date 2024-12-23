#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
using namespace std;
//global variables.


char degree='0';
string reduced;
int flag = 0;


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
    if (code == -6)
    {
        cout <<"Error : The Exponenets aren't  sorted"<<endl;
    }
        exit(0);
}

// void ft_output()
// {
//     cout<<"Reduced form: "<<endl;
//     cout<<"Polynomial degree: "<<endl;
//     cout<<"The solution is: "<<endl;
// }



void split_by_space(string str)
{
    vector<string> tokens;
    string token;

    std::istringstream tt(str);
    while (tt >> token)
    {
        // cout<<"|"<<token<<"|"<<endl;
        tokens.push_back(token);
    }
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

//valid chars are: numbers / - + * =  ^ . space / X / 
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
    // string newTkn;
    cout<<"Split by MINUS  |"<<str<<"|"<<std::endl;
    while (std::getline(ss, token, '-'))
    {
        cout<<"{} |"<<token<<"|"<<endl;
        //add 1 * token  binsba ltoken that hasn't a coeff
        //hadsh li zedt bash n handli case d bns , ms still hadi =X^2
        if (token.substr(0, 2) == "%X" || token.substr(0, 2) == "@X")
        {
            cout <<"just the coeff |"<<token.substr(0, 2) <<"|"<<endl;
            //must add between @ and X the 1 , but I must flag it.
            //hena fin kayn error, cuz substr matspltas zn.
            // %X^3
            token  = token.substr(0, 1) + "1*" +token.substr(1);
            cout <<"########## |"<<token<<"|"<<endl;
        }
        else if (token.substr(0, 1) == "X")
        {
            token  = "1*" +token;
            cout <<"~~~~~~~~~~~~~~~~~~  |"<<token<<"|"<<endl;
        }
        data.push_back(token);
    }
    return (data);
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
    // cout <<" ********** After spliting by star :: "<<endl;
    // cout <<"size of vector "<<data.size();
    // cout <<"------------------------"<<endl;
    // for (string value:data)
    // {
    //     cout <<"|"<<value<<"|"<<endl;
    // }
    // cout <<"-----------------------------"<<endl;
    // cout <<"Size of the original vec is "<<vec.size()<<endl;
    // //hadi ila zedtha , u ll nor handle the bonus
    // // if (vec.size() * 2 != data.size() && vec.size() != 1)
    // // {
    // //     ft_error(-2);
    // // }
    // cout <<"FINAL "<<endl;
    return (data);
}


string replace_with_minus(string str) {

    int i = 0;
    while (str[i])
    {
        if (str[i] == '+')
        {
            str[i] = '-';
            str.insert(i + 1, 1, '@');//flag position
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
                // else if (word[i + 1] == 'X')
                // {
                //     word[i + 1]='@';
                // }
        }
        i++;
    }
    return (word);
}

// void combine_all(vector<string> leftTokens, vector<string> rightTokens)
// {
//     //store duplicate keys and unsorted :
//     std::vector<std::pair<int, std::string>> all;

//     std::vector<string> first;
//     std::vector<string> second;

//     // split_vec_by_star(leftTokens);
//     // split_vec_by_star(rightTokens);
// }

double get_number(string str)
{
    try {
        if (str[0] == '@')
            str[0]='+';
        else if (str[0] == '%')
            str[0] = '-';

        double num = std::stod(str); // Attempt to convert
        // std::cout << "Integer: " << num << std::endl;
        return num;
    } catch (const std::invalid_argument& e) {
        // cout <<"HON "<<endl;
        ft_error(-3);
    } catch (const std::out_of_range& e) {
        ft_error(-4);
    }
    return (0);
}

void get_expo(string str)
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
}

//take the number jsk each the end of string or reach the star.
//WESLT HENA 
vector<pair<double, string>> check_format_expo_left(vector<string> data)
{
    // int i = 0;
    double number;
    vector<pair<double, string>> leftAll;//like map but hold duplicated keys and unorder
    // int key, 
    // string expo;
    //should check the 4 cases :
    // 1 case :
    //number * X
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
            leftAll.push_back({number, result});
        }
        else {
                //there is no star, that's mean , should check if the input is a nbr or expo
                std::cout << "Delimiter not found! |" <<str<<"|"<< endl;
                // get_expo(result);
                //ban liya nezidha hena hadik case deyal  or %X2.
                // // leftAll.push_back({1, result});
                // if (!str.empty())
                // {
                // //also may be will be just the expo , and it is true, bcz I will predict the coeff is 1.
                //     if (str[0] == '%' || str[0] == '@')
                //     {
                //         // %X2 or @X2
                //         cout <<"INside str.substr(1)  "<<str.substr(1)<<endl;
                //         get_expo(str.substr(1));
                //         if (str[0] == '@')
                //             str[0] = '+';
                //         else if (str[0] == '%')
                //             str[0] = '-';
                //         leftAll.push_back({'1', str});
                //     }
                // }
            
                //SHOULD BE A NUMBER AND i WLL PREDICT THE X HAS 0 EXP.x^0
                    double numiro = get_number(str);
                    leftAll.push_back({numiro, ""});
            }
    }
    return (leftAll);
}


//take the last char of value.
//need to check if the exp are organized from the lower to the bigger.
void check_order_exp(vector<pair<double, string>> leftAll)
{
    cout <<"Global degree is  |"<<degree<<"|"<<endl;
    std::vector<char> charExpo;
    if (!leftAll.empty())
    {
        for (const auto& p : leftAll) {
            if (!p.second.empty()){
                std::cout << "{ value :" << p.second.back() << "}" << std::endl;
                if (p.second.back() == 'X')
                    charExpo.push_back('1');
                else
                    charExpo.push_back(p.second.back());
            }
        }
    }
    if (!charExpo.empty())
    {
        cout <<"--- Outputing char chars ---- "<<endl;
        for(const auto & c: charExpo)
        {
            cout <<"A: "<<c<<endl;
        }
        if ( !(std::is_sorted(charExpo.begin(), charExpo.end())) ) {
            ft_error(-6);
        }
            // flag = 1;
            // auto maxIt = std::max_element(charExpo.begin(), charExpo.end());
            // if (*maxIt > degree)
            //     degree = *maxIt;
            // cout <<"Max Degree is "<<*maxIt<<endl;
        // } else {
        //     ft_error(-6);
        //     // std::cout << "The vector is not sorted." << std::endl;
        // }

    }
}

// - * -1 = +
// + * -1 = -
// add numbers with the same coefficients:
// making the reduced form:

void calcul_all_tokens(vector<pair<double, string>> &left, vector<pair<double, string>>&right)
{
    cout<< "produce the reduced form "<<endl;

    for (auto it1 = left.begin(); it1 != left.end();)
    {   
        for (auto it2 = right.begin(); it2 != right.end();)
        {
        
                    cout <<"it1->second is "<<it1->second << " and it2->second is "<<it2->second<<endl;
                    cout <<"1TRue or false "<<(it1->second == "X^0" && it2->second == "!") <<endl;
                    cout <<"2TRue or false "<<(it1->second == "!" && it2->second  == "X^0") <<endl;
                    if ((it1->second == it2->second)) 
                    {
                        cout <<"111111111111111111111111"<<endl;

                        it1->first = it1->first + (it2->first * -1);
                        cout <<"REsult is "<<it1->first<<endl;
                        it2 = right.erase(it2);
                    
                    }
                    else if ((it1->second == "X^0" && it2->second == "") || 
                        (it1->second == "" && it2->second  == "X^0"))
                    {
                        cout <<"222222222222222222222222222222"<<endl;

                        it1->first = it1->first + (it2->first  * - 1);
                        it1->second = "X^0";
                        cout <<"REsult is "<<it1->first<<endl;
                        it2 = right.erase(it2);
                    }
                 else
                    it2++;
        }
        it1++;
    }
    // add what's left in right to the left vector: 

  
    for (auto it2 = right.begin(); it2 != right.end();)
    {
        left.push_back(std::make_pair((it2->first)*(-1), it2->second));
        it2++;
    }
    //must be added 
    // for (auto it2 = left.begin(); it2 != left.end();)
    // {
    //     if (it2->first == 0)
    //     {
    //         it2 = left.erase(it2);
    //     }
    //     else
    //         it2++;
    // }
    // cout<< "after calcule and remove the form "<<endl;
    // for (const auto& p : left) {
    //     std::cout << "{" << p.first << ", " << p.second << "}\n";
    // }
}

//second vers :
void calcul_tokens(vector<pair<double, string>> &left)
{
    cout<< "produce the reduced form "<<endl;

    for (auto it1 = left.begin(); it1 != left.end();)
    {   
        for (auto it2 = it1 + 1; it2 != left.end();)
        {
        
                //if (!it1->second.empty() && !it2->second.empty()) 
                //{
                //cout <<"it1->second is "<<it1->second << " and it2->second is "<<it2->second<<endl;
                //cout <<"1TRue or false "<<(it1->second == "X^0" && it2->second == "!") <<endl;
                //cout <<"2TRue or false "<<(it1->second == "!" && it2->second  == "X^0") <<endl;

                    if ((it1->second == it2->second)) 
                    {
                        cout <<"111111111111111111111111"<<endl;

                        it1->first = it1->first + it2->first;
                        cout <<"REsult is "<<it1->first<<endl;
                        it2 = left.erase(it2);
                    
                    }
                    else if ((it1->second == "X^0" && it2->second == "") || 
                        (it1->second == "" && it2->second  == "X^0"))
                    {
                        cout <<"222222222222222222222222222222"<<endl;
                        it1->first = it1->first + it2->first;
                        it1->second = "X^0";
                        cout <<"REsult is "<<it1->first<<endl;
                        it2 = left.erase(it2);
                    }
                 else
                    it2++;
        }
        it1++;
    }
}

void remove_zero_coeff(vector<pair<double, string>> &left)
{
    for (auto it2 = left.begin(); it2 != left.end();)
    {
        if (it2->first == 0)
        {
            it2 = left.erase(it2);
        }
        else
            it2++;
    }
}
void check_degree(vector<pair<double, string>> leftAll)
{
    cout <<"Global degree is  |"<<degree<<"|"<<endl;
    std::vector<char> charExpo;
    if (!leftAll.empty())
    {
        for (const auto& p : leftAll) {
            if (!p.second.empty()){
                std::cout << "{ value :" << p.second.back() << "}" << std::endl;
                if (p.second.back() == 'X')
                    charExpo.push_back('1');
                else
                    charExpo.push_back(p.second.back());
            }
        }
    }
    if (!charExpo.empty())
    {
        auto maxIt = std::max_element(charExpo.begin(), charExpo.end());
        if (*maxIt > degree)
            degree = *maxIt;
    }
}

void output_reduced_form(vector<pair<double, string>> left)
{
    string test= "";
    string sign = "";
    //must concatenate the vector with the next.
     std::stringstream ss;
     cout <<"size of vector is "<<left.size()<<endl;
    for (auto it = left.begin(); it != left.end();)
    {
        auto signPtr = it + 1;
        if (signPtr != left.end())
        {
            if (signPtr->first >= 0)
            {
                cout <<"+signPtr "<<signPtr->first<<" and value is "<<signPtr->second<<endl;
                sign = " + ";

            }
            else
            {
                cout <<"-signPtr "<<signPtr->first<<" and value is "<<signPtr->second<<endl;
                sign = " - ";
                // it->first = it->first * (-1);
            }
        }
        if (it->first < 0 && it != left.begin())
        {
            cout <<"it->first is negative "<<it->first<<endl;
            it->first = it->first * (-1);

        }
        std::stringstream ss;
        ss << (it->first);
        std::string str = ss.str();
        cout <<"str is "<<str<<" and sign is "<<sign<<endl;
        
        // if (it == left.end() - 1)
        //     sign = " = 0";
        //KAYN SHI PRLM F SIGN KHASNI NEGAD ORDER DEYAL HAD CONCATENATION
        if (!it->second.empty())
        {
            it->second = " * " + it->second;
        }
        test +=str + it->second + sign;
        // else
        //     test +=str + " * " + it->second + sign;
        it++;
        sign = "";
    }
    cout <<"Reduced form: "<<test<<" = 0 "<<endl;
}

double calculateSqrt(double n, double precision = 1e-6) {
    if (n < 0) {
        std::cerr << "Square root of negative numbers is undefined for real numbers.\n";
        return -1;
    }
    double low = 0, high = n, mid;

    while (high - low > precision) {
        mid = (low + high) / 2.0;
        if (mid * mid > n) {
            high = mid; // Narrow the range to the lower half
        } else {
            low = mid; // Narrow the range to the upper half
        }
    }
    return (low + high) / 2.0;
}

//if degree == 2
//we calcul delta only if the equation is like : ax^2+bx^1+c=0
void calcul_delta(vector<pair<double, string>> &leftAll)
{
    double a , b, c;
    //a --> x^2
    //b -- >x^1
    //c --> x^0
    cout<< "equation of two  "<<endl;
    for (const auto& p : leftAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
        if (p.second == "X^2")
            a = p.first;
        else if (p.second == "X^1" || p.second == "X")
            b = p.first;
        else
            c = p.first;
    }
    double delta = (b*b) - (4 * a * c);
    if (delta > 0)
    {
        double root1 = (-b + calculateSqrt(delta)) / (2 * a);
        double root2 = (-b - calculateSqrt(delta)) / (2 * a);
        cout <<"Discriminant is strictly positive, the two solutions are: "<<endl;
        cout <<root1<<endl;
        cout <<root2<<endl;
    }
    else if (delta == 0)
    {
        cout <<"Discriminant is null, the solution is: "<<endl;

        double root = -b / (2 * a);
        cout <<root<<endl;
    }
    else
    {
        cout <<"Discriminant is strictly negative, the two Complex solutions are: "<<endl;
        double realPart = -b / (2 * a);
        double imagPart = calculateSqrt(-delta) / (2 * a);
        std::cout << realPart << " + " << imagPart << "i, "<<endl;
        std::cout << realPart << " - " << imagPart << "i" << std::endl;

    }
}

void equation_degrre1(vector<pair<double, string>> &leftAll)
{
    double a, b;

    for (const auto& p : leftAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
        if (p.second == "X^1" || p.second == "X")
            a = p.first;
        else
            b = p.first;
    }
    cout <<"The solution is:"<<endl;
    cout<<(-b)/a<<endl;
}

int main(int argc, char *argv[])
{
    vector<pair<double, string>> leftAll;
    vector<pair<double, string>> rightAll;
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
    // add_one_to_exp(leftTokens);
    rightTokens = split_by_minus(data[1]);
    cout <<"###################"<<endl;
    leftAll = check_format_expo_left(leftTokens);
    rightAll = check_format_expo_left(rightTokens);
    cout <<" --------------- Calling the fct check order exp "<<endl;
    check_order_exp(leftAll);
    check_order_exp(rightAll);
        cout <<"OUTPUT THE Left VECTOR WITH KEY/VALUE "<<endl;
    for (const auto& p : leftAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
    }
    cout <<"OUTPUT THE Right VECTOR WITH KEY/VALUE "<<endl;
    for (const auto& p : rightAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
    }
    calcul_tokens(leftAll);
    calcul_tokens(rightAll);
    calcul_all_tokens(leftAll, rightAll);
    cout<< "LEFTALL after calcule and remove the form "<<endl;
        for (const auto& p : leftAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
    }
    cout <<"-----------------------------"<<endl;
    cout<< "RIGHT ALL calcule and remove the form "<<endl;
        for (const auto& p : rightAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
    }
    output_reduced_form(leftAll);
    remove_zero_coeff(leftAll);
    check_degree(leftAll);
    cout <<"Polynomial degree: "<<degree<<endl;
    if (degree > 50)
    {
        cout <<"The polynomial degree is strictly greater than 2, I can't solve."<<endl;
    }
    else
    {
        cout<< "LEFTALL after calcule and remove the form "<<endl;
        for (const auto& p : leftAll) {
        std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
        }
        if (degree == 50)
            calcul_delta(leftAll);
        else if(degree == 49)
        {
            cout <<" 111111111 "<<endl;
            equation_degrre1(leftAll);
        }
        else if(degree == 48)
        {
            cout <<" 000000000 "<<endl;
        for (const auto& p : leftAll)
        {
            std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
        }
        if (leftAll.size() == 0)
            cout <<"The equation is always true and has infinitely many solutions."<<endl;
        else
            cout <<"The equation is false, so there are no solutions.."<<endl;
        }
    }
    return 0;
}