# WattControl · Sistema de Gestión Energética (Panadería) — Evidencia 3

Sistema en C++ orientado a objetos para simular, controlar y optimizar el consumo eléctrico semanal (`7 días × 24 horas`) de una panadería comercial en Colombia, respetando el límite de potencia contratada (`9.0 kW`), franjas horarias pico (`18:00–20:00`) y alertas por nivel crítico de embalses (`< 40%`).

---

## Arquitectura Orientada a Objetos (POO)

El sistema implementa las 5 relaciones fundamentales del paradigma orientado a objetos aplicadas al dominio energético:

* **Herencia (`Carga` → `CargaCritica`, `CargaAplazable`):** Polimorfismo en la decisión de encendido (`debeEncender`) según la criticidad operativa del equipo (hornos y refrigeración vs. amasadoras y batidoras) y el estado del mercado.
* **Composición (`Negocio` ◆— `Medidor`):** El medidor inteligente pertenece exclusivamente al ciclo de vida del negocio y almacena la matriz semanal de consumo (`[7][24]`).
* **Agregación (`Negocio` ◇— `Carga*`):** El negocio administra una colección dinámica de equipos eléctricos (`Carga*`) independientes entre sí.
* **Asociación (`Negocio` —— `Mercado*`):** El negocio consulta las tarifas horarias en COP/kWh y el porcentaje de embalses del mercado energético colombiano.
* **Dependencia (`wattcontrol.cpp`, `Reporte`, `utilidades`, `configuracion`):** Módulos transversales de análisis semanal, proyección de ahorro mensual (`× 4`) y formateo de tablas en consola.

---

## Diagrama de Clases (UML)

```mermaid
classDiagram
    class Carga {
        <<abstract>>
        #string nombre_
        #double potenciaKW_
        #bool encendida_
        #double consumoSemanal_[7][24]
        +debeEncender(hora, precio, embalses)* bool
        +tipo()* string
        +registrarConsumo(dia, hora) void
        +calcularConsumoTotalSemanal() double
    }
    class CargaCritica {
        +debeEncender(hora, precio, embalses) bool
        +tipo() string
    }
    class CargaAplazable {
        -double umbralPrecio_
        +debeEncender(hora, precio, embalses) bool
        +tipo() string
    }
    class Medidor {
        -double limitePotenciaKW_
        -double lecturasSemana_[7][24]
        +registrarLectura(dia, hora, kwh) void
        +superaLimite(potenciaActual) bool
        +energiaTotalSemanalKWh() double
    }
    class Mercado {
        -double preciosSemana_[7][24]
        -double nivelEmbalsesPct_
        +precioEn(dia, hora) double
        +enRiesgoEmbalses() bool
        +detectarHorasPico(dia) int
    }
    class Negocio {
        -string nombre_
        -Medidor medidor_
        -vector~Carga*~ cargas_
        -Mercado* mercado_
        +simularDia() void
        +simularSemana() void
        +mostrarResumen() void
    }
    class Reporte {
        +mostrarReporteSemanal(negocio) void
        +compararEscenarios(base, optimizado) void
    }

    Carga <|-- CargaCritica : Herencia
    Carga <|-- CargaAplazable : Herencia
    Negocio *-- Medidor : Composición
    Negocio o-- Carga : Agregación
    Negocio --> Mercado : Asociación
    Negocio ..> Reporte : Dependencia

    wattcontrol-Evidencia3/
├── include/
│   ├── Carga.h
│   ├── CargaAplazable.h
│   ├── CargaCritica.h
│   ├── Medidor.h
│   ├── Mercado.h
│   ├── Negocio.h
│   ├── Reporte.h
│   ├── configuracion.h
│   └── utilidades.h
├── src/
│   ├── Carga.cpp
│   ├── CargaAplazable.cpp
│   ├── CargaCritica.cpp
│   ├── Medidor.cpp
│   ├── Mercado.cpp
│   ├── Negocio.cpp
│   ├── Reporte.cpp
│   └── wattcontrol.cpp
└── README.md

g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o wattcontrol
./wattcontrol