#include <iostream>
using namespace std;

void ft_error(int code)
{
    if (code == -1)
    {
        cout <<"Please enter an argument"<<endl;
        exit(0);
    }
}
void ft_output()
{
    cout<<"Reduced form: "<<endl;
    cout<<"Polynomial degree: "<<endl;
    cout<<"The solution is: "<<endl;
}

int ft_check_coefficient()
{

}

int ft_check_exponent()
{

}

int create_reduced_form()
{

}

int main(int argc, char *argv[])
{
    cout <<"argc is "<<argc<<endl;
    if (argc == 1)
        ft_error(-1);
    cout <<argv[1]<<endl;
    //you need to check the term entered (they said that every enteris always right)
    //so we should make the reduced form:
    

    return 0;
}