#include "string.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>

string::string() {
  // Weist Heap-Speicher mit der Größe von einem char zu
  str = (char *)malloc(sizeof(char));
}

string::string(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine exception geworfen
  if (inputString) {
    // größe für internen str festlegen
    str = (char *)malloc(sizeof(char) * strlen(inputString));

    // c-string von der Eingabe in den internen str kopieren
    strcpy(str, inputString);
  } else {
    // Exception werfen
    throw std::invalid_argument("recieved nullptr");
  }
}

void string::append(const char *inputString) {
  // inputString auf nullptr überprüfen, damit strlen() keinen segfault erzeugt.
  // Bei einem nullptr wird eine exception geworfen
  if (inputString) {
    // Größe des internen str um Länge des inputStrings erweitern
    str = (char *)realloc(str,
                          sizeof(char) * (strlen(inputString) + strlen(str)));
    // inputString an bestehenden str anhängen
    strcat(str, inputString);
  } else {
    // Exception werfen
    throw std::invalid_argument("recieved nullptr");
  }
}

char *string::data() {
  // Gibt den internen str zurück.
  // Kann keinen nullptr zurückgeben, da bei eingabe eines nullptrs eine
  // exception geworfen wird
  return str;
}

int string::find(char c) {
  // Findet den ersten char, im internen str und gibt den entsprechenden Index
  // zurück. Wird char nicht gefunden, wird -1 zurück gegeben.
  char *res;
  int index;

  // Gibt Zeiger auf gefundenen str zurück und speichert ihn als res
  res = strchr(str, c);

  // Wenn res keinen nullptr zurückgibt, wurde char gefunden
  if (res) {
    // Adresse des gefundenen Zeigers - Adresse des Strings ergibt den Index
    index = (int)(res - str);
    return index;
  } else {
    // Falls char nicht gefunden wurde, also res = nullptr, gib als index -1
    // zurück
    return -1;
  }
}

void string::print() {
  // Zeichenkette wird mit cout ausgegeben
  std::cout << str << std::endl;
}

void string::clear() {
  // str wird mit 0 gefüllt und dann auf die Länge 1 zurückgesetzt, damit
  // dieser wiederverwendet werden kann.
  // str mit 0 füllen.
  memset(str, 0, strlen(str));
  // Größe zurücksetzen
  str = (char *)malloc(sizeof(char));
}

string::~string() {
  // Speicher an der Stelle des str pointers freigeben.
  // Clear aufzurufen reicht nicht, da der Speicher dadurch nicht freigegeben
  // wird.
  free(str);
  // Zeiger auf nullptr setzen, um dangling pointers zu vermeiden
  str = nullptr;
}