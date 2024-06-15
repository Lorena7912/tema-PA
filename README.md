Regula de rulare este:
./lanParty c.in d.in r.out
iar pentru a executa toate testele, este necesară rularea în terminalul bash al comenzii:
./checker
din folder-ul proiectului.

Programul determină clasamentul, meciurile disputate si punctajele finale ale echipelor care participă într-un turneu.
---
Fișierele c.in conțin o linie cu 5 cifre de 0 sau 1, unde 0 înseamnă neefectuarea task-ului numerorat cu poziția cifrei respective, iar 1 efectuarea acesteia. Fișierele d.in conțin echipele la începutul turneului. Astfel, programul:
- citește echipele din fișierele d.in (Task1), elimină echipele cu cel mai mic punctaj din lista inițială (Task2)
-determină meciurile care au loc în fiecare rundă, actualizează punctajul echipelor,află clasamentul ultimelor 8 echipe și echipa câștigatoare (Task3)
-ordonează ultimele 8 echipele într-un  arbore BST și le afișează în ordine descrescătoare (Task4)
-realizează un arbore AVL cu ultimele 8 echipe și afișează nivelul 2 (Task5)

Funcția void elim_c(char *s) elimină începând de la sfârșitul numelui unei echipe caracterele nedorite (spațiu, '\r', '\n') care pot apărea în șirul de caractere ca urmare a citirii numelui echipei cu funcția fgets.
