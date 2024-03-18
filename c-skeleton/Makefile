CC=gcc
CFLAGS=-Wall -Werror -g
LIBS=-lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY= -Iheaders

#ordre du fichier python, à discuter
kmeans: main.c src/distance.o src/update_centroids.o src/assign_vector_to_centro.o src/k_means.o src/distortion.o src/binary_file_reader.o    # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)    #this will run the following command: gcc -Wall -Werror -g -o kmeans src/distance.o other_object_filespresent_above.o ... -lcunit -lpthread

%.o: %.c
	@echo Compilation du kmeans                  # if for example you want to compute example.c this will create an object file called example.o in the same directory as example.c. Don't forget to clean it in your "make clean"
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<
	@echo
	@echo Compilation des tests
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o tests tests.c src/*.o $(LIBS)

clean:
	rm -f src/*.o
	rm -f kmeans
	rm -f tests/*.o 
 #ATTENTION il faut créer un répertoire tests pour mettre les tests (le faire quand personnes d'autres travaille sur le projet )

tests: kmeans
	@echo Start tests:
	./tests 
# pas certaine de la derniere ligne 

tests_memoire: kmeans
	@echo Start tests with Valgrind:
	valgrind --leak-check=full ./tests 

# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests