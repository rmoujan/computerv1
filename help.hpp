#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
using namespace std;



void ft_error(int code);
vector<string> split_by_equal(string str);
int check_valid_char(string str);
vector<string> split_by_minus(string str);
vector<pair<double, string>> check_format_expo_left(vector<string> data);
void get_expo(string str);
double get_number(string str);
string flag_sign(string word);
string remove_space(string word);
string replace_with_minus(string str);
vector<string> split_vec_by_star(vector<string> vec);
void equation_degrre1(vector<pair<double, string>> &leftAll);
void calcul_delta(vector<pair<double, string>> &leftAll);
// double calculateSqrt(double n);
double calculateSquareRoot(double number);
double power(double base, double exponent);
void output_reduced_form(vector<pair<double, string>> left);
void check_degree(vector<pair<double, string>> leftAll);
void remove_zero_coeff(vector<pair<double, string>> &left);
void calcul_tokens(vector<pair<double, string>> &left);
void calcul_all_tokens(vector<pair<double, string>> &left, vector<pair<double, string>>&right);
void check_order_exp(vector<pair<double, string>> leftAll);