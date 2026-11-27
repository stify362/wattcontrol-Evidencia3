#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "configuracion.h"
#include <iostream>
#include <string>
#include <cctype>

// --- 1. FUNCIONES DE ANALISIS SOBRE MATRICES [7][24] ---

inline double totalSemana(const double matriz[DIAS_SEMANA][HORAS_DIA]) {
    double suma = 0.0;
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        for (int h = 0; h < HORAS_DIA; ++h) {
            suma += matriz[d][h];
        }
    }
    return suma;
}

inline double promedio(const double matriz[DIAS_SEMANA][HORAS_DIA]) {
    return totalSemana(matriz) / (DIAS_SEMANA * HORAS_DIA);
}

inline int diaMayor(const double matriz[DIAS_SEMANA][HORAS_DIA]) {
    int mejorDia = 0;
    double maxSuma = -1.0;
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        double sumaDia = 0.0;
        for (int h = 0; h < HORAS_DIA; ++h) {
            sumaDia += matriz[d][h];
        }
        if (sumaDia > maxSuma) {
            maxSuma = sumaDia;
            mejorDia = d;
        }
    }
    return mejorDia;
}

inline int horaMayor(const double matriz[DIAS_SEMANA][HORAS_DIA]) {
    int mejorHora = 0;
    double maxSuma = -1.0;
    for (int h = 0; h < HORAS_DIA; ++h) {
        double sumaHora = 0.0;
        for (int d = 0; d < DIAS_SEMANA; ++d) {
            sumaHora += matriz[d][h];
        }
        if (sumaHora > maxSuma) {
            maxSuma = sumaHora;
            mejorHora = h;
        }
    }
    return mejorHora;
}

// --- 2. SOBRECARGA DE FUNCIONES ---

inline double sumar(double a, double b) {
    return a + b;
}

inline double sumar(const double valores[], int cantidad) {
    double total = 0.0;
    for (int i = 0; i < cantidad; ++i) {
        total += valores[i];
    }
    return total;
}

inline double calcularCosto(double kwh, double tarifaCop) {
    return kwh * tarifaCop;
}

inline double calcularCosto(const double consumo[DIAS_SEMANA][HORAS_DIA],
                            const double tarifas[DIAS_SEMANA][HORAS_DIA]) {
    double costoTotal = 0.0;
    for (int d = 0; d < DIAS_SEMANA; ++d) {
        for (int h = 0; h < HORAS_DIA; ++h) {
            costoTotal += consumo[d][h] * tarifas[d][h];
        }
    }
    return costoTotal;
}

inline void linea(char caracter, int longitud) {
    for (int i = 0; i < longitud; ++i) {
        std::cout << caracter;
    }
    std::cout << "\n";
}

inline void linea(char caracter) {
    linea(caracter, 60);
}

// --- 3. VALIDACIONES Y NORMALIZACION DE std::string ---

inline std::string normalizarTexto(const std::string& texto) {
    size_t inicio = 0;
    while (inicio < texto.size() && std::isspace(static_cast<unsigned char>(texto[inicio]))) {
        ++inicio;
    }
    size_t fin = texto.size();
    while (fin > inicio && std::isspace(static_cast<unsigned char>(texto[fin - 1]))) {
        --fin;
    }
    std::string limpio = texto.substr(inicio, fin - inicio);
    if (!limpio.empty()) {
        limpio[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(limpio[0])));
    }
    return limpio;
}

inline bool validarNombreEquipo(const std::string& nombre) {
    std::string limpio = normalizarTexto(nombre);
    if (limpio.size() < 3 || limpio.size() > 30) {
        return false;
    }
    for (char c : limpio) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (!std::isalnum(uc) && c != ' ' && c != '-' && c != '_') {
            return false;
        }
    }
    return true;
}

inline std::string pedirNombreEquipoValido() {
    std::string entrada;
    while (true) {
        std::cout << "Ingrese nombre del equipo (3-30 caracteres alfanumericos): ";
        std::getline(std::cin, entrada);
        if (validarNombreEquipo(entrada)) {
            return normalizarTexto(entrada);
        }
        std::cout << "Nombre invalido. Evite simbolos especiales o textos vacios.\n";
    }
}

#endif