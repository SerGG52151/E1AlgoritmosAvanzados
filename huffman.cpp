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

    Nodo(char c, int f) : caracter(c), frecuencia(f), izquierda(nullptr), derecha(nullptr) {}
    Nodo(Nodo* l, Nodo* r) : caracter('\0'), frecuencia(l->frecuencia + r->frecuencia), izquierda(l), derecha(r) {}
};

struct Comparador {
    bool operator()(Nodo* a, Nodo* b) {
        return a->frecuencia > b->frecuencia;
    }
};

Nodo* construirArbolHuffman(const std::string & texto) {
    std::unordered_map<char, int> frecuencia;
    for (char c : texto) {
        frecuencia[c]++;
    }

    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparador> pq;
    for (auto& par : frecuencia) {
        pq.push(new Nodo(par.first, par.second));
    }

    while (pq.size() > 1) {
        Nodo* izquierda = pq.top(); pq.pop();
        Nodo* derecha = pq.top(); pq.pop();
        pq.push(new Nodo(izquierda, derecha));
    }

    return pq.top();  // Raíz del árbol
}

void generarCodigos(Nodo* nodo, const std::string& codigo, std::unordered_map<char, std::string>& codigos) {
    if (!nodo) return;
    if (!nodo->izquierda && !nodo->derecha) {
        codigos[nodo->caracter] = codigo;
        return;
    }
    generarCodigos(nodo->izquierda, codigo + "0", codigos);
    generarCodigos(nodo->derecha, codigo + "1", codigos);
}

int longitudCodificada(const std::string& texto, const std::unordered_map<char, std::string>& codigos) {
    int total = 0;
    for (char c : texto) {
        total += codigos.at(c).size();
    }
    return total;
}

double longitudPromedioEsperada(const std::string& texto, const std::unordered_map<char, std::string>& codigos) {
    std::unordered_map<char, int> frecuencia;
    for (char c : texto) frecuencia[c]++;
    double totalCaracteres = texto.size();
    double promedio = 0.0;
    for (auto& par : frecuencia) {
        promedio += (par.second / totalCaracteres) * codigos.at(par.first).size();
    }
    return promedio;
}