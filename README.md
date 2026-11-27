# WattControl · Sistema de Gestión Energética (Panadería) — Evidencia 3

Sistema en C++ orientado a objetos para simular, controlar y optimizar el consumo eléctrico semanal (`7 días × 24 horas`) de una panadería comercial en Colombia, respetando el límite de potencia contratada (`9.0 kW`), franjas horarias pico (`18:00–20:00`) y alertas por nivel crítico de embalses (`< 40%`).

## Diagrama de Clases UML (Arquitectura Evidencia 3)

```mermaid
classDiagram
    class Carga {
        #string nombre_
        #double potenciaKW_
        #bool encendida_
        #double consumoSemanal_[7][24]
        +debeEncender(hora, precio, embalses)* bool
        +tipo()* string
        +registrarConsumo(dia, hora, kwh) void
        +registrarConsumo(dia, hora) void
        +calcularConsumoTotalSemanal() double
    }

    class CargaCritica {
        +debeEncender(hora, precio, embalses) bool
        +tipo() string
    }

    class CargaAplazable {
        +debeEncender(hora, precio, embalses) bool
        +tipo() string
    }

    class Mercado {
        -string operador
        -double nivelEmbalses
        -double preciosSemana[7][24]
        +cargarTarifasSemanales() void
        +getPrecio(dia, hora) double
        +getPrecio(hora) double
        +esHoraPico(hora) bool
        +hayAlertaEmbalses() bool
        +calcularPromedioSemanal() double
    }

    class Medidor {
        -double lecturasSemana[7][24]
        +registrarLectura(dia, hora, kw) void
        +superaPotenciaContratada(kw) bool
        +calcularTotalSemanal() double
    }

    class Negocio {
        -string nombre_
        -Medidor medidor_
        -Carga* cargas_[10]
        -Mercado* mercado_
        +agregarCarga(carga) bool
        +evaluarCargas(dia, hora) void
        +simularSemana() void
    }

    class Reporte {
        +mostrarResumenDiario(negocio, kwh, cop)$ void
        +mostrarReporteSemanal(negocio, cargas, n, tarifas)$ void
    }

    class Utilidades {
        <<modulo utilidades.h>>
        +totalSemana(matriz) double
        +promedio(matriz) double
        +diaMayor(matriz) int
        +horaMayor(matriz) int
        +calcularCosto(kwh, tarifa) double
        +calcularCosto(consumo, tarifas) double
        +validarNombreEquipo(nombre) bool
    }

    Carga <|-- CargaCritica : Herencia
    Carga <|-- CargaAplazable : Herencia
    Negocio "1" *-- "1" Medidor : Composicion
    Negocio "1" o-- "1..*" Carga : Agregacion
    Negocio --> "1" Mercado : Asociacion
    Reporte ..> Carga : Dependencia
    Mercado ..> Utilidades : Dependencia
    Carga ..> Utilidades : Dependencia