// configuracion.h: librerias, #define y constantes del parqueadero en Medellin
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// --- Directivas del preprocesador ------------------------------------------
#define HORAS_DIA 24        // columnas de las matrices: 24 horas del dia
#define DIAS_SEMANA 7       // filas de las matrices: 7 dias de la semana
#define TIPOS 2             // tipos de vehiculo: carro y moto

// --- Constantes con tarifas reales por hora en Medellin (COP) --------------
const int CUPOS_CARRO = 30;             // capacidad maxima de carros por hora
const int CUPOS_MOTO = 20;              // capacidad maxima de motos por hora
const int TARIFA_CARRO_DIA = 6800;      // COP/hora carro diurno (promedio comercial Medellin)
const int TARIFA_CARRO_NOCHE = 4200;    // COP/hora carro nocturno
const int TARIFA_MOTO = 3400;           // COP/hora moto (tarifa unica)
const int NOCHE_INICIO = 20;            // inicio jornada nocturna (8:00 p. m.)
const int NOCHE_FIN = 5;                // fin jornada nocturna (5:00 a. m.)
const int SEMANAS_MES = 4;              // factor para proyeccion mensual

// Nombres de los dias para el reporte semanal (fila 0 = Lunes)
const string DIAS[DIAS_SEMANA] = {"Lunes", "Martes", "Miercoles", "Jueves",
                                  "Viernes", "Sabado", "Domingo"};