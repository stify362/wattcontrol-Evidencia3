// utilidades.h: funciones libres, sobrecarga y validaciones de texto
#pragma once
#include "configuracion.h"

// 1. SOBRECARGA DE FUNCIONES (mismo nombre, distintos parametros)
int sumar(const int datos[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += datos[i];
    }
    return total;
}

float sumar(const float datos[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += datos[i];
    }
    return total;
}

// Sobrecarga aplicada al cobro por hora vs. acumulado de varias horas
float calcularCosto(float cantidad, float tarifaHora) {
    return cantidad * tarifaHora;
}

float calcularCosto(const float valores[], int n) {
    return sumar(valores, n);
}

// 2. FUNCIONES PROPIAS CON PARAMETROS Y VALOR DE RETORNO
float promedio(const float datos[], int n) {
    if (n <= 0) return 0;
    return sumar(datos, n) / n;
}

float totalSemana(const float porDia[], int dias) {
    return sumar(porDia, dias);
}

int diaMayor(const float porDia[], int dias) {
    int posMayor = 0;
    for (int i = 1; i < dias; i++) {
        if (porDia[i] > porDia[posMayor]) {
            posMayor = i;
        }
    }
    return posMayor;
}

int horaMayor(const float porHora[], int horas) {
    int posMayor = 0;
    for (int i = 1; i < horas; i++) {
        if (porHora[i] > porHora[posMayor]) {
            posMayor = i;
        }
    }
    return posMayor;
}

// 3. UTILIDADES DE FORMATO (Sobrecarga de linea)
void linea(int largo) {
    for (int i = 0; i < largo; i++) cout << '-';
    cout << endl;
}

void linea(int largo, char caracter) {
    for (int i = 0; i < largo; i++) cout << caracter;
    cout << endl;
}