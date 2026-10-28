#include <iostream>
#include <string>

using namespace std;

int val[256];
bool used[10];
string uniq = "", w1, w2, w3; 

bool solve(int i) {
    if (i == uniq.length()) {
        if (val[w1[0]] == 0 || val[w2[0]] == 0 || val[w3[0]] == 0) return false;
        
        long long n1 = 0, n2 = 0, n3 = 0;
        for (char c : w1) n1 = n1 * 10 + val[c];
        for (char c : w2) n2 = n2 * 10 + val[c];
        for (char c : w3) n3 = n3 * 10 + val[c];
        
        if (n1 + n2 == n3) {
            cout << "\nValues: ";
            for (char c : uniq) cout << c << "=" << val[c] << "  ";
            cout << "\n\nResult: " << n1 << " + " << n2 << " = " << n3 << "\n";
            return true;
        }
        return false;
    }

    for (int d = 0; d <= 9; d++) {
        if (!used[d]) {
            used[d] = true;
            val[uniq[i]] = d;
            
            if (solve(i + 1)) return true; 
            
            used[d] = false; 
        }
    }
    return false;
}

int main() {
    cout << "Enter 3 words (eg: SEND MORE MONEY): ";
    cin >> w1 >> w2 >> w3;

    bool seen[256] = {false};
    for (char c : w1 + w2 + w3) {
        if (!seen[c]) {
            uniq += c;
            seen[c] = true;
        }
    }

    if (uniq.length() > 10 || !solve(0)) {
        cout << "No solution exists.\n";
    }

    return 0;
}

// g++ file.cpp -o file
// .\file