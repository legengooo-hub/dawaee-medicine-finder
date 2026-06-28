/*
 * constants.h
 * Définitions des constantes et macros
 * Dawaee - Medicine Finder Application
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Limites et tailles */
#define MAX_PHARMACIES 100
#define MAX_MEDICINES 500
#define MAX_STRING_LENGTH 100
#define MAX_RESULTS 100

/* Fichiers */
#define PHARMACY_DATA_FILE "data/pharmacy.txt"
#define BACKUP_FILE "data/pharmacy_backup.txt"

/* Dates */
#define EXPIRATION_WARNING_DAYS 30
#define DATE_FORMAT "%Y-%m-%d"
#define DATE_LENGTH 11

/* Pharmacies Mauritaniennes - Wilayas */
#define WILAYAS_COUNT 13
#define WILAYAS { \
    "Nouakchott", \
    "Atar", \
    "Chinguetti", \
    "Tidjikja", \
    "Kaedi", \
    "Aioun", \
    "Nema", \
    "Rosso", \
    "Boutilimit", \
    "Aleg", \
    "Akjoujt", \
    "Mederdra", \
    "Guerguerat" \
}

/* Constantes d'équivalence de médicaments */
#define EQUIVALENT_PARACETAMOL "Doliprane"
#define EQUIVALENT_IBUPROFEN "Brufen"
#define EQUIVALENT_ASPIRIN "Cardio-Aspirin"

/* Codes de statut */
#define SUCCESS 1
#define FAILURE 0
#define NOT_FOUND -1

/* Notes des pharmacies */
#define MIN_RATING 1.0
#define MAX_RATING 5.0

#endif /* CONSTANTS_H */
