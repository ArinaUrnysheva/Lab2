#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Vector { //����� ������

    double* p = nullptr; //��������� �� ������
    int n = 0; //����������� �������
public:
    Vector(double* p, int n) {//����������, ��������� ���������� ������ ����������� n
        this->n = n; // ������ ����� ���������
        this->p = new double[n]; // �������� ������
        for (int i = 0; i < n; i++) this->p[i] = p[i]; // �������� ���� ������ � ������
        // cout << "Vector(double *p, int n)" << endl;
    }

    Vector(int n) : n(n) { // ����������� - �������� ������ ��� �������������
        p = new double[n];
        //cout << "Vector(int n)" << endl;
    }

    Vector(const Vector& V) { //����������� �����������
        n = V.n;
        p = new double[n];
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];
    }

    Vector(Vector&& V) { //����������� �����������
        swap(p, V.p);
        swap(n, V.n);
    }
    void print() const {  //������ ������� (�������), ����� �������� �� ���������� <<
        cout << "n = " << n << endl;
        for (int i = 0; i < n; i++)
            cout << p[i] << " ";
        cout << std::endl;
    }
    Vector() { //����������� ��� ����������, ������ ������ ������
        p = nullptr; n = 0;
    }

    double& operator[](int index) { //���������� ��������� ��������� �� �������
        return p[index];
    }
    Vector& operator =(const Vector& v2) { //���������� ��������� ����������� �������
        if (this != &v2) { //������ ����������� ������� ������ � ����
            n = v2.n;
            if (p != nullptr) delete[] p; //����������� ������ ������� �������
            p = new double[n]; //�������� ������ ��� ������ �������
            for (int i = 0; i < n; i++) {
                p[i] = v2.p[i]; //�������� ������ �������
            }
        }
        return *this; //���������� ������ �� ������� ������
    }

    Vector& operator =(Vector&& v2) { //���������� �������� ����������� �������
        if (this != &v2) { //������ ����������� ������� ������ � ����
            std::swap(p, v2.p);
            std::swap(n, v2.n);
        }
        return *this; //���������� ������ �� ������� ������
    }
    ~Vector() { //����������
        if (p != nullptr) delete[] p; //����������� ������
    }

    //������������� �������, ������������ ��� ������, ��� ���������� �������������� ��������

    friend Vector operator *(double x, Vector& v2);
    friend Vector operator +(const Vector& v1, const Vector& v2);
    friend bool operator <(const Vector& v1, const Vector& v2);

    //������������� �������, ������������ ��� ������, ��� ���������� �������� ����� � ������
    friend ostream& operator <<(ostream& os, const Vector& v1);
    friend istream& operator >>(istream& is, const Vector& v1);
};

Vector operator *(double x, Vector& v2) //���������� ��������� ��������� ������� �� �����
{
    Vector V(v2.n); //������� ����� ������� �������� �����������
    for (int i = 0; i < v2.n; i++) {
        V.p[i] = x * v2.p[i]; //��������� ������
    }
    return V; // ���������� ������
}

Vector operator +(const Vector& v1, const Vector& v2) { //���������� ��������� �������� ���� ��������
    Vector V(v1.n + v2.n); //������� ����� ������ ��������� �������
    for (int i = 0; i < v1.n; i++) {
        V.p[i] = v1.p[i]; //��������� ������
    }
    for (int i = 0; i < v2.n; i++) {
        V.p[i + v1.n] = v2.p[i]; //��������� ������
    }
    return V; //���������� ������
}

bool operator <(const Vector& v1, const Vector& v2) { //���������� ��������� ��������� ���� ��������
    bool f = true;
    if (v1.n != v2.n) { //���� �� ����� ������, �� ������� false
        f = false;
    }
    for (int i = 0; i < v1.n; ++i) {
        if (v1.p[i] >= v2.p[i]) { //���� ������� v1 >= ������� v2, �� ������� false
            f = false;
            break;
        }
    }
    return f;
}

ostream& operator <<(ostream& os, const Vector& v1) { //���������� �������� ������ 
    for (int i = 0; i < v1.n; ++i) {
        os << v1.p[i] << ' ';
    }
    return os;
}

istream& operator >>(istream& is, const Vector& v1) { //���������� �������� �����
    for (int i = 0; i < v1.n; ++i) {
        is >> v1.p[i];
    }
    return is;
}