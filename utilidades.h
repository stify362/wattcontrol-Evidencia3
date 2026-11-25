#pragma once            // #pragma once: si dos archivos lo incluyen, se copia una sola vez
#include "configuracion.h"   // necesita cout, string y las constantes

// =============================================================
// FUNCIONES: piezas de codigo con nombre, que reciben datos
// (parametros) y devuelven un resultado (retorno)
// =============================================================

// SOBRECARGA: dos funciones con el MISMO nombre y parametros DISTINTOS.
// 1) Suma un arreglo de enteros (por ejemplo, los vehiculos de un dia)
int sumar(const int datos[], int n) {
    int total = 0;                    // empieza en cero
    for (int i = 0; i < n; i++) {     // recorre las n posiciones
        total += datos[i];            // y va sumando cada una
    }
    return total;                     // devuelve la suma
}

// 2) Suma un arreglo de decimales (por ejemplo, los ingresos de un dia)
float sumar(const float datos[], int n) {
    float total = 0;                  // igual que la anterior,
    for (int i = 0; i < n; i++) {     // pero con float:
        total += datos[i];            // C++ elige cual usar segun el tipo del arreglo
    }
    return total;
}

// Promedio de un arreglo de decimales: usa la funcion sumar
float promedio(const float datos[], int n) {
    return sumar(datos, n) / n;       // la suma dividida por la cantidad
}

// Posicion del valor mas alto de un arreglo
int posicionMaximo(const float datos[], int n) {
    int posicion = 0;                 // supone que el mayor es el primero
    for (int i = 1; i < n; i++) {     // compara con los demas
        if (datos[i] > datos[posicion]) {
            posicion = i;             // encontro uno mayor: guarda su posicion
        }
    }
    return posicion;                  // devuelve la POSICION, no el valor
}

// SOBRECARGA: una linea de guiones, o de cualquier caracter
void linea(int largo) {
    for (int i = 0; i < largo; i++) cout << '-';   // largo guiones
    cout << endl;                                  // y salta de linea
}

void linea(int largo, char caracter) {
    for (int i = 0; i < largo; i++) cout << caracter;  // largo veces el caracter pedido
    cout << endl;
}

// FUNCIONES DE STRING: revisa una placa de carro colombiana (ABC123).
// Devuelve el problema que tiene, o "" si esta bien
string problemaPlaca(string placa) {
    if (placa.empty()) {                          // empty(): esta vacia?
        return "no puede estar vacia";
    }
    if (placa.length() != 6) {                    // length(): cuantos caracteres tiene
        return "debe tener 6 caracteres";
    }
    for (int i = 0; i < 3; i++) {                 // las 3 primeras posiciones
        if (!isupper(placa.at(i))) {              // at(i): el caracter de la posicion i
            return "debe empezar con 3 letras mayusculas";
        }
    }
    for (int i = 3; i < (int)placa.size(); i++) { // size(): igual que length()
        if (!isdigit(placa.at(i))) {              // isdigit: es un numero?
            return "debe terminar con 3 numeros";
        }
    }
    return "";                                    // "" = no hay problema
}

// Pide una placa hasta que sea valida
string pedirPlaca() {
    string placa;                                 // lo que escribe el usuario
    string problema;                              // lo que tiene mal, o ""
    do {
        cout << "Placa del carro (ejemplo ABC123): ";
        getline(cin, placa);                      // getline: lee la linea completa
        problema = problemaPlaca(placa);          // la revisa
        if (problema != "") cout << "  La placa " << problema << "." << endl;
    } while (problema != "");                     // repite mientras tenga problema
    return placa;
}