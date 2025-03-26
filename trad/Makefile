############
# Exemplo de makefile
# Prof. João Paulo A. Almeida
# Programação OO
# 
# A princípio, você não precisa alterar nada, mas aqui assume-se que o diretório atual
# é o diretório onde está o Makefile, e os códigos fonte estão em src/.
#

# nome do compilador
CPP = g++

# opções de compilação
CFLAGS = -Wall -g
CPPFLAGS = -std=c++17

# define lista de arquivos-fonte dentro de src/
FONTES = $(wildcard src/*.cpp)

# define lista dos arquivos-objeto usando nomes da lista de arquivos-fonte
OBJETOS = $(patsubst %.cpp,%.o,$(notdir $(FONTES)))
OBJETOS := $(addprefix src/,$(OBJETOS))

# nome do arquivo executável
EXECUTAVEL = vereadores

############ alvos
#
# use @ antes de todos os comandos, pois é necessário no script de teste
#

# alvo principal é o executável
all: $(EXECUTAVEL)

# para linkar o executável, precisamos dos arquivos-objeto
$(EXECUTAVEL): $(OBJETOS)
	@$(CPP) -o $@ $^

# alvo para cada arquivo-objeto depende do código fonte em src/
src/%.o: src/%.cpp
	@$(CPP) $(CPPFLAGS) -c $(CFLAGS) -o $@ $<

# comandos para execução
run: $(EXECUTAVEL)
	@./$(EXECUTAVEL) $(CDMUN) ./candidatos.csv ./votacao.csv 06/10/2024

# comando para limpeza
clean:
	@rm -f src/*.o $(EXECUTAVEL)
