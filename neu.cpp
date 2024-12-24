#include "help.cpp"
char degree='0';

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


string replace_with_minus(string str) {

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
    // else if (str != "X^0" && str != "X^1" && str != "X^2" && str != "X^3" && str != "X")
    // {
    //     ft_error(-2);
    // }
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


void check_order_exp(vector<pair<double, string>> leftAll)
{
    std::vector<char> charExpo;

    if (!leftAll.empty())
    {
        for (const auto& p : leftAll) {
            if (!p.second.empty()){
                if (p.second.back() == 'X')
                    charExpo.push_back('1');
                else
                    charExpo.push_back(p.second.back());
            }
        }
    }
    if (!charExpo.empty())
    {
        if ( !(std::is_sorted(charExpo.begin(), charExpo.end())) ) {
            ft_error(-6);
        }
    }
}

void calcul_all_tokens(vector<pair<double, string>> &left, vector<pair<double, string>>&right)
{
    
    for (auto it1 = left.begin(); it1 != left.end();)
    {   
        for (auto it2 = right.begin(); it2 != right.end();)
        {

                    if ((it1->second == it2->second)) 
                    {
                        it1->first = it1->first + (it2->first * -1);
                        it2 = right.erase(it2);
                    }
                    else if ((it1->second == "X^0" && it2->second == "") || 
                        (it1->second == "" && it2->second  == "X^0"))
                    {
                        it1->first = it1->first + (it2->first  * - 1);
                        it1->second = "X^0";
                        it2 = right.erase(it2);
                    }
                    else if ((it1->second == "X^1" && it2->second == "X") || 
                        (it1->second == "X" && it2->second  == "X^1"))
                    {
                        it1->first = it1->first + (it2->first  * - 1);
                        it1->second = "X^1";
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
}


void calcul_tokens(vector<pair<double, string>> &left)
{


    for (auto it1 = left.begin(); it1 != left.end();)
    {   
        for (auto it2 = it1 + 1; it2 != left.end();)
        {
                    if ((it1->second == it2->second)) 
                    {
                        it1->first = it1->first + it2->first;
                        it2 = left.erase(it2);
                    
                    }
                    else if ((it1->second == "X^0" && it2->second == "") || 
                        (it1->second == "" && it2->second  == "X^0"))
                    {
                        it1->first = it1->first + it2->first;
                        it1->second = "X^0";
                        it2 = left.erase(it2);
                    } 
                    else if ((it1->second == "X^1" && it2->second == "X") || 
                        (it1->second == "X" && it2->second  == "X^1"))
                    {
                        it1->first = it1->first + it2->first;
                         it1->second = "X^1";
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

void remove_zero_coeff_expo(vector<pair<double, string>> &left)
{
    for (auto it2 = left.begin(); it2 != left.end();)
    {
        if (it2->first == 0 && it2->second.empty())
        {
            it2 = left.erase(it2);
        }
        else
            it2++;
    }
}

void check_degree(vector<pair<double, string>> leftAll)
{
    std::vector<char> charExpo;

    if (!leftAll.empty())
    {
        for (const auto& p : leftAll) {
            if (!p.second.empty()){
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

    std::stringstream ss;

    for (auto it = left.begin(); it != left.end();)
    {
        auto signPtr = it + 1;
        if (signPtr != left.end())
        {
            if (signPtr->first >= 0)
            {
                sign = " + ";
            }
            else
            {
                sign = " - ";
            }
        }
        if (it->first < 0 && it != left.begin())
        {
            it->first = it->first * (-1);
        }
        std::stringstream ss;
        ss << (it->first);
        std::string str = ss.str();

        if (!it->second.empty())
        {
            it->second = " * " + it->second;
        }
        test +=str + it->second + sign;
        it++;
        sign = "";
    }
    cout <<endl<<"Reduced form: "<<test<<" = 0 "<<endl;
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
            high = mid;
        } else {
            low = mid;
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
    for (const auto& p : leftAll) {
        if (p.second == "X^2")
            a = p.first;
        else if (p.second == "X^1" || p.second == "X")
            b = p.first;
        else
            c = p.first;
    }
    double delta = (b*b) - (4 * a * c);        

    cout <<endl<<"---------------- Starting calcule DELTA ----------------"<<endl<<endl;
    cout <<"DELTA = ("<<b<<" * "<<b<<") - "<<"(4 * "<<a<<" * "<<c<<")"<<endl;
    cout <<"DELTA = "<<(b*b) - (4 * a * c)<<endl<<endl;

    if (delta > 0)
    {
        double root1 = (-b + calculateSqrt(delta)) / (2 * a);
        double root2 = (-b - calculateSqrt(delta)) / (2 * a);
        cout <<"Discriminant is strictly positive, the two solutions are: "<<endl<<endl;
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
        std::cout << realPart << " + " << imagPart << "*i"<<endl;
        std::cout << realPart << " - " << imagPart << "*i" << std::endl;
    }
}

void equation_degrre1(vector<pair<double, string>> &leftAll)
{
    double a, b;

    for (const auto& p : leftAll) {
        if (p.second == "X^1" || p.second == "X")
            a = p.first;
        else
            b = p.first;
    }

    cout <<"The solution is: "<<-b<<" / " <<a<< " =====> " <<(-b)/a<<endl;
}

int main(int argc, char *argv[])
{
    vector<pair<double, string>> leftAll;
    vector<pair<double, string>> rightAll;

    if (argc == 1)
        ft_error(-1);

    check_valid_char(argv[1]);
    string word = remove_space(argv[1]);
    string strr = flag_sign(word);
    string newStr = replace_with_minus(strr);

    vector<string> data;
    vector<string> leftTokens;
    vector<string> rightTokens;

    data = split_by_equal(newStr);
    leftTokens = split_by_minus(data[0]);
    rightTokens = split_by_minus(data[1]);
    leftAll = check_format_expo_left(leftTokens);
    rightAll = check_format_expo_left(rightTokens);

    check_order_exp(leftAll);
    check_order_exp(rightAll);
    calcul_tokens(leftAll);
    calcul_tokens(rightAll);
    calcul_all_tokens(leftAll, rightAll);
    remove_zero_coeff(leftAll);
    output_reduced_form(leftAll);
    check_degree(leftAll);
    cout <<endl<<"Polynomial degree: "<<degree<<endl;
    if (degree > 50)
    {
        cout <<"The polynomial degree is strictly greater than 2, I can't solve."<<endl;
    }
    else
    {
        if (degree == 50)
            calcul_delta(leftAll);
        else if(degree == 49)
        {
            equation_degrre1(leftAll);
        }
        else if(degree == 48)
        {
        if (leftAll.size() == 0)
            cout <<"The equation is always true and has infinitely many solutions."<<endl;
        else
            cout <<"The equation is false, so there are no solutions.."<<endl;
        }
    }
    return 0;
}