__start__: obj libs interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp config/opis_dzialan.cmd

obj:
	mkdir obj

libs:
	mkdir libs

__plugin__:
	cd plugin; make


CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall

interp: obj/Set4LibInterfaces.o obj/LibInterface.o obj/main.o obj/xmlinterp.o obj/Testy.o obj/Scena.o obj/ProgramInterpreter.o obj/Send.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/Set4LibInterfaces.o obj/xmlinterp.o obj/Testy.o obj/Scena.o obj/ProgramInterpreter.o obj/Send.o -ldl -lxerces-c

obj/LibInterface.o: inc/LibInterface.hh inc/Interp4Command.hh src/LibInterface.cpp
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Scena.o: inc/Scena.hh inc/MobileObj.hh src/Scena.cpp inc/Scena.hh
	g++ -c ${CPPFLAGS} -o obj/Scena.o src/Scena.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/Testy.o: inc/Testy.hh src/Testy.cpp
	g++ -c ${CPPFLAGS} -o obj/Testy.o src/Testy.cpp

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/LibInterface.hh inc/Set4LibInterfaces.hh inc/xmlinterp.hh inc/Testy.hh inc/Scena.hh inc/ProgramInterpreter.hh inc/Scena.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Set4LibInterfaces.o: inc/LibInterface.hh inc/Set4LibInterfaces.hh src/Set4LibInterfaces.cpp
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/ProgramInterpreter.o: src/ProgramInterpreter.cpp inc/Set4LibInterfaces.hh inc/xmlinterp.hh inc/ProgramInterpreter.hh inc/Scena.hh
	g++ -c ${CPPFLAGS} -o obj/ProgramInterpreter.o src/ProgramInterpreter.cpp

obj/Send.o: inc/Send.hh src/Send.cpp
	g++ -c ${CPPFLAGS} -o obj/Send.o src/Send.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;
	rmdir obj
	rmdir libs

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
