#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>

// Dimensiones temporales para simulacion semanal (Evidencia 3)
const int DIAS_SEMANA = 7;
const int HORAS_DIA = 24;
const int SEMANAS_MES = 4;

// Parametros energeticos de la Panaderia (WattControl)
const double POTENCIA_CONTRATADA_KW = 9.0;
const double UMBRAL_ALERTA_EMBALSES = 40.0;
const int HORA_PICO_INICIO = 18;
const int HORA_PICO_FIN = 20;

const std::string DIAS[DIAS_SEMANA] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
};

#endif