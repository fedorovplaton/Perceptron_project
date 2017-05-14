#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>

#include "Functions.hpp"// my .hpp

using namespace std;

//Consts
//const int INPUT_SIZE_OF_PARCEPTRON = 16;
//End_of_Consts

class perceptron{
private:
    int _levels; // Кол-во уровней в перцептроне
    double*** _perc; // Массив весов рёбер
    bool*** _used;
    double** _points;
    int _func; // ННомер функции
    int _sizeinput; // кол-во чисел в первом слою
    int* _levelsize; // кол-во вершин в слою под номером i
    int* _roots; // кол-во ребер из слоя i в слой i + 1
    double _rand;
    int _deg;
    double _eta; // коэффициент скорости обучения
    double function(double x)
    {
        if(_func == 1)
        {
            return Exp(x);
        }
        if(_func == 2)
        {
            return Sign(x);
        }
        if(_func == 3)
        {
            return Oneorzero(x);
        }
        if(_func == 4)
        {
            return Arctg(x);
        }
        if(_func != 1 && _func != 2 && _func != 3 && _func != 4)
        {
            return 0;
        }
    }
    double _function(double x)
    {
        {
        if(_func == 1)
        {
            return _Exp(x);
        }
        if(_func == 2)
        {
            return 1;
        }
        if(_func == 3)
        {
            return 1;
        }
        if(_func == 4)
        {
            return _Arctg(x);
        }
        if(_func != 1 && _func != 2 && _func != 3 && _func != 4)
        {
            return 0;
        }
    }
    }
public:
    void Set(double x)
    {
        _eta = x;
    }
    perceptron(const char * file_name)
    {
        _eta = 0.4;
        int random_weights;
        ifstream fin(file_name);
        fin >> _levels;
        fin >> _func; 
        fin >> random_weights;
        _perc = new double**[_levels];
        _used = new bool**[_levels];
        _roots = new int[_levels - 1];
        _points = new double*[_levels];
        _levelsize = new int[_levels];

        fin >> _sizeinput;

        _perc[0] = new double*[_sizeinput];
        _used[0] = new bool*[_sizeinput];
        _points[0] = new double[_sizeinput];
        
        _levelsize[0] = _sizeinput;

        for(int i = 1; i < _levels; i++)
        {
            int x;
            int y;
            fin >> x >> y;
            _roots[i - 1] = y;
            _levelsize[i] = x;
            _perc[i] = new double*[x];
            _used[i] = new bool*[x];
            _points[i] = new double[x];
            for(int j = 0; j < _levelsize[i - 1]; j++)
            {
                _perc[i-1][j] = new double[x];
                _used[i-1][j] = new bool[x];
            }
            if(random_weights == 1)
            {
                for(int j = 0; j < y; j++)
                {
                    int a, b;
                    fin >> a >> b;
                    _perc[i - 1][a][b] =((double)( rand() % 100 ) + 1)/ 100;
                    _used[i - 1][a][b] = true;
                }
            }
            else
            {
                for(int j = 0; j < y; j++)
                {
                    int a, b;
                    double c;
                    fin >> a >> b >> c;
                    _perc[i - 1][a][b] = c;
                    _used[i - 1][a][b] = true;
                }
            }
        }
        fin.close();
    }
    ~perceptron()
    {
        for(int i = 0; i < _levels - 1; i++)
        {
            for(int j = 0; j < _levelsize[i]; j++)
            {
                delete [] (_perc[i][j]);
            }
        }
        for(int i = 0; i < _levels - 1; i++)
            delete [] (_perc[i]);
        delete [] _perc;
        for(int i = 0; i < _levels - 1; i++)
        {
            for(int j = 0; j < _levelsize[i]; j++)
            {
                delete [] (_used[i][j]);
            }
        }
        for(int i = 0; i < _levels - 1; i++)
            delete [] (_used[i]);
        delete [] _used;

        for(int i = 0; i < _levels; i++)
        {
            delete [] _points[i];
        }
        delete [] _points;
        delete [] _levelsize;
        delete [] _roots;
    }

    void Save(const char*out)
    {
        ofstream fout(out);
        fout << _levels << " " << _func << " " << "0" << '\n';
        fout << _levelsize[0] << '\n';
        for(int i = 0; i < _levels - 1; i++)
        {
            fout << _levelsize[i + 1] << " "    <<_roots[i] <<'\n';
            for(int j = 0; j < _levelsize[i]; j++)
            {
                for(int k = 0; k < _levelsize[i + 1]; k++)
                {
                    if(_used[i][j][k])
                        fout << j << " " << k << " " << (_perc[i][j][k]) << " ";
                }
                fout << '\n';
            }
            fout << '\n';
        }
        fout.close();
    }

    void Study(const char* name, int n)
    {
        double * right_answer = new double[_levelsize[_levels - 1]];     
        double ** d = new double*[_levels];
        for(int i = 0 ; i < _levels; i++)
        {
            d[i] = new double[_levelsize[i]]; 
        }
        ifstream fin(name);
        for(int vek = 0; vek < n; vek++)
        { 
            for(int j  = 0; j < _sizeinput; j++)
            {
                fin >> _points[0][j];
            }
            for(int j = 1; j < _levels; j++)
            {
                    for(int k = 0; k < _levelsize[j]; k++)
                    {
                        for(int l = 0; l < _levelsize[j - 1]; l++)
                        {
                            if(_used[j-1][l][k])
                                _points[j][k] += _points[j - 1][l] * _perc[j - 1][l][k];                            
                        }
                    }
                    for(int l = 0; l < _levelsize[j]; l++)
                    {
                         _points[j][l] = function(_points[j][l]); 
                    }                        
            }
        for(int i =  0; i < _levelsize[_levels - 1]; i++)
        {
            double x;
            fin >> x;
            right_answer[i] = x;
            d[_levels - 1][i] = _function(_points[_levels - 1][i]) * (x - _points[_levels - 1][i]);
        }
        for(int i = 0; i < _levelsize[_levels - 2]; i++)
        {
            for(int j  = 0; j < _levelsize[_levels - 1]; j++)
            {
                if(_used[_levels - 2][i][j]){
                    _perc[_levels - 2][i][j] = /*Round*/(_perc[_levels - 2][i][j] + _eta * d[_levels - 1][j] * _points[_levels - 1][j]);
                }
            }
        }
        for(int i = _levels - 3; i >= 0; i--)
        {
            for(int j  = 0; j < _levelsize[i]; j++)
            {
                double sum = 0;
                    for(int m = 0; m < _levelsize[i + 1]; m++)
                    {
                        if(_used[i][j][m])
                        {
                            sum += d[i + 1][m] * _perc[i][j][m];
                        } 
                    }
                for(int k  = 0; k < _levelsize[i + 1]; k++)
                {
                    if(_used[i][j][k])
                    {
                        d[i][j] = _function(_points[i][k]) * sum;
                    }
                }
            } 
            for(int j  = 0; j < _levelsize[i]; j++)
            {
                for(int k  = 0; k < _levelsize[i + 1]; k++)
                {
                    if(_used[i][j][k])
                    {
                        _perc[i][j][k] =  /*Round*/(_perc[i][j][k] + _eta * d[i][k] * _points[i+1][k]);

                    }
                }
            }
        }
        }
        for(int i = 0; i < _levels; i++)
        {
            delete [] d[i];
        }
        delete [] d;
        delete [] right_answer;
        fin.close();
    }
    void Show(const char* path);
    void ConsoleCounUp();
};

void perceptron::Show(const char* name)
{
    string p(name);
    string tex = ".tex";
     for(int i = 0; i < sizeof(name); i++){
        p[i] = name[i];
    }
    p += tex;
    const char* str = p.c_str();
    ofstream fout(str);
    int n = _levels;
    int m = -1;
    for(int i = 0; i < _levels; i++)
        if(m < _levelsize[i])
            m = _levelsize[i];
    fout << "\\documentclass{article}" << '\n';
    fout << "\\usepackage{tikz}" << '\n';
    fout << "\\begin{document}" << '\n';
    fout << "\\begin{tikzpicture}[xscale=0.1, yscale=0.1]" << '\n';
    fout << "\\color{red}" << '\n';
    for(int i = 0; i < _levels - 1; i++)
    {
        for(int j = 0; j < _levelsize[i]; j++)
        {
            for(int k = 0; k < _levelsize[i + 1]; k++)
            {
                if(_used[i][j][k])
                {
                    fout << "\\draw (" << (1 + i)*(100/(n+1)) << "," << (1 + j)*(80/(_levelsize[i] + 1)) << ") -- (" << (2 + i)*(100/(n+1)) << "," << (1 + k)*(80/(_levelsize[i + 1] + 1)) << ");" << '\n';
                    fout << "\\color{black}" << '\n';
                    if(j == k)
                        fout << "\\node at (" << (((1 + i)*(100/(n+1))) + ((2 + i)*(100/(n+1)))) / 2 << ", " << (((1 + j)*(80/(_levelsize[i] + 1))) + ((1 + k)*(80/(_levelsize[i + 1] + 1)))) / 2 << ") {" << Round(_perc[i][j][k]) << "};" << '\n'; 
                    else{
                        if((((1 + j)*(80/(_levelsize[i] + 1))) < ((1 + k)*(80/(_levelsize[i + 1] + 1)))))
                            fout << "\\node at (" << (((1 + i)*(100/(n+1))) + ((2 + i)*(100/(n+1))) / 10)  << ", " << (((1 + j)*(80/(_levelsize[i] + 1))) + ((1 + k)*(80/(_levelsize[i + 1] + 1))) / 10)  << ") {" << Round(_perc[i][j][k]) << "};" << '\n';
                        else
                            fout << "\\node at (" << (((1 + i)*(100/(n+1))) + ((2 + i)*(100/(n+1))) / 10)  << ", " << (((1 + j)*(80/(_levelsize[i] + 1))) - (80 - ((1 + k)*(80/(_levelsize[i + 1] + 1))) )  / 10)  << ") {" <<Round( _perc[i][j][k]) << "};" << '\n';
                    }
                    fout << "\\color{red}" << '\n';
                }
            }
        }
    }
    fout << "\\color{red}" << '\n';
    for(int j = 0; j < _levelsize[0]; j++)
    {
        fout << "\\draw [->] (0," << (1 + j)*(80/(_levelsize[0] + 1)) << ") -- (" << 100/(n+1) - 5 << "," << (1 + j)*(80/(_levelsize[0] + 1)) << ");" << '\n'; 
    }
    for(int j = 0; j < _levelsize[_levels - 1]; j++)
    {
        fout << "\\draw [->] (" << (_levels )*(100/(n+1)) + 5 << "," << (1 + j)*(80/(_levelsize[_levels - 1] + 1)) << ") -- (" << "100"/*(_levels )*(100/(n+1)) + 10*/ << "," << (1 + j)*(80/(_levelsize[_levels - 1] + 1)) << ");" << '\n'; 
    }

    fout << "\\color{blue}" << '\n';
    for(int i = 0; i < _levels; i++)
    {
        for(int j = 0; j < _levelsize[i]; j++)
        {
            fout << "\\filldraw (" << (1 + i)*(100/(n+1)) << "," << (1 + j)*(80/(_levelsize[i] + 1)) << ") circle [radius=4];" << '\n';
        }
    }
    fout << "\\color{white}" << '\n';
    for(int i = 0; i < _levels; i++)
    {
        for(int j = 0; j < _levelsize[i]; j++)
        {
            fout << "\\filldraw (" << (1 + i)*(100/(n+1)) << "," << (1 + j)*(80/(_levelsize[i] + 1)) << ") circle [radius=3.8];" << '\n';
            fout << "\\color{black}" << '\n';
            fout << "\\node at (" << (1 + i)*(100/(n+1)) << "," << (1 + j)*(80/(_levelsize[i] + 1)) << ") {" << Round(_points[i][j]) << "};" << '\n';
            fout << "\\color{white}";
        }
    }
    fout << "\\end{tikzpicture}" << '\n';
    fout << "\\end{document}" << '\n';
    fout.close();
    return;
}

void perceptron::ConsoleCounUp()
{

    for(int i = 0; i < _sizeinput; i++)
        cin >> _points[0][i];
    for(int j = 1; j < _levels; j++)
    {
        for(int k = 0; k < _levelsize[j]; k++)
        {
            for(int l = 0; l < _levelsize[j - 1]; l++)
            {
                if(_used[j-1][l][k])
                    _points[j][k] += _points[j - 1][l] * _perc[j - 1][l][k];                            
            }
        }
        for(int l = 0; l < _levelsize[j]; l++)
        {
            _points[j][l] = function(_points[j][l]); 
        }                        
    }
    for(int i = 0; i < _levelsize[_levels - 1]; i++)
        cout << _points[_levels - 1][i] << " " << '\n';
    
}


#endif