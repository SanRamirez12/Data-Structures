#include "Ticket.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <fstream>

using std::string;

/**
 * @file Ticket.cpp
 * @brief Implementación de la clase Ticket.
 *
 * Esta clase encapsula la información de un comprobante (ticket) emitido al cobrar
 * a un cliente. Genera la fecha/hora actual, un texto legible y un archivo .txt
 * con el contenido del ticket.
 */

 // =======================================================
 //  Genera la fecha y hora actual en formato legible
 // =======================================================
string Ticket::now_string() {
    using clock = std::chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);  // versión segura en Windows
#else
    local = *std::localtime(&t); // versión estándar en Linux/Mac
#endif
    std::ostringstream os;
    os << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

// -------------------------------------------------------
//  Utilidad interna: convierte número a dos dígitos
// -------------------------------------------------------
static std::string two_digits(int v) {
    std::ostringstream os;
    os << std::setw(2) << std::setfill('0') << v;
    return os.str();
}

// =======================================================
//  Genera una marca de tiempo compacta (AAAAMMDD_HHMMSS)
//  usada para nombres únicos de archivos
// =======================================================
std::string Ticket::timestamp_compacto_for_filename() {
    using clock = std::chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    std::ostringstream os;
    os << (local.tm_year + 1900)
        << two_digits(local.tm_mon + 1)
        << two_digits(local.tm_mday)
        << "_"
        << two_digits(local.tm_hour)
        << two_digits(local.tm_min)
        << two_digits(local.tm_sec);
    return os.str();
}

// =======================================================
//  Constructor: inicializa ticket con datos del cliente
//  y registra la fecha/hora actual
// =======================================================
Ticket::Ticket(const std::string& nombre, int mesa, double total)
    : nombre_(nombre), mesa_(mesa), total_(total), fecha_(now_string()) {
}

// =======================================================
//  Retorna una representación textual legible del ticket
// =======================================================
std::string Ticket::texto() const {
    std::ostringstream os;
    os << "===== TICKET LA CUCHARA CALIENTE =====\n"
        << "Nombre : " << nombre_ << "\n"
        << "Mesa   : " << mesa_ << "\n"
        << "Fecha  : " << fecha_ << "\n"
        << "Total  : " << std::fixed << std::setprecision(2) << total_ << "\n";
    return os.str();
}

// =======================================================
//  Sanitiza el nombre del cliente para usarlo en el archivo
//  Reemplaza caracteres no válidos por guiones bajos
// =======================================================
std::string Ticket::sanitizar(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s)
        out.push_back(std::isalnum(c) ? char(c) : '_');
    if (out.empty()) out = "cliente";
    return out;
}

// =======================================================
//  Guarda el ticket como archivo .txt en la carpeta indicada
// =======================================================
std::filesystem::path Ticket::guardarEn(const std::filesystem::path& carpeta) const {
    namespace fs = std::filesystem;

    std::error_code ec;
    fs::create_directories(carpeta, ec); // crea carpeta si no existe

    // Nombre de archivo: <timestamp>-<cliente>.txt
    fs::path fname = carpeta / (timestamp_compacto_for_filename() + "-" + sanitizar(nombre_) + ".txt");

    // Escribir el archivo con el contenido del ticket
    std::ofstream f(fname, std::ios::out | std::ios::trunc);
    if (f) {
        f << texto();
        f.close();
    }
    return fname;
}

