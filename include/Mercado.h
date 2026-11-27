
#pragma once
#include <string>
#include "configuracion.h"
#include "utilidades.h"

// Asociacion con Negocio: suministra tarifas semanales y estado hidrico.
class Mercado {
private:
    std::string operador_ = "XM - SIN Colombia";
    double embalsesPct_ = config::EMBALSE_INICIAL_PCT;

    // Matriz de 7 dias por 24 horas.
    double preciosSemana_[DIAS_SEMANA][HORAS_DIA]{};

public:
    Mercado();
    Mercado(const std::string& operador, double nivelEmbalsesPct);

    void cargarTarifasSemanales();

    // Consultas de precios.
    double getPrecio(int dia, int hora) const;
    double getPrecio(int hora) const;
    double precioHora(int hora) const;

    // Reglas del mercado energetico.
    bool esHoraPico(int hora) const;
    bool hayAlertaEmbalses() const;
    double calcularPromedioSemanal() const;

    // Consultas y actualizacion del estado.
    std::string operador() const;
    double nivelEmbalses() const;
    void actualizarNivelEmbalses(double nivelPct);
};

