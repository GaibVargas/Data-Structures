#include <iostream>
#include "array_stack.h"

using namespace std;

int fibo_iterativa(int n) {  // mais eficiente
    int a = 1, b = 1;
    if (n==1 || n==2) {
        return 1;
    }
    int f = a + b;
    for (int i = 3; i < n; i++) {
        a = b;
        b = f;
        f = a + b;
    }
    return f;
}

int fibo(int n) {  // recursivo
    if (n==1 || n==2) {
        return 1;
    }
    return fibo(n-2) + fibo(n-1);
}

int fibo_pilha(int n) {  // recursivo transformado em nao recursivo
    structures::ArrayStack<int> p(1000);
    int f = 0;
    p.push(n);
    while (!p.empty()) {
        n = p.pop();
        if (n==1 || n==2) {
            f = f + 1;
        } else {
            p.push(n-2);
            p.push(n-1);
        }
    }
    return f;
}

int main() {
    int x, y, z;
    int n = 4;

    x = fibo_iterativa(n);
    cout << "fibo(" << n << ") = " << x << endl;

    y = fibo(n);
    cout << "fibo(" << n << ") = " << y << endl;

    z = fibo_pilha(n);
    cout << "fibo(" << n << ") = " << z << endl;

    return 0;
}