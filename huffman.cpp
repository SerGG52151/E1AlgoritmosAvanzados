#include "Huffman.h"

Nodo::Nodo(char c, int f) : caracter(c), frecuencia(f), izquierda(nullptr), derecha(nullptr) {}
Nodo::Nodo(Nodo* l, Nodo* r) : caracter('\0'), frecuencia(l->frecuencia + r->frecuencia), izquierda(l), derecha(r) {}


 bool Comparador::operator()(Nodo* a, Nodo* b) {
        return a->frecuencia > b->frecuencia;
}

Nodo* construirArbolHuffman(const std::string& texto) {
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

std::string leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return "";
    }
    std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

void analizarConHuffman(const std::string& nombreTransmision, const std::vector<std::string>& archivosMcode) {
    std::string textoTransmision = leerArchivo(nombreTransmision);

    // Construir árbol de Huffman y codigos
    Nodo* raiz = construirArbolHuffman(textoTransmision);
    std::unordered_map<char, std::string> codigos;
    generarCodigos(raiz, "", codigos);

    // Longitud promedio esperada y total codificada de la transmisión
    double promedioEsperado = longitudPromedioEsperada(textoTransmision, codigos);
    int longitudTransmisionCodificada = longitudCodificada(textoTransmision, codigos);

    std::cout << "Transmisión: " << nombreTransmision << std::endl;
    std::cout << "Tamaño comprimido: " << longitudTransmisionCodificada << " bits" << std::endl;

    for (const std::string& archivoMcode : archivosMcode) {
        std::string textoMcode = leerArchivo(archivoMcode);
        int longitudMcodeCodificada = longitudCodificada(textoMcode, codigos);
        double promedioMcode = static_cast<double>(longitudMcodeCodificada) / textoMcode.size();

        // Umbral de sospecha: por ejemplo, 1.5x del promedio
        bool sospechoso = promedioMcode > promedioEsperado * 1.5;

        std::cout << (sospechoso ? "sospechoso" : "no-sospechoso") << " " << longitudMcodeCodificada << std::endl;
    }

    std::cout << std::endl;
}
