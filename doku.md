# Aufgaben 2 - Zeigerarithmetik

## Aufgabe 1

## Aufgabe 2

### a)

Siehe `main.cpp` und `string.cpp`, sowie `string.hpp`.

### b)

Siehe `main.cpp` in der Funktion `b()`.

Ein Fehler tritt auf, nachdem der String `s` durch den Destruktor freigegeben wurde und der Zeiger auf 0x0 gesetzt wurde. Der Zeiger `data` auf den befreiten Speicher, der vorher von `s` belegt wurde, wird nie auf 0 gesetzt. Aus diesem Grund tritt, wenn der `data` Zeiger benutzt wird ein Use-After-Free Fehler auf, wenn auf den befreiten Speicher über den Zeiger `data` zugegriffen wird.

Ein anderer Fehler könnte auftreten, wenn der Speicherbereich von `s` durch `s.append()` reallokiert wird. Ist also nicht genügend kontinuierlicher Speicher für die Reallokation verfügbar, wird der vom Allokator ein Speicherbereich gewählt, welcher groß genug für den neuen String ist. Hierbei wird der Zeiger auf diesen Speicherbereich durch `realloc()` verschoben. Durch dieses Verschieben weiß zwar der String `s`, wo der neue Speicher liegt, allerdings ist in dem Zeiger `data` immer noch die alte Adresse gespeichert. Dadurch zeigt der Zeiger `data` auf einen nicht mehr zugewiesenen Speicherbereich, was undefiniertes Verhalten ist.

### c)

Hier entsteht ein Fehler, da der String `test` an die Funktion `print_string` übergeben wird. Bei der Betrachtung der Signatur fällt auf, dass der Parameter mit als Wert übergeben wird (Pass-By-Value). Also wird der String `test` in die Funktion kopiert. Der Aufruf von `.print()` funktioniert normal. Sobald die `print_string` Methode abgeschlossen ist, geht der String `s` out-of-scope und der Destruktor von `string` wird ausgelöst. Dieser gibt nun den Speicher an der Adresse des Strings frei. Da in der `main`-Funktion immer noch eine Kopie des Strings existiert, kann hier auch die `.print()` Methode ausgeführt werden. Hier tritt dann das Problem auf, da der Speicher auf den, der Zeiger in der `string`-Instanz zeigt schon durch die `print_string` Methode freigegeben wurde.
Somit wird auf freigegebenen Speicher zugegriffen, was undefiniertes Verhalten darstellt.
