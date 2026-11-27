#include "Negocio.h"
#include "Reporte.h"
#include <iostream>

// Constructor de la clase Negocio (inicializa nombre, mercado y valores por defecto)
Negocio::Negocio(const std::string& nombre, Mercado* mercado) 
    : nombre_(nombre), numeroCargas_(0), mercado_(mercado), horasSimuladas_(0), fallasLectura_(0), emergencia_(false), tieneSimulacion_(false) {
    // Inicializa el arreglo de cargas en nullptr
    for (int i = 0; i < MAX_CARGAS; ++i) {
        cargas_[i] = nullptr;
    }
}

// Método para agregar cargas al negocio (necesario para el main)
bool Negocio::agregarCarga(Carga* carga) {
    if (numeroCargas_ < MAX_CARGAS && carga != nullptr) {
        cargas_[numeroCargas_++] = carga;
        return true;  // Retorna verdadero si se agregó con éxito
    }
    return false;     // Retorna falso si el arreglo está lleno o la carga es nula
}

// Método para evaluar las cargas según la hora, precio y embalses.
void Negocio::evaluarCargas(int hora, double precio, double embalses) {
    const bool riesgoEmbalses = embalses < config::EMBALSE_ALERTA_PCT;

    if (riesgoEmbalses) {
        std::cout << "[ALERTA] Riesgo: embalses por debajo de "
                  << config::EMBALSE_ALERTA_PCT
                  << "%. Solo se mantendran las cargas no aplazables.\n";
    }

    // Esta es la unica consulta de decision: cada carga responde de forma
    // polimorfica y Negocio aplica despues las reglas generales del negocio.
    for (int i = 0; i < numeroCargas_; ++i) {
        if (cargas_[i] != nullptr) {
            bool encender = cargas_[i]->debeEncender(hora, precio, embalses);
            if (riesgoEmbalses && cargas_[i]->esAplazable()) {
                encender = false;
            }
            cargas_[i]->fijarEncendida(encender);
        }
    }

    double potenciaTotalKW = 0.0;
    for (int i = 0; i < numeroCargas_; ++i) {
        if (cargas_[i] != nullptr && cargas_[i]->encendida()) {
            potenciaTotalKW += cargas_[i]->potenciaKW();
        }
    }

    while (medidor_.superaPotenciaContratada(potenciaTotalKW)) {
    int indiceApagar = -1;
    double mayorPotenciaKW = 0.0;

    // Buscar primero la carga aplazable encendida de mayor potencia.
    for (int i = 0; i < numeroCargas_; ++i) {
        if (cargas_[i] != nullptr &&
            cargas_[i]->encendida() &&
            cargas_[i]->esAplazable() &&
            cargas_[i]->potenciaKW() > mayorPotenciaKW) {
            indiceApagar = i;
            mayorPotenciaKW = cargas_[i]->potenciaKW();
        }
    }

    // Si no quedan aplazables encendidas, buscar cualquier carga encendida.
    if (indiceApagar == -1) {
        for (int i = 0; i < numeroCargas_; ++i) {
            if (cargas_[i] != nullptr &&
                cargas_[i]->encendida() &&
                cargas_[i]->potenciaKW() > mayorPotenciaKW) {
                indiceApagar = i;
                mayorPotenciaKW = cargas_[i]->potenciaKW();
            }
        }

        if (indiceApagar != -1) {
            std::cout << "[EMERGENCIA] Se apaga una carga para respetar el limite.\n";
        }
    }

    // Si no hay nada encendido que apagar, salir del ciclo.
    if (indiceApagar == -1) {
        break;
    }

    cargas_[indiceApagar]->fijarEncendida(false);
    potenciaTotalKW -= mayorPotenciaKW;

    std::cout << "[CONTROL] Se apaga " << cargas_[indiceApagar]->nombre()
              << ". Potencia restante: " << potenciaTotalKW << " kW.\n";
}
}

// Método principal que ejecuta la simulación de las 24 horas del día
void Negocio::simularDia() {
    if (mercado_ == nullptr) {
        std::cout << "[ERROR] No se puede simular: el mercado no esta disponible.\n";
        return;
    }

    // 1. Inicializamos el contador de horas simuladas a 24
    horasSimuladas_ = 24;
    tieneSimulacion_ = true;
    
    // 2. Limpiamos cualquier acumulador previo en el medidor antes de empezar el día
    medidor_.reiniciar();

    std::cout << "\n[SIMULACION] Iniciando ciclo de 24 horas para: " << nombre_ << "..." << std::endl;

    // 3. Bucle que recorre cada hora del día (desde la hora 0 hasta la hora 23)
    for (int hora = 0; hora < 24; ++hora) {
        // A. Consultamos al Mercado el precio de la energía y el nivel de los embalses en esta hora específica
        double precioActual = mercado_->precioHora(hora);
        double embalsesActual = mercado_->nivelEmbalses();

        // B. Evaluamos el estado de las cargas según las reglas de negocio, el costo de la hora y el agua
        evaluarCargas(hora, precioActual, embalsesActual);

        // C. Registramos el consumo energético de esta hora exacta en el medidor
        registrarConsumoHora(0, hora, precioActual);
    }

    std::cout << "[SIMULACION] ¡Simulacion de 24 horas completada con exito!" << std::endl;

    // 4. Al finalizar las 24 horas, invocamos el reporte de consumo con los totales del medidor
    generarReporteConsumo(medidor_.energiaTotalKWh(), medidor_.costoTotalCOP());
}
void Negocio::simularSemana() {
    if (mercado_ == nullptr) {
        std::cout << "[ERROR] No se puede simular: el mercado no esta disponible.\n";
        return;
    }

    medidor_.reiniciar();

    for (int i = 0; i < numeroCargas_; ++i) {
        if (cargas_[i] != nullptr) {
            cargas_[i]->reiniciar();
        }
    }

    horasSimuladas_ = 0;
    tieneSimulacion_ = true;

    for (int dia = 0; dia < DIAS_SEMANA; ++dia) {
        for (int hora = 0; hora < HORAS_DIA; ++hora) {
            const double precioActual = mercado_->precioHora(hora);
            const double embalsesActual = mercado_->nivelEmbalses();

            evaluarCargas(hora, precioActual, embalsesActual);
            registrarConsumoHora(dia, hora, precioActual);
            ++horasSimuladas_;
        }
    }

    generarReporteConsumo(
        medidor_.energiaTotalKWh(),
        medidor_.costoTotalCOP()
    );
}
// Método para calcular y registrar el consumo de una hora dada en el medidor
void Negocio::registrarConsumoHora(int dia, int hora, double precioCOPkWh) {
    double potenciaTotalKW = 0.0;
    for (int i = 0; i < numeroCargas_; ++i) 
    {
        if (cargas_[i] != nullptr && cargas_[i]->encendida()) {
            potenciaTotalKW += cargas_[i]->potenciaKW();
            cargas_[i]->registrarHora();
        }
    }

    medidor_.registrarLectura(dia, hora, potenciaTotalKW, precioCOPkWh);
}

// Método para mostrar el resumen de la última simulación
void Negocio::mostrarResumen() const {
    std::cout << "\n========================================\n";
    std::cout << "   C03: RESUMEN DE CONSUMO Y AHORRO     \n";
    std::cout << "========================================\n";
    
    double totalKWh = medidor_.energiaTotalKWh();
    double costoCOP = medidor_.costoTotalCOP();
    generarReporteConsumo(totalKWh, costoCOP);

    std::cout << " Negocio: Panaderia\n";
    std::cout << " Energia total consumida : " << totalKWh << " kWh\n";
    std::cout << " Costo total estimado    : $" << costoCOP << " COP\n";
    std::cout << " Estado de optimizacion  : Completado\n";
    std::cout << "========================================\n";
}