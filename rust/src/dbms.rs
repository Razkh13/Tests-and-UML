use std::collections::HashMap;
use crate::container::Container;
use crate::stack::Stack;
use crate::array::Array;
use crate::forward_list::ForwardList;
use crate::hash_table::HashTable;
use crate::queue::Queue;
use crate::tree::BST;
use crate::doubly_list::DoublyList;

pub struct DBMS {
    pub containers: HashMap<String, Box<dyn Container>>,
    pub hash_tables: HashMap<String, HashTable>,
    pub queues: HashMap<String, Queue>,
}

impl DBMS {
    pub fn new() -> Self {
        DBMS { containers: HashMap::new(), hash_tables: HashMap::new(), queues: HashMap::new() }
    }

    pub fn execute(&mut self, query: &str) {
        let parts: Vec<&str> = query.split_whitespace().collect();
        if parts.is_empty() { return; }
        let cmd = parts[0];

        if cmd == "MSAVE" && parts.len() >= 3 {
            let path = parts[2];
            if let Some(c) = self.containers.get(parts[1]) {
                if let Some(a) = c.as_any().downcast_ref::<Array>() { a.save_text(path); }
                else if let Some(f) = c.as_any().downcast_ref::<ForwardList>() { f.save_text(path); }
                else if let Some(d) = c.as_any().downcast_ref::<DoublyList>() { d.save_text(path); }
                else if let Some(s) = c.as_any().downcast_ref::<Stack>() { s.save_text(path); }
                else if let Some(t) = c.as_any().downcast_ref::<BST>() { t.save_text(path); }
            } else if let Some(q) = self.queues.get(parts[1]) { q.save_text(path); }
            else if let Some(h) = self.hash_tables.get(parts[1]) { h.save_text(path); }
            return;
        }
        if cmd == "MLOAD" && parts.len() >= 3 {
            let path = parts[2];
            let prefix = parts[1].chars().next().unwrap_or(' ');
            let boxed: Box<dyn Container> = match prefix {
                'M' => Box::new(Array::load_text(path)),
                'F' => Box::new(ForwardList::load_text(path)),
                'L' => Box::new(DoublyList::load_text(path)),
                'S' => Box::new(Stack::load_text(path)),
                'T' => Box::new(BST::load_text(path)),
                _ => { println!("Неизвестный тип"); return; }
            };
            self.containers.insert(parts[1].to_string(), boxed);
            return;
        }

        if cmd == "HTADD" && parts.len() >= 4 {
            let name = parts[1];
            let method = parts[2].parse().unwrap_or(1);
            let val = parts[3].to_string();
            let ht = self.hash_tables.entry(name.to_string()).or_insert_with(|| HashTable::new(10007, method));
            ht.add(val);
            ht.print();
            return;
        }
        if cmd == "HTGET" && parts.len() >= 3 {
            let name = parts[1];
            let val = parts[2];
            if let Some(ht) = self.hash_tables.get(name) {
                if ht.contains(val) { println!("TRUE"); }
                else { println!("FALSE"); }
            } else { println!("FALSE"); }
            return;
        }
        if cmd == "HTLONGEST" && parts.len() >= 2 {
            let mut ht = HashTable::new(10007, 1);
            println!("{}", ht.length_of_longest_substring(parts[1]));
            return;
        }
        if cmd == "SVALIDATE" && parts.len() >= 3 {
            println!("{}", if Stack::validate_xml(parts[2]) { "TRUE" } else { "FALSE" });
            return;
        }
        if cmd == "SFIXXML" && parts.len() >= 3 {
            println!("{}", Stack::fix_xml(parts[2]));
            return;
        }

        let name = if parts.len() > 1 { parts[1] } else { "" };
        let prefix = cmd.chars().next().unwrap_or(' ');

        if prefix == 'S' && cmd == "SPUSH" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(Stack::new()));
            if let Some(s) = c.as_any_mut().downcast_mut::<Stack>() { s.push(parts[2].to_string()); s.print(); }
        }
        else if cmd == "SPRINT" && parts.len() >= 2 {
            if let Some(c) = self.containers.get(name) {
                if let Some(s) = c.as_any().downcast_ref::<Stack>() { s.print(); }
            }
        }
        else if prefix == 'M' && cmd == "MPUSH" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(Array::new()));
            if let Some(a) = c.as_any_mut().downcast_mut::<Array>() { a.push(parts[2].to_string()); a.print(); }
        }
        else if cmd == "MSUBARRAYS" && parts.len() >= 2 {
            if let Some(c) = self.containers.get(name) {
                if let Some(a) = c.as_any().downcast_ref::<Array>() { a.print_subarrays(); }
            }
        }
        else if prefix == 'F' && cmd == "FPUSH" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(ForwardList::new()));
            if let Some(f) = c.as_any_mut().downcast_mut::<ForwardList>() { f.push_tail(parts[2].to_string()); }
        }
        else if cmd == "FPRINT" && parts.len() >= 2 {
            if let Some(c) = self.containers.get(name) {
                if let Some(f) = c.as_any().downcast_ref::<ForwardList>() {
                    for x in f.get_all() { print!("{} ", x); }
                    println!();
                }
            }
        }
        else if prefix == 'Q' && cmd == "QPUSH" && parts.len() >= 3 {
            let q = self.queues.entry(name.to_string()).or_insert_with(Queue::new);
            q.push(parts[2].to_string());
            q.print();
        }
        else if cmd == "QPRINT" && parts.len() >= 2 {
            if let Some(q) = self.queues.get(name) { q.print(); }
        }
        else if prefix == 'T' && cmd == "TINSERT" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(BST::new()));
            if let Some(t) = c.as_any_mut().downcast_mut::<BST>() { t.insert(parts[2].to_string()); }
        }
        else if cmd == "THEIGHT" && parts.len() >= 2 {
            if let Some(c) = self.containers.get(name) {
                if let Some(t) = c.as_any().downcast_ref::<BST>() { println!("{}", t.height()); }
            }
        }
        else if prefix == 'L' && cmd == "LPUSH" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(DoublyList::new()));
            if let Some(d) = c.as_any_mut().downcast_mut::<DoublyList>() { d.push(parts[2].to_string()); d.print(); }
        }
        else if cmd == "LPUSHTAIL" && parts.len() >= 3 {
            let c = self.containers.entry(name.to_string()).or_insert_with(|| Box::new(DoublyList::new()));
            if let Some(d) = c.as_any_mut().downcast_mut::<DoublyList>() { d.push_tail(parts[2].to_string()); d.print(); }
        }
        else if cmd == "LPRINT" && parts.len() >= 2 {
            if let Some(c) = self.containers.get(name) {
                if let Some(d) = c.as_any().downcast_ref::<DoublyList>() { d.print(); }
            }
        }
        else {
            println!("Неизвестная команда");
        }
    }
}