# 🎮 UNO Avanzado

Implementación completa del juego de cartas UNO en C++ con soporte para reglas configurables, múltiples mazos dinámicos y características avanzadas.

## 📋 Descripción del Proyecto

Este proyecto es una implementación académica del juego UNO desarrollada en C++ que incluye:

- ✅ **Estructuras de datos implementadas desde cero** (sin uso de STL para lógica principal)
- ✅ **Sistema de reglas configurables** mediante flags
- ✅ **Mazos dinámicos** que escalan automáticamente según el número de jugadores
- ✅ **Soporte para 2 o más jugadores** sin límite superior
- ✅ **Sistema de grito de UNO** con reportes y penalizaciones
- ✅ **Acumulación de +2 y +4** opcional
- ✅ **Reto del +4** con validación de jugadas legales

---

## 🏗️ Arquitectura del Proyecto

### Estructuras de Datos Implementadas

1. **Pila Genérica** (`Pila.h`)
   - Implementación: Lista enlazada simple
   - Uso: Pila de descarte
   - Complejidad: O(1) para push/pop/peek

2. **Lista Circular Doblemente Enlazada** (`ListaCircular.h`)
   - Implementación: Lista circular con soporte bidireccional
   - Uso: Manejo de turnos de jugadores
   - Complejidad: O(1) para cambio de turno y reversa

3. **Lista Doblemente Enlazada** (`Mano.h`)
   - Implementación: Lista no circular con punteros cabeza y cola
   - Uso: Cartas en mano de cada jugador
   - Complejidad: O(1) para agregar, O(n) para acceso por índice

### Clases Principales

```
UNO_Avanzado/
├── include/
│   ├── Carta.h           # Definición de cartas (Color, Valor, Lado)
│   ├── Mazo.h            # Generación y gestión de mazos
│   ├── Pila.h            # Pila genérica (template)
│   ├── Mano.h            # Mano del jugador (lista enlazada)
│   ├── Jugador.h         # Clase jugador
│   ├── ListaCircular.h   # Lista circular para turnos
│   ├── Juego.h           # Motor principal del juego
│   └── Configuracion.h   # Sistema de flags de reglas
├── src/
│   ├── Carta.cpp         # Implementación de cartas
│   ├── Mazo.cpp          # Lógica de mazos y barajado
│   └── Juego.cpp         # Lógica del juego
├── main.cpp              # Punto de entrada
├── Makefile              # Compilación tradicional
├── CMakeLists.txt        # Compilación con CMake
├── Manual.md             # Manual de usuario completo
├── Analisis.md           # Análisis de complejidad
└── README.md             # Este archivo
```

---

## 🚀 Instalación y Compilación

### Requisitos Previos

- **Compilador C++**: g++, clang++, o MSVC con soporte para C++11 o superior
- **Make** (opcional): Para usar el Makefile
- **CMake 3.10+** (opcional): Para usar CMake
- **Sistema Operativo**: Windows, Linux o macOS

### Método 1: Compilación con Makefile (Recomendado)

```bash
# Clonar o descargar el proyecto
cd UNO_Avanzado

# Compilar
make

# Ejecutar
./bin/UNO_Avanzado

# O compilar y ejecutar directamente
make run
```

#### Comandos adicionales del Makefile

```bash
make clean     # Eliminar archivos compilados
make rebuild   # Limpiar y recompilar
make info      # Mostrar información del proyecto
make help      # Ver todos los comandos disponibles
```

### Método 2: Compilación con CMake

```bash
# Crear directorio de compilación
mkdir build
cd build

# Configurar
cmake ..

# Compilar
cmake --build .

# Ejecutar
./UNO_Avanzado   # En Linux/macOS
# o
UNO_Avanzado.exe # En Windows
```

### Método 3: Compilación Manual

```bash
# En Linux/macOS
g++ -std=c++11 -Iinclude main.cpp src/*.cpp -o UNO_Avanzado

# En Windows con MinGW
g++ -std=c++11 -Iinclude main.cpp src\*.cpp -o UNO_Avanzado.exe

# Ejecutar
./UNO_Avanzado
```

---

## 🎮 Cómo Jugar

### Inicio Rápido

1. **Ejecutar el programa**
   ```bash
   ./bin/UNO_Avanzado
   ```

2. **Configurar reglas** (presiona 'n' para usar configuración por defecto)
   ```
   === CONFIGURACION DE REGLAS ===
   1. Modo de robo: Robar hasta poder jugar
      Activar? (s/n): n
   
   2. Acumulacion de +2 y +4
      Activar? (s/n): n
   
   3. Reto del +4
      Activar? (s/n): n
   
   4. Ganar con carta negra
      Activar? (s/n): s
   ```

3. **Ingresar número de jugadores**
   ```
   Ingrese el numero de jugadores (minimo 2): 4
   ```

4. **Ingresar nombres**
   ```
   Nombre del Jugador 1: Ana
   Nombre del Jugador 2: Carlos
   Nombre del Jugador 3: María
   Nombre del Jugador 4: Pedro
   ```

5. **Jugar**
   - En tu turno, verás tu mano numerada del 1 al N
   - Ingresa el número de la carta para jugarla
   - Ingresa `0` para robar carta
   - Escribe `UNO` cuando te quede 1 carta

### Reglas Configurables

#### 🎲 Modo de Robo
- **Activado**: Robas cartas hasta obtener una jugable
- **Desactivado** (clásico): Robas 1 carta y pasas el turno

#### ➕ Acumulación de +2 y +4
- **Activado**: Puedes defenderte de un +2 con otro +2 (lo mismo con +4)
- El siguiente jugador recibe la suma acumulada
- **Desactivado**: Recibes las cartas inmediatamente

#### 🎯 Reto del +4
- **Activado**: Puedes retar a quien jugó +4 si sospechas que tenía otra opción
- Si el reto es exitoso: El lanzador recibe 4 cartas
- Si el reto falla: Recibes 6 cartas (4+2 de penalización)

#### 🃏 Ganar con Carta Negra
- **Activado**: Puedes ganar con cualquier carta
- **Desactivado**: No puedes ganar jugando comodines como última carta

---

## 📚 Documentación

- **[Manual de Usuario](Manual.md)**: Guía completa de juego, reglas y estrategias
- **[Análisis de Complejidad](Analisis.md)**: Análisis detallado de estructuras y algoritmos

---

## 🔧 Características Técnicas

### Escalamiento Dinámico de Mazos

El sistema calcula automáticamente cuántos mazos se necesitan:

```
Mazos = ((Jugadores - 1) / 6) + 1

Ejemplos:
- 2-6 jugadores  → 1 mazo  (108 cartas)
- 7-12 jugadores → 2 mazos (216 cartas)
- 13-18 jugadores → 3 mazos (324 cartas)
```

### Algoritmo de Barajado

Utiliza **Fisher-Yates shuffle** mediante `std::shuffle`:
- Complejidad: O(n)
- Distribución uniforme de permutaciones
- Generador: Mersenne Twister (`std::mt19937`)

### Gestión de Memoria

- **Sin memory leaks**: Destructores implementados correctamente
- **Punteros inteligentes**: Se podrían usar shared_ptr/unique_ptr en versión futura
- **Estructuras dinámicas**: Listas enlazadas crecen/decrecen según necesidad

---

## 📊 Complejidad Computacional

### Resumen de Operaciones Principales

| Operación | Complejidad | Estructura |
|-----------|-------------|------------|
| Barajar mazo | O(n) | Vector + Fisher-Yates |
| Robar carta | O(1) | Vector::pop_back |
| Validar jugada | O(1) | Comparaciones directas |
| Cambiar turno | O(1) | Lista circular |
| Buscar carta en mano | O(m) | Lista enlazada |
| Aplicar efecto | O(1) - O(d) | Pila de descarte |

Donde:
- `n` = cartas en mazo
- `m` = cartas en mano del jugador
- `d` = cartas en pila de descarte

Ver [Analisis.md](Analisis.md) para detalles completos.

---

## 🧪 Pruebas

### Casos de Prueba Recomendados

1. **Partida básica (2 jugadores)**
   ```bash
   make run
   # Ingresar: 2 jugadores, configuración por defecto
   ```

2. **Partida con acumulación (4 jugadores)**
   ```bash
   make run
   # Activar acumulación y reto del +4
   ```

3. **Estrés test (50 jugadores)**
   ```bash
   make run
   # Ingresar 50+ jugadores para probar escalamiento
   ```

### Escenarios Críticos Probados

- ✅ Mazo se agota y rebaraja descarte automáticamente
- ✅ Reversa con 2 jugadores funciona como Salta
- ✅ Acumulación de +2 y +4 (hasta 5 jugadores seguidos)
- ✅ Reto del +4 exitoso y fallido
- ✅ Grito de UNO con reporte correcto/incorrecto
- ✅ Múltiples mazos (probado hasta 10 mazos / 60 jugadores)

---

## 🐛 Solución de Problemas

### Error: "make: command not found"
```bash
# En Windows con MinGW:
# Agregar MinGW/bin al PATH o usar:
mingw32-make

# O usar compilación manual
g++ -std=c++11 -Iinclude main.cpp src/*.cpp -o UNO_Avanzado
```

### Error: Caracteres extraños en consola
- El juego evita usar tildes para compatibilidad
- Asegúrate de que tu terminal soporte UTF-8
- En Windows, ejecuta: `chcp 65001` antes de correr el juego

### Error: "undefined reference to..."
- Asegúrate de compilar todos los archivos .cpp
- Verifica que las rutas de include sean correctas (-Iinclude)

---

## 📝 Trabajo Futuro

### Características Pendientes

- [ ] **UNO Flip**: Implementar cartas FLIP y lado oscuro
- [ ] **Cartas Personalizadas**: Agregar 2 tipos nuevos inventados
- [ ] **Diagrama UML**: Crear diagrama de clases completo
- [ ] **TADs**: Especificación formal de tipos abstractos
- [ ] **IA**: Jugadores automáticos con diferentes niveles de dificultad
- [ ] **Persistencia**: Guardar/cargar partidas
- [ ] **Interfaz Gráfica**: GUI con SDL2 o Qt

### Optimizaciones Propuestas

1. **Cambiar Mano a Vector**: Reducir acceso O(n) → O(1)
2. **Caché de cartas jugables**: Evitar recalcular en cada turno
3. **Pool de cartas**: Reutilizar objetos Carta en lugar de crear/destruir

---

## 👥 Contribuciones

Este es un proyecto académico. Si deseas contribuir:

1. Fork el repositorio
2. Crea una rama (`git checkout -b feature/nueva-caracteristica`)
3. Commit tus cambios (`git commit -m 'Agregar nueva característica'`)
4. Push a la rama (`git push origin feature/nueva-caracteristica`)
5. Abre un Pull Request

---

## 📄 Licencia

Este proyecto fue desarrollado con fines educativos para el curso de Estructuras de Datos y Algoritmos.

**Uso académico permitido** - Se permite usar, modificar y distribuir con fines educativos citando la fuente original.

---

## 🎓 Créditos

**Proyecto**: UNO Avanzado  
**Curso**: Estructuras de Datos y Algoritmos  
**Año**: 2026  
**Lenguaje**: C++11  

### Estructuras Implementadas
- Pila genérica (template)
- Lista circular doblemente enlazada
- Lista doblemente enlazada (mano de jugador)

### Bibliotecas Utilizadas
- `<iostream>`: Entrada/salida
- `<vector>`: Almacenamiento de cartas en mazo
- `<algorithm>`: Algoritmo de barajado (std::shuffle)
- `<random>`: Generador de números aleatorios (Mersenne Twister)
- `<limits>`: Manejo de entrada de usuario

---

## 📞 Contacto

Para preguntas, sugerencias o reportar bugs:
- Abrir un issue en GitHub
- Contactar al profesor del curso

---

## 🎉 Agradecimientos

Gracias por usar UNO Avanzado. ¡Disfruta el juego y que gane el mejor!

---

**Última actualización**: Febrero 2026  
**Versión**: 1.0.0
