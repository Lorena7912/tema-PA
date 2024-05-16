build:
	gcc main.c ./src/functii_cerinte.c ./src/functii_liste.c ./src/altele.c -o lanParty
clean:
	rm -f lanParty
