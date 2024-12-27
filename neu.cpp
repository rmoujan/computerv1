#include "help.hpp"
char degree = '0';


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
            else if (p.first)
            {
                charExpo.push_back('0');
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
    if(test.empty())
    {
        cout <<endl<<"Reduced form: 0 = 0 "<<endl;
    }
    else
        cout <<endl<<"Reduced form: "<<test<<" = 0 "<<endl;
}

// double calculateSqrt(double number) {
//     if (number < 0) {
//         cout << "Square root of negative numbers is not defined for integers!" << endl;
//         return -1;
//     }
    
//     double low = 0, high = number, result = 0;

//     while (low <= high) {
//         double mid = low + (high - low) / 2;

//         // Check if mid*mid is less than or equal to number
//         if (mid * mid <= number) {
//             result = mid; // Store the mid as the answer
//             low = mid + 1;
//         } else {
//             high = mid - 1;
//         }
//     }

//     return result;
// }

double calculateSquareRoot(double number) {
    if (number < 0) {
        cout << "Square root of negative numbers is not real!" << endl;
        return -1;
    }

    double guess = number;  // Initial guess
    double epsilon = 0.00001; // Desired precision

    while (true) {
        double nextGuess = 0.5 * (guess + number / guess);
        if (abs(guess - nextGuess) < epsilon) {
            break;
        }
        guess = nextGuess;
    }

    return guess;
}


//if degree == 2
//we calcul delta only if the equation is like : ax^2+bx^1+c=0
void calcul_delta(vector<pair<double, string>> &leftAll)
{
    double a = 0 , b = 0, c = 0;
    //a --> x^2
    //b -- >x^1
    //c --> x^0
    for (const auto& p : leftAll) {
        if (p.second == "X^2")
        {
            if (p.first)
                a = p.first;
        }
        else if (p.second == "X^1" || p.second == "X")
        {
            if (p.first)
                b = p.first;
        }
        else
        {
            if (p.first)
                c = p.first;
        }
    }
    // cout <<"a is "<<a<<" and b is "<<b<< " and c is "<<c<<endl;
    double delta = (b*b) - (4 * a * c);        

    cout <<endl<<"---------------- Starting to calculate DELTA ----------------"<<endl<<endl;
    cout <<"Δ = ("<<b<<" * "<<b<<") - "<<"(4 * "<<a<<" * "<<c<<")"<<endl;
    cout <<"Δ = "<<(b*b) - (4 * a * c)<<endl<<endl;

    if (delta > 0)
    {
        double root1 = (-b + calculateSquareRoot(delta)) / (2 * a);
        double root2 = (-b - calculateSquareRoot(delta)) / (2 * a);
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
        double imagPart = calculateSquareRoot(-delta) / (2 * a);
        std::cout << realPart << " + " << imagPart << "*i"<<endl;
        std::cout << realPart << " - " << imagPart << "*i" << std::endl;
    }
}

void equation_degrre1(vector<pair<double, string>> &leftAll)
{
    double a = 0, b = 0;

    // cout<< "^^^^^^^ Equation 1 Degree ^^^^^^^^^^^^^^"<<endl;
    //     for (const auto& p : leftAll) {
    //     std::cout << "{" << p.first << ", " << p.second << "}" << std::endl;
    // }
    cout <<endl<< "-----------------------------------------" << endl;
    cout << "| Solving the equation step by step     |" << endl;
    cout << "-----------------------------------------" << endl<<endl;
    for (const auto& p : leftAll) {
        if (p.second == "X^1" || p.second == "X")
        {
            // cout <<"@@ p.first is "<<p.first<<endl;
            a = p.first;
        }
        else
        {
            //  cout <<"## p.first is "<<p.first<<endl;
            b = p.first;
        }
    }
    cout <<"\t\t\t"<<a<<" * X = "<<-b<<endl;
    cout <<"\t\t\tX = "<<-b<<"/"<<a<<endl<<endl;
    // cout <<"The solution is: "<<(-b)/a<<endl<<endl;
    cout << "-----------------------------------------" << endl;
    cout << "| Solution: X =                          |" << (-b)/a <<endl;
    cout << "-----------------------------------------\n";
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
        cout <<endl<<"The polynomial degree is strictly greater than 2, I can't solve."<<endl;
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
            cout <<endl<<"The equation is always true and has infinitely many solutions."<<endl;
        else
            cout <<endl<<"The equation is false, so there are no solutions.."<<endl;
        }
    }
    return 0;
}