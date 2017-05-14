#include "MainHeader.hpp"

///home/platon/Рабочий стол/universit
void Check()
{
    const char* study = "study.in";
    const char* forshow = "b";
    const char* output = "Output.out";
    const char* input = "Input.in";
    const char* beforestudy = "a"; 

    ofstream f(study); // заполним файл для обучния
    double j = 0.001;
    int n = 0;
    while(j < 1)
    {
        n++;
        j *= 1.2;
        double m = j * 1.2;
        f << j << " " << m << " " << (j + m) / 2 << '\n';
        j = m;
    }
    f.close();
    
    perceptron myperc(input); // создаём перцептрон со входными данными, как в файле
    myperc.Set(2); // задаём ему скорость обучния
    myperc.Show(beforestudy); // создём tex файл, чтобы посмотреть как выглядит перцептрон до обучния
    myperc.Study(study, n); // открываем файл study и учимся на первых n элементах
    myperc.Show(forshow); // создём tex файл, чтобы посмотреть как выглядит перцептрон после обучния
    myperc.Save(output); // сохраним результат в файл
    myperc.ConsoleCounUp(); // проверим результат для введенного с клавиатуры вектора
    return;
}


int main()
{
    Check();
    return 0;
}