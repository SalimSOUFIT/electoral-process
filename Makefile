#drapeaux du compilateur
#les options Wall et Wextra activent le plus de warnings possibles
#l'option pedantic provoque des warnings en cas de non respect du standard C 
CFLAGS = -Wall -Wextra -pedantic

#l'exécutable cible de construction
TARGET1 = mainNbPremTests
TARGET2 = mainDeclaSecuTests
TARGET3 = mainBaseCentraliseeTests
TARGET4 = mainMecanismeConsensusTests
TARGET5 = main

RM = rm -f 

#pour créer tous les exécutables en une fois
all : $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)



nbPremiers.o : nbPremiers.c
	gcc $(CFLAGS) -c nbPremiers.c

mainNbPremTests.o : mainNbPremTests.c
	gcc $(CFLAGS) -c mainNbPremTests.c

$(TARGET1) : mainNbPremTests.o nbPremiers.o
	gcc $(CFLAGS) -o mainNbPremTests mainNbPremTests.o nbPremiers.o



declarationsSecu.o : declarationsSecu.c
	gcc $(CFLAGS) -c declarationsSecu.c

mainDeclaSecuTests.o : mainDeclaSecuTests.c
	gcc $(CFLAGS) -c mainDeclaSecuTests.c

$(TARGET2) : declarationsSecu.o mainDeclaSecuTests.o nbPremiers.o
	gcc $(CFLAGS) -o $(TARGET2) declarationsSecu.o mainDeclaSecuTests.o nbPremiers.o



baseCentralisee.o : baseCentralisee.c
	gcc $(CFLAGS) -c baseCentralisee.c

mainBaseCentraliseeTests.o : mainBaseCentraliseeTests.c
	gcc $(CFLAGS) -c mainBaseCentraliseeTests.c

$(TARGET3) : baseCentralisee.o mainBaseCentraliseeTests.o declarationsSecu.o nbPremiers.o
	gcc $(CFLAGS) -o $(TARGET3) baseCentralisee.o mainBaseCentraliseeTests.o declarationsSecu.o nbPremiers.o



mecanismeConsensus.o : mecanismeConsensus.c
	gcc $(CFLAGS) -c mecanismeConsensus.c 

mainMecanismeConsensusTests.o : mainMecanismeConsensusTests.c 
	gcc $(CFLAGS) -c mainMecanismeConsensusTests.c 

$(TARGET4) : mecanismeConsensus.o mainMecanismeConsensusTests.o baseCentralisee.o declarationsSecu.o nbPremiers.o
	gcc $(CFLAGS) -o $(TARGET4)  mecanismeConsensus.o mainMecanismeConsensusTests.o baseCentralisee.o declarationsSecu.o nbPremiers.o -lssl -lcrypto 



main.o : main.c
	gcc $(CFLAGS) -c main.c

$(TARGET5) : mecanismeConsensus.o main.o baseCentralisee.o declarationsSecu.o nbPremiers.o
	gcc $(CFLAGS) -o $(TARGET5)  mecanismeConsensus.o main.o baseCentralisee.o declarationsSecu.o nbPremiers.o -lssl -lcrypto -lm




#pour recommencer à zéro, tapez 'make clean'
#supprime les fichiers exécutables, ainsi que les fichiers .o
clean :
	$(RM) *.o
	$(RM) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)