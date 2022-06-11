mainFile = main.cpp
libFile = lib.cpp

lib: $(libFile)
	g++ -c $(libFile)

main: $(mainFile)
	g++ -c $(mainFile)

build: main.o lib.o
	g++ lib.o main.o -lsfml-graphics -lsfml-window -lsfml-system -o app

clear:
	rm app main.o lib.o