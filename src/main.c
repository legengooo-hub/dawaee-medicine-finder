/*
 * main.c
 * Programme principal - Dawaee Medicine Finder
 * Application de gestion et recherche de médicaments en Mauritanie
 * 
 * Auteur: Projet Universitaire
 * Date: 2024
 * 
 * Concepts C utilisés:
 * - Chaînes de caractères
 * - Fonctions (prototypes, passage par valeur et adresse)
 * - Pointeurs
 * - Fichiers (séquentiels et texte)
 * - Tri des données
 * - Gestion mémoire
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pharmacy.h"
#include "medicine.h"
#include "constants.h"

/* Prototypes des fonctions de menu */
void displayMainMenu(void);
void displaySearchMenu(void);
void displayComparisonMenu(void);
void displayPharmacyMenu(void);
void handleSearchOption(Medicine *medicines, int medicineCount);
void handlePharmacyOption(Pharmacy *pharmacies, int pharmacyCount);
void handleComparisonOption(Medicine *medicines, int medicineCount);
void handleExpirationCheck(Medicine *medicines, int medicineCount);
void handleRatingOption(Pharmacy *pharmacies, int pharmacyCount);

/**
 * Fonction principale
 * Initialise le système et affiche le menu
 */
int main(void)
{
    /* Déclaration des tableaux de données */
    Medicine medicines[MAX_MEDICINES];
    Pharmacy pharmacies[MAX_PHARMACIES];
    
    /* Compteurs */
    int medicineCount = 0;
    int pharmacyCount = 0;
    
    /* Variable pour le menu */
    int choice = 0;
    
    /* Message de bienvenue */
    printf("\n");
    printf("========================================\n");
    printf("     BIENVENUE DANS DAWAEE | دوائي    \n");
    printf("  Find medicine. Fast. Near you.      \n");
    printf("========================================\n");
    printf("Application de Gestion des Médicaments\n");
    printf("========================================\n\n");
    
    /* Initialisation des données */
    printf("Initialisation des données...\n");
    initializeMedicines(medicines, &medicineCount);
    initializePharmacies(pharmacies, &pharmacyCount);
    printf("✓ %d médicaments chargés\n", medicineCount);
    printf("✓ %d pharmacies chargées\n\n", pharmacyCount);
    
    /* Boucle du menu principal */
    while (1) {
        displayMainMenu();
        
        printf("Entrez votre choix: ");
        scanf("%d", &choice);
        getchar(); /* Consomme le newline */
        
        printf("\n");
        
        switch (choice) {
            case 1:
                handleSearchOption(medicines, medicineCount);
                break;
            case 2:
                handlePharmacyOption(pharmacies, pharmacyCount);
                break;
            case 3:
                handleComparisonOption(medicines, medicineCount);
                break;
            case 4:
                handleExpirationCheck(medicines, medicineCount);
                break;
            case 5:
                handleRatingOption(pharmacies, pharmacyCount);
                break;
            case 6:
                printf("Affichage de tous les médicaments...\n");
                displayAllMedicines(medicines, medicineCount);
                break;
            case 7:
                printf("Affichage de toutes les pharmacies...\n");
                displayAllPharmacies(pharmacies, pharmacyCount);
                break;
            case 8:
                printf("\n========================================\n");
                printf("    Merci d'avoir utilisé Dawaee!    \n");
                printf("========================================\n\n");
                return 0;
            default:
                printf("❌ Choix invalide. Veuillez réessayer.\n");
                break;
        }
        
        printf("\n");
    }
    
    return 0;
}

/**
 * Affiche le menu principal
 */
void displayMainMenu(void)
{
    printf("========== MENU PRINCIPAL =========\n");
    printf("1. 🔍 Rechercher un médicament\n");
    printf("2. 🏥 Trouver les pharmacies proches\n");
    printf("3. 💰 Comparer les prix\n");
    printf("4. ⚠️  Vérifier les péremptions\n");
    printf("5. ⭐ Évaluer une pharmacie\n");
    printf("6. 📋 Afficher tous les médicaments\n");
    printf("7. 💼 Afficher toutes les pharmacies\n");
    printf("8. 🚪 Quitter\n");
    printf("===================================\n");
}

/**
 * Gère la recherche de médicaments
 */
void handleSearchOption(Medicine *medicines, int medicineCount)
{
    char searchTerm[MAX_STRING_LENGTH];
    Medicine results[MAX_RESULTS];
    int resultCount = 0;
    int i;
    
    printf("--- RECHERCHE DE MÉDICAMENT ---\n");
    printf("Entrez le nom du médicament: ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    
    /* Supprime le newline */
    size_t len = strlen(searchTerm);
    if (len > 0 && searchTerm[len - 1] == '\n') {
        searchTerm[len - 1] = '\0';
    }
    
    resultCount = searchMedicineByName(medicines, medicineCount, searchTerm, results);
    
    if (resultCount == 0) {
        printf("\n❌ Aucun médicament trouvé contenant '%s'\n", searchTerm);
        return;
    }
    
    printf("\n✓ %d résultat(s) trouvé(s):\n\n", resultCount);
    
    for (i = 0; i < resultCount; i++) {
        printf("[Résultat %d]\n", i + 1);
        displayMedicine(&results[i]);
        printf("\n");
    }
}

/**
 * Gère la recherche de pharmacies
 */
void handlePharmacyOption(Pharmacy *pharmacies, int pharmacyCount)
{
    char region[MAX_STRING_LENGTH];
    Pharmacy results[MAX_PHARMACIES];
    int resultCount = 0;
    int i;
    
    printf("--- RECHERCHE DE PHARMACIES ---\n");
    printf("Régions disponibles:\n");
    printf("  - Nouakchott, Atar, Chinguetti, Tidjikja\n");
    printf("  - Kaedi, Aioun, Nema, Rosso, Boutilimit\n");
    printf("\nEntrez le nom de la région (wilaya): ");
    fgets(region, sizeof(region), stdin);
    
    /* Supprime le newline */
    size_t len = strlen(region);
    if (len > 0 && region[len - 1] == '\n') {
        region[len - 1] = '\0';
    }
    
    resultCount = filterPharmaciesByRegion(pharmacies, pharmacyCount, region, results);
    
    if (resultCount == 0) {
        printf("\n❌ Aucune pharmacie trouvée dans '%s'\n", region);
        return;
    }
    
    printf("\n✓ %d pharmacie(s) trouvée(s) dans %s:\n\n", resultCount, region);
    
    for (i = 0; i < resultCount; i++) {
        printf("[%d] %s - Note: %.1f/5 - %s\n", 
               i + 1, results[i].name, results[i].rating,
               results[i].isOpen ? "🟢 Ouvert" : "🔴 Fermé");
    }
}

/**
 * Gère la comparaison des prix
 */
void handleComparisonOption(Medicine *medicines, int medicineCount)
{
    char medicineName[MAX_STRING_LENGTH];
    Medicine results[MAX_RESULTS];
    int resultCount = 0;
    int i;
    float minPrice, maxPrice;
    
    printf("--- COMPARAISON DES PRIX ---\n");
    printf("Entrez le nom du médicament à comparer: ");
    fgets(medicineName, sizeof(medicineName), stdin);
    
    /* Supprime le newline */
    size_t len = strlen(medicineName);
    if (len > 0 && medicineName[len - 1] == '\n') {
        medicineName[len - 1] = '\0';
    }
    
    resultCount = compareMedicinePrices(medicines, medicineCount, medicineName, results);
    
    if (resultCount == 0) {
        printf("\n❌ Aucun résultat pour la comparaison\n");
        return;
    }
    
    /* Trouve le prix min et max */
    minPrice = results[0].price;
    maxPrice = results[0].price;
    
    for (i = 1; i < resultCount; i++) {
        if (results[i].price < minPrice) minPrice = results[i].price;
        if (results[i].price > maxPrice) maxPrice = results[i].price;
    }
    
    printf("\n✓ Comparaison des prix pour '%s':\n", medicineName);
    printf("Prix min: %.0f UM | Prix max: %.0f UM | Différence: %.0f UM\n\n", 
           minPrice, maxPrice, maxPrice - minPrice);
    
    printf("%-20s %-15s %-20s %-10s\n", "Médicament", "Dosage", "Pharmacie", "Prix");
    printf("------------------------------------------------------\n");
    
    for (i = 0; i < resultCount; i++) {
        printf("%-20s %-15s %-20s %.0f UM\n", 
               results[i].name, results[i].dosage, 
               results[i].pharmacy, results[i].price);
    }
}

/**
 * Gère la vérification des péremptions
 */
void handleExpirationCheck(Medicine *medicines, int medicineCount)
{
    Medicine expiringMedicines[MAX_MEDICINES];
    int expiringCount = 0;
    int i;
    
    printf("--- VÉRIFICATION DES PÉREMPTIONS ---\n");
    printf("Recherche des médicaments expirant dans 30 jours...\n\n");
    
    expiringCount = checkExpiringMedicines(medicines, medicineCount, expiringMedicines);
    
    if (expiringCount == 0) {
        printf("✓ Aucun médicament n'expire bientôt\n");
        return;
    }
    
    printf("⚠️  %d médicament(s) en alerte de péremption:\n\n", expiringCount);
    
    for (i = 0; i < expiringCount; i++) {
        printf("[%d] %s (%s) - Expire le: %s\n",
               i + 1, expiringMedicines[i].name, expiringMedicines[i].dosage,
               expiringMedicines[i].expirationDate);
        printf("    Pharmacie: %s | Prix: %.0f UM\n\n",
               expiringMedicines[i].pharmacy, expiringMedicines[i].price);
    }
}

/**
 * Gère les évaluations des pharmacies
 */
void handleRatingOption(Pharmacy *pharmacies, int pharmacyCount)
{
    char pharmacyName[MAX_STRING_LENGTH];
    float rating;
    int result;
    
    printf("--- ÉVALUATION D'UNE PHARMACIE ---\n");
    printf("Entrez le nom de la pharmacie: ");
    fgets(pharmacyName, sizeof(pharmacyName), stdin);
    
    /* Supprime le newline */
    size_t len = strlen(pharmacyName);
    if (len > 0 && pharmacyName[len - 1] == '\n') {
        pharmacyName[len - 1] = '\0';
    }
    
    printf("Entrez votre évaluation (1-5 étoiles): ");
    scanf("%f", &rating);
    getchar();
    
    if (rating < 1 || rating > 5) {
        printf("❌ Note invalide. Veuillez entrer une note entre 1 et 5\n");
        return;
    }
    
    result = ratePharmacy(pharmacies, pharmacyCount, pharmacyName, rating);
    
    if (result == SUCCESS) {
        printf("✓ Évaluation enregistrée avec succès!\n");
    } else {
        printf("❌ Pharmacie non trouvée\n");
    }
}
