#include "Carro.h"            // los tipos concretos que crea el main
#include "Moto.h"
#include "Parqueadero.h"      // trae tambien Caja y Afluencia

// =============================================================
// main: crea los objetos, muestra el menu y llama metodos
// =============================================================
int main() {
    Carro carro;                        // los tipos se crean aqui, fuera del parqueadero
    Moto moto;                          // (por eso es AGREGACION)
    Afluencia afluencia;                // la matriz de llegadas
    Parqueadero parqueadero("Parqueadero Central", &carro, &moto, &afluencia);  // & = la direccion del objeto

    int opcion;                         // la opcion que elige el usuario
    do {
        cout << "\n=== ParqueaControl ===" << endl;
        cout << "1. Ver la afluencia de carros" << endl;
        cout << "2. Simular la semana" << endl;
        cout << "3. Ver el reporte semanal" << endl;
        cout << "4. Validar una placa" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();                   // quita el Enter que queda despues del numero

        switch (opcion) {
            case 1: afluencia.mostrar(); break;
            case 2: parqueadero.simularSemana(); break;
            case 3: parqueadero.reporte(); break;
            case 4: {                   // llaves: el case declara una variable
                string placa = pedirPlaca();            // pide hasta que sea valida
                cout << "Placa valida: " << placa << endl;
                break;
            }
            case 0: cout << "Hasta luego." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);              // repite hasta que elija 0
    return 0;
}
