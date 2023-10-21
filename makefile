# exe:bin/CSV_ctrl.exe

exe:CSV_ctrl.exe

# bin/CSV_ctrl.exe:obj/main.o obj/table.o obj/command.o obj/stdout_color.o bin log CSV_ctrl.exe
# 	gcc -Wall obj/main.o obj/table.o obj/command.o obj/stdout_color.o -o bin/CSV_ctrl.exe

CSV_ctrl.exe:obj/main.o obj/table.o obj/command.o obj/log.o obj/stdout_color.o log
	gcc -Wall obj/main.o obj/table.o obj/command.o obj/log.o obj/stdout_color.o -o CSV_ctrl.exe

obj/main.o:src/main.c obj
	gcc -Wall -c src/main.c -o obj/main.o

obj/table.o:src/table.c lib/table.h obj
	gcc -Wall -c src/table.c -o obj/table.o

obj/command.o:src/command.c lib/command.h obj
	gcc -Wall -c src/command.c -o obj/command.o

obj/log.o:src/log.c lib/log.h obj
	gcc -Wall -c src/log.c -o obj/log.o

obj/stdout_color.o:src/stdout_color.c lib/stdout_color.h obj
	gcc -Wall -c src/stdout_color.c -o obj/stdout_color.o

# bin:
# 	mkdir bin

obj:
	mkdir obj

log:
	mkdir log



debug:debug.exe

debug.exe:dobj/main.o dobj/table.o dobj/command.o dobj/log.o dobj/stdout_color.o log
	gcc -g -Wall dobj/main.o dobj/table.o dobj/command.o dobj/log.o dobj/stdout_color.o -o debug.exe

dobj/main.o:src/main.c dobj
	gcc -g -Wall -c src/main.c -o dobj/main.o

dobj/table.o:src/table.c lib/table.h dobj
	gcc -g -Wall -c src/table.c -o dobj/table.o

dobj/command.o:src/command.c lib/command.h dobj
	gcc -g -Wall -c src/command.c -o dobj/command.o

dobj/log.o:src/log.c lib/log.h dobj
	gcc -g -Wall -c src/log.c -o dobj/log.o

dobj/stdout_color.o:src/stdout_color.c lib/stdout_color.h dobj
	gcc -g -Wall -c src/stdout_color.c -o dobj/stdout_color.o

dobj:
	mkdir dobj

log:
	mkdir log



clean:
	rm obj/*.o
	rmdir obj
	rm dobj/*.o
	rmdir dobj
#	rm bin/*.exe
	rm *.exe
#	rmdir bin
#	rm log/*.log
#	rmdir log

zip:
	zip "CSV_ctrl.zip" src/*.c lib/*.h fics/*.txt README.md makefile