/*
 * pharmacy.h
 * Header file for pharmacy management functions
 * Dawaee - Medicine Finder Application
 * 
 * Concepts utilisés:
 * - Structures (struct)
 * - Pointeurs
 * - Fichiers
 */

#ifndef PHARMACY_H
#define PHARMACY_H

#include <time.h>

/* Maximum de pharmacies et de chaînes */
#define MAX_PHARMACIES 100
#define MAX_STRING_LENGTH 100
#define MAX_MEDICINES 500

/* Structure pour une pharmacie */
typedef struct {
    char name[MAX_STRING_LENGTH];
    char region[MAX_STRING_LENGTH];          /* Wilaya/Région */
    int isOpen;                               /* 1 = ouvert, 0 = fermé */
    float rating;                             /* Note 1-5 */
    int numberOfMedicines;                    /* Nombre de médicaments */
} Pharmacy;

/* Structure pour un médicament */
typedef struct {
    char name[MAX_STRING_LENGTH];
    char dosage[MAX_STRING_LENGTH];
    float price;                              /* Prix en Ouguiya */
    char pharmacy[MAX_STRING_LENGTH];
    char expirationDate[11];                  /* Format: YYYY-MM-DD */
    char region[MAX_STRING_LENGTH];
    int isOpen;                               /* Statut de la pharmacie */
} Medicine;

/* Fonctions de gestion des pharmacies */

/**
 * Initialise les données des pharmacies
 * Param: tableau de pharmacies et nombre de pharmacies
 */
void initializePharmacies(Pharmacy *pharmacies, int *count);

/**
 * Affiche toutes les pharmacies
 * Param: tableau de pharmacies et nombre de pharmacies
 */
void displayAllPharmacies(const Pharmacy *pharmacies, int count);

/**
 * Filtre les pharmacies par région
 * Param: tableau de pharmacies, nombre, région, et tableau de résultats
 * Retour: nombre de pharmacies trouvées
 */
int filterPharmaciesByRegion(const Pharmacy *pharmacies, int count, 
                            const char *region, Pharmacy *results);

/**
 * Affiche les pharmacies ouvertes (de garde)
 * Param: tableau de pharmacies et nombre de pharmacies
 */
int showOpenPharmacies(const Pharmacy *pharmacies, int count, 
                      Pharmacy *openPharmacies);

/**
 * Ajoute une évaluation à une pharmacie
 * Param: tableau de pharmacies, nombre, nom de la pharmacie, note
 */
int ratePharmacy(Pharmacy *pharmacies, int count, 
                const char *pharmacyName, float rating);

/**
 * Trouve la pharmacie avec la meilleure évaluation
 * Param: tableau de pharmacies et nombre de pharmacies
 * Retour: pointeur sur la meilleure pharmacie
 */
Pharmacy* findBestRatedPharmacy(const Pharmacy *pharmacies, int count);

#endif /* PHARMACY_H */
