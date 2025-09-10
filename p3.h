#include <bits/stdc++.h>
#include "readFiles.h"

using namespace std;
struct State {
    int link = -1;           // sufijo sufijo
    int len  = 0;            // longitud máxima del estado
    int first_pos = -1;      // una posición de fin para len
    int next[256];           // char
    State() {
        memset(next, -1, sizeof(next));
    }
};

struct SuffixAutomaton {
    vector<State> st;
    int last;

    SuffixAutomaton(size_t reserve_size = 0) {
        st.reserve(max<size_t>(2, 2 * reserve_size));
        st.push_back(State()); // estado 0 
        st[0].link = -1;
        st[0].len = 0;
        st[0].first_pos = -1;
        last = 0;
    }

    void extend(unsigned char c) {
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = st[cur].len - 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]); // copia de q
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};

pair<int,int> longestCommonSubstringPositions1BasedInclusive(const string &s1, const string &s2) {
    SuffixAutomaton sam(s1.size());
    for (unsigned char c : s1) sam.extend(c);

    int v = 0;        // estado actual en SAM
    int l = 0;        // longitud actual de match
    int bestLen = 0;  // mejor longitud encontrada
    int bestEnd = -1; // fin 0

    for (unsigned char c : s2) {
        if (sam.st[v].next[c] != -1) {
            v = sam.st[v].next[c];
            l++;
        } else {
            while (v != -1 && sam.st[v].next[c] == -1) v = sam.st[v].link;
            if (v == -1) {
                v = 0;
                l = 0;
                continue;
            } else {
                l = sam.st[v].len + 1;
                v = sam.st[v].next[c];
            }
        }
        while (l > 0 && sam.st[sam.st[v].link].len >= l) {
            v = sam.st[v].link;
        }
        int candLen = l;
        int candEnd = sam.st[v].first_pos;
        if (candLen > bestLen) {
            bestLen = candLen;
            bestEnd = candEnd;
        } else if (candLen == bestLen && bestLen > 0) {
            int curStart = candEnd - candLen + 1;
            int bestStart = bestEnd - bestLen + 1;
            if (curStart < bestStart) {
                bestEnd = candEnd;
            }
        }
    }

    if (bestLen == 0) {
        return {0, 0};
    }

    int start0 = bestEnd - bestLen + 1; 
    int start1 = start0 + 1;
    int end1   = bestEnd + 1;
    return {start1, end1};
}



