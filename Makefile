main: main.cpp include/FunctionParser.h FunctionParser.o AddFunction.o BaseFunction.o ConstantFunction.o CosFunction.o DivideFunction.o IndependentVariable.o LnFunction.o MinusFunction.o MultiplyFunction.o PiecewiseFunction.o PowerFunction.o Segment.o SinFunction.o TanFunction.o
	g++ -o main -I ./include main.cpp FunctionParser.o AddFunction.o BaseFunction.o ConstantFunction.o CosFunction.o DivideFunction.o IndependentVariable.o LnFunction.o MinusFunction.o MultiplyFunction.o PiecewiseFunction.o PowerFunction.o Segment.o SinFunction.o TanFunction.o -std=c++11 -lm

AddFunction.o: src/AddFunction.cpp include/AddFunction.h
	g++ -I ./include src/AddFunction.cpp -c -std=c++11

BaseFunction.o: src/BaseFunction.cpp include/BaseFunction.h
	g++ -I ./include src/BaseFunction.cpp -c -std=c++11

ConstantFunction.o: src/ConstantFunction.cpp include/ConstantFunction.h
	g++ -I ./include src/ConstantFunction.cpp -c -std=c++11

CosFunction.o: src/CosFunction.cpp include/CosFunction.h MultiplyFunction.o ConstantFunction.o SinFunction.o
	g++ -I ./include src/CosFunction.cpp -c -std=c++11

DivideFunction.o: src/DivideFunction.cpp include/DivideFunction.h MinusFunction.o CosFunction.o SinFunction.o MultiplyFunction.o
	g++ -I ./include src/DivideFunction.cpp -c -std=c++11

FunctionParser.o: src/FunctionParser.cpp include/FunctionParser.h
	g++ -I ./include -c src/FunctionParser.cpp -std=c++11

IndependentVariable.o: src/IndependentVariable.cpp include/IndependentVariable.h ConstantFunction.o
	g++ -I ./include src/IndependentVariable.cpp -c -std=c++11

LnFunction.o: src/LnFunction.cpp include/LnFunction.h MultiplyFunction.o DivideFunction.o ConstantFunction.o
	g++ -I ./include src/LnFunction.cpp -c -std=c++11

MinusFunction.o: src/MinusFunction.cpp include/MinusFunction.h
	g++ -I ./include src/MinusFunction.cpp -c -std=c++11

MultiplyFunction.o: src/MultiplyFunction.cpp include/MultiplyFunction.h AddFunction.o
	g++ -I ./include src/MultiplyFunction.cpp -c -std=c++11

PiecewiseFunction.o: src/PiecewiseFunction.cpp include/PiecewiseFunction.h
	g++ -I ./include src/PiecewiseFunction.cpp -c -std=c++11

PowerFunction.o: src/PowerFunction.cpp include/PowerFunction.h AddFunction.o MultiplyFunction.o ConstantFunction.o LnFunction.o
	g++ -I ./include src/PowerFunction.cpp -c -std=c++11

Segment.o: src/Segment.cpp include/Segment.h
	g++ -I ./include src/Segment.cpp -c -std=c++11

SinFunction.o: src/SinFunction.cpp include/SinFunction.h
	g++ -I ./include src/SinFunction.cpp -c -std=c++11

TanFunction.o: src/TanFunction.cpp include/TanFunction.h MultiplyFunction.o ConstantFunction.o DivideFunction.o PowerFunction.o
	g++ -I ./include src/TanFunction.cpp -c -std=c++11

clean:
	rm AddFunction.o BaseFunction.o ConstantFunction.o CosFunction.o DivideFunction.o FunctionParser.o IndependentVariable.o LnFunction.o MinusFunction.o MultiplyFunction.o PiecewiseFunction.o PowerFunction.o Segment.o SinFunction.o TanFunction.o main
