# Zach Lieberman, zl5nrs, Makefile, 4/20/20

CXX=clang++
path=traveling.o middleearth.o
doxy=doxygen

lit: $(path)
	$(CXX) $(path)
	$(doxy)

traveling.o: traveling.cpp middleearth.h

middleearth.o: middleearth.cpp middleearth.h

.PHONY: clean
clean:
	-rm -f *.o *~ a.out
