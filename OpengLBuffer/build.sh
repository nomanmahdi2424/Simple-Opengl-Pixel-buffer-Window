gcc -c main.c -lSDL2 -lX11 -lGL -lpng -ljpeg && gcc -c getImageRGBBuffer.c -lSDL2 -lX11 -lGL -lpng -ljpeg && gcc -o run *.o  -lSDL2 -lX11 -lGL -lpng -ljpeg && ./run
