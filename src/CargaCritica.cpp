#include "CargaCritica.h"

CargaCritica::CargaCritica(const std::string& nombre, double potenciaKW)
    : Carga(nombre, potenciaKW) {
    encendida_ = true;
}

bool CargaCritica::debeEncender(int /*hora*/, double /*precioCOPkWh*/, double /*embalsesPct*/) const {
    // Una carga critica (nevera de insumos) opera 24/7 sin interrupcion
    return true;
}

std::string CargaCritica::tipo() const {
    return "Critica";
}