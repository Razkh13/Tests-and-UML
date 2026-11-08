#pragma once
#include "container.h"

class Queue : public Container {
    struct Node {
        std::string data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    Queue() = default;
    ~Queue();

    void Push(const std::string& value) override;
    void Pop() override;
    void Print() const override;
    bool Find(const std::string& value) const override;

    void Save(std::ofstream& out) const override;
    void Load(std::ifstream& in) override;
    std::string TypeName() const override { return "QUEUE"; }

    void SaveBinary(std::ofstream& out) const;
    void LoadBinary(std::ifstream& in);
};