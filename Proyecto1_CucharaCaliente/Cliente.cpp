#include "Cliente.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Cliente::Cliente(const std::string& nombre, int mesa)
    : nombre_(nombre), mesa_(mesa), total_(0.0) {
}

const std::string& Cliente::nombre() const { return nombre_; }
int Cliente::mesa() const { return mesa_; }
double Cliente::total() const { return total_; }

void Cliente::acumular(double monto) {
    if (monto > 0) total_ += monto;
}

static std::string now_string() {
    using clock = std::chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    std::ostringstream os;
    os << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

std::string Cliente::ticket() const {
    std::ostringstream os;
    os << "==== TICKET LA CUCHARA CALIENTE ====\n"
        << "Nombre: " << nombre_ << "\n"
        << "Fecha : " << now_string() << "\n"
        << "Mesa  : " << mesa_ << "\n"
        << "Total : " << std::fixed << std::setprecision(2) << total_ << "\n"
        << "====================================\n";
    return os.str();
}
