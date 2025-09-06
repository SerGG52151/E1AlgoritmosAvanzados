#include "readFiles.cpp"
#include <utility>
#include <vector>

using namespace std;

// From Geeks4Geeks
void constructLps(string &pat, vector<int> &lps) {

    // len stores the length of longest prefix which
    // is also a suffix for the previous index
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.length()) {

        // If characters match, increment the size of lps
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else { // If mismatch
            if (len != 0) {

                // Update len to the previous lps value
                // to avoid reduntant comparisons
                len = lps[len - 1];
            } else {

                // If no matching prefix found, set lps[i] to 0
                lps[i] = 0;
                i++;
            }
        }
    }
}

pair<bool, int> kmp(string &txt, string &pat) {
    int n = txt.length();
    int m = pat.length();

    vector<int> lps(m);
    pair<bool, int> ans(false, 0);

    constructLps(pat, lps);

    // Pointers i and j, for traversing
    // the text and pattern
    int i = 0;
    int j = 0;

    while (i < n) {

        // If characters match, move both pointers forward
        if (txt[i] == pat[j]) {
            i++;
            j++;

            // If the entire pattern is matched
            // store the start index in result
            if (j == m) {
                ans.first = true;
                ans.second = (i - j);

                // Use LPS of previous index to
                // skip unnecessary comparisons
                j = lps[j - 1];
            }
        } else { // If mismatch
            // Use lps value of previous index
            // to avoid redundant comparisons
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return ans;
}

pair<bool, int> findSubseq(string fileScan, string fileSeq){
    pair<bool, int> ans(false, 0);
    string scan = getString(fileScan);
    string seq = getString(fileSeq);

    if(scan.length() == 0){
        cout << "String not found in file to scan\n";
        return ans;
    } 

    if(seq.length() == 0){
        cout << "Sequence to scan for not found\n";
        return ans;
    } 

    // KMP
    ans = kmp(scan, seq); 

    return ans;
}
