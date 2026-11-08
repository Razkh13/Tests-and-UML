#include "dbms.h"
#include "HashTable/hash_table.h"
#include "Stack/stack.h"
#include "Array/array.h"
#include "Forward_list/forward_list.h"
#include "Doubly_list/doubly_list.h"
#include "Queue/queue.h"
#include "AVL_tree/avl_tree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

DBMS::~DBMS() {
    for (auto& pair : containers) delete pair.second;
    for (auto& pair : hashTables) delete pair.second;
}

Container* DBMS::CreateByPrefix(char prefix) {
    if (prefix == 'S') return new Stack();
    if (prefix == 'M') return new Array();
    if (prefix == 'F') return new ForwardList();
    if (prefix == 'L') return new DoublyList();
    if (prefix == 'Q') return new Queue();
    if (prefix == 'T') return new AVLTree();
    return nullptr;
}

Container* DBMS::GetOrCreate(const string& name, const string& cmd) {
    auto it = containers.find(name);
    if (it != containers.end()) return it->second;

    Container* c = CreateByPrefix(cmd[0]);
    if (c == nullptr) return nullptr;
    containers[name] = c;
    return c;
}

void DBMS::LoadAll() {
    ifstream in(dataFile);
    if (!in.is_open()) {
        cout << "Файл данных не найден — начинаем с пустого" << endl;
        return;
    }

    string name, type;
    while (in >> name >> type) {
        if (type == "HASHTABLE") {
            int method = 1;
            in >> method; 
            HashTable* ht = new HashTable(10007, method);
            ht->Load(in);
            hashTables[name] = ht;
            continue;
        }

        Container* c = nullptr;
        if (type == "STACK") c = new Stack();
        else if (type == "ARRAY") c = new Array();
        else if (type == "FORWARD_LIST") c = new ForwardList();
        else if (type == "DOUBLY_LIST") c = new DoublyList();
        else if (type == "QUEUE") c = new Queue();
        else if (type == "AVLTREE") c = new AVLTree();
        else {
            string skip;
            getline(in, skip);
            continue;
        }
        c->Load(in);
        containers[name] = c;
    }
    in.close();
}

void DBMS::SaveAll() {
    ofstream out(dataFile);
    if (!out.is_open()) return;

    for (auto& pair : containers) {
        out << pair.first << " " << pair.second->TypeName() << "\n";
        pair.second->Save(out);
    }

    for (auto& pair : hashTables) {
        out << pair.first << " HASHTABLE " << pair.second->GetMethod() << "\n";
        pair.second->Save(out);
    }

    out.close();
}

void DBMS::ExecuteQuery(const string& query) {
    istringstream iss(query);
    string cmd, name, arg1, arg2;
    iss >> cmd >> name;

    if (cmd.empty() || name.empty()) {
        cout << "Неверный формат команды" << endl;
        return;
    }

    if (cmd == "PRINT") {
        auto it = containers.find(name);
        if (it != containers.end()) it->second->Print();
        return;
    }

    if (cmd == "HTADD") {
        int method;
        iss >> method >> arg1;
        if (hashTables.find(name) == hashTables.end()) {
            hashTables[name] = new HashTable(10007, method);
        }
        hashTables[name]->Add(arg1);
        hashTables[name]->Print();
        return;
    }
    else if (cmd == "HTDEL") {
        iss >> arg1;
        if (hashTables.find(name) != hashTables.end()) {
            hashTables[name]->Remove(arg1);
            hashTables[name]->Print();
        }
        return;
    }
    else if (cmd == "HTGET") {
        iss >> arg1;
        if (hashTables.find(name) != hashTables.end()) {
            if (hashTables[name]->Contains(arg1)) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
        }
        return;
    }
    else if (cmd == "HTLONGEST") {
        if (hashTables.find(name) == hashTables.end()) {
            hashTables[name] = new HashTable(10007, 1);
        }
        cout << hashTables[name]->LengthOfLongestSubstring(name) << endl;
        return;
    }

    Container* c = GetOrCreate(name, cmd);
    if (c == nullptr) {
        cout << "Неизвестная команда" << endl;
        return;
    }

    if (cmd == "SPUSH" || cmd == "MPUSH" || cmd == "FPUSH" ||
        cmd == "LPUSH" || cmd == "QPUSH" || cmd == "TINSERT") {
        iss >> arg1;
        c->Push(arg1);
        c->Print();
    }
    else if (cmd == "SPOP" || cmd == "SDEL" ||
             cmd == "MPOP" || cmd == "MDEL" ||
             cmd == "FPOP" || cmd == "FDEL" ||
             cmd == "LPOP" || cmd == "LDEL" ||
             cmd == "QPOP" || cmd == "QDEL") {
        c->Pop();
        c->Print();
    }
    else if (cmd == "SPRINT" || cmd == "SGET" ||
             cmd == "MPRINT" || cmd == "MGETALL" ||
             cmd == "FPRINT" || cmd == "FGET" ||
             cmd == "LPRINT" || cmd == "LGET" ||
             cmd == "QPRINT" || cmd == "QGET" ||
             cmd == "TPRINT" || cmd == "TBFS") {
        c->Print();
    }
    else if (cmd == "SFIND" || cmd == "MFIND" || cmd == "FFIND" ||
             cmd == "LFIND" || cmd == "QFIND" ||
             cmd == "TGET" || cmd == "ISMEMBER") {
        iss >> arg1;
        if (c->Find(arg1)) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    }
    else if (cmd == "MPUSHAT") {
        int idx;
        iss >> idx >> arg1;
        Array* a = dynamic_cast<Array*>(c);
        if (a) { a->PushAt(idx, arg1); a->Print(); }
    }
    else if (cmd == "MPOPAT") {
        int idx;
        iss >> idx;
        Array* a = dynamic_cast<Array*>(c);
        if (a) { a->PopAt(idx); a->Print(); }
    }
    else if (cmd == "MSET") {
        int idx;
        iss >> idx >> arg1;
        Array* a = dynamic_cast<Array*>(c);
        if (a) { a->SetAt(idx, arg1); a->Print(); }
    }
    else if (cmd == "MGET") {
        int idx;
        iss >> idx;
        Array* a = dynamic_cast<Array*>(c);
        if (a) { cout << a->GetAt(idx) << endl; }
    }
    else if (cmd == "MSIZE") {
        Array* a = dynamic_cast<Array*>(c);
        if (a) { cout << a->Size() << endl; }
    }
    else if (cmd == "FPUSHTAIL") {
        iss >> arg1;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PushTail(arg1); f->Print(); }
    }
    else if (cmd == "FPUSHBEFORE") {
        iss >> arg1 >> arg2;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PushBefore(arg1, arg2); f->Print(); }
    }
    else if (cmd == "FPUSHAFTER") {
        iss >> arg1 >> arg2;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PushAfter(arg1, arg2); f->Print(); }
    }
    else if (cmd == "FPOPTAIL") {
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PopTail(); f->Print(); }
    }
    else if (cmd == "FPOPBEFORE") {
        iss >> arg1;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PopBefore(arg1); f->Print(); }
    }
    else if (cmd == "FPOPAFTER") {
        iss >> arg1;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PopAfter(arg1); f->Print(); }
    }
    else if (cmd == "FPOPVALUE") {
        iss >> arg1;
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) { f->PopValue(arg1); f->Print(); }
    }
    else if (cmd == "FPRINTREVERSE") {
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) f->PrintReverse();
    }
    else if (cmd == "FPRINTEVERYSECOND") {
        ForwardList* f = dynamic_cast<ForwardList*>(c);
        if (f) f->PrintEverySecond();
    }
    else if (cmd == "LPUSHTAIL") {
        iss >> arg1;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PushTail(arg1); d->Print(); }
    }
    else if (cmd == "LPUSHBEFORE") {
        iss >> arg1 >> arg2;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PushBefore(arg1, arg2); d->Print(); }
    }
    else if (cmd == "LPUSHAFTER") {
        iss >> arg1 >> arg2;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PushAfter(arg1, arg2); d->Print(); }
    }
    else if (cmd == "LPOPTAIL") {
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PopTail(); d->Print(); }
    }
    else if (cmd == "LPOPBEFORE") {
        iss >> arg1;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PopBefore(arg1); d->Print(); }
    }
    else if (cmd == "LPOPAFTER") {
        iss >> arg1;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PopAfter(arg1); d->Print(); }
    }
    else if (cmd == "LPOPVALUE") {
        iss >> arg1;
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) { d->PopValue(arg1); d->Print(); }
    }
    else if (cmd == "LPRINTREVERSE") {
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) d->PrintReverse();
    }
    else if (cmd == "LPRINTEVERYSECOND") {
        DoublyList* d = dynamic_cast<DoublyList*>(c);
        if (d) d->PrintEverySecond();
    }
    else if (cmd == "TDEL") {
        iss >> arg1;
        AVLTree* t = dynamic_cast<AVLTree*>(c);
        if (t) { t->PopValue(arg1); t->Print(); }
    }
    else if (cmd == "SVALIDATE") {
        iss >> arg1;
        Stack* s = dynamic_cast<Stack*>(c);
        if (s) {
            if (s->ValidateXML(arg1)) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
        }
    }
    else if (cmd == "SFIXXML") {
        iss >> arg1;
        Stack* s = dynamic_cast<Stack*>(c);
        if (s) { cout << s->FixXML(arg1) << endl; }
    }
    else if (cmd == "MSUBARRAYS") {
        Array* a = dynamic_cast<Array*>(c);
        if (a) { a->PrintSubarrays(); }
    }
    else if (cmd == "THEIGHT") {
        AVLTree* t = dynamic_cast<AVLTree*>(c);
        if (t) cout << t->GetHeight() << endl;
    }
    else if (cmd == "THUFFMAN") {
        AVLTree* t = dynamic_cast<AVLTree*>(c);
        if (t) { t->HuffmanEncode(name); }
    }
    else if (cmd == "THUFFMANDEC") {
        string code, table;
        iss >> code >> table;
        AVLTree* t = dynamic_cast<AVLTree*>(c);
        if (t) { t->HuffmanDecode(code, table); }
    }
    else if (cmd == "SAVEBIN") {
        ofstream out(name, ios::binary);
        if (auto a = dynamic_cast<Array*>(c)) a->SaveBinary(out);
        else if (auto f = dynamic_cast<ForwardList*>(c)) f->SaveBinary(out);
        else if (auto d = dynamic_cast<DoublyList*>(c)) d->SaveBinary(out);
        else if (auto s = dynamic_cast<Stack*>(c)) s->SaveBinary(out);
        else if (auto q = dynamic_cast<Queue*>(c)) q->SaveBinary(out);
        else if (auto h = dynamic_cast<HashTable*>(c)) h->SaveBinary(out);
        else if (auto t = dynamic_cast<AVLTree*>(c)) t->SaveBinary(out);
        out.close();
    }
    else if (cmd == "LOADBIN") {
        ifstream in(name, ios::binary);
        if (auto a = dynamic_cast<Array*>(c)) a->LoadBinary(in);
        else if (auto f = dynamic_cast<ForwardList*>(c)) f->LoadBinary(in);
        else if (auto d = dynamic_cast<DoublyList*>(c)) d->LoadBinary(in);
        else if (auto s = dynamic_cast<Stack*>(c)) s->LoadBinary(in);
        else if (auto q = dynamic_cast<Queue*>(c)) q->LoadBinary(in);
        else if (auto h = dynamic_cast<HashTable*>(c)) h->LoadBinary(in);
        else if (auto t = dynamic_cast<AVLTree*>(c)) t->LoadBinary(in);
        in.close();
        c->Print();
    }
    else {
        cout << "Неизвестная команда" << endl;
    }
}