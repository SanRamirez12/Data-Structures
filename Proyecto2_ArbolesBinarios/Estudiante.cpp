#include "Estudiante.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

Estudiante::Estudiante() : id_(0), promedio_(0.0) {}

Estudiante::Estudiante(int id, const string& nombre, const string& carrera, double promedio)
    : id_(id), nombre_(nombre), carrera_(carrera), promedio_(promedio) {
}

int Estudiante::id() const { return id_; }
const string& Estudiante::nombre() const { return nombre_; }
const string& Estudiante::carrera() const { return carrera_; }
double Estudiante::promedio() const { return promedio_; }

void Estudiante::set_id(int id) { id_ = id; }
void Estudiante::set_nombre(const string& nombre) { nombre_ = nombre; }
void Estudiante::set_carrera(const string& carrera) { carrera_ = carrera; }
void Estudiante::set_promedio(double promedio) { promedio_ = promedio; }

string Estudiante::a_texto() const {
    ostringstream salida;
    salida << "ID=" << id_ << " | " << nombre_ << " (" << carrera_ << ") | Promedio="
        << fixed << setprecision(2) << promedio_;
    return salida.str();
}

int convertir_promedio_a_clave(double promedio) {
    return static_cast<int>(round(promedio * 100.0));
}
