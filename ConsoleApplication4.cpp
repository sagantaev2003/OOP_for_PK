#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

// узел дерева Хаффмана
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// компаратор для приоритетеой очереди
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// рекурсивная генерация кодов Хаффмана
void buildCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;

    // Листовой узел
    if (!root->left && !root->right) {
        codes[root->ch] = code;
    }

    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

int main() {
    setlocale(LC_ALL, "Russian");
    string text = "hello world";

  
    cout << "Исходный текст: " << text << "\n\n";

    // ----- частоты -----
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    cout << "Частоты символов:\n";
    for (auto& p : freq)
        cout << p.first << ": " << p.second << "\n";
    cout << "\n";

    // ----- построение дерева Хаффмана -----
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto& p : freq) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();

    // ----- генерация кодов -----
    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    cout << "Коды Хаффмана:\n";
    for (auto& p : codes) {
        cout << p.first << ": " << p.second << "\n";
    }
    cout << "\n";

    // ----- кодирование строки -----
    string encoded = "";
    for (char ch : text) encoded += codes[ch];

    cout << "Закодированная строка:\n" << encoded << "\n";

    return 0;
}
