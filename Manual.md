# Manual de Usuario - UNO Avanzado

## Tabla de Contenidos
1. [Introducción](#introducción)
2. [Instalación y Compilación](#instalación-y-compilación)
3. [Inicio del Juego](#inicio-del-juego)
4. [Configuración de Reglas](#configuración-de-reglas)
5. [Mecánicas de Juego](#mecánicas-de-juego)
6. [Reglas Especiales](#reglas-especiales)
7. [Cartas y Sus Efectos](#cartas-y-sus-efectos)
8. [Consejos y Estrategias](#consejos-y-estrategias)

---

## Introducción

Bienvenido a **UNO Avanzado**, una implementación completa del juego de cartas UNO en C++ con soporte para reglas configurables, múltiples mazos dinámicos y características avanzadas como acumulación de cartas y reto del +4.

### Características Principales
- ✅ Soporte para **2 o más jugadores** (sin límite superior)
- ✅ **Mazos dinámicos**: Se agregan mazos automáticamente según el número de jugadores
- ✅ **Reglas configurables**: Activa o desactiva reglas antes de cada partida
- ✅ **Sistema de grito de UNO**: Manual con sistema de reportes
- ✅ **Acumulación de +2 y +4**: Los jugadores pueden defenderse acumulando cartas
- ✅ **Reto del +4**: Desafía a quien jugó un +4 si sospechas que tenía otra opción

---

## Instalación y Compilación

### Requisitos
- Compilador C++ con soporte para C++11 o superior (g++, clang++, MSVC)
- CMake 3.10 o superior (opcional, se puede usar Makefile)
- Sistema operativo: Windows, Linux o macOS

### Compilación con CMake (Recomendado)

```bash
# Desde el directorio raíz del proyecto
mkdir build
cd build
cmake ..
cmake --build .
```

### Compilación con Makefile

```bash
make
```

### Ejecución

```bash
# Si compilaste con CMake
./build/UNO_Avanzado

# Si compilaste con Makefile
./UNO_Avanzado
```

---

## Inicio del Juego

### 1. Configuración de Reglas

Al iniciar el juego, se te presentará un menú de configuración:

```
=== CONFIGURACION DE REGLAS ===

1. Modo de robo: Robar hasta poder jugar
   (Desactivado: Robar 1 carta y pasar turno)
   Activar? (s/n): 
```

**Recomendación para nuevos jugadores**: Acepta la configuración por defecto (presiona 'n' en todas las opciones).

### 2. Número de Jugadores

```
Ingrese el numero de jugadores (minimo 2): 4
```

- **Mínimo**: 2 jugadores
- **Máximo**: Sin límite (se mostrará advertencia si excede 50)
- El sistema calculará automáticamente cuántos mazos se necesitan:
  - 1-6 jugadores: 1 mazo (108 cartas)
  - 7-12 jugadores: 2 mazos (216 cartas)
  - Formula: `((n_jugadores - 1) / 6) + 1`

### 3. Nombres de Jugadores

Ingresa el nombre de cada jugador cuando se solicite:

```
Nombre del Jugador 1: Ana
Nombre del Jugador 2: Carlos
Nombre del Jugador 3: María
Nombre del Jugador 4: Pedro
```

---

## Configuración de Reglas

### Regla 1: Modo de Robo

**Opción A - Robar hasta poder jugar** (Por defecto)
- Cuando no tienes carta jugable, sigues robando hasta obtener una que puedas jugar
- Más dinámico y rápido

**Opción B - Robar 1 y pasar**
- Robas solo 1 carta y pierdes el turno
- Modo clásico de UNO

### Regla 2: Acumulación de +2 y +4

**Activada**:
- Si alguien te lanza un +2, puedes defenderte jugando otro +2
- El siguiente jugador recibe la suma acumulada (4, 6, 8 cartas...)
- Lo mismo aplica para +4 (4, 8, 12 cartas...)
- **No se pueden mezclar** +2 con +4

**Desactivada** (Por defecto):
- Recibes las cartas inmediatamente y pierdes el turno

### Regla 3: Reto del +4

**Activada**:
- Cuando alguien te lanza un +4, puedes retarlo
- Si el lanzador **SÍ tenía** otra carta jugable: Reto exitoso
  - El lanzador recibe 4 cartas de penalización
  - Tú no recibes cartas y juegas normalmente
- Si el lanzador **NO tenía** otra opción: Reto fallido
  - Recibes 6 cartas (4 del +4 + 2 de penalización)
  
**Desactivada** (Por defecto):
- Recibes las 4 cartas sin poder retar

### Regla 4: Ganar con Carta Negra

**Activada** (Por defecto):
- Puedes ganar el juego con cualquier carta, incluyendo comodines

**Desactivada**:
- No puedes ganar con cartas negras (Comodín o +4)
- Si juegas tu última carta y es negra, debes robar 1 carta

---

## Mecánicas de Juego

### Durante Tu Turno

En cada turno verás:

```
----------------------------------------
Turno de: Ana
Carta en mesa: [ROJO 7]
Color actual juego: ROJO

Mano de Ana:
1: [AZUL 3]
2: [ROJO SALTA]
3: [VERDE 5]
4: [COMODIN]

Opciones: [Indice carta] para jugar, [0] para robar:
```

### Cómo Jugar

1. **Jugar una carta**: Ingresa el número de la carta (1, 2, 3, 4...)
   - La carta debe coincidir en **color** o **valor** con la carta en mesa
   - Los **comodines** siempre se pueden jugar

2. **Robar carta**: Ingresa `0`
   - Dependiendo de la configuración, robarás 1 o hasta poder jugar

### Validación de Jugadas

Las cartas válidas son aquellas que cumplen **al menos una** de estas condiciones:
- ✅ Mismo **color** que la carta en mesa
- ✅ Mismo **valor/número** que la carta en mesa
- ✅ Es un **comodín** (siempre válido)

Ejemplo:
```
Carta en mesa: [ROJO 7]
Color actual: ROJO

Cartas válidas:
- [ROJO 3]      → Mismo color
- [AZUL 7]      → Mismo valor
- [ROJO SALTA]  → Mismo color
- [COMODIN]     → Siempre válido
- [+4]          → Siempre válido

Cartas NO válidas:
- [AZUL 3]      → Diferente color y valor
- [VERDE SALTA] → Diferente color y valor
```

---

## Reglas Especiales

### Sistema de Grito de UNO

Cuando te queda **1 carta**, debes gritar UNO:

```
Tienes 1 carta! Escribe 'UNO' para gritar UNO (o presiona Enter para omitir):
```

**Si gritas UNO correctamente**:
- Escribes exactamente `UNO` (mayúsculas o `uno` minúsculas)
- Continúas jugando normalmente

**Si NO gritas UNO**:
- Cualquier jugador puede reportarte en su turno
- Si el reporte es exitoso: Recibes **2 cartas de penalización**
- Si el reporte es erróneo: El reportador recibe 2 cartas de penalización

### Ejemplo de Reporte

```
>>> Alguien quiere reportar que Ana no grito UNO? (s/n): s

REPORTE EXITOSO! Ana no grito UNO y debe robar 2 cartas.
Ana ahora tiene 3 cartas.
```

### Acumulación (Si está activada)

Cuando recibes un +2 o +4 y tienes la misma carta:

```
Carta en mesa: [TOMA_DOS]
ALERTA! Hay 2 cartas acumuladas!
Tienes una carta para acumular!

Mano de Carlos:
1: [AZUL 3]
2: [TOMA_DOS]
3: [VERDE 5]

Opciones: [Indice carta] para jugar, [0] para robar:
```

Si juegas tu +2:
```
Acumulacion! Ahora son 4 cartas acumuladas.
Siguiente turno: María debe acumular o recibir 4 cartas.
```

Si no tienes carta para acumular:
```
No tienes cartas para acumular. Debes recibir 4 cartas.
Carlos ha recibido 4 cartas y pierde su turno.
```

### Reto del +4 (Si está activado)

```
Carta en mesa: [+4]
Color elegido: AZUL

María, quieres retar el +4? (s/n): s

=== RETO DEL +4 ===
María ha retado a Pedro!
Verificando si Pedro podia haber jugado otra carta...

Juez/Admin: Tenia Pedro otra carta jugable? (s/n): n

RETO FALLIDO! Pedro NO tenia otra opcion.
María debe robar 6 cartas (4 del +4 + 2 de penalizacion).
=== FIN DEL RETO ===
```

---

## Cartas y Sus Efectos

### Cartas Numéricas (0-9)
**Colores**: Rojo, Azul, Verde, Amarillo  
**Cantidad por mazo**: 76 cartas
- 1 carta de 0 por color (4 total)
- 2 cartas de cada número 1-9 por color (72 total)

**Efecto**: Ninguno, solo coincidencia de color/número

---

### Cartas de Acción

#### SALTA
**Cantidad**: 2 por color (8 por mazo)  
**Efecto**: El siguiente jugador pierde su turno

```
Turno de Ana → Juega SALTA
Carlos pierde su turno
Turno de María
```

**Caso especial con 2 jugadores**: Funciona como Reversa (vuelve a jugar el mismo jugador)

---

#### REVERSA
**Cantidad**: 2 por color (8 por mazo)  
**Efecto**: Invierte el sentido de juego (horario ↔ antihorario)

```
Sentido original: Ana → Carlos → María → Pedro → Ana
Después de REVERSA: Ana → Pedro → María → Carlos → Ana
```

**Caso especial con 2 jugadores**: Funciona como Salta (vuelve a jugar)

---

#### TOMA DOS (+2)
**Cantidad**: 2 por color (8 por mazo)  
**Color**: Rojo, Azul, Verde, Amarillo  
**Efecto**: El siguiente jugador roba 2 cartas y pierde el turno

**Con acumulación activada**:
- Puede defenderse jugando otro +2
- La suma se acumula para el siguiente jugador

---

### Cartas Comodín (Negras)

#### COMODÍN (Cambio de Color)
**Cantidad**: 4 por mazo  
**Color**: Negro (se puede jugar siempre)

**Efecto**:
1. Cambias el color de juego a cualquiera de los 4 colores
2. El juego continúa con ese color

```
Elige color (0: Rojo, 1: Azul, 2: Verde, 3: Amarillo): 2
Color cambiado a: VERDE
```

---

#### COMODÍN +4
**Cantidad**: 4 por mazo  
**Color**: Negro (se puede jugar siempre)

**Efecto**:
1. Cambias el color de juego
2. El siguiente jugador roba 4 cartas y pierde el turno

**Restricción oficial** (opcional según configuración):
- Solo se puede jugar si NO tienes carta del color actual
- Por eso existe el "Reto del +4"

**Con reto activado**:
- El siguiente jugador puede retarte
- Si tenías otra opción, recibes penalización

---

## Condiciones de Victoria

### Cómo Ganar

Un jugador gana cuando:
1. Juega su **última carta** y se queda sin cartas (0 cartas en mano)
2. (Opcional) No viola la regla de "No ganar con carta negra"

```
[VERDE 7] → Última carta de Ana

Ana HA GANADO !!!
```

### Validación de Victoria

**Si "Ganar con carta negra" está DESACTIVADA**:
- Si tu última carta es un Comodín o +4, NO ganas
- Debes robar 1 carta y continuar jugando

**Si está ACTIVADA** (Por defecto):
- Puedes ganar con cualquier carta

---

## Consejos y Estrategias

### Para Principiantes

1. **Guarda los comodines**: Son tu salvavidas cuando no tienes cartas jugables
2. **Observa los colores**: Intenta jugar cartas de colores que notes que otros jugadores no tienen
3. **Grita UNO siempre**: No arriesgues la penalización de 2 cartas
4. **Cuenta las cartas especiales**: Si ya salieron 2 Salta rojas, no quedan más en el mazo

### Estrategias Avanzadas

#### Gestión de Comodines
- No desperdicies un +4 cuando tienes otras opciones (te pueden retar)
- Usa comodines simples para cambiar a un color que tengas en abundancia

#### Defensa con Acumulación
- Si tienes un +2, guárdalo para defenderte de otro +2
- No uses tu última carta de defensa a menos que sea necesario

#### Control del Ritmo
- Usa cartas SALTA y REVERSA estratégicamente para evitar que ciertos jugadores jueguen
- Con 2 jugadores, SALTA y REVERSA te dan turnos extra

#### Presión Psicológica
- Si alguien no gritó UNO, repórtalo inmediatamente
- Observa quién tiene pocas cartas y juega cartas que les dificulten ganar

#### Reto del +4
- Solo reta si sospechas fuertemente que tenían otra opción
- Recuerda qué colores ha jugado antes el lanzador
- Un reto fallido te cuesta 6 cartas (muy costoso)

---

## Solución de Problemas

### El juego no compila
```bash
# Verifica que tienes g++ instalado
g++ --version

# Intenta limpiar y recompilar
make clean
make
```

### Caracteres extraños en la terminal
- El juego evita usar tildes en los mensajes para compatibilidad
- Asegúrate de que tu terminal soporte UTF-8

### El mazo se agota
- El juego automáticamente rebaraja el descarte cuando el mazo está vacío
- Solo se mantiene la última carta jugada fuera del mazo

### Duda sobre una regla
- Revisa este manual en la sección correspondiente
- Las reglas configurables se muestran al inicio del juego

---

## Créditos

**Proyecto**: UNO Avanzado  
**Curso**: Estructuras de Datos y Algoritmos  
**Lenguaje**: C++11  
**Estructuras implementadas**: Pila, Lista Circular, Lista Doblemente Enlazada

---

## Apéndice: Resumen de Comandos

| Acción | Comando |
|--------|---------|
| Jugar carta | `1`, `2`, `3`... (número de la carta en tu mano) |
| Robar carta | `0` |
| Gritar UNO | Escribe `UNO` cuando tengas 1 carta |
| Reportar UNO | Responde `s` cuando se pregunte |
| Retar +4 | Responde `s` cuando se ofrezca |
| Elegir color de comodín | `0` (Rojo), `1` (Azul), `2` (Verde), `3` (Amarillo) |

---

**¡Buena suerte y que gane el mejor jugador!** 🎮🃏
