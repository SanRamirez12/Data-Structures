#pragma once
#include <string>

class Cliente {
    std::string nombre_;
    int mesa_;
    double total_;
public:
    Cliente(const std::string& nombre, int mesa);
    const std::string& nombre() const;
    int mesa() const;
    double total() const;
    void acumular(double monto);
    std::string ticket() const;
};
