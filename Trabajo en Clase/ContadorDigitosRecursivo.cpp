#include <iostream>
#include <cstdlib>  // llabs

int contar_digitos(long long n) {
    n = std::llabs(n);              // ignorar signo
    if (n < 10) return 1;           // caso base: un solo dígito (incluye n == 0)
    return 1 + contar_digitos(n / 10);
}

int main() {
    long long n;
    std::cout << "Digite el valor de n: ";
    if (!(std::cin >> n)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Valor " << n << " tiene " << contar_digitos(n) << " digitos\n";
    return 0;
}
