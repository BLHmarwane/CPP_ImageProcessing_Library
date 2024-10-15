# Nom de l'exécutable
EXEC = Debug/image_processor

# Répertoires des fichiers source et des en-têtes
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
GEN_IMG_DIR = generated_images

# Options du compilateur
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INC_DIR)

# Liste des fichiers source (TER_lib.cpp pour tester Addition)
SRC_FILES = TER_lib_V1.2.cpp

# Correspondance des fichiers objets
OBJ_FILES = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

# Compilation de l'exécutable
$(EXEC): $(OBJ_FILES) | $(OBJ_DIR) $(GEN_IMG_DIR) Debug
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# dépendance frequency_filtering.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/frequency_filtering.h
# dépendance sobel_filter.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/sobel_filter.h
# dépendance thresholding.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/thresholding.h
# dépendance otsu_thresholding.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/otsu_thresholding.h
# dépendance kmeans.h ... 
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/kmeans.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/RGB.h
$(OBJ_DIR)/TER_lib_V1.2.o: TER_lib_V1.2.cpp include/synthetic_images.h



# Crée le répertoire obj si nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Crée le répertoire Debug si nécessaire
Debug:
	mkdir -p Debug

# Crée le répertoire de génération d'images
$(GEN_IMG_DIR):
	mkdir -p $(GEN_IMG_DIR)

# Commande pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

# Test du TER_lib_V1.2.cpp [ce fichier est toujours en mise à jour là où je test chaque traitement separement]
test: $(EXEC)
	./$(EXEC)
