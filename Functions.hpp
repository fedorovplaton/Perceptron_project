#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cmath>

int Sign(double check_value)
{
    if(check_value)
    {
        if(check_value > 0)
            return 1;
        else 
            return -1;
    }
    else
        return 0;
}

double Round(double x)
{
    double y  = x * 100;
    int k = int(y);
    y = (double)k / 100;
    return y;
}

double Exp(double check_value)
{
    double _const = 1;
    return 1 / (1 + exp((-1) * check_value * _const));    
}

double _Exp(double check_value)
{
    double _const = 1;
    return (exp((-1) * check_value * _const) * _const)/((1 + exp((-1) * check_value * _const)) * (1 + exp((-1) * check_value * _const)));
}

int Oneorzero(double check_value)
{
    if(check_value >= 1)
        return 1;
    else
        return 0;
}

int _Oneorzero(double check_value)
{
    return 0;
}

double Arctg(double check_value)
{
    return atan(check_value);
}

double _Arctg(double check_value)
{
    return 1/(1 + check_value * check_value);
}

#endif