# Nome do executável
TARGET = output/bin/rna_evolutiva

# Compilador
CXX = g++

# Diretórios
SRC_DIR = src
OBJ_DIR = output/obj
BIN_DIR = output/bin
OUTPUT_DIR = output

# Arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto (gerados a partir dos fontes)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Flags de compilação para Release
CXXFLAGS_RELEASE = -Wall -std=c++11 -O3 -march=native -flto -fomit-frame-pointer

# Flags de compilação para Debug
CXXFLAGS_DEBUG = -Wall -std=c++11 -O0 -g

# Selecionar o modo de compilação
# Para definir o modo, use "make MODE=debug" ou "make MODE=release"
MODE ?= release

ifeq ($(MODE),debug)
    CXXFLAGS = $(CXXFLAGS_DEBUG)
else
    CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

# Regras de construção
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação dos diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(OUTPUT_DIR)/*.txt

run:
	./output/bin/rna_evolutiva

debug:
	gdb ./output/bin/rna_evolutiva

.PHONY: all clean debug run
