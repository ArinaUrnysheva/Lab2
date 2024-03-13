#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Vector { //класс вектор

    double* p = nullptr; //указатель на массив
    int n = 0; //размерность вектора
public:
    Vector(double* p, int n) {//коструктор, создающий одномерный массив размерности n
        this->n = n; // Задаем число элементов
        this->p = new double[n]; // Выделяем память
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // Копируем один массив в другой
        // cout << "Vector(double *p, int n)" << endl;
    }

    Vector(int n) : n(n) { // Конструктор - выделяем память без инициализации
        p = new double[n];
        //cout << "Vector(int n)" << endl;
    }

    Vector(const Vector& V) { //конструктор копирования
        n = V.n;
        p = new double[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
    }

    Vector(Vector&& V) { //конструктор перемещения
        swap(p, V.p);
        swap(n, V.n);
    }
    void print() const {  //печать вектора (массива), далее заменено на перегрузку <<
        cout << "n = " << n << endl;
        for (int i = 0; i < n; i++)
            cout << p[i] << " ";
        cout << std::endl;
    }
    Vector() { //конструктор без параметров, задает пустой объект
        p = nullptr; n = 0;
    }

    double& operator[](int index) { //перегрузка оператора обращения по индексу
        return p[index];
    }
    Vector& operator =(const Vector& v2) { //перегрузка оператора копирования объекта
        if (this != &v2) { //запрет копирования вектора самого в себя
            n = v2.n;
            if (p != nullptr) delete[] p; //освобождаем память старого вектора
            p = new double[n]; //выделяем память для нового вектора
            for (int i = 0; i < n; i++) {
                p[i] = v2.p[i]; //копируем каждый элемент
            }
        }
        return *this; //возвращаем ссылку на текущий объект
    }

    Vector& operator =(Vector&& v2) { //перегрузка операции перемещения объекта
        if (this != &v2) { //запрет перемещения вектора самого в себя
            std::swap(p, v2.p);
            std::swap(n, v2.n);
        }
        return *this; //возвращаем ссылку на текущий объект
    }
    ~Vector() { //деструктор
        if (p != nullptr) delete[] p; //освобождаем память
    }

    //дружественные функции, определенные вне класса, для перегрузки математических операций

    friend Vector operator *(double x, Vector& v2);
    friend Vector operator +(const Vector& v1, const Vector& v2);
    friend bool operator <(const Vector& v1, const Vector& v2);

    //дружественные функции, определенные вне класса, для перегрузки операций ввода и вывода
    friend ostream& operator <<(ostream& os, const Vector& v1);
    friend istream& operator >>(istream& is, const Vector& v1);
};

Vector operator *(double x, Vector& v2) //перегрузка оператора умножения вектора на число
{
    Vector V(v2.n); //создаем новый объекта заданной размерности
    for (int i = 0; i < v2.n; i++) {
        V.p[i] = x * v2.p[i]; //заполняем массив
    }
    return V; // Возвращаем объект
}

Vector operator +(const Vector& v1, const Vector& v2) { //перегрузка оператора сложения двух векторов
    Vector V(v1.n + v2.n); //создаем новый объект заданного размера
    for (int i = 0; i < v1.n; i++) {
        V.p[i] = v1.p[i]; //заполняем массив
    }
    for (int i = 0; i < v2.n; i++) {
        V.p[i + v1.n] = v2.p[i]; //заполняем массив
    }
    return V; //возвращаем объект
}

bool operator <(const Vector& v1, const Vector& v2) { //перегрузка оператора сравнения двух векторов
    bool f = true;
    if (v1.n != v2.n) { //если их длины разные, то выводим false
        f = false;
    }
    for (int i = 0; i < v1.n; ++i) {
        if (v1.p[i] >= v2.p[i]) { //если элемент v1 >= элемент v2, то выводим false
            f = false;
            break;
        }
    }
    return f;
}

ostream& operator <<(ostream& os, const Vector& v1) { //перегрузка операции вывода 
    for (int i = 0; i < v1.n; ++i) {
        os << v1.p[i] << ' ';
    }
    return os;
}

istream& operator >>(istream& is, const Vector& v1) { //перегрузка операции ввода
    for (int i = 0; i < v1.n; ++i) {
        is >> v1.p[i];
    }
    return is;
}