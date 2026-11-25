// configuracion.h: librerias, #define y constantes del problema
#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include <iostream>   // cout (escribir en pantalla) y cin (leer del teclado)
#include <iomanip>    // setw (ancho de columna)
#include <string>     // el tipo string y sus funciones: empty, length, size, at
#include <cctype>     // isupper() (mayuscula?) e isdigit() (numero?)

using namespace std;  // para escribir cout en vez de std::cout

// --- Directivas del preprocesador ------------------------------------------
#define HORAS_DIA 24      // columnas de la matriz: las horas de un dia
#define DIAS_SEMANA 7     // filas de la matriz: los dias de la semana
#define TIPOS 2           // cuantos tipos de vehiculo hay: carro y moto

// --- Constantes: todos los valores del problema, en un solo lugar ----------
const int CUPOS_CARRO = 25;           // carros que el parqueadero recibe en una hora
const int CUPOS_MOTO = 15;            // motos que el parqueadero recibe en una hora
const int TARIFA_CARRO_DIA = 4000;    // COP por hora de un carro, de dia
const int TARIFA_CARRO_NOCHE = 2500;  // COP por hora de un carro, de noche
const int TARIFA_MOTO = 2000;         // COP por hora de una moto, a cualquier hora
const int NOCHE_INICIO = 20;          // la tarifa de noche empieza a las 8 pm
const int NOCHE_FIN = 5;              // y termina a las 5 am (hora 5 incluida)
const int SEMANAS_MES = 4;            // para proyectar los ingresos del mes

// Nombres de los dias, para mostrarlos en el reporte (fila 0 = Lunes)
const string DIAS[DIAS_SEMANA] = {"Lunes", "Martes", "Miercoles", "Jueves",
                                  "Viernes", "Sabado", "Domingo"};