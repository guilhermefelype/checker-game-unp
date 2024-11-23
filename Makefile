# Variáveis principais
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Arquivos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/checker_game

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Debug
debug: CXXFLAGS += -g
debug: clean all

# Executar
run: all
	./$(TARGET)
