#include <iostream>
#include <vector>
using namespace std;


//                  БИНАРНЫЙ ПОИСК

int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}


//                  BST ДЕРЕВО
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root = NULL;

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return node;
    }

    bool search(Node* node, int key) {
        if (!node) return false;
        if (node->key == key) return true;

        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
};


//                  AVL ДЕРЕВО
struct AVLNode {
    int key, height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

class AVL {
public:
    AVLNode* root = NULL;

    int height(AVLNode* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(AVLNode* n) {
        return height(n->left) - height(n->right);
    }

    void updateHeight(AVLNode* n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;

        x->right = y;
        y->left = T;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;

        y->left = x;
        x->right = T;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1 && key < node->left->key) return rotateRight(node);      // LL
        if (bf < -1 && key > node->right->key) return rotateLeft(node);     // RR
        if (bf > 1 && key > node->left->key) {                               // LR
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && key < node->right->key) {                             // RL
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
};


//                       запуск

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> arr = { 2, 5, 7, 10, 12, 15, 20 };
    int target = 10;

    cout << "Исходные данные для бинарного поиска:\n";
    cout << "Массив: ";
    for (int x : arr) cout << x << " ";
    cout << "\nИскомый элемент: " << target << "\n\n";

    // ---------- БИНАРНЫЙ ПОИСК ----------
    int index = binarySearch(arr, target);
    if (index != -1)
        cout << "Результат бинарного поиска: найден в индексе " << index << "\n\n";
    else
        cout << "Результат бинарного поиска: не найден\n\n";


    cout << "Исходные данные для BST дерева:\n"
        << "Вставляемые ключи: 15, 10, 20, 8, 12\n\n";

    BST bst;
    bst.root = bst.insert(bst.root, 15);
    bst.insert(bst.root, 10);
    bst.insert(bst.root, 20);
    bst.insert(bst.root, 8);
    bst.insert(bst.root, 12);

    cout << "BST обход (in-order): ";
    bst.inorder(bst.root);
    cout << "\nПоиск числа 12 в BST: "
        << (bst.search(bst.root, 12) ? "найдено" : "не найдено") << "\n\n";


    //     3. Исходные данные AVL

    cout << "Исходные данные для AVL дерева:\n"
        << "Вставляемые ключи: 30, 20, 40, 10\n\n";

    AVL avl;
    avl.root = avl.insert(avl.root, 30);
    avl.root = avl.insert(avl.root, 20);
    avl.root = avl.insert(avl.root, 40);
    avl.root = avl.insert(avl.root, 10); // вызовет балансировку

    cout << "AVL дерево (in-order): ";
    avl.inorder(avl.root);

    return 0;
}
