use criterion::{criterion_group, criterion_main, Criterion, BenchmarkId};
use rust::array::Array;
use rust::stack::Stack;
use rust::forward_list::ForwardList;
use rust::doubly_list::DoublyList;
use rust::queue::Queue;
use rust::hash_table::HashTable;
use rust::tree::BST;

fn bench_array(c: &mut Criterion) {
    let mut group = c.benchmark_group("Array");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut a = Array::new();
                for i in 0..size {
                    a.push(format!("test{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_stack(c: &mut Criterion) {
    let mut group = c.benchmark_group("Stack");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut s = Stack::new();
                for i in 0..size {
                    s.push(format!("test{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_forward_list(c: &mut Criterion) {
    let mut group = c.benchmark_group("ForwardList");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut f = ForwardList::new();
                for i in 0..size {
                    f.push_tail(format!("test{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_doubly_list(c: &mut Criterion) {
    let mut group = c.benchmark_group("DoublyList");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut d = DoublyList::new();
                for i in 0..size {
                    d.push_tail(format!("test{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_queue(c: &mut Criterion) {
    let mut group = c.benchmark_group("Queue");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut q = Queue::new();
                for i in 0..size {
                    q.push(format!("test{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_hash_table(c: &mut Criterion) {
    let mut group = c.benchmark_group("HashTable");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut h = HashTable::new(10007, 1);
                for i in 0..size {
                    h.add(format!("key{}", i));
                }
            });
        });
    }
    group.finish();
}

fn bench_tree(c: &mut Criterion) {
    let mut group = c.benchmark_group("BST");
    for size in [1000, 10000].iter() {
        group.bench_with_input(BenchmarkId::from_parameter(size), size, |b, &size| {
            b.iter(|| {
                let mut t = BST::new();
                for i in 0..size {
                    t.insert(format!("{}", i));
                }
            });
        });
    }
    group.finish();
}

criterion_group!(
    benches,
    bench_array,
    bench_stack,
    bench_forward_list,
    bench_doubly_list,
    bench_queue,
    bench_hash_table,
    bench_tree
);
criterion_main!(benches);