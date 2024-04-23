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
L'objectif de ce projet est de résoudre le défi du regroupement en mettant en œuvre l'algorithme des k-means de Lloyd en langage C : 
1. **Initialisation des clusters et des centroids** : Démarre avec des clusters composés de points et des centroids de base déjà assignés à chaque cluster.

2. **Boucle itérative** :
    - **Attribution des points aux centroids les plus proches** : Pour chaque point, calcule sa distance par rapport à chaque centroid et l'assigne au centroid le plus proche.
    - **Mise à jour des centroids** : Recalcule la position de chaque centroid en fonction des points qui lui sont attribués.

3. **Critère d'arrêt** : La boucle itérative continue jusqu'à la convergence des centroides.

4. **Résultat final** : Une fois la boucle terminée, les centroides finaux et les clusters correspondants représentent les groupes de points trouvés par l'algorithme.

---


Structure du code
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
#### *Dans c-skeleton*
  * **main.c**
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
      * **test_distance** : compilation du test pour le calcul des distances
      * **test_distance_fichier** : compilation du test pour le calcul des distances avec fichier
      * **test_up_centroids** : compilation du test pour la mise à jour des centroïdes
      * **test_distortion** : compilation du test pour le calcul de la distorsion
      * **test_assign_vector** : compilation du test pour l'attribution des vecteurs aux centroïdes
      * **test_k_means** : compilation du test pour l'algorithme de K-means
    * Règles pour exécuter les tests :
      * **tests_fonctions** : exécute tous les tests de fonctions
      * **tests** : exécute tous les tests avec Valgrind
      * **tests_memoire** : exécute les tests de mémoire avec Valgrind
    * Règle pour nettoyer les fichiers générés :
      * **clean** : supprime les fichiers objets et exécutables


#### *Dans c-skeleton/src*
  * **distance.c**
    * **squared_manhattan_distance** : calcule la distance de Manhattan au carré entre deux points
    * **squared_euclidean_distance** : calcule la distance euclidienne au carré entre deux points
    * **distortion** : calcule la distorsion d'un ensemble de clusters

  * **assign_vectors_to_centroides.c**
    * **assign_vectors_to_centroides** : assignation des vecteurs aux centroïdes les plus proches

  * **update_centroids.c**
    * **update_centroids** : met à jour les centroids des clusters

  * **combinaison.c**
    * **factorial** : calcule la factorielle d'un entier
    * **combinaison** : calcule le nombre de combinaisons de p éléments pris k par k
    * **next_comb** : génère la combinaison suivante de k éléments pris parmi n
    * **generate_combinations** : génère toutes les combinaisons possibles de k éléments parmi un ensemble de n vecteurs

  * **kmeans.c**
    * **k_means** : fonction principale qui implémente l'algorithme K-means

  * **binary_file_reader.c**
    * **get_dimension_from_binary_file** : fonction pour extraire la dimension et le nombre de vecteurs à partir d'un fichier binaire
    * **point_input** : fonction pour lire les points à partir d'un fichier binaire
    * **free_vectors** : fonction pour libérer la mémoire allouée aux vecteurs

  * **write_csv.c**
    * **write_centroid** : fonction pour écrire les coordonnées des centroids dans un fichier CSV
    * **write_cluster** : fonction pour écrire les points de chaque cluster dans un fichier CSV
    * **write_csv** : fonction principale pour écrire les données initiales, de distortion, de centroids, et de clusters dans un fichier CSV


#### *Dans c-skeleton/headers*
  * **cluster.h** : Définition de la structure `cluster_t` représentant un cluster et de la structure `result_t` pour le résultat des opérations sur les clusters.
  * **point.h** : Définition de la structure `point_t` représentant un point dans l'espace.

  * **main.h** : Définit les structures et les fonctions utilisées dans le fichier principal du programme.
  * **distance.h** : Définit les fonctions pour calculer les distances entre les points.
  * **assign_vector_to_centroids.h** : Définit la fonction `assign_vectors_to_centroids`, qui assigne les vecteurs aux centroids.
  * **update_centroids.h** : Définit la fonction `update_centroids`, qui calcule les nouveaux centroids pour chaque cluster.
  * **combination.h** : Définit les fonctions pour calculer le nombre de combinaisons et générer des combinaisons de vecteurs.
  * **k_means.h** : Définit la fonction `k_means` pour exécuter l'algorithme K-means.
  * **binary_file_reader.h** : Déclare les fonctions pour lire les informations à partir d'un fichier binaire, telles que la dimension des points et les coordonnées des vecteurs.
  * **write_csv.h** : Définit les fonctions pour écrire les données des centroids, des clusters et de la distorsion dans un fichier CSV.

  * **portable_endian.h** : Inclus les macros pour les conversions d'endian portable, notamment pour les systèmes Apple.
  * **portable_semaphore.h** : Fournit des fonctions d'initialisation et de destruction de sémaphores portables pour les systèmes Apple et autres.

#### *Dans c-skeleton/test_file*
Des tests indépendants pour chaque fichier peuvent être trouvés dans le répertoire c-skeleton/test_file.



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

  - **Exécution des tests unitaires** :
    Pour exécuter tous les tests unitaires, utilisez la commande suivante :
    ```bash
    make tests_fonctions
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

Exemples
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════

---

📌 Version
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════
2.0
---