
# Build options
CC = g++
CFLAGS = -std=c++11 -g
LDFLAGS =

# Phony targets
.PHONY: all clean FORCE

all:main
#	@echo "Build Success!"

Constant.o: Constant.cpp Constant.h Node.h Tensor.h Session.h
	$(CC) $< -c -o $@  $(CFLAGS)

DoubleOperator.o: DoubleOperator.cpp DoubleOperator.h Node.h Tensor.h \
 Session.h Variable.h Constant.h Meow.h SingleOperator.h Placeholder.h
	$(CC) $< -c -o $@  $(CFLAGS)

LSM.o: LSM.cpp LSM.h Meow.h Constant.h Node.h Tensor.h Session.h \
 DoubleOperator.h Variable.h SingleOperator.h Placeholder.h
	$(CC) $< -c -o $@  $(CFLAGS)

main.o: main.cpp Meow.h Constant.h Node.h Tensor.h Session.h \
 DoubleOperator.h Variable.h SingleOperator.h Placeholder.h Newton.h
	$(CC) $< -c -o $@  $(CFLAGS)

Node.o: Node.cpp Node.h Tensor.h Session.h Constant.h SingleOperator.h \
 DoubleOperator.h Variable.h
	$(CC) $< -c -o $@  $(CFLAGS)

Placeholder.o: Placeholder.cpp Placeholder.h Node.h Tensor.h Session.h
	$(CC) $< -c -o $@  $(CFLAGS)

Session.o: Session.cpp Session.h Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

SingleOperator.o: SingleOperator.cpp SingleOperator.h Node.h Tensor.h \
 Session.h Constant.h DoubleOperator.h Variable.h
	$(CC) $< -c -o $@  $(CFLAGS)

Tensor.o: Tensor.cpp Tensor.h
	$(CC) $< -c -o $@  $(CFLAGS)

Variable.o: Variable.cpp Variable.h Node.h Tensor.h Session.h
	$(CC) $< -c -o $@  $(CFLAGS)

main:Constant.o DoubleOperator.o LSM.o main.o Node.o Placeholder.o Session.o SingleOperator.o Tensor.o Variable.o 
	$(CC) $(CFLAGS)  $^ -o $@

FORCE:

clean:
	rm *.o main

main.zip: FORCE
	#make clean
	zip -r main.zip *.cpp *.h Readme.md *.docx Makefile 

