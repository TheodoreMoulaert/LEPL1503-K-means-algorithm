
CC=gcc
CFLAGS=-Wall -Werror -g
LIBS=-lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY= -Iheaders



kmeans: main_avec_threads.c src/binary_file_reader.o src/combinaison.o src/distance.o src/update_centroids.o src/assign_vectors_to_centroides.o src/kmeans.o src/write_csv.o  src/kmeans_thread2.o src/write_thread.o  # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)  

kmeans_mono: main.c src/binary_file_reader.o src/combinaison.o src/distance.o src/update_centroids.o src/assign_vectors_to_centroides.o src/kmeans.o src/write_csv.o    # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)  


%.o: %.c # toutes les cibles en dépendance c sont crées comme ceci
	@echo Compilation de kmeans                  
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<




test_binary_file: tests_file/test_binary_file.c src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_binary_file_beaucoup_de_points: tests_file/test_binary_beaucoup_de_points.c src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distance: tests_file/test_distance.c src/distance.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distance_fichier : tests_file/test_distance_fichier.c src/distance.o src/binary_file_reader.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_up_centroids: tests_file/test_update_centroids.c src/update_centroids.o 
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_distortion : tests_file/test_distortion.c src/distance.o 
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_write_csv : tests_file/test_write_csv.c src/write_csv.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_assign_vector : tests_file/test_assign_vector_to_centro.c src/assign_vectors_to_centroides.o  src/distance.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_kmeans : tests_file/test_kmeans2.c src/kmeans.o src/update_centroids.o src/distance.o src/assign_vectors_to_centroides.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

test_comb : tests_file/test_comb.c src/combinaison.o 
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)



# Règle pour exécuter les tests
tests:  test_binary_file  test_distance test_up_centroids test_distance_fichier  test_distortion test_assign_vector test_kmeans test_comb test_binary_file_beaucoup_de_points 
	@echo "Exécution des tests"
	./test_binary_file
	./test_distance
	./test_up_centroids
	./test_distance_fichier
	./test_distortion 
	./test_assign_vector
	./test_binary_file_beaucoup_de_points
	./test_kmeans
	./test_comb 
	make clean 


tests_memoire:  test_binary_file  test_distance test_up_centroids test_distance_fichier  test_distortion test_assign_vector test_kmeans test_comb test_binary_file_beaucoup_de_points 
#@echo
	@echo Tests avec Valgrind:
	valgrind --leak-check=full ./test_binary_file_beaucoup_de_points
	valgrind --leak-check=full ./test_binary_file
	valgrind --leak-check=full ./test_distance
	valgrind --leak-check=full ./test_up_centroids
	valgrind --leak-check=full ./test_distance_fichier
	valgrind --leak-check=full ./test_kmeans
	valgrind --leak-check=full ./test_assign_vector
	valgrind --leak-check=full ./test_distortion
	valgrind --leak-check=full ./test_comb
	
	make clean 


clean:
	rm -f src/*.o
	rm -f kmeans
	rm -f kmeans_mono
	rm -f test_distance
	rm -f test_binary_file
	rm -f test_up_centroids
	rm -f test_distance_fichier
	rm -f test_distortion 
	rm -f test_write_csv 
	rm -f test_assign_vector
	rm -f test_kmeans 
	rm -f test_comb
	rm -f main
	rm -f test_binary_file_beaucoup_de_points
	rm -f main_avec_threads



# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests tests_memoire