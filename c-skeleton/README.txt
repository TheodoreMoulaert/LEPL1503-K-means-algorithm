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
#### *Dans c-skeleton*
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


#### *Dans c-skeleton/src*
  
  * **assign_vectors_to_centroides.c**
    * **assign_vectors_to_centroides** : 
            Assignation des vecteurs aux centroïdes les plus proches.
            Arguments :
                    * pointeur point_t
                    * double pointeur cluster_t
                    * nombre de clusters à calculer (k)
                    * fonction distance de type squared_distance_func_t
            Retourne :
                    * result_t 


  * **binary_file_reader.c**
    * **get_dimension_from_binary_file** : 
            Fonction pour extraire la dimension et le nombre de vecteurs à partir d'un fichier binaire.
            Arguments :
                    * pointeur FILE
                    * pointeur entier non-signé
                    * pointeur entier non-signé
            Retourne :
                    * entier non-signé
    * **point_input** : 
            Fonction pour lire les points à partir d'un fichier binaire.
            Arguments :
                    * double pointeurs point_t
                    * pointeur entier non-signé
                    * pointeur entier non-signé
            Retourne :
                    * double pointeur point_t
    * **free_vectors** : 
            Fonction pour libérer la mémoire allouée aux vecteurs.
            Arguments :
                    * double pointeur point_t
                    * entier non-signé


  * **combinaison.c**
    * **factorial** : 
            Calcule la factorielle d'un entier.
            Arguments :
                    * entier non-signé
            Retourne :
                    * entier non-signé
    * **combinaison** : 
            Calcule le nombre de combinaisons de p éléments pris k par k.
            Arguments :
                    * entier non-signé
                    * entier non-signé
            Retourne :
                    * entier non-signé
    * **next_comb** : 
            Génère la combinaison suivante de k éléments pris parmi n.
            Arguments :
                    * tableau d'entiers non-signés
                    * entier non-signé
                    * entier non-signé
            Retourne :
                    * pointeur entier non-signé
    * **generate_combinations** : 
            Génère toutes les combinaisons possibles de k éléments parmi un ensemble de n vecteurs.
            Arguments :
                    * double pointeurs point_t
                    * entier non-signé
                    * entier non-signé
                    * entier non-signé
            Retourne :
                    * triple pointeurs point_t


  * **distance.c**
    * **squared_manhattan_distance** : 
            Calcule la distance de Manhattan au carré entre deux points.
            Arguments : 
                    * pointeur point_t 
                    * pointeur point_t
            Retourne :
                    * entier signé
    * **squared_euclidean_distance** : 
            Calcule la distance euclidienne au carré entre deux points.
            Arguments  :
                    * pointeur point_t 
                    * pointeur point_t
            Retourne :
                    * entier signé
    * **distortion** : 
            Calcule la distorsion d'un ensemble de clusters.
            Arguments :
                    * double pointeur cluster_t
                    * nombre de clusters (uint32_t)
                    * fonction distance de type squared_distance_func_t
            Retourne :
                    * entier non-signé


  * **kmeans_thread2.c**
    * **kmeans_thread2** : 
            Fonction principale qui implémente l'algorithme K-means multi-threadé.
            Arguments :
                    * double pointeurs cluster_t
                    * entier non-signé
                    * entier non-signé
                    * pointeur point_t
                    * pointeur point_t
                    * fonction distance de type squared_distance_func_t
            Retourne :
                    * result_thread
    * **k_means_thread** :
            Fonction exécutée par les threads.
            Arguments :
                    * pointeur void


  * **kmeans.c**
    * **k_means** : 
            Fonction principale qui implémente l'algorithme K-means.
            Arguments :
                    * double pointeurs cluster_t
                    * entier non-signé
                    * entier non-signé
                    * pointeur point_t
                    * pointeur point_t
                    * fonction distance de type squared_distance_func_t
            Retourne :
                    * double pointeur cluster_t


  * **update_centroids.c**
    * **update_centroids** : 
            Met à jour les centroids des clusters.
            Arguments :
                    * pointeur vers un tableau cluster_t
                    * nombre de clusters à calculer (k)
            Retourne :
                    * double pointeurs cluster_t
  

  * **write_csv.c**
    * **write_centroid** : 
            Fonction pour écrire les coordonnées des centroids dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * pointeurs point_t 
                    * entier signé
                    * entier signé       
    * **write_cluster** : 
            Fonction pour écrire les points de chaque cluster dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * double pointeurs cluster_t
                    * entier signé
                    * entier signé
    * **write_csv** : 
            Fonction principale pour écrire les données initiales, de distortion, de centroids, et de clusters dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * pointeur entier non-signé
                    * double pointeurs point_t
                    * double pointeurs point_t
                    * tripe pointeurs cluster_t
                    * entier signé
                    * entier signé
                    * entier signé 
                    * booléens
    

  * **write_thread.c**
    * **write_centro_thread** : 
            Fonction pour écrire les coordonnées des centroids dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * pointeurs point_t 
                    * entier signé
                    * entier signé       
    * **write_clu_thread** : 
            Fonction pour écrire les points de chaque cluster dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * double pointeurs cluster_t
                    * entier signé
                    * entier signé
    * **write_thread** : 
            Fonction principale pour écrire les données initiales, de distortion, de centroids, et de clusters obtenu lors de l'exécution d'un thread dans un fichier CSV.
            Arguments :
                    * pointeur FILE
                    * entier non-signé
                    * pointeur point_t
                    * pointeur point_t
                    * double pointeurs cluster_t
                    * entier signé
                    * entier signé
                    * entier signé 
                    * booléens



#### *Dans c-skeleton/headers*
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

#### *Dans c-skeleton/tests_file*
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
  1. Assurez-vous que vous vous trouvez dans le répertoire racine du projet `c-skeleton`.
  2. Ouvrez un terminal.
  3. Exécutez la commande suivante pour compiler le programme :
    ```bash
    make
    ```
  Cette commande va compiler le programme principal kmeans


### Utilisation des règles de compilation et d'exécution des tests :
  - **Compilation du programme principal (kmeans)** :
    Pour compiler le programme principal, utilisez la commande suivante :
    ```bash
    make kmeans
    ```

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
  - k = le nombre de cluster
  - p = le nombre de combinaison
  - distance = le noms de la fonction distance à appliquer soit manhattan soit euclidean
  - f = fichier de sortie

Exemples
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════

--- 

📌 Version
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
2.0
---