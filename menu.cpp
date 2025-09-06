#include "p1.cpp"

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
                

                option = -1;
                break;
            case 3:
                option = -1;
                break;
            case 4:
                option = -1;
                break;
            default:
                cout << "Choose valid option\n";
                option = -1;
        }
    }

    return 0;
}