#include "p1.h"   
#include "p2.h"   
#include "p3.h" 
#include "p4.h"   

using namespace std;

int main() {
    vector<string> transmissions = {"Transmission1.txt", "Transmission2.txt"};
    vector<string> mcodes = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    int option = -1;

    while (option != 0) {
        cout << "\nMenu\n"
             << "0. Exit\n"
             << "1. Subsequence Search\n"
             << "2. Palindrome Search\n"
             << "3. Longest Common Substring\n"
             << "4. Huffman Coding\n"
             << endl;

        cin >> option;

        switch (option) {
            case 0: {
                break;
            }

            case 1: { 
                for (auto transmission : transmissions) {
                    for (auto mcode : mcodes) {
                        pair<bool, int> ans = findSubseq(transmission, mcode);
                        string out;
                        if (ans.first) out = "true<" + to_string(ans.second) + ">";
                        else out = "false";
                        cout << transmission << " | " << mcode << ": " << out << endl;
                    }
                }
                option = -1;
                break;
            }

            case 2: { 
                for (int i = 0; i < (int)transmissions.size(); i++) {
                    string filename = transmissions[i];
                    string texto = getString(transmissions[i]);

                    cout << "Analizando archivo: " << filename << endl;

                    string posiciones_palindromo = manacher(texto);
                    cout << "Las posiciones del palindromo mas largo: "
                         << posiciones_palindromo << endl << endl;
                }
                option = -1;
                break;
            }

            case 3: {
             
                string t1 = getString(transmissions[0]);
                string t2 = getString(transmissions[1]);
                auto [i1, j1, sub] = lcs_positions_and_text(t1, t2);
                cout << i1 << " " << j1 << endl;
                cout << "Substring comun mas largo: " << sub << endl;

                option = -1;
                break;
            }

            case 4: {
                for (const string& transmission : transmissions) {
                    analizarConHuffman(transmission, mcodes);
                }
                option = -1;
                break;
            }

            default: {
                cout << "Choose valid option\n";
                option = -1;
            }
        }
    }

    return 0;
}
