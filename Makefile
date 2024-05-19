build:
	gcc main.c ./src/functii_cerinte.c ./src/functii_liste.c ./src/altele.c ./src/functii_cozi.c ./src/functii_stive.c ./src/functii_BiT.c -o lanParty
clean:
	rm -f lanParty
