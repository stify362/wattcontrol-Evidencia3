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
    linea('=', 76);
    std::cout << "REPORTE SEMANAL DE CONSUMO Y COSTOS [7x24] - " << negocio << "\n";
    linea('-', 76);

    std::cout << std::left << std::setw(22) << "Equipo"
              << std::setw(12) << "Tipo"
              << std::setw(14) << "Total (kWh)"
              << std::setw(14) << "Dia Pico"
              << std::setw(14) << "Costo COP" << "\n";
    linea('-', 76);

    double granTotalKWh = 0.0;
    double granTotalCOP = 0.0;
    double costoSinGestor = 0.0;

    double kwhPorDia[DIAS_SEMANA] = {0.0};
    double costoPorDia[DIAS_SEMANA] = {0.0};
    double costoHorarioTotal[DIAS_SEMANA][HORAS_DIA] = {{0.0}};

    // 1. Consolidado por equipo y acumulacion horaria/diaria
    for (int i = 0; i < numCargas; ++i) {
        if (cargas[i] == nullptr) continue;

        double kwhEquipo = cargas[i]->calcularConsumoTotalSemanal();
        double costoEquipo = 0.0;
        double potenciaMaxHora = 0.0;

        for (int d = 0; d < DIAS_SEMANA; ++d) {
            for (int h = 0; h < HORAS_DIA; ++h) {
                double kwh = cargas[i]->getConsumo(d, h);
                if (kwh > potenciaMaxHora) {
                    potenciaMaxHora = kwh;
                }
                double costoHora = calcularCosto(kwh, tarifasSemana[d][h]);
                costoEquipo = sumar(costoEquipo, costoHora);
                kwhPorDia[d] = sumar(kwhPorDia[d], kwh);
                costoPorDia[d] = sumar(costoPorDia[d], costoHora);
                costoHorarioTotal[d][h] = sumar(costoHorarioTotal[d][h], costoHora);
            }
        }

        // Escenario SIN gestor: cargas aplazables operan toda la jornada (05:00-21:00) incluida hora pico
        if (cargas[i]->tipo() == "Aplazable") {
            for (int d = 0; d < DIAS_SEMANA; ++d) {
                for (int h = 5; h <= 21; ++h) {
                    costoSinGestor = sumar(costoSinGestor, calcularCosto(potenciaMaxHora, tarifasSemana[d][h]));
                }
            }
        } else {
            costoSinGestor = sumar(costoSinGestor, costoEquipo);
        }

        granTotalKWh = sumar(granTotalKWh, kwhEquipo);
        granTotalCOP = sumar(granTotalCOP, costoEquipo);

        std::cout << std::left << std::setw(22) << cargas[i]->nombre()
                  << std::setw(12) << cargas[i]->tipo()
                  << std::setw(14) << std::fixed << std::setprecision(2) << kwhEquipo
                  << std::setw(14) << DIAS[cargas[i]->obtenerDiaMayorConsumo()]
                  << "$" << std::setprecision(0) << costoEquipo << "\n";
    }

    // 2. Tabla con el costo de cada dia de la semana
    linea('=', 76);
    std::cout << "COSTO DIARIO DE LA SEMANA (LUNES A DOMINGO)\n";
    linea('-', 76);
    std::cout << std::left << std::setw(18) << "Dia"
              << std::right << std::setw(20) << "Consumo (kWh)"
              << std::setw(22) << "Costo Diario (COP)" << "\n";
    linea('-', 76);

    int diaMasCaro = 0;
    double maxCostoDia = -1.0;

    for (int d = 0; d < DIAS_SEMANA; ++d) {
        if (costoPorDia[d] > maxCostoDia) {
            maxCostoDia = costoPorDia[d];
            diaMasCaro = d;
        }
        std::cout << std::left << std::setw(18) << DIAS[d]
                  << std::right << std::setw(20) << std::fixed << std::setprecision(2) << kwhPorDia[d]
                  << std::setw(18) << "$" << std::setprecision(0) << costoPorDia[d] << "\n";
    }

    // 3. Dia mas caro, hora mas cara, ahorro semanal y proyeccion mensual (x4)
    int diaHoraMasCara = 0;
    int horaMasCara = 0;
    double maxCostoHora = -1.0;
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        for (int h = 0; h < HORAS_DIA; ++h) {
            if (costoHorarioTotal[d][h] > maxCostoHora) {
                maxCostoHora = costoHorarioTotal[d][h];
                diaHoraMasCara = d;
                horaMasCara = h;
            }
        }
    }

    double ahorroSemanal = costoSinGestor - granTotalCOP;
    if (ahorroSemanal < 0.0) ahorroSemanal = 0.0;
    double ahorroMensual = ahorroSemanal * 4.0;

    linea('-', 76);
    std::cout << "Dia mas caro de la semana  : " << DIAS[diaMasCaro]
              << " ($" << std::fixed << std::setprecision(0) << maxCostoDia << " COP)\n";
    std::cout << "Hora mas cara de la semana : " << horaMasCara << ":00 hrs ("
              << DIAS[diaHoraMasCara] << " - $" << maxCostoHora << " COP)\n";
    std::cout << "Costo SIN gestor energetico: $" << costoSinGestor << " COP\n";
    std::cout << "Costo CON gestor energetico: $" << granTotalCOP << " COP\n";
    std::cout << "Ahorro semanal             : $" << ahorroSemanal << " COP\n";
    std::cout << "Proyeccion ahorro mensual  : $" << ahorroMensual << " COP (x4)\n";

    // 4. Dias en que se cumplieron las horas minimas de cada carga aplazable
    const int HORAS_MINIMAS_DIARIAS = 6;
    linea('-', 76);
    std::cout << "CUMPLIMIENTO DE HORAS MINIMAS EN CARGAS APLAZABLES (Meta: "
              << HORAS_MINIMAS_DIARIAS << " h/dia)\n";

    for (int i = 0; i < numCargas; ++i) {
        if (cargas[i] != nullptr && cargas[i]->tipo() == "Aplazable") {
            int diasCumplidos = 0;
            for (int d = 0; d < DIAS_SEMANA; ++d) {
                int horasActivas = 0;
                for (int h = 0; h < HORAS_DIA; ++h) {
                    if (cargas[i]->getConsumo(d, h) > 0.0) {
                        ++horasActivas;
                    }
                }
                if (horasActivas >= HORAS_MINIMAS_DIARIAS) {
                    ++diasCumplidos;
                }
            }
            std::cout << " - " << std::left << std::setw(22) << cargas[i]->nombre()
                      << ": " << diasCumplidos << " de " << DIAS_SEMANA << " dias cumplidos\n";
        }
    }
    linea('=', 76);
}