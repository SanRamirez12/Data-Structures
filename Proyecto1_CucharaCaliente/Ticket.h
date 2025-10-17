#pragma once
#include <string>
#include <filesystem>

class Ticket {
    std::string nombre_;
    int mesa_;
    double total_;
    std::string fecha_; // AAAA-MM-DD HH:MM:SS

    static std::string now_string();

public:
    Ticket(const std::string& nombre, int mesa, double total);

    const std::string& nombre() const { return nombre_; }
    int mesa() const { return mesa_; }
    double total() const { return total_; }
    const std::string& fecha() const { return fecha_; }

    std::string texto() const; // representación legible
    std::filesystem::path guardarEn(const std::filesystem::path& carpeta) const; // escribe .txt
};


