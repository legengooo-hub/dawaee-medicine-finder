# Makefile pour Dawaee Medicine Finder
# Compilation du projet C

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g
INCLUDE = -I./include
LIBS = -lm

SOURCES = src/main.c src/medicine.c src/pharmacy.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dawaee

# Création des répertoires nécessaires
DATADIR = data

.PHONY: all clean run help setup

# Cible principale
all: setup $(TARGET)

# Création des répertoires
setup:
	@mkdir -p $(DATADIR)
	@echo "✓ Répertoires créés"

# Compilation du programme principal
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)
	@echo "✓ Compilation terminée: $(TARGET)"

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "  → Compilation de $<"

# Exécution du programme
run: $(TARGET)
	@echo "Lancement de Dawaee..."
	./$(TARGET)

# Nettoyage
clean:
	@rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Fichiers de compilation supprimés"

# Aide
help:
	@echo "Dawaee - Medicine Finder"
	@echo ""
	@echo "Commandes disponibles:"
	@echo "  make all      - Compile le projet"
	@echo "  make run      - Compile et exécute le programme"
	@echo "  make clean    - Supprime les fichiers compilés"
	@echo "  make setup    - Crée les répertoires nécessaires"
	@echo "  make help     - Affiche cette aide"

# Compilation et exécution directe
compile: all
	@echo "✓ Projet compilé avec succès"

realclean: clean
	@rm -rf $(DATADIR)/*.txt
	@echo "✓ Base de données supprimée"
