# Makefile para UNO Avanzado
# Proyecto: Implementación de UNO en C++
# Curso: Estructuras de Datos y Algoritmos

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = 

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nombre del ejecutable
TARGET = $(BIN_DIR)/UNO_Avanzado

# Archivos fuente (buscar en src/)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

# Archivos objeto (convertir .cpp a .o en obj/)
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))

# Regla por defecto: compilar todo
all: directories $(TARGET)

# Crear directorios necesarios
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS)
	@echo "Enlazando ejecutable: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilacion exitosa! Ejecutable en: $(TARGET)"

# Regla para compilar archivos .cpp a .o
# Para archivos en src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Para main.cpp en el directorio raíz
$(OBJ_DIR)/main.o: main.cpp
	@echo "Compilando: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos compilados..."
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
	@echo "Limpieza completa!"

# Limpiar todo (incluye directorios)
distclean: clean
	@echo "Eliminando directorios de compilacion..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Limpieza profunda completa!"

# Ejecutar el programa
run: $(TARGET)
	@echo "Ejecutando UNO Avanzado..."
	@./$(TARGET)

# Recompilar todo desde cero
rebuild: clean all

# Mostrar información del proyecto
info:
	@echo "==============================================="
	@echo "        UNO AVANZADO - Informacion"
	@echo "==============================================="
	@echo "Compilador:    $(CXX)"
	@echo "Flags:         $(CXXFLAGS)"
	@echo "Fuentes:       $(SOURCES)"
	@echo "Objetos:       $(OBJECTS)"
	@echo "Ejecutable:    $(TARGET)"
	@echo "==============================================="

# Ayuda
help:
	@echo "==============================================="
	@echo "    UNO AVANZADO - Comandos del Makefile"
	@echo "==============================================="
	@echo "make           - Compilar el proyecto"
	@echo "make all       - Compilar el proyecto (igual que make)"
	@echo "make clean     - Eliminar archivos objeto y ejecutable"
	@echo "make distclean - Eliminar todo (incluye directorios)"
	@echo "make run       - Compilar y ejecutar el juego"
	@echo "make rebuild   - Limpiar y recompilar desde cero"
	@echo "make info      - Mostrar informacion del proyecto"
	@echo "make help      - Mostrar esta ayuda"
	@echo "==============================================="

# Indicar que estas reglas no son archivos
.PHONY: all clean distclean run rebuild info help directories
