# tema2PA
### README - Sistem de Gestionare a Turneelor

#### Prezentare Generală
Acest proiect este un Sistem de Gestionare a Turneelor scris în C. Gestionează echipe, simulează meciuri și generează rezultate pe baza unor date de intrare. Sistemul folosește cozi pentru a gestiona meciurile și alocă dinamic memorie pentru gestionarea echipelor și meciurilor.

#### Fișiere și Structură

- **main.c**: Conține funcția principală și coordonează fluxul general al programului.
- **cozi.c**: Conține funcții pentru gestionarea cozilor.
- **teams.c**: Conține funcții pentru gestionarea echipelor și jucătorilor.
- **definitii.h**: Fișier header cu declarații de funcții și definiții de structuri.

#### Compilare și Executare

1. **Compilarea Programului:**
   Utilizează `Makefile` furnizat pentru a compila programul. `Makefile` conține următoarele ținte:
   - `all`: Compilează programul.
   - `build`: Compilează programul.
   - `run`: Execută programul cu fișiere de intrare și ieșire predefinite.
   - `clean`: Curăță fișierele executabile generate.
   - `valgrind`: Rulează programul cu Valgrind pentru a verifica scurgerile de memorie.

   Comanda pentru compilare este:
   ```sh
   make
   ```
   care execută:
   ```sh
   gcc -g main.c cozi.c teams.c -o clasament -lm -Wall
   ```

2. **Rularea Programului:**
   Programul așteaptă trei argumente în linia de comandă:
   - Fișierul de intrare care conține informații despre echipe și jucători.
   - Fișierul de ieșire pentru matricea meciurilor.
   - Fișierul de ieșire pentru scorurile finale ale echipelor.

   Comandă exemplu pentru rulare, cu date din folderul Input:
   ```sh
   make run number=1
   ```
   Pentru rulare cu alte fișiere, folosiți comanda:
   ```sh
   ./clasament intrare.in outputGraf.out outputScor.out
   ```

3. **Curățarea Fișierelor:**
   Pentru a elimina fișierele executabile generate, folosește:
   ```sh
   make clean
   ```

#### Formatul Fișierelor de Intrare și Ieșire

**Fișier de Intrare (`Input/test1.in`):**
- Fișierul de intrare ar trebui să conțină detalii despre echipe, inclusiv punctajele și numele acestora. 
- Programul funcționează doar dacă fișierul de intrare conține 32 de echipe.
  
Format exemplu:
```
7.20 EchipaA
3.30 EchipaB
2.40 EchipaC
7.50 EchipaD
...
```

**Fișiere de Ieșire:**
- `testGraf.out`: Conține matricea de adiacență a grafului meciurilor.
- `testScor.out`: Conține scorurile finale ale echipelor cu prestigiul calculat.

#### Funcționalitate

1. **Funcția Principală (`main.c`):**
   - Citește echipele din fișierul de intrare.
   - Simulează meciurile.
   - Scrie matricea meciurilor în `testGraf.out`.
   - Scrie scorurile finale ale echipelor în `testScor.out`.

2. **Gestionarea Cozilor (`cozi.c`):**
   - `createQueue()`: Creează o coadă goală.
   - `enQueue()`: Adaugă o echipă în coadă.
   - `deQueue()`: Elimină o echipă din coadă.
   - `deleteQueue()`: Șterge întreaga coadă.
   - `isEmpty()`: Verifică dacă coada este goală.

3. **Gestionarea Echipei (`teams.c`):**
   - `readTeam()`: Citește o echipă din fișierul de intrare.
   - `copyTeam()`: Copiază informațiile echipei.
   - `freeTeam()`: Eliberează memoria alocată pentru o echipă.
   - `playMatch()`: Simulează un meci între două echipe.
   - `createMatrix()`: Creează o matrice pentru a înregistra rezultatele meciurilor.
   - `writeMatrix()`: Scrie matricea meciurilor în fișierul de ieșire.
   - `freeMatrix()`: Eliberează memoria alocată pentru matrice.
   - `computePrestige()`: Calculează prestigiul unei echipe.
   - `WritePrestiges()`: Scrie prestigiul tuturor echipelor în fișierul de ieșire.

4. **Funcții Utilitare (`definitii.h`):**
   - `allocWorked()`: Verifică dacă alocarea memoriei a avut succes.
   - `verifyFile()`: Verifică dacă un fișier a fost deschis cu succes.
   - `truncateWhiteSpace()`: Elimină spațiile și caracterele `\r` și `\n` de la sfârșitul unui șir de caractere.

#### Gestionarea Memoriei
Programul alocă dinamic memorie pentru echipe, jucători și structuri de date. Sunt furnizate funcții pentru eliberarea memoriei alocate pentru a evita scurgerile de memorie. Folosiți Valgrind pentru a verifica scurgerile de memorie în timpul dezvoltării.

#### Gestionarea Erorilor
Programul include gestionarea de bază a erorilor pentru operațiunile cu fișiere și alocarea memoriei. Verifică succesul alocării memoriei și operațiunilor cu fișiere, oferind mesaje de eroare adecvate.