prog: main.0 source.0
	gcc main.0 source.0 -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.0: main.c
	gcc -c main.c -o main.0 -g

source.0: source.c
	gcc -c source.c -o source.0 -g

clean:
	rm -f *.0 prog
