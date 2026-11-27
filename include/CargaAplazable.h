#ifndef CARGAAPLAZABLE_H
#define CARGAAPLAZABLE_H

#include "Carga.h"

class CargaAplazable : public Carga {
public:
    CargaAplazable(const std::string& nombre, double potenciaKW);
    bool debeEncender(int hora, double precioCOPkWh, double embalsesPct) const override;
    std::string tipo() const override;
};

#endif
