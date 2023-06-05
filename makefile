exe:bin/progLinux.exe

bin/progLinux.exe:obj/main.o obj/fonctions.o obj/command.o obj/stdout_color.o bin projet_002.exe
	gcc -Wall obj/main.o obj/fonctions.o obj/command.o obj/stdout_color.o -o bin/progLinux.exe

projet_002.exe:obj/main.o obj/fonctions.o obj/command.o obj/stdout_color.o
	gcc -Wall obj/main.o obj/fonctions.o obj/command.o obj/stdout_color.o -o projet_002.exe

obj/main.o:src/main.c obj
	gcc -Wall -c src/main.c -o obj/main.o

obj/fonctions.o:src/fonctions.c lib/declarations.h obj
	gcc -Wall -c src/fonctions.c -o obj/fonctions.o

obj/command.o:src/command.c lib/command.h obj
	gcc -Wall -c src/command.c -o obj/command.o

obj/stdout_color.o:src/stdout_color.c lib/stdout_color.h obj
	gcc -Wall -c src/stdout_color.c -o obj/stdout_color.o

bin:
	mkdir bin

obj:
	mkdir obj



debug:debug.exe

debug.exe:dobj/main.o dobj/fonctions.o dobj/command.o dobj/stdout_color.o
	gcc -g -Wall dobj/main.o dobj/fonctions.o dobj/command.o dobj/stdout_color.o -o debug.exe

dobj/main.o:src/main.c dobj
	gcc -g -Wall -c src/main.c -o dobj/main.o

dobj/fonctions.o:src/fonctions.c lib/declarations.h dobj
	gcc -g -Wall -c src/fonctions.c -o dobj/fonctions.o

dobj/command.o:src/command.c lib/command.h dobj
	gcc -g -Wall -c src/command.c -o dobj/command.o

dobj/stdout_color.o:src/stdout_color.c lib/stdout_color.h dobj
	gcc -g -Wall -c src/stdout_color.c -o dobj/stdout_color.o

dobj:
	mkdir dobj



clean:
	rm obj/*.o
	rmdir obj
	rm dobj/*.o
	rmdir dobj
	rm bin/*.exe
	rm projet_002.exe
	rm debug.exe
	rmdir bin

zip:
	zip "Projet 002.zip" src/*.c lib/*.h makefile