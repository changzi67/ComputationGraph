
# Build options
CC = g++
CFLAGS = -std=c++11 -g
LDFLAGS =

# Phony targets
.PHONY: all clean

all:main

Constant.o: Constant.cpp Constant.h Node.h Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

DoubleOperator.o: DoubleOperator.cpp DoubleOperator.h Node.h Tensor.h \
 Constant.h Meow.h SingleOperator.h Variable.h Placeholder.h
	$(CC) $< -c -o $@  $(CFLAGS)

main.o: main.cpp Meow.h Constant.h Node.h Tensor.h DoubleOperator.h \
 SingleOperator.h Variable.h Placeholder.h Newton.h
	$(CC) $< -c -o $@  $(CFLAGS)

Node.o: Node.cpp Node.h Tensor.h Constant.h SingleOperator.h \
 DoubleOperator.h
	$(CC) $< -c -o $@  $(CFLAGS)

Placeholder.o: Placeholder.cpp Placeholder.h Node.h Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

SingleOperator.o: SingleOperator.cpp SingleOperator.h Node.h Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

Tensor.o: Tensor.cpp Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

Variable.o: Variable.cpp Variable.h Node.h Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

main:Constant.o DoubleOperator.o main.o Node.o Placeholder.o SingleOperator.o Tensor.o Variable.o 
	$(CC) $(CFLAGS)  $^ -o $@

clean:
	rm *.o main


main.zip:
	#make clean
	zip  *.cpp *.h Makefile -r main.zip

