#include "p1.h"
#include "p2.h"
#include "p4.h"

using namespace std;

int main(){

    vector<string> transmissions = {"Transmission1.txt", "Transmission2.txt"};
    vector<string> mcodes = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    int option = -1;

    while(option != 0){
        cout << "\nMenu\n"
        << "0. Exit\n"
        << "1. Subsequence Search\n"
        << "2. Palindrome Search\n"
        << "3. Longest Common Substring\n"
        << "4. Huffman Coding\n"
        << endl;

        pair<bool, int> ans;

        cin >> option;

        switch(option){
            case 0:
                option = 0;
                break;
            case 1:
                for(auto transmission : transmissions){
                    for(auto mcode : mcodes){
                        ans = findSubseq(transmission, mcode);
                        string out;
                        if(ans.first) out = "true<" + to_string(ans.second) + ">";
                        else out = "false";
                        cout << transmission << " | " << mcode << ": " << out << endl;
                    }
                }

                option = -1;
                break;
            case 2:
            for (int i = 0; i < transmissions.size(); i++) {
                string filename = transmissions[i];
                string texto = getString(transmissions[i]);


                cout << "Analizando archivo: " << filename << endl;


                string posiciones_palindromo = manacher(texto);

                cout << "Las posiciones del palindromo mas largo: " << posiciones_palindromo << endl << endl;


                option = -1;
                break;
            case 3:
                option = -1;
                break;
            case 4:
                for (const string& transmission : transmissions) {
                    analizarConHuffman(transmission, mcodes);
                }
                option = -1;
                break;
            default:
                cout << "Choose valid option\n";
                option = -1;
        }
    }

    return 0;
}
