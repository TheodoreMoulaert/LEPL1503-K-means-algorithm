#ifndef WRITE_CSV.H
#define WRITE_CSV.H
#include <stdint.h>

#include "../headers/point.h"
#include "../headers/cluster.h"



/*
Fonction pour créer un fichier CSV contenant les résultats de l'algorithme K-means.

Arguments :
- inits : Un tableau de points représentant les centroïdes initiaux.
- clusters : Un tableau de clusters contenant les centroïdes finaux et les points associés à chaque cluster.
- distortion : La distortion résultante du calcul de l'algorithme K-means.
- clusterParPoint : Un tableau indiquant à quel cluster chaque point appartient.

Retour :
- Un entier indiquant si une erreur s'est produite lors de l'écriture du fichier CSV :
    - 0 : Aucune erreur rencontrée.
    - -1 : Une erreur s'est produite lors de l'ouverture du fichier ou de l'écriture des données.

La fonction crée un fichier CSV nommé "output.csv" et y écrit les informations suivantes :
- Les centroïdes initiaux.
- Les centroïdes finaux et les points associés à chaque cluster.
- La distortion résultante de l'algorithme K-means.
*/
int8_t create_CSV(point_t* inits, cluster_t *clusters, uint64_t distortion, uint32_t *clusterParPoint);

/*
Fonction pour imprimer les coordonnées d'un point dans un fichier CSV.

Arguments :
- fp : Le pointeur vers le fichier dans lequel imprimer les coordonnées.
- pt : Le point dont les coordonnées doivent être imprimées.

La fonction imprime les coordonnées du point pt dans le fichier CSV associé au pointeur fp.
*/
void fprintCoordPoint(FILE *fp, point_t pt);

/*
Fonction pour imprimer un tableau de points dans un fichier CSV.

Arguments :
- fp : Le pointeur vers le fichier dans lequel imprimer les points.
- arrayPts : Le tableau de points à imprimer.
- nb : Le nombre de points dans le tableau arrayPts.

La fonction imprime les coordonnées des points dans le tableau arrayPts dans le fichier CSV associé au pointeur fp.
*/
void fprintArrayPoints(FILE *fp, point_t* arrayPts, uint64_t nb);
#endif 
