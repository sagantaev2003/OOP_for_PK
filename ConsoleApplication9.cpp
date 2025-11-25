#include <iostream>
#include <string>
using namespace std;

// Простая функция хеширования (сумма символов)
int hashString(const string& s, int base = 256, int mod = 101) {
    int h = 0;
    for (char c : s)
        h = (h * base + c) % mod;
    return h;
}

void rabinKarp(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    int base = 256;
    int mod = 101;

    int patternHash = hashString(pattern, base, mod);
    int currentHash = hashString(text.substr(0, m), base, mod);

    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * base) % mod;  // база^(m-1) для скользящего хеша

    cout << "Исходный текст: " << text << "\n";
    cout << "Искомая подстрока: " << pattern << "\n";

    cout << "Подстрока найдена на позициях: ";
    for (int i = 0; i <= n - m; i++) {
        if (currentHash == patternHash) {
            if (text.substr(i, m) == pattern)
                cout << i << " ";
        }
        if (i < n - m) {
            currentHash = (base * (currentHash - text[i] * h) + text[i + m]) % mod;
            if (currentHash < 0) currentHash += mod;
        }
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    string text = "abracadabra";
    string pattern = "abra";

    rabinKarp(text, pattern);

    return 0;
}
