lexer.o: lexer.cpp error.cpp
	g++ -c $^

token.o: token.cpp lexer.cpp
	g++ -c $^

parser.o: parser.cpp token.cpp
	g++ -c $^

interpreter.o: interpreter.cpp parser.cpp token.cpp error.cpp
	g++ -c $^

error.o: error.cpp
	g++ -c $^

main.o: main.cpp parser.cpp token.cpp interpreter.cpp error.cpp
	g++ -c $^

main: main.o parser.o token.o interpreter.o error.o lexer.o
	g++ -o main $^

