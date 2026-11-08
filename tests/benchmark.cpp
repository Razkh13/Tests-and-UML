#include <benchmark/benchmark.h>
#include "../Array/array.h"
#include "../Stack/stack.h"
#include "../Forward_list/forward_list.h"
#include "../Doubly_list/doubly_list.h"
#include "../Queue/queue.h"
#include "../HashTable/hash_table.h"
#include "../AVL_tree/avl_tree.h"

static void BM_ArrayPush(benchmark::State& state) {
    for (auto _ : state) {
        Array a;
        for (int i = 0; i < state.range(0); ++i) a.Push("test");
    }
}
BENCHMARK(BM_ArrayPush)->Arg(1000)->Arg(10000);

static void BM_StackPush(benchmark::State& state) {
    for (auto _ : state) {
        Stack s;
        for (int i = 0; i < state.range(0); ++i) s.Push("test");
    }
}
BENCHMARK(BM_StackPush)->Arg(1000);

static void BM_ForwardListPushTail(benchmark::State& state) {
    for (auto _ : state) {
        ForwardList f;
        for (int i = 0; i < state.range(0); ++i) f.PushTail("test");
    }
}
BENCHMARK(BM_ForwardListPushTail)->Arg(1000);

static void BM_DoublyListPushTail(benchmark::State& state) {
    for (auto _ : state) {
        DoublyList d;
        for (int i = 0; i < state.range(0); ++i) d.PushTail("test");
    }
}
BENCHMARK(BM_DoublyListPushTail)->Arg(1000);

static void BM_QueuePush(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < state.range(0); ++i) q.Push("test");
    }
}
BENCHMARK(BM_QueuePush)->Arg(1000);

static void BM_HashTableAdd(benchmark::State& state) {
    for (auto _ : state) {
        HashTable h(10007, 1);
        for (int i = 0; i < state.range(0); ++i) h.Add("key" + std::to_string(i));
    }
}
BENCHMARK(BM_HashTableAdd)->Arg(1000);

static void BM_AVLTreeInsert(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree t;
        for (int i = 0; i < state.range(0); ++i) t.Push(std::to_string(i));
    }
}
BENCHMARK(BM_AVLTreeInsert)->Arg(1000);

BENCHMARK_MAIN();