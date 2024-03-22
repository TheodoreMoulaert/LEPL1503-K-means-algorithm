# Variables ( noms d'usage) exemple :  exécutable on les initialise parce qu'on les utilise beaucoup pour y faire référence on note $(CC) 
# pour que ce soit plus dynamique
#https://www.youtube.com/watch?v=-riHEHGP2DU&t=965s --> lien vidéo youtube pour comprendre

CC=gcc
CFLAGS=-Wall -Werror -g
LIBS=-lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY= -Iheaders

# varaible spéciales
#$@ : nom de la cible
#$< : nom de la première dépendance
# $^ : liste des dépendances
# $* : nom du fichier sans son extension



#Il faut ajouter commande pour écrire dans un fichier csv je pense

#ordre du fichier python, à discuter
#kmeans: main.c src/binary_file_reader.o src/distance.o src/update_centroids.o src/assign_vector_to_centro.o src/k_means.o src/distortion.o src/binary_file_reader.o    # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list ! $(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)  
#this will run the following command: gcc -Wall -Werror -g -o kmeans src/distance.o other_object_filespresent_above.o ... -lcunit -lpthread
#kmeans: main.c src/binary_file_reader.o src/distance.o src/update_centroids.o src/assign_vector_to_centro.o src/k_means.o src/distortion.o src/binary_file_reader.o    # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list ! $(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)  
#this will run the following command: gcc -Wall -Werror -g -o kmeans src/distance.o other_object_filespresent_above.o ... -lcunit -lpthread



%.o: %.c # toutes les cibles en dépendance c sont crées comme ceci
# if for example you want to compute example.c this will create an object file called example.o in the same directory as example.c. Don't forget to clean it in your "make clean"
	@echo Compilation de kmeans                  
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<
#@echo
#@echo Compilation des tests
#$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o tests_file tests_file.c src/*.o $(LIBS)

# Règle de compilation des tests
#tests_file: tests_file.c src/binary_file_reader.o src/distance.o src/update_centroids.o src/assign_vector_to_centro.o src/k_means.o src/distortion.o src/binary_file_reader.o$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_binary_file: tests_file/test_binary_file.c src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distance: tests_file/test_distance.c src/distance.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distance_fichier : tests_file/test_distance_fichier.c src/distance.o src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_binary_beaucoup_de_points : tests_file/test_binary_beaucoup_de_points.c src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_up_centroids: tests_file/test_update_centroids.c src/update_centroids.o 
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_up_centro_fichier : tests_file/test_up_centro_fichier.c src/update_centroids.o src/binary_file_reader.o #src/binary_file_reader.o src/binary_file_avec_cluster.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distortion : tests_file/test_distortion.c src/distance.o src/distortion.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_write_csv : tests_file/test_write_csv.c src/write_csv.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distortion_update : tests_file/test_distortion_update.c src/distortion.o src/update_centroids.o src/distance.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)





clean:
	rm -f src/*.o
	rm -f kmeans
	rm -f test_distance
	rm -f test_binary_file
	rm -f test_up_centroids
	rm -f test_distance_fichier
	rm -f test_binary_beaucoup_de_points
	rm -f test_up_centro_fichier
	rm -f test_distortion 
	rm -f test_write_csv 
	rm -f test_distortion_update

#tests: kmeans
	#@echo Excécution des tests
	#./kmeans
	#@echo Excécution des tests avec Valgrind
	#valgrind --leak-check=full ./kmeans

# Règle pour exécuter les tests
tests:  test_binary_file test_binary_beaucoup_de_points test_distance test_up_centroids test_distance_fichier test_up_centro_fichier test_distortion test_write_csv test_distortion_update 
	@echo "Exécution des tests"
	./test_binary_beaucoup_de_points
	./test_binary_file
	./test_distance
	./test_up_centroids
	./test_distance_fichier
	./test_up_centro_fichier
	./test_distortion 
	./test_write_csv
	./test_distortion_update 

#pas certaine de la dernière ligne
tests_memoire: test_distance_fichier test_binary_file  test_binary_beaucoup_de_points test_distance test_distance_fichier test_distortion test_up_centroids 
#@echo Tests:
#./tests_file
#@echo
	@echo Tests avec Valgrind:
	valgrind --leak-check=full ./test_distance_fichier
	valgrind --leak-check=full ./test_binary_file
	valgrind --leak-check=full ./test_binary_beaucoup_de_points
	valgrind --leak-check=full ./test_distance
	valgrind --leak-check=full ./test_distance_fichier
	valgrind --leak-check=full ./test_distortion
	valgrind --leak-check=full ./test_up_centroids
	#valgrind --leak-check=full ./test_distortion_update
	#make clean

	make clean 
#pas certaine que la commande soit  finie  --> si  ça me semble ok

# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests tests_memoire