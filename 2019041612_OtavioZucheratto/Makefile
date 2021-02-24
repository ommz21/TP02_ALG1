# == VARIAVEIS ===
# ================
CC=g++ 
CFLAGS=-g -Wall -Wextra
EXEC=./tp02
MEM_LEAK=valgrind --leak-check=full --track-origins=yes --show-reachable=yes 

# === REGRAS =====
# ================
$(EXEC): main.cpp grafo.o
	$(CC) $(CFLAGS) main.cpp grafo.o -o $(EXEC)

grafo.o: headers/grafo.o
	$(CC) $(CFLAGS) -c headers/grafo.cpp -o grafo.o

all: $(EXEC)
	$(EXEC)

memcheck: $(EXEC) #Execucao usando valgrind para verificar se o codigo possui algum leak de memoria
	$(MEM_LEAK)$(EXEC)

clean: #remove todos os arquivos temporarios que forem gerados pela compilacao
	rm -rf tp02 grafo.o headers/grafo.o