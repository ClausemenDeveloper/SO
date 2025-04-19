# Makefile para compilar o projeto de escalonamento de processos

# Compiler
CC = gcc  # Define o compilador a ser usado (gcc)

# Compiler flags
CFLAGS = -Wall -g  # Flags do compilador:
                   # -Wall: Mostra todos os avisos
                   # -g: Gera informações de depuração
LDFLAGS = -lm  # Adiciona a flag para a biblioteca matemática

# Target executable
TARGET = main  # Nome do executável final

# Object files
OBJS = main.o algoritmos.o utilidades.o  # Lista de arquivos objeto necessários para o executável

# Default target
all: $(TARGET)  # Alvo padrão que será executado ao rodar `make`

# Build target
# Regra para criar o executável a partir dos arquivos objeto
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)  # Inclui LDFLAGS para linkar a biblioteca matemática

# Build main.o
# Regra para compilar main.c em main.o
main.o: main.c algoritmos.h 
	$(CC) $(CFLAGS) -c main.c  # Compila o arquivo main.c em um arquivo objeto (main.o)

# Build algoritmos.o
# Regra para compilar algoritmos.c em algoritmos.o
algoritmos.o: algoritmos.c algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos.c  # Compila o arquivo algoritmos.c em um arquivo objeto (algoritmos.o)

# Build utilidades.o
# Regra para compilar utilidades.c em utilidades.o
utilidades.o: utilidades.c 
	$(CC) $(CFLAGS) -c utilidades.c  # Compila o arquivo utilidades.c em um arquivo objeto (utilidades.o)

# Clean up
# Regra para limpar os arquivos gerados (executável e objetos)
clean:
	rm -f $(TARGET) $(OBJS)  # Remove o executável e os arquivos objeto gerados

# Phony targets
# Declara os alvos que não correspondem a arquivos reais
.PHONY: all clean