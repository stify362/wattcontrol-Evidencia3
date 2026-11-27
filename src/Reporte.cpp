#include "Reporte.h"
#include "utilidades.h"
#include <iostream>
#include <iomanip>

void Reporte::mostrarResumenDiario(const std::string& negocio, double totalKWh, double costoTotalCOP) {
    linea('=', 60);
    std::cout << "RESUMEN DIARIO - " << negocio << "\n";
    std::cout << "Consumo total : " << std::fixed << std::setprecision(2) << totalKWh << " kWh\n";
    std::cout << "Costo estimado: $" << std::setprecision(0) << costoTotalCOP << " COP\n";
    linea('=', 60);
}

void Reporte::mostrarReporteSemanal(const std::string& negocio,
                                    Carga* const cargas[],
                                    int numCargas,
                                    const double tarifasSemana[DIAS_SEMANA][HORAS_DIA]) {
    linea('=', 74);
    std::cout << "REPORTE SEMANAL DE CONSUMO Y COSTOS [7x24] - " << negocio << "\n";
    linea('-', 74);

    std::cout << std::left << std::setw(22) << "Equipo"
              << std::setw(12) << "Tipo"
              << std::setw(14) << "Total (kWh)"
              << std::setw(14) << "Dia Pico"
              << std::setw(12) << "Costo COP" << "\n";
    linea('-', 74);

    double granTotalKWh = 0.0;
    double granTotalCOP = 0.0;

    for (int i = 0; i < numCargas; ++i) {
        if (cargas[i] == nullptr) continue;

        double kwhEquipo = cargas[i]->calcularConsumoTotalSemanal();
        double costoEquipo = 0.0;
        for (int d = 0; d < DIAS_SEMANA; ++d) {
            for (int h = 0; h < HORAS_DIA; ++h) {
                costoEquipo += calcularCosto(cargas[i]->getConsumo(d, h), tarifasSemana[d][h]);
            }
        }

        granTotalKWh = sumar(granTotalKWh, kwhEquipo);
        granTotalCOP = sumar(granTotalCOP, costoEquipo);

        std::cout << std::left << std::setw(22) << cargas[i]->nombre()
                  << std::setw(12) << cargas[i]->tipo()
                  << std::setw(14) << std::fixed << std::setprecision(2) << kwhEquipo
                  << std::setw(14) << DIAS[cargas[i]->obtenerDiaMayorConsumo()]
                  << "$" << std::setprecision(0) << costoEquipo << "\n";
    }

    linea('-', 74);
    std::cout << "TOTAL SEMANAL PANADERIA: " << std::fixed << std::setprecision(2) << granTotalKWh
              << " kWh | Costo Total: $" << std::setprecision(0) << granTotalCOP << " COP\n";
    linea('=', 74);
}