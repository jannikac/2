# Aufgaben 2 - Zeigerarithmetik

## Aufgabe 1

### a)

Das Ergebnis der Addition auf einen Zeiger verschiebt den Zeiger um den Integer-Wert. Falls das Ziel des Zeigers ungültig ist, entsteht undefiniertes Verhalten.

### b)

`*(ptr +5)` und `ptr[5]` sind das Gleiche. Das heißt der Array Zugriff, ist eine Kurzform bzw. Syntax-Zucker für Zeigerarithmetik. Die Daten müssen kontinuierlich im Speicher hintereinanderliegen.

### c)

#### Beispiel A

`malloc()` gibt einen `void`-Zeiger zurück und kann deshalb nicht auf den Zeiger `data[]`, welcher auf einen Integer zeigt, zugewiesen werden. Außerdem fehlt in Zeile 3 ein Semikolon. Zudem gibt es ein Speicherleck, da in Zeile 2 Speicher zugewiesen wurde aber nicht freigegeben wird.

#### Beispiel B

Das Array, welches in Zeile 2 erstellt wird, wird nicht initialisiert. Somit wird in Zeile 5 auf nicht initialisierten Speicher zugegriffen → undefiniertes Verhalten.

#### Beispiel C

Das Array wird in Zeile 2 erstellt, jedoch nicht initialisiert. In Zeile 3 wird der Zugriff mit `sizeof(int)`, was 4 entspricht, multipliziert. In Zeile 4 wird auf einen nicht initialisierten Wert zugegriffen. Dann wird in Zeile 5 versucht auf den Index 40 zuzugreifen, obwohl das Array nur 20 Elemente groß ist.

#### Beispiel D

`Fehler: ` repräsentiert ein `char`-Array mit neun Elementen. In Zeile 3 wird durch das Addieren der Zahl 16, versucht auf das 16. Element im Array zuzugreifen, was nicht möglich ist.

#### Beispiel E

In Zeile 2 wird Speicher mit der Größe für 4 Integer zugewiesen und `iptr` ist ein Zeiger darauf. Die Schleife in Zeile 3 läuft immer 4 Mal durch, sodass der Speicher an `iptr` viermal freigegeben wird (double-free Fehler). Ein einziges `free` würde ausreichen.

#### Beispiel F

In Zeile 2 wird ein Integer Array mit der Größe 10 auf dem Stack erstellt. In Zeile 3 wird ein Zeiger `p` auf das Array erstellt. Das `free` in Zeile 4 ist nicht nötig, da das Array auf dem Stack liegt und der Speicher automatisch freigegeben wird.

## Aufgabe 2

### a)

Siehe `main.cpp` und `string.cpp`, sowie `string.hpp`.

### b)

Siehe `main.cpp` in der Funktion `b()`.

Ein Fehler tritt auf, nachdem der String `s` durch den Destruktor freigegeben wurde und der Zeiger auf 0x0 gesetzt wurde. Der Zeiger `data` auf den befreiten Speicher, der vorher von `s` belegt wurde, wird nie auf 0 gesetzt. Aus diesem Grund tritt, wenn der `data` Zeiger benutzt wird ein Use-After-Free Fehler auf, wenn auf den befreiten Speicher über den Zeiger `data` zugegriffen wird.

Ein anderer Fehler könnte auftreten, wenn der Speicherbereich von `s` durch `s.append()` reallokiert wird. Ist also nicht genügend kontinuierlicher Speicher für die Reallokation verfügbar, wird der vom Allokator ein Speicherbereich gewählt, welcher groß genug für den neuen String ist. Hierbei wird der Zeiger auf diesen Speicherbereich durch `realloc()` verschoben. Durch dieses Verschieben weiß zwar der String `s`, wo der neue Speicher liegt, allerdings ist in dem Zeiger `data` immer noch die alte Adresse gespeichert. Dadurch zeigt der Zeiger `data` auf einen nicht mehr zugewiesenen Speicherbereich, was undefiniertes Verhalten ist.

### c)

Hier entsteht ein Fehler, da der String `test` an die Funktion `print_string` übergeben wird. Bei der Betrachtung der Signatur fällt auf, dass der Parameter mit als Wert übergeben wird (Pass-By-Value). Also wird der String `test` in die Funktion kopiert. Der Aufruf von `.print()` funktioniert normal. Sobald die `print_string` Methode abgeschlossen ist, geht der String `s` out-of-scope und der Destruktor von `string` wird ausgelöst. Dieser gibt nun den Speicher an der Adresse des Strings frei. Da in der `main`-Funktion immer noch eine Kopie des Strings existiert, kann hier auch die `.print()` Methode ausgeführt werden. Hier tritt dann das Problem auf, da der Speicher auf den, der Zeiger in der `string`-Instanz zeigt schon durch die `print_string` Methode freigegeben wurde. Somit wird auf freigegebenen Speicher zugegriffen, was undefiniertes Verhalten darstellt.

### d)

`unsigned integral type`

Alias eines der grundlegenden Ganzzahltypen ohne Vorzeichen.

Es handelt sich um einen Typ, der die Größe eines beliebigen Objekts in Bytes darstellen kann: `size_t` ist der vom `sizeof`-Operator zurückgegebene Typ und wird in der Standardbibliothek häufig zur Darstellung von Größen und Zählungen verwendet.

In `<cstring>` wird er als Typ des Parameters `num` in den Funktionen `memchr`, `memcmp`, `memcpy`, `memmove`, `memset`, `strncat`, `strncmp`, `strncpy` und `strxfrm` verwendet, die in allen Fällen die maximale Anzahl von Bytes oder Zeichen angeben, die die Funktion beeinflussen soll.

Er wird auch als Rückgabetyp für `strcspn`, `strlen`, `strspn` und `strxfrm` verwendet, um Größen und Längen zurückzugeben.

## Aufgabe 3

### a)

| Mehrstufige Arrays                                                                      | Mehrdimensionale Arrays                      |
| --------------------------------------------------------------------------------------- | -------------------------------------------- |
| Bestehen aus Zeigern auf ein Zeigerarray                                                | Nur Heap Allokation möglich                  |
| Beliebige Dimensionen pro Zeiger möglich, d.h. Unterschiedliche Allokationslänge        | Alle haben gleiche Länge                     |
| Zusatzaufwand für individuelle Allokationen                                             | Abbildung auf eindimensionales Array möglich |
| Beispiel: <br />`Heap: int *ptr_array[3] = {0};` <br />`Stack: int **ptr = &ptr_array;` |                                              |
| Mehrstufige Arrays durch Zeiger auf Zeiger realisiert                                   |                                              |

#### Mehrstufige Arrays

- Beliebige Schachtelung möglich (Vorteil)
- Beliebige Dimensionen pro Zeiger möglich (Vorteil)
- Zusatzaufwand für individuelle Allokationen (Nachteil)

#### Mehrdimensionale Arrays

- Besitzen eine feste Größe (Vorteil)
- Spalten und Zeilen müssen immer die gleiche Größe haben (Nachteil)

### b)

#### Gleichung: Index zu Punkt

$$i = (x + y *size\_x + z* size\_x * size\_y); $$

#### Gleichung: Punkt zu Index

$$(x,y,z)=i\mod  size\_x, \frac{i}{size\_x}\mod size\_x, \frac{i}{size\_x*size\_y} $$
