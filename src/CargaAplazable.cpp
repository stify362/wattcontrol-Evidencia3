#include "CargaAplazable.h"

CargaAplazable::CargaAplazable(const std::string& nombre, double potenciaKW)
    : Carga(nombre, potenciaKW) {}

bool CargaAplazable::debeEncender(int hora, double precioCOPkWh, double embalsesPct) const {
    const bool embalsesCriticos = embalsesPct < config::EMBALSE_ALERTA_PCT;
    const bool horaPico = (hora >= config::PICO_INICIO && hora <= config::PICO_FIN);
    const bool precioAlto = precioCOPkWh > config::PRECIO_CARO_COP_KWH;

    // Se aplaza durante franja pico, tarifa alta o alerta de embalses bajos
    return !(embalsesCriticos || horaPico || precioAlto);
}

std::string CargaAplazable::tipo() const {
    return "Aplazable";
}