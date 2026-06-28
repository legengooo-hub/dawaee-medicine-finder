/*
 * medicine.c
 * Implémentation des fonctions de gestion des médicaments
 * Dawaee - Medicine Finder Application
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "medicine.h"
#include "constants.h"

/* Fonction auxiliaire pour convertir une chaîne en minuscules */
static void toLowerCase(char *str)
{
    if (str == NULL) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/* Fonction auxiliaire pour comparer les prix (utilisée par qsort) */
static int comparePrices(const void *a, const void *b)
{
    const Medicine *medA = (const Medicine *)a;
    const Medicine *medB = (const Medicine *)b;
    
    if (medA->price < medB->price) return -1;
    if (medA->price > medB->price) return 1;
    return 0;
}

/**
 * Initialise les médicaments à partir du fichier pharmacy.txt
 * Cette fonction lit la base de données et remplit le tableau
 */
void initializeMedicines(Medicine *medicines, int *count)
{
    FILE *file = NULL;
    char line[256];
    int i = 0;
    
    /* Ouverture du fichier de données */
    file = fopen(PHARMACY_DATA_FILE, "r");
    
    if (file == NULL) {
        printf("⚠️  Fichier pharmacy.txt non trouvé. Création automatique...\n");
        createDefaultDatabase();
        file = fopen(PHARMACY_DATA_FILE, "r");
    }
    
    if (file == NULL) {
        printf("❌ Erreur lors de l'ouverture du fichier\n");
        *count = 0;
        return;
    }
    
    /* Lecture du fichier ligne par ligne */
    while (fgets(line, sizeof(line), file) != NULL && i < MAX_MEDICINES) {
        /* Supprime le newline */
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) == 0) continue;
        
        /* Parse la ligne avec format: Name,Dosage,Price,Pharmacy,ExpirationDate,Region */
        if (sscanf(line, "%99[^,],%99[^,],%f,%99[^,],%10[^,],%99s",
                   medicines[i].name,
                   medicines[i].dosage,
                   &medicines[i].price,
                   medicines[i].pharmacy,
                   medicines[i].expirationDate,
                   medicines[i].region) == 6) {
            
            medicines[i].isAvailable = 1;
            i++;
        }
    }
    
    fclose(file);
    *count = i;
}

/**
 * Recherche des médicaments par nom
 * Retourne le nombre de résultats trouvés
 */
int searchMedicineByName(const Medicine *medicines, int count,
                        const char *name, Medicine *results)
{
    int resultCount = 0;
    int i;
    char lowerName[MAX_STRING_LENGTH];
    char lowerSearchTerm[MAX_STRING_LENGTH];
    
    if (name == NULL || medicines == NULL || results == NULL) {
        return 0;
    }
    
    /* Copie et convertit en minuscules pour une recherche insensible à la casse */
    strncpy(lowerSearchTerm, name, MAX_STRING_LENGTH - 1);
    lowerSearchTerm[MAX_STRING_LENGTH - 1] = '\0';
    toLowerCase(lowerSearchTerm);
    
    /* Recherche */
    for (i = 0; i < count && resultCount < MAX_RESULTS; i++) {
        strncpy(lowerName, medicines[i].name, MAX_STRING_LENGTH - 1);
        lowerName[MAX_STRING_LENGTH - 1] = '\0';
        toLowerCase(lowerName);
        
        if (strstr(lowerName, lowerSearchTerm) != NULL) {
            results[resultCount] = medicines[i];
            resultCount++;
        }
    }
    
    return resultCount;
}

/**
 * Affiche tous les médicaments
 */
void displayAllMedicines(const Medicine *medicines, int count)
{
    int i;
    
    if (count == 0) {
        printf("Aucun médicament disponible\n");
        return;
    }
    
    printf("\n=========== TOUS LES MÉDICAMENTS ==========\n");
    printf("%-20s %-15s %-10s %-20s %-12s\n", 
           "Médicament", "Dosage", "Prix", "Pharmacie", "Expiration");
    printf("===========================================\n");
    
    for (i = 0; i < count; i++) {
        printf("%-20s %-15s %-10.0f %-20s %-12s\n",
               medicines[i].name,
               medicines[i].dosage,
               medicines[i].price,
               medicines[i].pharmacy,
               medicines[i].expirationDate);
    }
    printf("\n");
}

/**
 * Affiche un médicament individual
 */
void displayMedicine(const Medicine *medicine)
{
    if (medicine == NULL) return;
    
    printf("   Médicament: %s\n", medicine->name);
    printf("   Dosage: %s\n", medicine->dosage);
    printf("   Prix: %.0f UM\n", medicine->price);
    printf("   Pharmacie: %s\n", medicine->pharmacy);
    printf("   Région: %s\n", medicine->region);
    printf("   Expiration: %s\n", medicine->expirationDate);
    
    if (isExpirationSoon(medicine)) {
        printf("   ⚠️  ALERTE: Date d'expiration proche!\n");
    } else {
        printf("   ✓ Délai d'expiration acceptable\n");
    }
}

/**
 * Compare les prix d'un médicament et retourne les résultats triés
 */
int compareMedicinePrices(const Medicine *medicines, int count,
                        const char *name, Medicine *results)
{
    Medicine tempResults[MAX_RESULTS];
    int resultCount = 0;
    
    /* Cherche tous les médicaments avec ce nom */
    resultCount = searchMedicineByName(medicines, count, name, tempResults);
    
    if (resultCount == 0) {
        return 0;
    }
    
    /* Copie les résultats */
    for (int i = 0; i < resultCount; i++) {
        results[i] = tempResults[i];
    }
    
    /* Trie par prix */
    qsort(results, resultCount, sizeof(Medicine), comparePrices);
    
    return resultCount;
}

/**
 * Trie les médicaments par prix croissant
 */
void sortMedicinesByPrice(Medicine *medicines, int count)
{
    if (medicines == NULL || count <= 0) return;
    qsort(medicines, count, sizeof(Medicine), comparePrices);
}

/**
 * Vérifie si un médicament expire bientôt
 */
int isExpirationSoon(const Medicine *medicine)
{
    time_t now;
    struct tm expDate = {0};
    struct tm currentDate = {0};
    time_t expTime;
    double secondsDifference;
    int daysDifference;
    
    if (medicine == NULL) return 0;
    
    /* Récupère la date actuelle */
    time(&now);
    currentDate = *localtime(&now);
    
    /* Parse la date d'expiration (YYYY-MM-DD) */
    sscanf(medicine->expirationDate, "%d-%d-%d",
           &expDate.tm_year, &expDate.tm_mon, &expDate.tm_mday);
    
    expDate.tm_year -= 1900;
    expDate.tm_mon -= 1;
    expDate.tm_hour = 23;
    expDate.tm_min = 59;
    expDate.tm_sec = 59;
    
    expTime = mktime(&expDate);
    
    secondsDifference = difftime(expTime, now);
    daysDifference = (int)(secondsDifference / (24 * 3600));
    
    return daysDifference <= EXPIRATION_WARNING_DAYS && daysDifference >= 0;
}

/**
 * Affiche tous les médicaments proches de l'expiration
 */
int checkExpiringMedicines(const Medicine *medicines, int count,
                          Medicine *expiringMedicines)
{
    int expiringCount = 0;
    int i;
    
    if (medicines == NULL || expiringMedicines == NULL) {
        return 0;
    }
    
    for (i = 0; i < count && expiringCount < MAX_RESULTS; i++) {
        if (isExpirationSoon(&medicines[i])) {
            expiringMedicines[expiringCount] = medicines[i];
            expiringCount++;
        }
    }
    
    return expiringCount;
}

/**
 * Trouve les alternatives d'un médicament
 * Retourne le nombre d'alternatives trouvées
 */
int findMedicineAlternatives(const Medicine *medicines, int count,
                            const char *name, Medicine *alternatives)
{
    int altCount = 0;
    int i;
    char lowerName[MAX_STRING_LENGTH];
    
    if (name == NULL || medicines == NULL || alternatives == NULL) {
        return 0;
    }
    
    strncpy(lowerName, name, MAX_STRING_LENGTH - 1);
    lowerName[MAX_STRING_LENGTH - 1] = '\0';
    toLowerCase(lowerName);
    
    /* Récupère le principe actif du médicament */
    char activeIngredient[MAX_STRING_LENGTH] = {0};
    if (strstr(lowerName, "doliprane") != NULL || 
        strstr(lowerName, "paracetamol") != NULL) {
        strcpy(activeIngredient, "paracetamol");
    } else if (strstr(lowerName, "ibuprofen") != NULL ||
               strstr(lowerName, "brufen") != NULL) {
        strcpy(activeIngredient, "ibuprofen");
    } else if (strstr(lowerName, "aspirin") != NULL) {
        strcpy(activeIngredient, "aspirin");
    }
    
    if (strlen(activeIngredient) == 0) {
        return 0;
    }
    
    /* Cherche les alternatives */
    for (i = 0; i < count && altCount < MAX_RESULTS; i++) {
        char medName[MAX_STRING_LENGTH];
        strncpy(medName, medicines[i].name, MAX_STRING_LENGTH - 1);
        medName[MAX_STRING_LENGTH - 1] = '\0';
        toLowerCase(medName);
        
        if (strstr(medName, activeIngredient) != NULL &&
            strcasecmp(medicines[i].name, name) != 0) {
            alternatives[altCount] = medicines[i];
            altCount++;
        }
    }
    
    return altCount;
}

/**
 * Crée une base de données par défaut
 */
void createDefaultDatabase(void)
{
    FILE *file = fopen(PHARMACY_DATA_FILE, "w");
    if (file == NULL) return;
    
    /* Écrit les données de test */
    fprintf(file, "Doliprane,500mg,120,Mauripharma,2026-12-01,Nouakchott\n");
    fprintf(file, "Doliprane,1000mg,200,Central Pharmacy,2025-10-10,Nouakchott\n");
    fprintf(file, "Paracetamol,500mg,100,Pharmacie Al Amal,2027-01-01,Rosso\n");
    fprintf(file, "Ibuprofen,200mg,150,Pharma City,2026-06-30,Nouakchott\n");
    fprintf(file, "Paracetamol,1000mg,180,Central Pharmacy,2026-08-15,Nouakchott\n");
    fprintf(file, "Aspirin,500mg,90,Mauripharma,2027-03-20,Nouakchott\n");
    
    fclose(file);
}
