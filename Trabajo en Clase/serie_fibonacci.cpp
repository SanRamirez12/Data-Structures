#include <iostream>
#include <vector>

std::vector<long long> SerieFibonacci(int indice) {
    std::vector<long long> serie;
    if (indice < 0) return serie;         // vacío si índice inválido

    serie.push_back(0);                    // F(0)
    if (indice == 0) return serie;

    serie.push_back(1);                    // F(1)
    for (int i = 2; i <= indice; ++i) {
        long long siguiente = serie[i - 1] + serie[i - 2];
        serie.push_back(siguiente);
    }
    return serie;
}

int main() {
    int indice;
    std::cout << "Ingrese el indice maximo de la serie: ";
    if (!(std::cin >> indice)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    auto serie = SerieFibonacci(indice);
    if (serie.empty()) {
        std::cout << "El indice debe ser >= 0.\n";
        return 0;
    }

    std::cout << "Serie de Fibonacci hasta F(" << indice << "): ";
    for (size_t i = 0; i < serie.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << serie[i];
    }
    std::cout << "\n";
    return 0;
}
