# Makefile for book recommendation engine 
# Group: icutmyhairbecauseyoudontcaremyheart

EXECUTABLES= main$(EXECEXT) 

all : $(EXECUTABLES)

chainedHashTable.o :	chainedHashTable.c abstractHashTable.h linkedListUtil.h structure.h
	gcc -c chainedHashTable.c

dataManagement.o :	dataManagement.c declareFunction.h abstractHashTable.h
	gcc -c dataManagement.c

linkedListUtil.o :	linkedListUtil.c linkedListUtil.h
	gcc -c linkedListUtil.c

login.o :	login.c declareFunction.h
	gcc -c login.c

register.o :	register.c declareFunction.h
	gcc -c register.c

search.o :	search.c abstractHashTable.h declareFunction.h
	gcc -c search.c

purchase.o :	purchase.c abstractHashTable.h declareFunction.h
	gcc -c purchase.c

validation.o : 	validation.c declareFunction.h
	gcc -c validation.c

recommendBook.o :  recommendBook.c declareFunction.h abstractHashTable.h
	gcc -c recommendBook.c

main.o :	main.c declareFunction.h abstractHashTable.h
	gcc -c main.c

main$(EXECEXT) : main.o chainedHashTable.o dataManagement.o linkedListUtil.o login.o register.o search.o validation.o recommendBook.o purchase.o
	gcc -o main$(EXECEXT) main.o chainedHashTable.o dataManagement.o linkedListUtil.o login.o register.o search.o validation.o recommendBook.o purchase.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 