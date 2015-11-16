all: testscene testimage

testscene: testscene.o scene.o png.o rgbapixel.o image.o
	clang++ -lpng png.o rgbapixel.o image.o scene.o testscene.o -o testscene

testimage: png.o rgbapixel.o image.o testimage.o
	clang++ -lpng png.o rgbapixel.o image.o testimage.o -o testimage

testimage.o: testimage.cpp
	clang++ -std=c++11 -c testimage.cpp

image.o: image.cpp image.h png.o
	clang++ -std=c++11 -c image.cpp

png.o: png.cpp png.h
	clang++ -std=c++11 -c png.cpp

rgbapixel.o: rgbapixel.cpp rgbapixel.h 
	clang++ -std=c++11 -c rgbapixel.cpp

scene.o: scene.cpp scene.h png.o image.o
	clang++ -std=c++11 -c scene.cpp

testscene.o: testscene.cpp png.h rgbapixel.h scene.h image.h 
	clang++ -std=c++11 -c testscene.cpp

clean:
	rm ./testimage ./testscene ./*.o

