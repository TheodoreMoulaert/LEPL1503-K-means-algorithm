#include <stdio.h>
#include <inttypes.h> // Ajout de l'en-tête inttypes.h
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"

int main() {
    // Création de quelques points fictifs
    point_t inits[] = {
        {.dim = 2, .coords = (int64_t[]){1, 2}},
        {.dim = 2, .coords = (int64_t[]){3, 4}},
        {.dim = 2, .coords = (int64_t[]){5, 6}}
    };

    // Création de quelques clusters fictifs
    cluster_t clusters[] = {
        {.center = {.dim = 2, .coords = (int64_t[]){2, 2}}, .data = inits, .size = 3},
        {.center = {.dim = 2, .coords = (int64_t[]){4, 4}}, .data = inits, .size = 3}
    };

    // Appel de la fonction create_CSV
    int8_t result = create_CSV(inits, clusters, 100, NULL); // La variable clusterParPoint est passée comme NULL car elle n'est pas utilisée dans la fonction create_CSV

    if (result == 0) {
        printf("Le fichier CSV a été créé avec succès.\n");
    } else {
        printf("Une erreur s'est produite lors de la création du fichier CSV.\n");
    }

    return 0;
}
