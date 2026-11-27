#ifndef CARGACRITICA_H
#define CARGACRITICA_H

#include "Carga.h"

class CargaCritica : public Carga {
public:
    CargaCritica(const std::string& nombre, double potenciaKW);
    bool debeEncender(int hora, double precioCOPkWh, double embalsesPct) const override;
    std::string tipo() const override;
};

#endif
