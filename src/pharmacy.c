/*
 * pharmacy.c
 * Implémentation des fonctions de gestion des pharmacies
 * Dawaee - Medicine Finder Application
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pharmacy.h"
#include "constants.h"

/* Fonction auxiliaire pour convertir en minuscules */
static void toLowerCase(char *str)
{
    if (str == NULL) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/**
 * Initialise les données des pharmacies
 */
void initializePharmacies(Pharmacy *pharmacies, int *count)
{
    if (pharmacies == NULL || count == NULL) {
        return;
    }
    
    /* Créé les pharmacies par défaut */
    
    /* Nouakchott */
    strcpy(pharmacies[0].name, "Mauripharma");
    strcpy(pharmacies[0].region, "Nouakchott");
    pharmacies[0].isOpen = 1;
    pharmacies[0].rating = 4.5;
    pharmacies[0].numberOfMedicines = 25;
    
    strcpy(pharmacies[1].name, "Central Pharmacy");
    strcpy(pharmacies[1].region, "Nouakchott");
    pharmacies[1].isOpen = 1;
    pharmacies[1].rating = 4.8;
    pharmacies[1].numberOfMedicines = 35;
    
    strcpy(pharmacies[2].name, "Pharma City");
    strcpy(pharmacies[2].region, "Nouakchott");
    pharmacies[2].isOpen = 1;
    pharmacies[2].rating = 4.6;
    pharmacies[2].numberOfMedicines = 28;
    
    /* Rosso */
    strcpy(pharmacies[3].name, "Pharmacie Al Amal");
    strcpy(pharmacies[3].region, "Rosso");
    pharmacies[3].isOpen = 0;
    pharmacies[3].rating = 4.2;
    pharmacies[3].numberOfMedicines = 15;
    
    /* Atar */
    strcpy(pharmacies[4].name, "Pharmacie Atar");
    strcpy(pharmacies[4].region, "Atar");
    pharmacies[4].isOpen = 1;
    pharmacies[4].rating = 4.1;
    pharmacies[4].numberOfMedicines = 12;
    
    /* Tidjikja */
    strcpy(pharmacies[5].name, "Pharmacie Tidjikja");
    strcpy(pharmacies[5].region, "Tidjikja");
    pharmacies[5].isOpen = 0;
    pharmacies[5].rating = 3.9;
    pharmacies[5].numberOfMedicines = 10;
    
    *count = 6;
}

/**
 * Affiche toutes les pharmacies
 */
void displayAllPharmacies(const Pharmacy *pharmacies, int count)
{
    int i;
    
    if (count == 0) {
        printf("Aucune pharmacie disponible\n");
        return;
    }
    
    printf("\n=========== TOUTES LES PHARMACIES ==========\n");
    printf("%-25s %-15s %-10s %-8s\n",
           "Nom", "Région", "Note", "État");
    printf("=============================================\n");
    
    for (i = 0; i < count; i++) {
        printf("%-25s %-15s %-10.1f %s\n",
               pharmacies[i].name,
               pharmacies[i].region,
               pharmacies[i].rating,
               pharmacies[i].isOpen ? "🟢 Ouvert" : "🔴 Fermé");
    }
    printf("\n");
}

/**
 * Filtre les pharmacies par région
 * Retourne le nombre de pharmacies trouvées
 */
int filterPharmaciesByRegion(const Pharmacy *pharmacies, int count,
                            const char *region, Pharmacy *results)
{
    int resultCount = 0;
    int i;
    char lowerRegion[MAX_STRING_LENGTH];
    char lowerPharmacyRegion[MAX_STRING_LENGTH];
    
    if (region == NULL || pharmacies == NULL || results == NULL) {
        return 0;
    }
    
    /* Convertit en minuscules pour comparaison insensible à la casse */
    strncpy(lowerRegion, region, MAX_STRING_LENGTH - 1);
    lowerRegion[MAX_STRING_LENGTH - 1] = '\0';
    toLowerCase(lowerRegion);
    
    for (i = 0; i < count && resultCount < MAX_PHARMACIES; i++) {
        strncpy(lowerPharmacyRegion, pharmacies[i].region, MAX_STRING_LENGTH - 1);
        lowerPharmacyRegion[MAX_STRING_LENGTH - 1] = '\0';
        toLowerCase(lowerPharmacyRegion);
        
        if (strcmp(lowerPharmacyRegion, lowerRegion) == 0) {
            results[resultCount] = pharmacies[i];
            resultCount++;
        }
    }
    
    return resultCount;
}

/**
 * Affiche les pharmacies ouvertes (de garde)
 * Retourne le nombre de pharmacies ouvertes
 */
int showOpenPharmacies(const Pharmacy *pharmacies, int count,
                      Pharmacy *openPharmacies)
{
    int openCount = 0;
    int i;
    
    if (pharmacies == NULL || openPharmacies == NULL) {
        return 0;
    }
    
    for (i = 0; i < count && openCount < MAX_PHARMACIES; i++) {
        if (pharmacies[i].isOpen) {
            openPharmacies[openCount] = pharmacies[i];
            openCount++;
        }
    }
    
    return openCount;
}

/**
 * Ajoute une évaluation à une pharmacie
 * Retourne SUCCESS ou FAILURE
 */
int ratePharmacy(Pharmacy *pharmacies, int count,
                const char *pharmacyName, float rating)
{
    int i;
    char lowerName[MAX_STRING_LENGTH];
    char lowerPharmacyName[MAX_STRING_LENGTH];
    
    if (pharmacies == NULL || pharmacyName == NULL) {
        return FAILURE;
    }
    
    if (rating < MIN_RATING || rating > MAX_RATING) {
        return FAILURE;
    }
    
    strncpy(lowerName, pharmacyName, MAX_STRING_LENGTH - 1);
    lowerName[MAX_STRING_LENGTH - 1] = '\0';
    toLowerCase(lowerName);
    
    for (i = 0; i < count; i++) {
        strncpy(lowerPharmacyName, pharmacies[i].name, MAX_STRING_LENGTH - 1);
        lowerPharmacyName[MAX_STRING_LENGTH - 1] = '\0';
        toLowerCase(lowerPharmacyName);
        
        if (strstr(lowerPharmacyName, lowerName) != NULL) {
            /* Calcule la nouvelle note moyenne */
            pharmacies[i].rating = (pharmacies[i].rating + rating) / 2.0;
            return SUCCESS;
        }
    }
    
    return FAILURE;
}

/**
 * Trouve la pharmacie avec la meilleure évaluation
 * Retourne un pointeur sur la pharmacie
 */
Pharmacy* findBestRatedPharmacy(const Pharmacy *pharmacies, int count)
{
    int i, maxIndex = 0;
    float maxRating = 0;
    
    if (pharmacies == NULL || count <= 0) {
        return NULL;
    }
    
    for (i = 0; i < count; i++) {
        if (pharmacies[i].rating > maxRating) {
            maxRating = pharmacies[i].rating;
            maxIndex = i;
        }
    }
    
    return (Pharmacy *)&pharmacies[maxIndex];
}
