lexer.o: lexer.cpp
	g++ -c $^

token.o: token.cpp lexer.cpp
	g++ -c $^

parser.o: parser.cpp token.cpp
	g++ -c $^

interpreter.o: interpreter.cpp parser.cpp token.cpp
	g++ -c $^

main.o: main.cpp parser.cpp token.cpp interpreter.cpp
	g++ -c $^

main: main.o parser.o token.o interpreter.o lexer.o
	g++ -o main $^

