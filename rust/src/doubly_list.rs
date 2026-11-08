use crate::container::Container;
use std::any::Any;

struct Node {
    data: String,
    next: Option<Box<Node>>,
    prev: *mut Node,
}

pub struct DoublyList {
    head: Option<Box<Node>>,
    tail: *mut Node,
    size: usize,
}

impl DoublyList {
    pub fn new() -> Self {
        DoublyList { head: None, tail: std::ptr::null_mut(), size: 0 }
    }

    pub fn push(&mut self, value: String) {
        let mut n = Box::new(Node {
            data: value,
            next: self.head.take(),
            prev: std::ptr::null_mut(),
        });
        let raw = &mut *n as *mut Node;
        if let Some(ref mut old_head) = n.next {
            old_head.prev = raw;
        } else {
            self.tail = raw;
        }
        self.head = Some(n);
        self.size += 1;
    }

    pub fn push_tail(&mut self, value: String) {
        let mut n = Box::new(Node {
            data: value,
            next: None,
            prev: self.tail,
        });
        let raw = &mut *n as *mut Node;
        if self.tail.is_null() {
            self.head = Some(n);
        } else {
            unsafe { (*self.tail).next = Some(n); }
        }
        self.tail = raw;
        self.size += 1;
    }

    pub fn push_before(&mut self, target: &str, value: String) {
        if self.head.is_none() { println!("Список пуст"); return; }
        if self.head.as_ref().unwrap().data == target { self.push(value); return; }

        let mut cur = self.head.as_mut().unwrap();
        while let Some(next) = cur.next.as_mut() {
            if next.data == target {
                let mut new_node = Box::new(Node {
                    data: value,
                    next: cur.next.take(),
                    prev: &mut **cur as *mut Node,
                });
                let raw = &mut *new_node as *mut Node;
                if let Some(ref mut nn) = new_node.next {
                    nn.prev = raw;
                } else {
                    self.tail = raw;
                }
                cur.next = Some(new_node);
                self.size += 1;
                return;
            }
            cur = cur.next.as_mut().unwrap();
        }
        println!("Не найдено");
    }

    pub fn push_after(&mut self, target: &str, value: String) {
        let mut cur = self.head.as_mut();
        while let Some(node) = cur {
            if node.data == target {
                if node.next.is_none() { self.push_tail(value); return; }
                let mut new_node = Box::new(Node {
                    data: value,
                    next: node.next.take(),
                    prev: &mut **node as *mut Node,
                });
                let raw = &mut *new_node as *mut Node;
                if let Some(ref mut nn) = new_node.next {
                    nn.prev = raw;
                }
                node.next = Some(new_node);
                self.size += 1;
                return;
            }
            cur = node.next.as_mut();
        }
        println!("Не найдено");
    }

    pub fn pop(&mut self) -> Option<String> {
        if self.head.is_none() { println!("Список пуст"); return None; }
        let old = self.head.take().unwrap();
        if let Some(ref next) = old.next {
            let np = next.as_ref() as *const Node as *mut Node;
            unsafe { (*np).prev = std::ptr::null_mut(); }
        } else {
            self.tail = std::ptr::null_mut();
        }
        self.head = old.next;
        self.size -= 1;
        Some(old.data)
    }

    pub fn pop_tail(&mut self) -> Option<String> {
        if self.tail.is_null() { println!("Список пуст"); return None; }
        unsafe {
            let data = (*self.tail).data.clone();
            let prev = (*self.tail).prev;
            if prev.is_null() {
                self.head = None;
                self.tail = std::ptr::null_mut();
            } else {
                (*prev).next = None;
                self.tail = prev;
            }
            self.size -= 1;
            Some(data)
        }
    }

    pub fn pop_before(&mut self, target: &str) -> Option<String> {
        if self.head.is_none() || self.head.as_ref().unwrap().next.is_none() {
            println!("Нечего удалять"); return None;
        }
        if self.head.as_ref().unwrap().next.as_ref().unwrap().data == target {
            return self.pop();
        }
        let mut cur = self.head.as_mut().unwrap();
        while let Some(next) = cur.next.as_mut() {
            if let Some(nn) = next.next.as_ref() {
                if nn.data == target {
                    let removed = cur.next.take().unwrap();
                    cur.next = removed.next;
                    self.size -= 1;
                    return Some(removed.data);
                }
            }
            cur = cur.next.as_mut().unwrap();
        }
        println!("Не найдено");
        None
    }

    pub fn pop_after(&mut self, target: &str) -> Option<String> {
        let mut cur = self.head.as_mut();
        while let Some(node) = cur {
            if node.data == target {
                if node.next.is_none() { println!("Нечего удалять"); return None; }
                let removed = node.next.take().unwrap();
                node.next = removed.next;
                self.size -= 1;
                return Some(removed.data);
            }
            cur = node.next.as_mut();
        }
        println!("Не найдено");
        None
    }

    pub fn pop_value(&mut self, value: &str) -> Option<String> {
        if self.head.is_none() { println!("Список пуст"); return None; }
        if self.head.as_ref().unwrap().data == value { return self.pop(); }
        let mut cur_ptr: *mut Node = &mut **self.head.as_mut().unwrap();
        unsafe {
            while (*cur_ptr).next.is_some() {
                let next_ptr = (*cur_ptr).next.as_mut().unwrap().as_mut() as *mut Node;
                if (*next_ptr).data == value {
                    let nn = (*next_ptr).next.take();
                    if let Some(ref x) = nn {
                        let xp = x.as_ref() as *const Node as *mut Node;
                        (*xp).prev = cur_ptr;
                    } else {
                        self.tail = cur_ptr;
                    }
                    (*cur_ptr).next = nn;
                    self.size -= 1;
                    let removed = Box::from_raw(next_ptr);
                    return Some(removed.data);
                }
                cur_ptr = next_ptr;
            }
        }
        println!("Не найдено");
        None
    }

    pub fn find(&self, value: &str) -> bool {
        let mut cur = self.head.as_ref();
        while let Some(n) = cur {
            if n.data == value { return true; }
            cur = n.next.as_ref();
        }
        false
    }

    pub fn print(&self) {
        let mut cur = self.head.as_ref();
        while let Some(n) = cur { print!("{} ", n.data); cur = n.next.as_ref(); }
        println!();
    }

    pub fn print_reverse(&self) {
        if self.tail.is_null() { println!(); return; }
        unsafe {
            let mut cur = self.tail;
            while !cur.is_null() {
                print!("{} ", (*cur).data);
                cur = (*cur).prev;
            }
        }
        println!();
    }

    pub fn print_every_second(&self) {
        let mut cur = self.head.as_ref();
        let mut i = 0;
        while let Some(n) = cur {
            if i % 2 == 0 { print!("{} ", n.data); }
            cur = n.next.as_ref();
            i += 1;
        }
        println!();
    }

    pub fn get_all(&self) -> Vec<String> {
        let mut res = Vec::new();
        let mut cur = self.head.as_ref();
        while let Some(n) = cur { res.push(n.data.clone()); cur = n.next.as_ref(); }
        res
    }

    pub fn save_text(&self, path: &str) {
        let items = self.get_all();
        let mut out = String::new();
        out.push_str(&format!("{}\n", items.len()));
        for x in items { out.push_str(&format!("{}\n", x)); }
        std::fs::write(path, out).unwrap();
    }

    pub fn load_text(path: &str) -> Self {
        let content = std::fs::read_to_string(path).unwrap_or_default();
        let mut lines = content.lines();
        let n: usize = lines.next().unwrap_or("0").parse().unwrap_or(0);
        let mut d = DoublyList::new();
        for _ in 0..n { if let Some(line) = lines.next() { d.push_tail(line.to_string()); } }
        d
    }
}

impl Container for DoublyList {
    fn as_any(&self) -> &dyn Any { self }
    fn as_any_mut(&mut self) -> &mut dyn Any { self }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_push_and_pop() {
        let mut dl = DoublyList::new();
        dl.push("A".to_string());
        dl.push_tail("B".to_string());
        assert!(dl.find("A"));
        assert!(dl.find("B"));
        dl.pop_tail();
        assert!(!dl.find("B"));
    }
}