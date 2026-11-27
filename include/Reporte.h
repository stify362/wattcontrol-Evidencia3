#ifndef REPORTE_H
#define REPORTE_H

#include "Carga.h"
#include "configuracion.h"
#include <string>

class Reporte {
public:
    static void mostrarResumenDiario(const std::string& negocio, double totalKWh, double costoTotalCOP);
    static void mostrarReporteSemanal(const std::string& negocio,
                                      Carga* const cargas[],
                                      int numCargas,
                                      const double tarifasSemana[DIAS_SEMANA][HORAS_DIA]);
};

#endif