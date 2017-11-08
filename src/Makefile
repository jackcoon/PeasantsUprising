all: Test.out cleanAll

Test.out: Test.o Piece.o Point.o
	g++ Test.o Piece.o Point.o -o Test.out

Test.o: Test.cpp
	g++ -c -Wall Test.cpp

Piece.o: Piece.cpp
	g++ -c -Wall Piece.cpp

Point.o: Point.cpp
	g++ -c -Wall Point.cpp

clean:
	rm -rf *o hello

cleanAll:
	rm -rf *o
