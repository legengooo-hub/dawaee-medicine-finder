# Dawaee | دوائي
## Find medicine. Fast. Near you.

### 📋 Description
Dawaee est une application universitaire complète de gestion et recherche de médicaments en Mauritanie. L'application combine une logique backend en C avec une interface utilisateur moderne en HTML/CSS.

### 🎯 Fonctionnalités

1. **Recherche de médicaments** - Recherche par nom et affichage des résultats
2. **Pharmacies les plus proches** - Localisation par région/wilaya en Mauritanie
3. **Comparaison des prix** - Tri des pharmacies du moins cher au plus cher
4. **Alerte de péremption** - Avertissements pour dates d'expiration proches
5. **Alternatives de médicaments** - Propositions d'équivalents disponibles
6. **Pharmacies de garde** - Affichage des pharmacies ouvertes actuellement
7. **Évaluation des pharmacies** - Système de notation (1-5 étoiles)

### 📁 Structure du Projet

```
dawaee-medicine-finder/
├── index.html              # Interface utilisateur principale
├── styles.css              # Styling modern et responsif
├── src/
│   ├── main.c              # Programme principal
│   ├── pharmacy.c          # Gestion des pharmacies
│   ├── medicine.c          # Gestion des médicaments
│   ├── search.c            # Fonction de recherche
│   └── file_handler.c      # Gestion des fichiers
├── include/
│   ├── pharmacy.h          # Header pour pharmacies
│   ├── medicine.h          # Header pour médicaments
│   └── constants.h         # Constantes et définitions
├── data/
│   └── pharmacy.txt        # Base de données des pharmacies
├── Makefile                # Compilation automatique
└── README.md               # Ce fichier
```

### 🛠️ Technologies Utilisées

- **C** : Logique backend, gestion mémoire, fichiers
- **HTML/CSS** : Interface utilisateur responsive
- **Fichiers textes** : Stockage des données (pharmacy.txt)

### 📚 Concepts C Utilisés

✅ Chaînes de caractères (déclaration, manipulation)
✅ Fonctions (prototype, passage par valeur et adresse)
✅ Pointeurs et gestion mémoire dynamique
✅ Fichiers séquentiels et texte
✅ Lecture/écriture de fichiers
✅ Tri des données (prix croissant)

### 🚀 Compilation et Exécution

```bash
# Compiler le projet
make

# Exécuter le programme
./dawaee

# Nettoyer les fichiers compilés
make clean
```

### 📊 Format de la Base de Données

Le fichier `pharmacy.txt` contient:
```
NomMédicament,Dosage,Prix,Pharmacie,DateExpiration,Ouvert,Note
Doliprane,500mg,120,Mauripharma,2026-12-01,1,4.5
Doliprane,1000mg,200,Central Pharmacy,2025-10-10,1,4.8
```

### 👨‍🎓 Projet Universitaire

Ce projet démontre l'application pratique de concepts fondamentaux en programmation C:
- Gestion efficace de la mémoire
- Manipulation de fichiers
- Structures de données
- Algorithmes de tri et recherche

### 📝 Licence

Projet universitaire - Libre d'utilisation à des fins éducatives.
