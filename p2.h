#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Esta funcion no sirve para quitar los espacios y saltos de linea en el documento.
void depuracion(string &s){
    string depurado;
    // Itera sobre cada componente del texto
    for(char c : s){
        if(c != ' '){
            depurado += c;
        }
    }
    s = depurado;
}


/* Esta es la funcion principal para calcular los palindromos.
   Crea un vector que guarda el valor del radio de los palindromos mas largos,
   para despues sacar sus posiciones. Para lograrlo, transforma el texto
   original insertando '#' para unificar el manejo de palindromos pares e impares,
   y luego lo recorre de forma optimizada para encontrar el de mayor longitud. */

string manacher(string s){
    string ms = "@";
    vector<int>p;

    depuracion(s);

    for(char c : s){
            ms +=  "#" + string(1, c);
    }
    ms += "#$";

    int n =  ms.size();
    p.assign(n, 0);

    int L = 0;
    int R = 0;
    for(int i=1; i < n-1; i++){
        int mirror = L + R - i;
            if(i<R){
                p[i] = min(R-i, p[mirror]);
            }
            while(ms[i + p[i]+1] == ms[i - p[i] - 1]){
                ++p[i];
            }
            if((i+p[i]) > R){
                R = i + p[i];
                L = i - p[i];
            }
    }

    int radio_mayor = 0;
    int posicion_radio = 0;
    for(int i =  1; i < n-1; i++){
            if(radio_mayor < p[i]){
                radio_mayor = p[i];
                posicion_radio = i;
            }
    }

    int inicio = (posicion_radio - radio_mayor)/2;

    string posiciones = to_string(inicio + 1) + " " + to_string(radio_mayor + inicio);

    return posiciones;
}
