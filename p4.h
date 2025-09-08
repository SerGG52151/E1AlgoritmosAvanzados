// Huffman.h
#ifndef P4_H
#define P4_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iomanip>


struct Nodo {
    char caracter;
    int frecuencia;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(char c, int f);
    Nodo(Nodo* l, Nodo* r);
};

struct Comparador {
    bool operator()(Nodo* a, Nodo* b);
};

Nodo* construirArbolHuffman(const std::string& texto);
void generarCodigos(Nodo* nodo, const std::string& codigo, std::unordered_map<char, std::string>& codigos);
int longitudCodificada(const std::string& texto, const std::unordered_map<char, std::string>& codigos);
double longitudPromedioEsperada(const std::string& texto, const std::unordered_map<char, std::string>& codigos);
void analizarConHuffman(const std::string& nombreTransmision, const std::vector<std::string>& archivosMcode);

#endif