#include "Ticket.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

static string timestamp_compacto_for_filename() {
    using clock = chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    char buf[32];
    strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", &local);
    return string(buf);
}

string Ticket::now_string() {
    using clock = chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    ostringstream os;
    os << put_time(&local, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

Ticket::Ticket(const string& nombre, int mesa, double total)
    : nombre_(nombre), mesa_(mesa), total_(total), fecha_(now_string()) {
}

string Ticket::texto() const {
    ostringstream os;
    os << "==== TICKET LA CUCHARA CALIENTE ====\n"
        << "Nombre: " << nombre_ << "\n"
        << "Fecha : " << fecha_ << "\n"
        << "Mesa  : " << mesa_ << "\n"
        << "Total : " << fixed << setprecision(2) << total_ << "\n"
        << "====================================\n";
    return os.str();
}

static string sanitizar(const string& s) {
    string out; out.reserve(s.size());
    for (unsigned char c : s) out.push_back(std::isalnum(c) ? char(c) : '_');
    if (out.empty()) out = "cliente";
    return out;
}

std::filesystem::path Ticket::guardarEn(const std::filesystem::path& carpeta) const {
    namespace fs = std::filesystem;
    std::error_code ec;
    fs::create_directories(carpeta, ec);

    fs::path fname = carpeta / (timestamp_compacto_for_filename() + "-" + sanitizar(nombre_) + ".txt");
    ofstream f(fname, ios::out | ios::trunc);
    if (f) { f << texto(); f.close(); }
    return fname;
}
