#include "avl_tree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
using namespace std;

AVLTree::~AVLTree() {
    Clear(root);
}

int AVLTree::Height(Node* n) const {
    if (n == nullptr) return 0;
    return n->height;
}

int AVLTree::BalanceFactor(Node* n) const {
    if (n == nullptr) return 0;
    return Height(n->left) - Height(n->right);
}

void AVLTree::UpdateHeight(Node* n) {
    if (n == nullptr) return;
    int lh = Height(n->left);
    int rh = Height(n->right);
    n->height = 1 + (lh > rh ? lh : rh);
}

AVLTree::Node* AVLTree::RotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    Node* oldParent = x->parent;
    bool wasLeft = (oldParent != nullptr && oldParent->left == x);

    y->left = x;
    x->right = T2;

    if (T2 != nullptr) T2->parent = x;
    x->parent = y;
    y->parent = oldParent;

    if (oldParent == nullptr) root = y;
    else if (wasLeft) oldParent->left = y;
    else oldParent->right = y;

    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

AVLTree::Node* AVLTree::RotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    Node* oldParent = y->parent;
    bool wasLeft = (oldParent != nullptr && oldParent->left == y);

    x->right = y;
    y->left = T2;

    if (T2 != nullptr) T2->parent = y;
    y->parent = x;
    x->parent = oldParent;

    if (oldParent == nullptr) root = x;
    else if (wasLeft) oldParent->left = x;
    else oldParent->right = x;

    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

AVLTree::Node* AVLTree::Balance(Node* n) {
    if (n == nullptr) return nullptr;

    UpdateHeight(n);
    int bf = BalanceFactor(n);

    if (bf > 1) {
        if (BalanceFactor(n->left) < 0) {
            n->left = RotateLeft(n->left);
            if (n->left != nullptr) n->left->parent = n;
        }
        return RotateRight(n);
    }

    if (bf < -1) {
        if (BalanceFactor(n->right) > 0) {
            n->right = RotateRight(n->right);
            if (n->right != nullptr) n->right->parent = n;
        }
        return RotateLeft(n);
    }

    return n;
}

AVLTree::Node* AVLTree::Insert(Node* n, const string& value) {
    if (n == nullptr) return new Node(value);

    if (value < n->data) {
        n->left = Insert(n->left, value);
        if (n->left != nullptr) n->left->parent = n;
    }
    else if (value > n->data) {
        n->right = Insert(n->right, value);
        if (n->right != nullptr) n->right->parent = n;
    }
    else {
        return n;
    }

    return Balance(n);
}

AVLTree::Node* AVLTree::Minimum(Node* n) const {
    if (n == nullptr) return nullptr;
    while (n->left != nullptr) n = n->left;
    return n;
}

AVLTree::Node* AVLTree::Remove(Node* n, const string& value) {
    if (n == nullptr) return nullptr;

    if (value < n->data) {
        n->left = Remove(n->left, value);
        if (n->left != nullptr) n->left->parent = n;
    }
    else if (value > n->data) {
        n->right = Remove(n->right, value);
        if (n->right != nullptr) n->right->parent = n;
    }
    else {
        if (n->left == nullptr || n->right == nullptr) {
            Node* temp = n->left ? n->left : n->right;
            if (temp == nullptr) {
                delete n;
                return nullptr;
            } else {
                temp->parent = n->parent;
                delete n;
                return temp;
            }
        }
        else {
            Node* temp = Minimum(n->right);
            n->data = temp->data;
            n->right = Remove(n->right, temp->data);
            if (n->right != nullptr) n->right->parent = n;
        }
    }

    return Balance(n);
}

void AVLTree::Push(const string& value) {
    if (Find(value)) return;
    root = Insert(root, value);
    if (root != nullptr) root->parent = nullptr;
}

void AVLTree::Pop() {
    if (root == nullptr) {
        cout << "Дерево пусто" << endl;
        return;
    }
    PopValue(root->data);
}

void AVLTree::PopValue(const string& value) {
    if (!Find(value)) {
        cout << "Не найдено" << endl;
        return;
    }
    cout << value << endl;
    root = Remove(root, value);
    if (root != nullptr) root->parent = nullptr;
}

bool AVLTree::Find(const string& value) const {
    Node* n = root;
    while (n != nullptr) {
        if (n->data == value) return true;
        if (value < n->data) n = n->left;
        else n = n->right;
    }
    return false;
}

void AVLTree::Print() const {
    PrintBFS();
}

void AVLTree::PrintBFS() const {
    if (root == nullptr) {
        cout << "Дерево пусто" << endl;
        return;
    }

    vector<Node*> q;
    q.push_back(root);
    size_t i = 0;
    while (i < q.size()) {
        Node* node = q[i++];
        cout << node->data << " ";
        if (node->left) q.push_back(node->left);
        if (node->right) q.push_back(node->right);
    }
    cout << endl;
}

void AVLTree::Clear(Node* n) {
    if (n == nullptr) return;
    Clear(n->left);
    Clear(n->right);
    delete n;
}

int AVLTree::CountNodes(Node* n) const {
    if (n == nullptr) return 0;
    return 1 + CountNodes(n->left) + CountNodes(n->right);
}

void AVLTree::SaveNode(Node* n, ofstream& out) const {
    if (n == nullptr) return;
    out << n->data << " ";
    SaveNode(n->left, out);
    SaveNode(n->right, out);
}

void AVLTree::Save(ofstream& out) const {
    out << "Кол-во элементов: " << CountNodes(root) << "\n";
    SaveNode(root, out);
    out << "\n";
}

void AVLTree::Load(ifstream& in) {
    Clear(root);
    root = nullptr;

    string w1, w2;
    int n;
    if (!(in >> w1 >> w2 >> n) || n < 0) return;

    for (int i = 0; i < n; i++) {
        string v;
        if (!(in >> v)) break;
        Push(v);
    }
}

int AVLTree::GetHeight() const {
    return Height(root);
}

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(const HuffmanNode* l, const HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

static void BuildCodes(const HuffmanNode* node, string str, map<char, string>& huffmanCode) {
    if (!node) return;
    if (!node->left && !node->right) {
        huffmanCode[node->ch] = str;
    }
    BuildCodes(node->left, str + "0", huffmanCode);
    BuildCodes(node->right, str + "1", huffmanCode);
}

static void FreeTree(HuffmanNode* node) {
    if (!node) return;
    FreeTree(node->left);
    FreeTree(node->right);
    delete node;
}

void AVLTree::HuffmanEncode(const string& text) {
    if (text.empty()) {
        cout << "Пустая строка" << endl;
        return;
    }

    map<char, int> freq;
    for (char c : text) freq[c]++;

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* top = new HuffmanNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }

    HuffmanNode* huffmanRoot = pq.top();
    map<char, string> huffmanCode;
    BuildCodes(huffmanRoot, "", huffmanCode);

    cout << "Таблица кодов:" << endl;
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }

    string encoded = "";
    for (char c : text) {
        encoded += huffmanCode[c];
    }
    
    cout << "Закодированная строка:" << endl;
    cout << encoded << endl;

    FreeTree(huffmanRoot);
}

void AVLTree::HuffmanDecode(const string& code, const string& table_str) {
    if (code.empty() || table_str.empty()) {
        cout << "Пустой код или таблица" << endl;
        return;
    }

    map<char, string> huffmanCode;
    stringstream ss(table_str);
    string item;
    while (getline(ss, item, ',')) {
        if (item.size() >= 3) {
            char ch = item[0];
            string c = item.substr(2);
            huffmanCode[ch] = c;
        }
    }

    HuffmanNode* huffmanRoot = new HuffmanNode('\0', 0);
    for (auto pair : huffmanCode) {
        HuffmanNode* cur = huffmanRoot;
        for (char bit : pair.second) {
            if (bit == '0') {
                if (!cur->left) cur->left = new HuffmanNode('\0', 0);
                cur = cur->left;
            } else {
                if (!cur->right) cur->right = new HuffmanNode('\0', 0);
                cur = cur->right;
            }
        }
        cur->ch = pair.first;
    }

    string decoded = "";
    HuffmanNode* cur = huffmanRoot;
    for (char bit : code) {
        if (bit == '0') {
            if (!cur->left) { cout << "Ошибка декодирования" << endl; FreeTree(huffmanRoot); return; }
            cur = cur->left;
        } else {
            if (!cur->right) { cout << "Ошибка декодирования" << endl; FreeTree(huffmanRoot); return; }
            cur = cur->right;
        }

        if (!cur->left && !cur->right) {
            decoded += cur->ch;
            cur = huffmanRoot;
        }
    }
    cout << decoded << endl;
    FreeTree(huffmanRoot);
}

static void SavePreorder(AVLTree::Node* n, ofstream& out) {
    if (!n) return;
    int len = n->data.length();
    out.write((char*)&len, sizeof(len));
    out.write(n->data.c_str(), len);
    SavePreorder(n->left, out);
    SavePreorder(n->right, out);
}

void AVLTree::SaveBinary(ofstream& out) const {
    int n = CountNodes(root);
    out.write((char*)&n, sizeof(n));
    SavePreorder(root, out);
}

void AVLTree::LoadBinary(ifstream& in) {
    Clear(root);
    root = nullptr;
    int n;
    in.read((char*)&n, sizeof(n));
    for (int i = 0; i < n; ++i) {
        int len;
        in.read((char*)&len, sizeof(len));
        char* buf = new char[len + 1];
        in.read(buf, len);
        buf[len] = '\0';
        Push(string(buf));
        delete[] buf;
    }
}