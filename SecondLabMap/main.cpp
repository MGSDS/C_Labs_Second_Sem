#include <iostream>
#include "Polynomial.h"

int main() {
    Polynomial<int> a;
    Polynomial<int> b;
    std::cin >> a >> b;
    std::cout << a * b;
    return 0;
}
