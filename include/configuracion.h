#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>

// Dimensiones temporales (Evidencia 2 y Evidencia 3)
const int DIAS_SEMANA = 7;
const int HORAS_DIA = 24;
const int SEMANAS_MES = 4;
const int MAX_CARGAS = 10;
const unsigned int SEMILLA_SIMULACION = 42;

const std::string DIAS[DIAS_SEMANA] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
};

namespace config {
    const double POTENCIA_CONTRATADA_KW = 9.0;
    const double POTENCIA_NEVERA_KW = 0.45;
    const double POTENCIA_HORNO_KW = 5.5;
    const double POTENCIA_AMASADORA_KW = 2.2;

    const double EMBALSE_INICIAL_PCT = 52.0;
    const double EMBALSE_ALERTA_PCT = 40.0;

    const int PICO_INICIO = 18;
    const int PICO_FIN = 20;
    const double PRECIO_CARO_COP_KWH = 1000.0;
}

#endif