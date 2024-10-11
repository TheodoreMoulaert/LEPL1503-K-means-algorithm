╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║                                     LEPL1503 Projet C - L'agorithme de Lloyd                                 ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

Auteurs
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
Ce projet a été développé par :
- Camille Lefevre
- Clémentine Moreau
- Théodore Moulaert
- Pauline Meerman
- Louan Buckinx
- Victor Defrenne

---

Description
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
L'objectif de ce projet est de résoudre le défi du regroupement en mettant en œuvre l'algorithme des k-means de Lloyd en langage C.

1. **Initialisation des clusters et des centroids** :
    - Les clusters sont initialisés avec des points extraits d'un fichier binaire. Chaque cluster est associé à un centroid de base.
    - Les centroides initiaux sont générés en utilisant une méthode de combinaison de points. Cette étape garantit une exploration exhaustive de l'espace des données dès le début de l'algorithme.
2. **Boucle itérative** :
    - **Attribution des points aux centroids les plus proches** :
        - Pour chaque point, sa distance par rapport à chaque centroid est calculée en utilisant une fonction de distance spécifiée (par exemple, distance de Manhattan ou distance euclidienne).
        - Le point est ensuite attribué au centroid le plus proche.
    - **Mise à jour des centroids** :
        - Une fois tous les points attribués aux centroids, ces derniers sont mis à jour.
        - La nouvelle position de chaque centroid est calculée en fonction des points qui lui sont attribués.
    - La boucle itérative continue jusqu'à ce que les centroides convergent, c'est-à-dire qu'il n'y ait plus de changements significatifs dans leur position entre deux itérations successives.
4. **Écriture des résultats dans un fichier CSV** :
    - Une fois la convergence atteinte, les centroides finaux et les clusters correspondants sont écrits dans un fichier CSV.
    - Les résultats incluent les coordonnées des centroides finaux ainsi que les points appartenant à chaque cluster.
5. **Tests unitaires et analyse de la gestion de mémoire** :
    - Des tests unitaires sont réalisés pour chaque fonction de l'algorithme, ainsi que pour les différentes étapes de lecture et d'écriture de fichiers.
    - L'outil Valgrind est utilisé pour effectuer une analyse de la gestion de mémoire et détecter toute fuite de mémoire ou erreur potentielle.

---


Structure du code
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
#### *Dans dossier racine*
  * **main_avec_threads.c** : Fichier exécutant l'algorithme Kmeans monothreadé et multithreadé.
        * **parse_args** : fonction pour analyser les arguments de la ligne de commande
        * **usage** : fonction pour afficher l'usage du programme
        * **main** : fonction principale du programme 
  * **main.c** : Fichier exécutant l'algorithme Kmeans monothreadé.
        * **parse_args** : fonction pour analyser les arguments de la ligne de commande
        * **usage** : fonction pour afficher l'usage du programme
        * **main** : fonction principale du programme     

  * **Makefile**
    * **CC** : variable contenant le compilateur utilisé
    * **CFLAGS** : options de compilation
    * **LIBS** : bibliothèques nécessaires pour la compilation
    * **INCLUDE_HEADERS_DIRECTORY** : répertoire contenant les fichiers d'en-tête
    * Règles de compilation pour les fichiers objets :
      * **%.o** : règle générique pour créer des fichiers objets à partir des fichiers source C
    * Règles de compilation pour le programme principal :
      * **kmeans** : dépend des fichiers objets et compile le programme principal
    * Règles de compilation pour les tests :
      * **test_binary_file** : compilation du test pour la lecture de fichier binaire
      * **test_binary_file_beaucoup_de_points** : compilation du test avec beaucoup de points pour la lecture de fichier binaire
      * **test_distance** : compilation du test pour le calcul des distances
      * **test_distance_fichier** : compilation du test pour le calcul des distances avec fichier
      * **test_up_centroids** : compilation du test pour la mise à jour des centroïdes
      * **test_distortion** : compilation du test pour le calcul de la distorsion
      * **test_write_csv** : compilation du test monothreadé pour l'écriture des résultats dans un fichier csv
      * **test_write_thread** : compilation du test multi-threadé pour l'écriture des résultats dans un fichier csv
      * **test_assign_vector** : compilation du test pour l'attribution des vecteurs aux centroïdes
      * **test_k_means** : compilation du test pour l'algorithme de K-means
      * **test_comb** : compilation du test pour l'attribution des différentes combinaisons
    * Règles pour exécuter les tests :
      * **tests** : exécute tous les tests
      * **tests_memoire** : exécute tous les tests avec Valgrind
    * Règle pour nettoyer les fichiers générés :
      * **clean** : supprime les fichiers objets et exécutables



#### *Dans headers*
  * **cluster.h** : Définition de la structure `cluster_t` représentant un cluster et de la structure `result_t` pour le résultat des opérations sur les clusters.
  * **point.h** : Définition de la structure `point_t` représentant un point dans l'espace.
  * **kmeans_thread_args.h** : Définition de la structure `result_thread` rassemblant le résultats nécessaires pour l'écriture dans le fichier CSV lors que l'exécution avec threads 
                              et de la structure `k_means_thread_args_t` rassemblant les résultats nécessaires pour l'exécution de la fonction `kmeans_thread2`

  * **assign_vector_to_centroids.h** : Définit la fonction `assign_vectors_to_centroids`, qui assigne les vecteurs aux centroids.
  * **binary_file_reader.h** : Déclare les fonctions pour lire les informations à partir d'un fichier binaire, telles que la dimension des points et les coordonnées des vecteurs.
  * **combination.h** : Définit les fonctions pour calculer le nombre de combinaisons et générer des combinaisons de vecteurs.
  * **distance.h** : Définit les fonctions pour calculer les distances entre les points.
  * **kmeans_thread.h** : Définit les fonction pour exécuter l'algorithme K-means multithreadé.
  * **k_means.h** : Définit la fonction `k_means` pour exécuter l'algorithme K-means monothreadé.
  * **update_centroids.h** : Définit la fonction `update_centroids`, qui calcule les nouveaux centroids pour chaque cluster.
  * **write_csv.h** : Définit les fonctions pour écrire les données des centroids, des clusters et de la distorsion dans un fichier CSV.
  * **write_thread.h** : Définit les fonctions pour écrire les données des centroids, des clusters et de la distorsion obtenus lors de l'exécution d'un thread dans un fichier CSV.

  * **portable_endian.h** : Inclus les macros pour les conversions d'endian portable, notamment pour les systèmes Apple.
  * **portable_semaphore.h** : Fournit des fonctions d'initialisation et de destruction de sémaphores portables pour les systèmes Apple et autres.



#### *Dans src*
  * **assign_vectors_to_centroides.c**
    * **assign_vectors_to_centroides** : 
            Assignation des vecteurs aux centroïdes les plus proches.
            Arguments :
                    * point_t *centroids => centroides auxquelles les vecteurs vont être assignés
                    * cluster_t **clusters => vecteurs assignés
                    * int32_t K => nombre de clusters utiliser
                    * squared_distance_func_t distance_func => fonction distance à utiliser 
            Retourne :
                    * Une structure result_t indiquant si les clusters ont été modifiés (changes = true) et contenant les nouveaux clusters (result_cluster)


  * **binary_file_reader.c**
    * **get_dimension_from_binary_file** : 
            Fonction pour extraire la dimension et le nombre de vecteurs à partir d'un fichier binaire.
            Arguments :
                    * FILE *file => fichier contenant les données à lire
                    * uint32_t* dim => pointeur vers lequel sera assigné la dimension des vecteurs du fichier
                    * uint64_t* nbr_vector => pointeur vers lequel sera assigné le nombre de vecteurs du fichier
            Retourne :
                    * Entier (uint32_t), 0 si erreur, 1 sinon
    * **point_input** : 
            Fonction pour lire les points à partir d'un fichier binaire.
            Arguments :
                    * FILE *file => fichier contenant les données à lire
                    * uint32_t* dim => pointeur vers la dimension des vecteurs du fichier
                    * uint64_t* nbr_vector => pointeur vers le nombre de vecteurs du fichier
            Retourne :
                    * Tableau de pointeurs vers les vecteurs lus, ou NULL en cas d'erreur (point_t **)
    * **free_vectors** : 
            Fonction pour libérer la mémoire allouée aux vecteurs.
            Arguments :
                    * point_t **vectors => Tableau de pointeurs vers les vecteurs
                    * uint64_t nbr_vectors => Nombre de vecteurs dans le tableau


  * **combinaison.c**
    * **combinaison** : 
            Calcule le nombre de combinaisons de p éléments pris k par k.
            Arguments :
                    * int32_t p
                    * int32_t k
            Retourne :
                    * Le nombre de p éléments pris k par k (uint64_t)
    * **next_comb** : 
            Génère la combinaison suivante de k éléments pris parmi n.
            Arguments :
                    * uint64_t comb[] => tableau d'entiers
                    * uint64_t n
                    * uint32_t k
            Retourne :
                    * L'ensemble des combinaisons de k éléments pris k par k (uint64_t *)
    * **generate_combinations** : 
            Génère toutes les combinaisons possibles de k éléments parmi un ensemble de n vecteurs.
            Arguments :
                    * point_t **vectors => Pointeurs vers les vecteurs d'entrée
                    * uint64_t n => Nombre total de vecteurs dans l'ensemble
                    * int32_t k => Taille de chaque combinaison à générer 
                    * int32_t p => Nombre total de vecteurs dans l'ensemble d'entrée
            Retourne :
                    * Tableau de pointeurs vers les combinaisons générées, ou NULL en cas d'erreur (point_t ***)


  * **distance.c**
    * **squared_manhattan_distance** : 
            Calcule la distance de Manhattan au carré entre deux points.
            Arguments : 
                    * const point_t *p1 => Pointeur vers le premier point
                    * const point_t *p2 => Pointeur vers le second point
            Retourne :
                    * La distance de Manhattan au carré entre les deux points (int64_t).
    * **squared_euclidean_distance** : 
            Calcule la distance euclidienne au carré entre deux points.
            Arguments  :
                    * const point_t *p1 => Pointeur vers le premier point
                    * const point_t *p2 => Pointeur vers le second point
            Retourne :
                    * La distance euclidienne au carré entre les deux points (int64_t).
    * **distortion** : 
            Calcule la distorsion d'un ensemble de clusters.
            Arguments :
                    * cluster_t const **clusters => Un tableau de pointeurs vers les clusters
                    * int32_t num_clusters (k) => nombre de clusters
                    * squared_distance_func_t distance_func => fonction distance à utiliser
            Retourne :
                    * La distorsion totale des clusters (uint64_t)


  * **kmeans_thread2.c**
    * **kmeans_thread2** : 
            Fonction principale qui implémente l'algorithme K-means multi-threadé.
            Arguments :
                    * cluster_t** clusters => clusters initial
                    * uint64_t num_points => nombre de points dans les vecteurs du clusters
                    * int32_t k => nombre de cluster à utiliser
                    * point_t *initial_centroids => centroides initiaux
                    * point_t *final_centroids => centroides finaux 
                    * squared_distance_func_t distance_func => fonction distance à utiliser
            Retourne :
                    *  Structure result_thread qui contient l'ensemble des éléments nécessaire à la fonction `write_thread`
    * **k_means_thread** :
            Fonction exécutée par les threads.
            Arguments :
                    * void *args => pointeur contenant les éléments nécessaires à la fonction `kmeans_thread2`


  * **kmeans.c**
    * **k_means** : 
            Fonction principale qui implémente l'algorithme K-means.
            Arguments :
                    * cluster_t** clusters => clusters initial
                    * uint64_t num_points => nombre de points dans les vecteurs du clusters
                    * int32_t k => nombre de cluster à utiliser
                    * point_t *initial_centroids => centroides initiaux
                    * point_t *final_centroids => centroides finaux 
                    * squared_distance_func_t distance_func => fonction distance à utiliser
            Retourne :
                    * Tableau de pointeurs vers les clusters finaux, ou NULL en cas d'erreur (cluster_t**).


  * **update_centroids.c**
    * **update_centroids** : 
            Met à jour les centroids des clusters.
            Arguments :
                    * cluster_t *clusters[] => Tableau de pointeurs vers les clusters
                    * int32_t K => nombre de clusters
            Retourne :
                    * Tableau de pointeurs vers les clusters mis à jour (cluster_t**)
  

  * **write_csv.c**
    * **write_centroid** : 
            Fonction pour écrire les coordonnées des centroids dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * point_t* centroid => Tableau contenant les centroïdes des clusters. 
                    * int64_t k => Nombre total de centroïdes à écrire
                    * uint32_t dimension => Dimension des points dans les centroïdes      
    * **write_cluster** : 
            Fonction pour écrire les points de chaque cluster dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * cluster_t **cluster => Tableau de pointeurs vers les clusters.
                    * int32_t k => Nombre total de clusters
                    * uint32_t dimension => Dimension des points dans les clusters
    * **write_csv** : 
            Fonction principale pour écrire les données initiales, de distortion, de centroids, et de clusters dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * uint64_t* distortion => Tableau des valeurs de distorsion
                    * point_t **centroid_init_Array => Tableau des centroids initiaux pour chaque combinaison
                    * point_t **centroid_final_Array => Tableau des centroids finaux pour chaque combinaison
                    * cluster_t ***clustersArray => Tableau de tableaux de pointeurs vers les clusters pour chaque combinaison
                    * int32_t k => Nombre de clusters
                    * uint32_t dimension => Nombre de dimensions des données
                    * int64_t nombre_comb => Nombre total de combinaisons 
                    * bool quiet_mode => Si false les clusters sont également écrits
    

  * **write_thread.c**
    * **write_centro_thread** : 
            Fonction pour écrire les coordonnées des centroids dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * point_t* centroid => Tableau contenant les centroïdes des clusters
                    * int32_t k => Nombre total de centroïdes à écrire
                    * uint32_t dimension => Dimension des points dans les centroïdes       
    * **write_clu_thread** : 
            Fonction pour écrire les points de chaque cluster dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * cluster_t **cluster => Tableau de pointeurs vers les clusters
                    * int32_t k => Nombre total de clusters
                    * uint32_t dimension => Dimension des points dans les clusters
    * **write_thread** : 
            Fonction principale pour écrire les données initiales, de distortion, de centroids, et de clusters obtenu lors de l'exécution d'un thread dans un fichier CSV.
            Arguments :
                    * FILE *file => Pointeur vers le fichier dans lequel écrire
                    * uint64_t distortion => Tableau des valeurs de distorsion
                    * point_t *centroid_init => Tableau des centroids initiaux pour chaque combinaison
                    * point_t *centroid_final => Tableau des centroids finaux pour chaque combinaison
                    * cluster_t **clusters => Tableau de tableaux de pointeurs vers les clusters pour chaque combinaison
                    * int32_t k => Nombre de clusters
                    * uint32_t_t dimension => Nombre de dimensions des données
                    * int64_t nombre_comb => Nombre total de combinaisons 
                    * bool quiet => Si false les clusters sont également écrits



#### *Dans tests_file*
  * **test_assign_vector_to_centro.c** : Test CUnit de la fonction `assign_vector_to_centroids`.
  * **test_binary_file_beaucoup_de_points.c** : Test CUnit avec beaucoup de points des fonctions du fichier `binary_file_reader`.
  * **test_binary_file.c** : Test CUnit des fonctions du fichier `binary_file_reader`.
  * **test_comb.c** : Test CUnit des fonctions du fichier `combinaison`.
  * **test_distance_fichier.c** : Test avec fichier des fonctions du fichier `distance`.
  * **test_distance.c** : Test CUnit des fonctions du fichier `distance`.
  * **test_distortion.c** : Test CUnit de la fonction `distortion`.
  * **test_kmeans2.c** : Test CUnit de la fonction `kmeans`.
  * **test_update_centroids.c** : Test CUnit de la fonction `update_centroids`.
  * **test_write_csv.c** : Test CUnit de la fonction `write_csv`.
  * **test_write_thread.c** : Test CUnit de la fonction `write_thread`.



---

Utilisation [Makefile]
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
### Lancement simple du programme
  1. Ouvrez un terminal.
  2. Exécutez la commande suivante pour compiler le programme :
    ```bash
    make
    ```
  Cette commande va compiler le programme principal kmeans


### Utilisation des règles de compilation et d'exécution des tests :
  - **Compilation du programme principal (kmeans)** :
    Pour compiler le programme principal, utilisez la commande suivante :
    ```bash
    make kmeans
    ./kmeans -q -k [] -p [] -n [] -d [] -f [] exemple.bin
    ```
    où : 
    - exemple.bin  = fichier d'entrée
    - q si précisé, le programme n’affiche pas le contenu des clusters dans la sortie
    - k = le nombre de cluster
    - p = on considère les n_combinations premiers points présent en entrée pour générer les centroïdes initiaux de l’algorithme de Lloyd
    - n = nombre de threads
    - d = le noms de la fonction distance à appliquer soit manhattan soit euclidean
    - f = fichier de sortie



  - **Compilation des tests unitaires individuels** :
    Chaque test unitaire peut être compilé individuellement. Par exemple, pour compiler le test de lecture de fichier binaire, utilisez la commande suivante :
    ```bash
    make test_binary_file
    ```

  - **Exécution des tests avec Valgrind** :
    Si vous souhaitez exécuter les tests avec Valgrind pour vérifier les fuites de mémoire, utilisez la commande suivante :
    ```bash
    make tests
    ```

  - **Exécution des tests de mémoire avec Valgrind** :
    Pour exécuter les tests de mémoire avec Valgrind, utilisez la commande suivante :
    ```bash
    make tests_memoire
    ```

### Fin d'utilisation
  - **Nettoyer les fichiers générés** :
  Pour supprimer les fichiers objets et exécutables générés, utilisez la commande :
  ```bash
  make clean
  ```
---

Comparaison [compare_solutions.py]
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
#### *Dans python 
- La fonction compare_solutions permet de comparer le fichier csv retourné par le code C à celui retourné par le code python.
- **Exécution du code compare_solutions** :
  python3 compare_solutions.py fichier_PY.csv fichier_C.csv

  En cas de succès, le code renvoit "Success !" 

- Pour générer un fichier csv à partir du code python voici la commande à utiliser : 
  python3 k-means.py fichier_binaire.bin -k 3 -p 3 -d distance -f output.csv

  où : 
  - fichier_binaire.bin  = fichier d'entrée
  - q si précisé, le programme n’affiche pas le contenu des clusters dans la sortie
  - k = le nombre de cluster
  - p = on considère les n_combinations premiers points présent en entrée pour générer les centroïdes initiaux de l’algorithme de Lloyd
  - n = nombre de threads
  - d = le noms de la fonction distance à appliquer soit manhattan soit euclidean
  - f = fichier de sortie
  


Exemple de commande d'exécution
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
#### Exemple de commande pour exécuter le programme directement dans le terminal

- Deux commandes doivent être écrites dans votre terminal afin de faire compilé le fichier main_avec_threads : 
  1: Commande faisant appel à gcc et aux fonctions utilisées par le fichier main_avec_threads
gcc -g -o exemple main_avec_threads.c src/distance.c src/binary_file_reader.c src/kmeans.c 
                    src/kmeans_thread2.c src/write_csv.c src/write_thread.c 
                    src/combinaison.c src/assign_vectors_to_centroides.c src/update_centroids.c -lm
  2: Commande pour générer un fichier csv
./exemple -k 4 -p 5 -n 5 -d manhattan -f d.csv exemple.bin
  où : 
  - exemple.bin  = fichier d'entrée
  - q si précisé, le programme n’affiche pas le contenu des clusters dans la sortie
  - k = le nombre de cluster
  - p = on considère les n_combinations premiers points présent en entrée pour générer les centroïdes initiaux de l’algorithme de Lloyd
  - n = nombre de threads
  - d = le noms de la fonction distance à appliquer soit manhattan soit euclidean
  - f = fichier de sortie
--- 

📌 Version
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
2.0
---
