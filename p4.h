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

    //Creacion de nodo con caracter y frecuencia
    Nodo(char c, int f) : caracter(c), frecuencia(f), izquierda(nullptr), derecha(nullptr) {}
    //Creacion de nodo con suma de frecuencias de ambos hijos
    Nodo(Nodo* l, Nodo* r) : caracter('\0'), frecuencia(l->frecuencia + r->frecuencia), izquierda(l), derecha(r) {}
    
    ~Nodo() {
        delete izquierda;
        delete derecha;
    }
};

//Regla para ordenar priority-queue y asegurar que el primer nodo tenga mayor frecuencia que el segundo
struct Comparador {
    bool operator()(Nodo* a, Nodo* b) {
        return a->frecuencia > b->frecuencia;
    }
};

//Construccion de Arbol Huffman
inline Nodo* construirArbolHuffman(const std::string& texto) {
    //Contar frecuencia de cada caracter en el texto
    std::unordered_map<char, int> frecuencia;
    for (char c : texto) {
        frecuencia[c]++;
    }

    //Usar priority queue con regla de Comparador que contiene pointers a Nodos
    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparador> pq;
    for (auto& par : frecuencia) {
        char caracter = par.first;
        int frecuencia = par.second;
        pq.push(new Nodo(caracter, frecuencia));
    }

    //Extraer los dos nodos mas pequeños y crear un nuevo nodo que los tiene como hijos
    while (pq.size() > 1) {
        Nodo* izquierda = pq.top(); 
        pq.pop();
        Nodo* derecha = pq.top(); 
        pq.pop();
        pq.push(new Nodo(izquierda, derecha));
    }

    //Regresar el nodo raiz del Arbol de Huffman
    return pq.top();
}

//Generacion de codigos para cada caracter en el Arbol de Huffman
//Almacena el codigo que se ha construido ademas del mapa asociando cada caracter con su codigo
inline void generarCodigos(Nodo* nodo, const std::string& codigo, std::unordered_map<char, std::string>& codigos) {
    //Caso base
    if (!nodo) return;  

    //Checar si es un nodo hoja. Si lo es, asocia el codigo generado hasta este punto con el caracter en el mapa
    if (!nodo->izquierda && !nodo->derecha) {
        codigos[nodo->caracter] = codigo;
        return;
    }

    //Llamada recursiva, asegurando de cambiar el codigo segun la direccion traversada
    generarCodigos(nodo->izquierda, codigo + "0", codigos);
    generarCodigos(nodo->derecha, codigo + "1", codigos);
}

//Calcula la longitud de la version codificada del archivo transmission.txt que se uso
inline int longitudCodificada(const std::string& texto, const std::unordered_map<char, std::string>& codigos) {
    int total = 0;
    //Usa el mapa de codigos para acumular el tamaño total
    for (char c : texto) {
        total += codigos.at(c).size();
    }
    return total;
}

//Calcula promedio esperado en base de longitud de la transmision codificada
inline double longitudPromedioEsperada(const std::string& texto, int totalTransmisionBits) {
    return static_cast<double>(totalTransmisionBits) / texto.size();
}

//Leer archivo y regresarlo como un std::string para poder crear el Arbol de Huffman
inline std::string leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return "";
    }
    std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

//Funcion principal para analisis
inline void analizarConHuffman(const std::string& nombreTransmision, const std::vector<std::string>& archivosMcode) {
    std::string textoTransmision = leerArchivo(nombreTransmision);

    // Construir árbol de Huffman y codigos
    Nodo* raiz = construirArbolHuffman(textoTransmision);
    std::unordered_map<char, std::string> codigos;
    generarCodigos(raiz, "", codigos);

    // Longitud promedio esperada y total codificada de la transmisión
    int longitudTransmisionCodificada = longitudCodificada(textoTransmision, codigos);
    double promedioEsperado = longitudPromedioEsperada(textoTransmision, longitudTransmisionCodificada);

    std::cout << "Transmisión: " << nombreTransmision << std::endl;
    std::cout << "Tamaño comprimido: " << longitudTransmisionCodificada << " bits" << std::endl;

    //Comparar cada archivo mcode con el archivo de transmision
    for (const std::string& archivoMcode : archivosMcode) {
        std::string textoMcode = leerArchivo(archivoMcode);
        int longitudMcodeCodificada = longitudCodificada(textoMcode, codigos);
        double promedioMcode = static_cast<double>(longitudMcodeCodificada) / textoMcode.size();

        // Checar si es sospechoso
        bool sospechoso = promedioMcode > promedioEsperado * 1.5;

        std::cout << archivoMcode << ": " << (sospechoso ? "sospechoso" : "no-sospechoso") << " " << longitudMcodeCodificada << std::endl;
    }

    std::cout << std::endl;
}

#endif