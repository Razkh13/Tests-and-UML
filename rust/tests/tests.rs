use rust::stack::Stack;
use rust::array::Array;
use rust::forward_list::ForwardList;
use rust::queue::Queue;
use rust::hash_table::HashTable;
use rust::tree::BST;
use rust::doubly_list::DoublyList;
use rust::dbms::DBMS;
use rust::container::Container;

#[test]
fn test_array_push_and_find() {
    let mut a = Array::new();
    a.push("apple".to_string());
    a.push("banana".to_string());
    assert_eq!(a.data.len(), 2);
    assert!(a.find("apple"));
    assert!(!a.find("orange"));
}

#[test]
fn test_array_full() {
    let mut a = Array::new();
    a.push("x".to_string());
    a.push("y".to_string());
    a.print();
    a.print_subarrays();
    a.save_text("tmp_arr.txt");
    let loaded = Array::load_text("tmp_arr.txt");
    assert_eq!(loaded.data.len(), 2);
    std::fs::remove_file("tmp_arr.txt").unwrap();
}

#[test]
fn test_dbms_full_coverage() {
    let mut db = DBMS::new();
    db.execute("MPUSH arr1 x");
    db.execute("MPUSH arr1 y");
    db.execute("MSUBARRAYS arr1");
    db.execute("MSAVE arr1 tmp_demo.txt");
    db.execute("MLOAD arr2 tmp_demo.txt");
    db.execute("MLOAD unknown_type path");
    db.execute("SPUSH s1 A");
    db.execute("SPRINT s1");
    db.execute("SVALIDATE <a></a>");
    db.execute("SFIXXML <a><b></x></a>");
    db.execute("FPUSH f1 A");
    db.execute("FPRINT f1");
    db.execute("LPUSH l1 A");
    db.execute("LPUSHTAIL l1 B");
    db.execute("LPRINT l1");
    db.execute("QPUSH q1 1");
    db.execute("QPRINT q1");
    db.execute("TINSERT t1 10");
    db.execute("THEIGHT t1");
    db.execute("HTADD h1 1 apple");
    db.execute("HTGET h1 apple");
    db.execute("HTLONGEST abcabcbb");
    db.execute("UNKNOWN_CMD");
    std::fs::remove_file("tmp_demo.txt").unwrap_or(());
}

#[test]
fn test_doubly_list_push_and_pop() {
    let mut dl = DoublyList::new();
    dl.push("A".to_string());
    dl.push_tail("B".to_string());
    assert!(dl.find("A"));
    assert!(dl.find("B"));
    dl.pop_tail();
    assert!(!dl.find("B"));
}

#[test]
fn test_doubly_list_full() {
    let mut d = DoublyList::new();
    assert_eq!(d.pop(), None);
    assert_eq!(d.pop_tail(), None);
    assert_eq!(d.pop_before("none"), None);
    assert_eq!(d.pop_after("none"), None);
    assert_eq!(d.pop_value("none"), None);
    d.push("A".to_string());
    d.push_tail("C".to_string());
    d.push_before("C", "B".to_string());
    d.push_after("A", "A2".to_string());
    d.print();
    d.print_reverse();
    d.print_every_second();
    let _ = d.pop_value("B");
    let _ = d.pop_before("A");
    let _ = d.pop_after("C");
    let _ = d.pop_value("C");
    d.pop();
    d.pop_tail();
    d.save_text("tmp_dl.txt");
    let loaded = DoublyList::load_text("tmp_dl.txt");
    assert!(!loaded.find("A"));
    assert!(!loaded.find("C"));
    assert!(!loaded.find("B"));
    std::fs::remove_file("tmp_dl.txt").unwrap();
}

#[test]
fn test_pop_value_edges() {
    let mut d = DoublyList::new();
    d.push_tail("A".to_string());
    let _ = d.pop_value("A");
    d.push_tail("B".to_string());
    d.push_tail("C".to_string());
    let _ = d.pop_value("C");
    let _ = d.pop_value("none");
}

#[test]
fn test_binary_serialization() {
    let mut d = DoublyList::new();
    d.push_tail("A".to_string());
    d.push_tail("B".to_string());
    d.save_binary("tmp_dl.bin");
    let loaded = DoublyList::load_binary("tmp_dl.bin");
    assert!(loaded.find("A"));
    assert!(loaded.find("B"));
    std::fs::remove_file("tmp_dl.bin").unwrap();
}

#[test]
fn test_add_and_contains() {
    let mut h = HashTable::new(10007, 1);
    h.add("apple".to_string());
    assert!(h.contains("apple"));
    h.remove("apple");
    assert!(!h.contains("apple"));
}

#[test]
fn test_longest_substring() {
    let mut h = HashTable::new(10007, 1);
    assert_eq!(h.length_of_longest_substring("abcabcbb"), 3);
}

#[test]
fn test_hash_table_full() {
    let mut h = HashTable::new(10007, 1);
    h.add("a".to_string());
    h.add("a".to_string()); 
    h.print();
    h.save_text("tmp_ht.txt");
    let loaded = HashTable::load_text("tmp_ht.txt");
    assert!(loaded.contains("a"));
    std::fs::remove_file("tmp_ht.txt").unwrap();

    let mut h2 = HashTable::new(10007, 2);
    h2.add("apple".to_string());
    h2.add("banana".to_string());
    assert!(h2.contains("apple"));
    assert!(!h2.contains("orange"));
    h2.remove("apple");
    h2.remove("none");
    assert!(!h2.contains("apple"));
}

#[test]
fn test_hash_table_container_trait() {
    let h = HashTable::new(10007, 1);
    let _any_ref = h.as_any();
        
    let mut h_mut = HashTable::new(10007, 1);
    let _any_mut_ref = h_mut.as_any_mut();
}


#[test]
fn test_push_and_pop() {
    let mut q = Queue::new();
    q.push("1".to_string());
    q.push("2".to_string());
    assert!(q.find("1"));
    q.pop();
    assert!(!q.find("1"));
}

#[test]
fn test_queue_full() {
    let mut q = Queue::new();
    assert_eq!(q.pop(), None); 
    q.push("1".to_string());
    q.push("2".to_string());
    q.print();
    q.save_text("tmp_q.txt");
    let loaded = Queue::load_text("tmp_q.txt");
    assert!(loaded.find("1"));
    std::fs::remove_file("tmp_q.txt").unwrap();
}

#[test]
    fn test_queue_container_trait() {
    let q = Queue::new();
    let _any_ref = q.as_any();
        
    let mut q_mut = Queue::new();
    let _any_mut_ref = q_mut.as_any_mut();
}

#[test]
fn test_stack_push_and_pop() {
    let mut s = Stack::new();
    s.push("A".to_string());
    s.push("B".to_string());
    assert!(s.find("A"));
    s.pop();
    assert!(!s.find("B"));
}

#[test]
fn test_validate_xml() {
    assert!(Stack::validate_xml("<a><b></b></a>"));
    assert!(!Stack::validate_xml("<a><b></a></b>"));
}

#[test]
fn test_stack_full() {
    let mut s = Stack::new();
    assert!(s.is_empty());
    s.push("A".to_string());
    s.push("B".to_string());
    assert!(!s.is_empty());
    assert_eq!(s.peek(), Some(&"B".to_string()));
    s.print();
    s.save_text("tmp_stack.txt");
    let loaded = Stack::load_text("tmp_stack.txt");
    assert_eq!(loaded.data.len(), 2);
    std::fs::remove_file("tmp_stack.txt").unwrap();
    assert_eq!(Stack::fix_xml("<a><b></x></a>"), "<a><x></x></a>");
    assert_eq!(Stack::fix_xml("invalid"), "Incorrect");
}

#[test]
fn test_insert_and_height() {
    let mut t = BST::new();
    t.insert("10".to_string());
    t.insert("5".to_string());
    t.insert("15".to_string());
    assert_eq!(t.height(), 3);
}

#[test]
fn test_tree_full() {
    let mut t = BST::new();
    t.insert("10".to_string());
    t.insert("5".to_string());
    t.insert("15".to_string());
    t.insert("10".to_string());
    t.save_text("tmp_tree.txt");
    let loaded = BST::load_text("tmp_tree.txt");
    assert_eq!(loaded.height(), 3);
    std::fs::remove_file("tmp_tree.txt").unwrap();
}


#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_push_and_find() {
        let mut f = ForwardList::new();
        f.push_tail("A".to_string());
        f.push_tail("B".to_string());
        assert!(f.find("A"));
        assert!(f.find("B"));
    }
    #[test]
    fn test_forward_list_full() {
        let mut f = ForwardList::new();
        assert_eq!(f.pop_value("none"), None); 
        f.push_tail("A".to_string());
        f.push_tail("B".to_string());
        f.push_tail("C".to_string());
        f.pop_value("B"); 
        f.pop_value("A"); 
        f.pop_value("C"); 
        f.push_tail("D".to_string());
        assert!(!f.get_all().is_empty());
        f.save_text("tmp_fl.txt");
        let loaded = ForwardList::load_text("tmp_fl.txt");
        assert!(loaded.find("D"));
        std::fs::remove_file("tmp_fl.txt").unwrap();
    }
}