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

int posicionMaximo(const float datos[], int n) {
    return diaMayor(datos, n);
}

int posicionMaximo(const int datos[], int n) {
    int posMayor = 0;
    for (int i = 1; i < n; i++) {
        if (datos[i] > datos[posMayor]) {
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

// 4. VALIDACIONES Y MANIPULACION DE STRING
string normalizarTexto(string texto) {
    size_t inicio = texto.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fin = texto.find_last_not_of(" \t\r\n");
    string limpio = texto.substr(inicio, fin - inicio + 1);

    for (size_t i = 0; i < limpio.length(); i++) {
        limpio[i] = static_cast<char>(toupper(static_cast<unsigned char>(limpio[i])));
    }
    return limpio;
}

// Valida placa colombiana: Carro (ABC123) o Moto (ABC12D)
bool validarPlaca(string placa) {
    placa = normalizarTexto(placa);
    if (placa.length() != 6) return false;

    for (int i = 0; i < 3; i++) {
        if (!isalpha(static_cast<unsigned char>(placa[i]))) return false;
    }
    if (!isdigit(static_cast<unsigned char>(placa[3])) ||
        !isdigit(static_cast<unsigned char>(placa[4]))) {
        return false;
    }
    char ultimo = placa[5];
    return isdigit(static_cast<unsigned char>(ultimo)) ||
           isalpha(static_cast<unsigned char>(ultimo));
}

// Valida que el tipo ingresado corresponda a CARRO o MOTO
bool validarTipoVehiculo(string tipo) {
    tipo = normalizarTexto(tipo);
    return (tipo == "CARRO" || tipo == "MOTO");
}

// Verifica que una cadena no este vacia ni compuesta solo por espacios
bool esCadenaValida(const string& texto) {
    return !normalizarTexto(texto).empty();
}

// Solicita una placa por consola hasta que cumpla el formato colombiano (ABC123 o ABC12D)
string pedirPlaca() {
    string placa;
    while (true) {
        cout << "Ingrese la placa (ej. ABC123 o ABC12D): ";
        cin >> ws;
        getline(cin, placa);
        placa = normalizarTexto(placa);
        if (validarPlaca(placa)) {
            return placa;
        }
        cout << "Placa invalida. Debe tener 3 letras seguidas de 3 digitos (carro) o 2 digitos y 1 letra (moto)." << endl;
    }
}