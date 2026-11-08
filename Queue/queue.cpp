#include "queue.h"
#include <iostream>
using namespace std;

Queue::~Queue() {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

void Queue::Push(const string& value) {
    Node* n = new Node{value, nullptr};
    if (!tail) {
        head = tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
}

void Queue::Pop() {
    if (!head) { cout << "Очередь пуста" << endl; return; }
    cout << head->data << endl;
    Node* t = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete t;
}

void Queue::Print() const {
    Node* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

bool Queue::Find(const string& value) const {
    Node* cur = head;
    while (cur) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

void Queue::Save(ofstream& out) const {
    int n = 0;
    Node* cur = head;
    while (cur) { n++; cur = cur->next; }

    out << "Кол-во элементов: " << n << "\n";

    cur = head;
    while (cur) {
        out << cur->data << " ";
        cur = cur->next;
    }
    out << "\n";
}

void Queue::Load(ifstream& in) {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    head = nullptr;
    tail = nullptr;

    string w1, w2;
    int n;
    if (!(in >> w1 >> w2 >> n) || n < 0) return;

    for (int i = 0; i < n; i++) {
        string v;
        if (!(in >> v)) break;
        Push(v);
    }
}

void Queue::SaveBinary(ofstream& out) const {
    int n = 0; Node* cur = head;
    while (cur) { n++; cur = cur->next; }
    out.write((char*)&n, sizeof(n));
    cur = head;
    while (cur) {
        int len = cur->data.length();
        out.write((char*)&len, sizeof(len));
        out.write(cur->data.c_str(), len);
        cur = cur->next;
    }
}
void Queue::LoadBinary(ifstream& in) {
    while (head) { Node* t = head; head = head->next; delete t; }
    head = nullptr; tail = nullptr;
    int n; in.read((char*)&n, sizeof(n));
    for (int i = 0; i < n; ++i) {
        int len; in.read((char*)&len, sizeof(len));
        char* buf = new char[len + 1];
        in.read(buf, len); buf[len] = '\0';
        Push(string(buf)); delete[] buf;
    }
}