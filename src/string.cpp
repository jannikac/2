#include "string.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>

// Erstellt eine `string`-Instanz mit der Zeichenfolge ""
string::string() {
  // Weist Heap-Speicher mit der Größe von einem char zu
  str = (char *)malloc(sizeof(char));
}

// Erstellt eine `string` Instanz aus einem Zeiger auf ein `char` Array.
string::string(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine Exception geworfen
  if (!inputString)
    throw std::invalid_argument("recieved nullptr");

  // größe für internen str festlegen
  str = (char *)malloc(sizeof(char) * strlen(inputString));

  // c-string von der Eingabe in den internen str kopieren
  strcpy(str, inputString);
}

// Fügt ein `char` Array an einen den internen `str` an.
void string::append(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine exception geworfen
  if (!inputString)
    throw std::invalid_argument("recieved nullptr");

  // Größe des internen str um Länge des inputStrings erweitern
  str =
      (char *)realloc(str, sizeof(char) * (strlen(inputString) + strlen(str)));
  // inputString an bestehenden str anhängen
  strcat(str, inputString);
}

// Gibt den internen `str` zurück.
// Kann keinen `nullptr` zurückgeben, da bei eingabe eines `nullptrs` eine
// Exception geworfen wird.
char *string::data() { return str; }

// Findet den ersten `char` im internen `str`, welcher mit `c` übereinstimmt und
// gibt den entsprechenden Index zurück. Wird char nicht gefunden, wird `-1`
// zurück gegeben.
int string::find(char c) {
  // Gibt Zeiger auf gefundenen char zurück und speichert ihn als res
  char *res = strchr(str, c);
  // Wenn res nullptr zurückgibt, wurde kein char gefunden, also -1 als index
  if (!res)
    return -1;

  // Wenn res keinen nullptr zurückgibt, wurde char gefunden
  // Adresse des gefundenen Zeigers - Adresse des Strings = Index
  int index = (int)(res - str);
  return index;
}

// Interner `str` wird mit `std::cout` ausgegeben.
void string::print() { std::cout << str << std::endl; }

// `str` wird mit 0 gefüllt und dann auf die Länge 1 zurückgesetzt, damit
// dieser mit `string::append` wiederverwendet werden kann.
void string::clear() {
  // str mit 0 füllen.
  memset(str, 0, strlen(str));
  // Größe zurücksetzen
  str = (char *)realloc(str, sizeof(char));
}

// Destruktor
string::~string() {
  // Speicher an der Stelle des str pointers freigeben.
  // Clear aufzurufen reicht nicht, da der Speicher dadurch nicht freigegeben
  // wird.
  free(str);
  // Zeiger auf nullptr setzen, um dangling pointers zu vermeiden
  str = nullptr;
}