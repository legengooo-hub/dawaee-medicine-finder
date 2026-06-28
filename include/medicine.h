/*
 * medicine.h
 * Header file for medicine management functions
 * Dawaee - Medicine Finder Application
 * 
 * Concepts utilisés:
 * - Structures (struct)
 * - Pointeurs
 * - Chaînes de caractères
 */

#ifndef MEDICINE_H
#define MEDICINE_H

#define MAX_MEDICINES 500
#define MAX_STRING_LENGTH 100
#define EXPIRATION_WARNING_DAYS 30

/* Structure pour un médicament */
typedef struct {
    char name[MAX_STRING_LENGTH];
    char dosage[MAX_STRING_LENGTH];
    float price;
    char pharmacy[MAX_STRING_LENGTH];
    char expirationDate[11];                  /* Format: YYYY-MM-DD */
    char region[MAX_STRING_LENGTH];
    int isAvailable;
} Medicine;

/* Fonctions de gestion des médicaments */

/**
 * Initialise les médicaments à partir de la base de données
 * Param: tableau de médicaments et pointeur sur le nombre
 */
void initializeMedicines(Medicine *medicines, int *count);

/**
 * Recherche des médicaments par nom
 * Param: tableau de médicaments, nombre, nom recherché, tableau de résultats
 * Retour: nombre de résultats trouvés
 */
int searchMedicineByName(const Medicine *medicines, int count,
                        const char *name, Medicine *results);

/**
 * Affiche tous les médicaments
 * Param: tableau de médicaments et nombre de médicaments
 */
void displayAllMedicines(const Medicine *medicines, int count);

/**
 * Affiche un médicament
 * Param: pointeur sur un médicament
 */
void displayMedicine(const Medicine *medicine);

/**
 * Compare les prix d'un médicament dans différentes pharmacies
 * Param: tableau de médicaments, nombre, nom du médicament, résultats triés
 * Retour: nombre de résultats
 */
int compareMedicinePrices(const Medicine *medicines, int count,
                        const char *name, Medicine *results);

/**
 * Trie les médicaments par prix croissant
 * Param: tableau de médicaments et nombre de médicaments
 */
void sortMedicinesByPrice(Medicine *medicines, int count);

/**
 * Vérifie si un médicament expire bientôt
 * Param: pointeur sur un médicament
 * Retour: 1 si expire bientôt, 0 sinon
 */
int isExpirationSoon(const Medicine *medicine);

/**
 * Affiche tous les médicaments proches de l'expiration
 * Param: tableau de médicaments, nombre, tableau de résultats
 * Retour: nombre de médicaments proches de l'expiration
 */
int checkExpiringMedicines(const Medicine *medicines, int count,
                          Medicine *expiringMedicines);

/**
 * Trouve les alternatives d'un médicament
 * Param: tableau de médicaments, nombre, nom du médicament, résultats
 * Retour: nombre d'alternatives trouvées
 */
int findMedicineAlternatives(const Medicine *medicines, int count,
                            const char *name, Medicine *alternatives);

#endif /* MEDICINE_H */
