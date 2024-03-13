#include "Vector.h"

void ReadFromFile(const string& filename, Vector& v1, Vector& v2) { //функция для чтения элементов класса из файла
    ifstream file(filename);
    if (file.is_open()) { //проверяем, открыт ли файл
        int n1, n2;
        file >> n1;
        v1 = Vector(n1);
        file >> v1;
        file >> n2;
        v2 = Vector(n2);
        file >> v2;
        file.close();
    }
    else {
        cerr << "Can't open this file :(" << endl;
    }
}

void SaveToFile(const string& filename, const Vector& v1) {
    ofstream file(filename);
    if (file.is_open()) {
        file << v1;
        file.close();
    }
    else {
        cerr << "Can't open this file :(" << endl;
    }
}

int main()
{
    /*double m1[] = {1, 2, 3, 4.5, 7};
    double m2[] = { 2, 3, 4 ,5.5, 8 };
    Vector V1(m1, 5);
    Vector V2(m2, 5);
    Vector V3 = V1 + V2;
    Vector V4 = V1;
    double a = V3[1];
    bool b = V1 < V2;
    cout << "b = " << b << endl;
    cout << "a = " << a << endl;
    cout << V3;
    V4.print();
    return 0;*/
    Vector V1, V2, V3;
    ReadFromFile("input.txt", V1, V2);
    cout << "Vector 1" << V1 << endl;
    cout << "Vector 2" << V2 << endl;
    V3 = V1 + V2;
    bool b = V1 < V2;
    cout << "b = " << b << endl;
    cout << "Sum of V1 and V2 = " << V3 << endl;
    SaveToFile("output.txt", V3);
    return 0;
}
