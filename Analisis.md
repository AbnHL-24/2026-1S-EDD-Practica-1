# Análisis de Complejidad - UNO Avanzado

## Tabla de Contenidos
1. [Introducción](#introducción)
2. [Análisis de Estructuras de Datos](#análisis-de-estructuras-de-datos)
3. [Análisis de Operaciones Principales](#análisis-de-operaciones-principales)
4. [Análisis de Funciones del Juego](#análisis-de-funciones-del-juego)
5. [Conclusiones y Optimizaciones](#conclusiones-y-optimizaciones)

---

## Introducción

Este documento presenta un análisis detallado de la **complejidad temporal y espacial** de las principales operaciones y estructuras de datos implementadas en el proyecto UNO Avanzado.

### Notación Big-O Utilizada

- **O(1)**: Tiempo constante
- **O(n)**: Tiempo lineal proporcional al tamaño de entrada
- **O(n²)**: Tiempo cuadrático
- **O(log n)**: Tiempo logarítmico
- **O(n log n)**: Tiempo lineal-logarítmico

---

## Análisis de Estructuras de Datos

### 1. Pila Genérica (`Pila.h`)

**Implementación**: Enlazada simple con nodos

#### Complejidad Temporal

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| `push(T dato)` | **O(1)** | Inserción al inicio de la lista |
| `pop()` | **O(1)** | Eliminación del primer nodo |
| `peek()` | **O(1)** | Acceso directo a `cima->dato` |
| `estaVacia()` | **O(1)** | Verificación de puntero `cima == nullptr` |

#### Complejidad Espacial

- **O(n)**: Donde `n` es el número de cartas en la pila de descarte
- Cada nodo almacena: `Carta*` + puntero `siguiente`

#### Código Relevante
```cpp
void push(T dato) {
    Nodo* nuevo = new Nodo(dato);
    nuevo->siguiente = cima;
    cima = nuevo;  // O(1): Solo actualiza puntero
}

T pop() {
    if (!estaVacia()) {
        Nodo* temp = cima;
        T dato = cima->dato;
        cima = cima->siguiente;  // O(1): Solo actualiza puntero
        delete temp;
        return dato;
    }
    return T();
}
```

---

### 2. Mano del Jugador (`Mano.h`) - Lista Doblemente Enlazada

**Implementación**: Lista doblemente enlazada no circular

#### Complejidad Temporal

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| `agregarCarta(Carta* c)` | **O(1)** | Inserción al final con puntero `cola` |
| `obtenerCarta(int indice)` | **O(n)** | Recorrido lineal hasta el índice |
| `removerCarta(int indice)` | **O(n)** | Recorrido + eliminación |
| `getCantidad()` | **O(1)** | Variable `cantidad` mantenida |
| `mostrarMano()` | **O(n)** | Recorrido completo para imprimir |

#### Complejidad Espacial

- **O(m)**: Donde `m` es el número de cartas en la mano del jugador
- Cada nodo: `Carta*` + `anterior*` + `siguiente*`

#### Análisis Detallado: `obtenerCarta(int indice)`

```cpp
Carta* obtenerCarta(int indice) {
    if (indice < 0 || indice >= cantidad) return nullptr;
    
    Nodo* actual = cabeza;
    for (int i = 0; i < indice; ++i) {  // Bucle O(n)
        actual = actual->siguiente;
    }
    return actual->carta;
}
```

**Peor caso**: O(n) cuando se accede a la última carta  
**Mejor caso**: O(1) cuando se accede a la primera carta  
**Caso promedio**: O(n/2) ≈ O(n)

#### Optimización Posible
Se podría optimizar acceso a mitad final usando el puntero `cola`:
```cpp
// Si indice > cantidad/2, recorrer desde cola hacia atrás
if (indice > cantidad / 2) {
    Nodo* actual = cola;
    for (int i = cantidad - 1; i > indice; --i) {
        actual = actual->anterior;
    }
    return actual->carta;
}
```
Esto reduciría el caso promedio a **O(n/4)**, aunque sigue siendo O(n).

---

### 3. Lista Circular (`ListaCircular.h`) - Manejo de Turnos

**Implementación**: Lista circular doblemente enlazada

#### Complejidad Temporal

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| `agregarJugador(string nombre)` | **O(1)** | Inserción al final con punteros circulares |
| `siguienteTurno()` | **O(1)** | Avance de puntero `actual` |
| `obtenerJugadorActual()` | **O(1)** | Retorno de `actual->jugador` |
| `obtenerSiguienteJugador()` | **O(1)** | Acceso directo circular |
| `invertirSentido()` | **O(1)** | Cambio de flag booleano |
| `getCantidad()` | **O(1)** | Variable mantenida |

#### Complejidad Espacial

- **O(p)**: Donde `p` es el número de jugadores
- Cada nodo: `Jugador*` + `anterior*` + `siguiente*`

#### Ventajas de Lista Circular

La estructura circular permite:
1. **Turnos infinitos** sin lógica de "reinicio"
2. **Reversa eficiente**: Solo cambia dirección de navegación
3. **Acceso O(1)** al siguiente/anterior jugador

```cpp
void siguienteTurno() {
    if (actual) {
        if (sentidoHorario) {
            actual = actual->siguiente;  // O(1)
        } else {
            actual = actual->anterior;   // O(1)
        }
    }
}
```

---

### 4. Mazo (`Mazo.h`)

**Implementación**: Vector (`std::vector<Carta*>`)

#### Complejidad Temporal

| Operación | Complejidad | Justificación |
|-----------|-------------|---------------|
| `generarMazoEstandar()` | **O(m)** | Donde m = 108 cartas por mazo |
| `barajar()` | **O(m log m)** | `std::shuffle` usa algoritmo Fisher-Yates |
| `robarCarta()` | **O(1)** amortizado | `pop_back()` de vector |
| `estaVacio()` | **O(1)** | Verificación de `cartas.empty()` |
| `rellenarDesde(Pila)` | **O(d)** | Donde d = cartas en pila descarte |

#### Análisis Detallado: `barajar()`

```cpp
void barajar() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartas.begin(), cartas.end(), g);  // O(n log n)
}
```

**Algoritmo interno de `std::shuffle`**:
- Implementación moderna: Fisher-Yates shuffle
- Complejidad: **O(n)** donde n = tamaño del mazo
- Genera permutación uniforme

**Corrección**: El análisis correcto es **O(n)**, no O(n log n):
```
Para cada posición i de n-1 hasta 1:
    - Generar número aleatorio: O(1)
    - Intercambiar elementos: O(1)
Total: n iteraciones × O(1) = O(n)
```

#### Análisis Detallado: `generarMazoEstandar()`

```cpp
void generarMazoEstandar() {
    for (int mazo = 0; mazo < numMazos; ++mazo) {          // M mazos
        for (int c = 0; c < 4; ++c) {                      // 4 colores
            Color color = static_cast<Color>(c);
            
            // 1 carta de 0
            cartas.push_back(new Carta(color, Valor::CERO));  // O(1)
            
            // 2 cartas de cada 1-9
            for (int v = 1; v <= 9; ++v) {                 // 9 valores
                for (int copia = 0; copia < 2; ++copia) {  // 2 copias
                    cartas.push_back(...);                 // O(1) amortizado
                }
            }
            
            // Cartas de acción (2 de cada tipo)
            for (int i = 0; i < 2; ++i) {
                cartas.push_back(... SALTA ...);
                cartas.push_back(... REVERSA ...);
                cartas.push_back(... TOMA_DOS ...);
            }
        }
        
        // Comodines (4 de cada tipo)
        for (int i = 0; i < 4; ++i) {
            cartas.push_back(... COMODIN ...);
            cartas.push_back(... COMODIN_TOMA_CUATRO ...);
        }
    }
}
```

**Cálculo de complejidad**:
- Cartas por mazo: 108
- Mazos: M = `((numJugadores - 1) / 6) + 1`
- Total iteraciones: 108 × M
- Cada `push_back`: O(1) amortizado
- **Complejidad total**: **O(108M)** = **O(M)** = **O(1)** relativo al número de jugadores

Como M crece muy lentamente (1 mazo cada 6 jugadores), esto es prácticamente constante para partidas normales.

#### Complejidad Espacial

- **O(108 × M)**: Memoria para todas las cartas
- Para 4 jugadores: 108 cartas ≈ 1.08 KB (asumiendo 10 bytes por carta)
- Para 50 jugadores: 972 cartas ≈ 9.72 KB

---

## Análisis de Operaciones Principales

### 1. Barajar el Mazo

#### Implementación
```cpp
void Mazo::barajar() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartas.begin(), cartas.end(), g);
}
```

#### Complejidad
- **Temporal**: **O(n)** donde n = número de cartas en el mazo
- **Espacial**: **O(1)** (no requiere memoria adicional significativa)

#### Desglose del algoritmo Fisher-Yates

```
Para i = n-1 hasta i = 1:
    j = random(0, i)
    swap(cartas[i], cartas[j])
```

**Prueba de O(n)**:
- Iteraciones: n-1
- Cada iteración: O(1) para generar aleatorio + O(1) para swap
- Total: (n-1) × O(1) = **O(n)**

---

### 2. Buscar Carta Jugable en Mano

#### Implementación (en `jugarTurno`)
```cpp
// Modo: Robar hasta poder jugar
while (!puedeJugar && cartasRobadas < 50) {
    Carta* robada = mazo->robarCarta();           // O(1)
    jugadorActual->tomarCarta(robada);            // O(1)
    cartasRobadas++;
    
    if (validarJugada(robada)) {                  // O(n)
        puedeJugar = true;
    }
}
```

#### Función `validarJugada()`
```cpp
bool Juego::validarJugada(Carta* carta) {
    // Verificaciones O(1)
    if (acumulacionActual > 0 && config->acumulacionActivada) {
        if (tipoAcumulacion == Valor::TOMA_DOS && carta->getValor() == Valor::TOMA_DOS) {
            return true;  // O(1)
        }
        // ...
        return false;
    }
    
    if (carta->getColor() == Color::NEGRO) return true;         // O(1)
    if (carta->getColor() == colorActual) return true;          // O(1)
    if (carta->getValor() == valorActual) return true;          // O(1)
    
    return false;
}
```

#### Complejidad de `validarJugada()`
- **Temporal**: **O(1)** (solo comparaciones directas)
- **Espacial**: **O(1)**

#### Complejidad del bucle de robo
- **Mejor caso**: O(1) - Primera carta robada es jugable
- **Peor caso**: O(k) - Roba k cartas hasta encontrar una jugable
- **k** está limitado por el tamaño del mazo restante
- En la práctica: **O(1) a O(10)** para partidas normales

---

### 3. Verificar si un Jugador Tiene Carta Jugable

#### Implementación (`puedeJugarCartaActual`)
```cpp
bool Juego::puedeJugarCartaActual(Jugador* jugador) {
    Mano* mano = jugador->getMano();
    
    for (int i = 0; i < mano->getCantidad(); ++i) {      // Bucle O(m)
        Carta* carta = mano->obtenerCarta(i);            // O(m) cada vez!
        if (carta) {
            if (carta->getColor() != Color::NEGRO) {
                if (carta->getColor() == colorActual || carta->getValor() == valorActual) {
                    return true;                         // O(1)
                }
            }
        }
    }
    
    return false;
}
```

#### Complejidad Actual (INEFICIENTE)
- **Temporal**: **O(m²)** donde m = cartas en la mano
  - Bucle externo: m iteraciones
  - `obtenerCarta(i)`: O(m) por el recorrido de la lista enlazada
  - Total: m × m = O(m²)
- **Espacial**: **O(1)**

#### Optimización Propuesta
```cpp
bool Juego::puedeJugarCartaActual(Jugador* jugador) {
    Mano* mano = jugador->getMano();
    Nodo* actual = mano->obtenerCabeza();  // Acceso directo O(1)
    
    while (actual != nullptr) {             // O(m) una sola vez
        Carta* carta = actual->carta;
        if (carta) {
            if (carta->getColor() != Color::NEGRO) {
                if (carta->getColor() == colorActual || carta->getValor() == valorActual) {
                    return true;
                }
            }
        }
        actual = actual->siguiente;         // O(1)
    }
    
    return false;
}
```

**Complejidad optimizada**: **O(m)** - Mejora significativa

---

### 4. Aplicar Efecto de Carta

#### Análisis de `aplicarEfectoCarta()`

```cpp
void Juego::aplicarEfectoCarta(Carta* carta) {
    valorActual = carta->getValor();          // O(1)
    
    if (carta->getColor() == Color::NEGRO) {  // O(1)
        // Solicitar color al usuario
        int colorElegido;
        std::cin >> colorElegido;              // O(1) - Entrada usuario
        colorActual = static_cast<Color>(colorElegido);  // O(1)
    } else {
        colorActual = carta->getColor();       // O(1)
    }

    switch (carta->getValor()) {
        case Valor::SALTA:
            jugadores->siguienteTurno();       // O(1) - Lista circular
            break;
            
        case Valor::REVERSA:
            if (jugadores->getCantidad() == 2) {
                jugadores->siguienteTurno();   // O(1)
            } else {
                jugadores->invertirSentido();  // O(1)
            }
            break;
            
        case Valor::TOMA_DOS:
        case Valor::COMODIN_TOMA_CUATRO: {
            int cantidad = (carta->getValor() == Valor::TOMA_DOS) ? 2 : 4;
            
            if (config->acumulacionActivada) {
                acumulacionActual += cantidad;  // O(1)
                // ... lógica de reto O(1)
            } else {
                Jugador* victima = jugadores->obtenerSiguienteJugador();  // O(1)
                for (int i = 0; i < cantidad; ++i) {  // O(cantidad) = O(1) - máximo 4
                    if (mazo->estaVacio()) {
                        mazo->rellenarDesde(*pilaDescarte);  // O(d)
                    }
                    victima->tomarCarta(mazo->robarCarta());  // O(1)
                }
                jugadores->siguienteTurno();    // O(1)
            }
            break;
        }
    }
}
```

#### Complejidad
- **Mejor caso**: **O(1)** - Cartas numéricas, SALTA, REVERSA
- **Peor caso**: **O(d)** - Cuando el mazo se vacía y hay que rellenar desde descarte
  - d = cartas en pila de descarte
  - En la práctica: d ≈ 20-50 cartas
- **Caso promedio**: **O(1)** - La mayoría de cartas no vacían el mazo

---

### 5. Rellenar Mazo desde Descarte

#### Implementación
```cpp
void Mazo::rellenarDesde(Pila<Carta*>& pilaDescarte) {
    while (!pilaDescarte.estaVacia()) {        // Bucle O(d)
        Carta* carta = pilaDescarte.pop();     // O(1)
        cartas.push_back(carta);               // O(1) amortizado
    }
    barajar();                                 // O(d)
}
```

#### Complejidad
- **Temporal**: **O(d)** donde d = cartas en descarte
  - Bucle while: d iteraciones
  - pop(): O(1) cada vez
  - push_back(): O(1) amortizado
  - barajar(): O(d)
  - Total: O(d) + O(d) = **O(d)**
- **Espacial**: **O(1)** - Solo mueve punteros, no crea nuevas cartas

#### Frecuencia
- En una partida de 4 jugadores con 108 cartas:
  - Primera recarga: ~50-70 turnos
  - Subsecuentes: ~30-40 turnos
  - Total recargas en partida promedio: 2-4 veces

---

## Análisis de Funciones del Juego

### 1. Inicialización del Juego

```cpp
void Juego::inicializarJuego() {
    config->configurarReglas();              // O(1) - Input usuario
    
    // Solicitar número de jugadores          // O(1) - Input usuario
    
    // Agregar jugadores
    for (int i = 0; i < numJugadores; ++i) { // O(p)
        jugadores->agregarJugador(nombre);   // O(1) cada vez
    }
    
    // Crear mazo múltiple
    int cantidadMazos = ((numJugadores - 1) / 6) + 1;  // O(1)
    mazo = new Mazo(cantidadMazos);          // O(M × 108) ≈ O(M)
    
    mazo->barajar();                         // O(M × 108)
    repartirCartasIniciales();               // O(p × 7)
    
    // Primera carta
    Carta* primeraCarta = mazo->robarCarta(); // O(1)
    pilaDescarte->push(primeraCarta);         // O(1)
}
```

#### Complejidad Total
- **Temporal**: **O(M × 108 + p)** ≈ **O(M + p)**
  - Generación de mazos: O(M × 108)
  - Barajado: O(M × 108)
  - Agregar jugadores: O(p)
  - Repartir cartas: O(p × 7) = O(p)
- **Dominante**: O(M × 108) que es prácticamente constante

Para partidas normales (4-10 jugadores):
- M = 1 o 2 mazos
- p = 4-10
- **Complejidad práctica**: **O(1)** - Tiempo constante

---

### 2. Repartir Cartas Iniciales

```cpp
void Juego::repartirCartasIniciales() {
    for (int i = 0; i < 7; ++i) {                    // 7 cartas
        Nodo* actual = jugadores->obtenerCabeza();   // O(1)
        
        for (int j = 0; j < jugadores->getCantidad(); ++j) {  // p jugadores
            if (mazo->estaVacio()) {
                mazo->rellenarDesde(*pilaDescarte);  // O(d) - Raro al inicio
            }
            
            if (!mazo->estaVacio()) {
                Carta* carta = mazo->robarCarta();   // O(1)
                actual->jugador->tomarCarta(carta);  // O(1) - Agregar al final
            }
            
            actual = actual->siguiente;              // O(1) - Circular
        }
    }
}
```

#### Complejidad
- **Temporal**: **O(7 × p)** = **O(p)** donde p = número de jugadores
- **Espacial**: **O(1)** - No crea estructuras nuevas

---

### 3. Bucle Principal del Juego

```cpp
void Juego::buclePrincipal() {
    while (!juegoTerminado) {                      // O(t) turnos
        Jugador* actual = jugadores->obtenerJugadorActual();  // O(1)
        
        verificarReporteUNO();                     // O(1) - Input usuario
        
        jugarTurno(actual);                        // O(m²) peor caso
        
        if (actual->getMano()->getCantidad() == 0) {  // O(1)
            juegoTerminado = true;
        } else {
            siguienteTurno();                      // O(1)
        }
    }
}
```

#### Complejidad por Turno
- **Mejor caso**: O(1) - Juega carta directa sin verificaciones
- **Peor caso**: O(m²) - Busca cartas jugables con `puedeJugarCartaActual()`
- **Caso promedio**: O(m) - Muestra mano y valida jugada

#### Complejidad de Partida Completa
- **t** = número de turnos hasta que alguien gane
- **t** depende de:
  - Número de jugadores (p)
  - Cartas de acción jugadas
  - Estrategia de jugadores
- **Estimación**: t ≈ 50-200 turnos para 4 jugadores
- **Complejidad total**: **O(t × m²)** en peor caso, **O(t × m)** promedio

---

### 4. Jugar un Turno

```cpp
void Juego::jugarTurno(Jugador* jugadorActual) {
    // Verificar acumulación
    if (acumulacionActual > 0) {                   // O(1)
        // Buscar si tiene carta para acumular
        for (int i = 0; i < mano->getCantidad(); ++i) {  // O(m)
            Carta* carta = mano->obtenerCarta(i);  // O(m) - INEFICIENTE
            if (carta && carta->getValor() == tipoAcumulacion) {
                tieneCartaParaAcumular = true;
                break;
            }
        }
        // Total: O(m²) por búsqueda ineficiente
    }
    
    jugadorActual->mostrarMano();                  // O(m)
    
    // Usuario elige opción
    if (opcion == 0) {
        // Robar carta(s)
        if (config->robarHastaPoderJugar) {
            while (!puedeJugar) {                  // O(k) iteraciones
                Carta* robada = mazo->robarCarta(); // O(1)
                if (validarJugada(robada)) {        // O(1)
                    puedeJugar = true;
                }
            }
        } else {
            Carta* robada = mazo->robarCarta();    // O(1)
            jugadorActual->tomarCarta(robada);     // O(1)
        }
    } else {
        // Jugar carta
        Carta* carta = jugadorActual->getMano()->obtenerCarta(opcion - 1);  // O(m)
        if (validarJugada(carta)) {                // O(1)
            jugadorActual->jugarCarta(opcion - 1); // O(m)
            pilaDescarte->push(carta);             // O(1)
            aplicarEfectoCarta(carta);             // O(1) o O(d)
        }
    }
}
```

#### Complejidad
- **Robar**: O(k) en modo "robar hasta poder jugar", O(1) en modo clásico
- **Jugar**: O(m) para acceso + O(m) para remoción + O(1) aplicar efecto
- **Total por turno**: **O(m)** en caso promedio, **O(m² + d)** en peor caso

---

## Conclusiones y Optimizaciones

### Resumen de Complejidades Principales

| Operación | Complejidad Actual | Optimización Posible | Impacto |
|-----------|-------------------|----------------------|---------|
| Barajar mazo | **O(n)** ✅ Óptimo | - | Ninguna |
| Validar jugada | **O(1)** ✅ Óptimo | - | Ninguna |
| Buscar carta en mano (índice) | **O(m)** ⚠️ | Usar array/vector: **O(1)** | Alto |
| Verificar cartas jugables | **O(m²)** ❌ Crítico | Recorrido directo: **O(m)** | Crítico |
| Aplicar efecto carta | **O(1)** - **O(d)** ✅ | - | Ninguna |
| Turno completo | **O(m²)** ❌ | Con optimizaciones: **O(m)** | Alto |
| Rellenar mazo | **O(d)** ✅ Óptimo | - | Ninguna |

### Optimizaciones Críticas Recomendadas

#### 1. Cambiar Mano a Vector
**Problema**: Acceso por índice en lista enlazada es O(m)

**Solución**:
```cpp
class Mano {
private:
    std::vector<Carta*> cartas;  // En lugar de lista enlazada
    
public:
    void agregarCarta(Carta* c) {
        cartas.push_back(c);     // O(1) amortizado
    }
    
    Carta* obtenerCarta(int indice) {
        if (indice >= 0 && indice < cartas.size()) {
            return cartas[indice];  // O(1) directo!
        }
        return nullptr;
    }
    
    Carta* removerCarta(int indice) {
        Carta* carta = cartas[indice];
        cartas.erase(cartas.begin() + indice);  // O(m) pero inevitable
        return carta;
    }
};
```

**Ganancia**:
- Acceso por índice: O(m) → **O(1)**
- `puedeJugarCartaActual()`: O(m²) → **O(m)**
- Reducción de 95% en tiempo para manos grandes

**Trade-off**:
- Remoción sigue siendo O(m) por `erase()`
- Pero en UNO se remueve máximo 1 carta por turno
- Ganancia neta: **Positiva**

---

#### 2. Optimizar Búsqueda de Cartas Jugables

**Solución actual (O(m²))**:
```cpp
for (int i = 0; i < mano->getCantidad(); ++i) {  // m veces
    Carta* carta = mano->obtenerCarta(i);        // O(m) cada vez
    // ...
}
```

**Solución optimizada (O(m))**:
```cpp
Nodo* actual = mano->obtenerCabeza();
while (actual != nullptr) {      // m veces
    Carta* carta = actual->carta; // O(1)
    // verificaciones O(1)
    actual = actual->siguiente;   // O(1)
}
```

**Ganancia**: 10x más rápido para manos de 10 cartas

---

#### 3. Caché de Cartas Jugables

**Idea**: Mantener un flag booleano `tieneCartaJugable` en cada jugador

```cpp
class Jugador {
private:
    bool tieneCartaJugable;
    
public:
    void actualizarCartasJugables(Color colorActual, Valor valorActual) {
        tieneCartaJugable = false;
        for (Carta* c : mano->getCartas()) {
            if (c->getColor() == colorActual || 
                c->getValor() == valorActual || 
                c->getColor() == Color::NEGRO) {
                tieneCartaJugable = true;
                break;
            }
        }
    }
};
```

**Ventaja**: Evita recalcular en cada consulta  
**Desventaja**: Debe actualizarse cada vez que cambia el estado del juego

---

### Análisis de Escalabilidad

#### Partida de 4 Jugadores (Caso Normal)
- Mazo: 108 cartas
- Turnos estimados: 80
- Complejidad por turno: O(10) promedio
- **Tiempo total**: O(800) ≈ **Constante en la práctica**

#### Partida de 50 Jugadores (Extremo)
- Mazos: 9 mazos (972 cartas)
- Turnos estimados: 500
- Complejidad por turno: O(15) promedio
- **Tiempo total**: O(7500) ≈ **Lineal aceptable**

#### Conclusión
El juego escala adecuadamente hasta 50+ jugadores con las estructuras actuales. Las optimizaciones propuestas mejorarían aún más el rendimiento.

---

### Complejidad Espacial Total

Para una partida de **p jugadores** con **M mazos**:

```
Memoria Total = Mazo + Jugadores + Descarte

Mazo:      O(M × 108) = O(M) cartas
Jugadores: O(p × m_promedio) ≈ O(p × 8) cartas en manos
Descarte:  O(d) ≈ O(30-50) cartas
Total:     O(M + p × 8 + d) ≈ O(M + p)
```

Para 4 jugadores:
- Mazo: 108 cartas × ~20 bytes = ~2.16 KB
- Jugadores: 4 × 8 cartas × 20 bytes = ~0.64 KB
- Descarte: 40 cartas × 20 bytes = ~0.8 KB
- **Total**: ~**3.6 KB** de memoria dinámica

**Conclusión**: Extremadamente eficiente en memoria.

---

## Apéndice: Fórmulas de Complejidad

### Cálculo de Mazos Necesarios
```
M = ((p - 1) / 6) + 1

Ejemplos:
p=2:  M = ((2-1)/6) + 1 = 0 + 1 = 1
p=6:  M = ((6-1)/6) + 1 = 0 + 1 = 1
p=7:  M = ((7-1)/6) + 1 = 1 + 1 = 2
p=13: M = ((13-1)/6) + 1 = 2 + 1 = 3
```

### Estimación de Turnos por Partida
```
t ≈ 7p + k

Donde:
- p = número de jugadores
- k = factor de cartas de acción (20-50)

Ejemplos:
p=4: t ≈ 7(4) + 30 = 58 turnos
p=8: t ≈ 7(8) + 40 = 96 turnos
```

---

**Autor**: Análisis de Complejidad - UNO Avanzado  
**Fecha**: 2026  
**Curso**: Estructuras de Datos y Algoritmos
