use crate::container::Container;
use std::any::Any;

pub struct HashTable {
    table: Vec<Option<String>>,
    capacity: usize,
    size: usize,
    method: i32,
}

impl HashTable {
    pub fn new(cap: usize, m: i32) -> Self {
        HashTable { table: vec![None; cap], capacity: cap, size: 0, method: m }
    }

    fn hash1(&self, key: &str) -> usize {
        let mut h: usize = 0;
        for c in key.bytes() {
            h = h.wrapping_mul(31).wrapping_add(c as usize);
        }
        h % self.capacity
    }

    fn hash2(&self, key: &str) -> usize {
        let mut h: usize = 0;
        for c in key.bytes() {
            h = h.wrapping_mul(37).wrapping_add(c as usize);
        }
        let step = (self.capacity - 1) - (h % (self.capacity - 1));
        if step == 0 { 1 } else { step }
    }

    pub fn add(&mut self, key: String) {
        if self.size >= self.capacity { return; }
        let mut idx = self.hash1(&key);
        let step = if self.method == 2 { self.hash2(&key) } else { 1 };
        let start_idx = idx;

        while let Some(ref k) = self.table[idx] {
            if k == &key { return; }
            idx = (idx + step) % self.capacity;
            if idx == start_idx { return; }
        }

        self.table[idx] = Some(key);
        self.size += 1;
    }

    pub fn contains(&self, key: &str) -> bool {
        let mut idx = self.hash1(key);
        let step = if self.method == 2 { self.hash2(key) } else { 1 };
        let start_idx = idx;

        while let Some(ref k) = self.table[idx] {
            if k == key { return true; }
            idx = (idx + step) % self.capacity;
            if idx == start_idx { break; }
        }
        false
    }

    pub fn remove(&mut self, key: &str) {
        let mut idx = self.hash1(key);
        let step = if self.method == 2 { self.hash2(key) } else { 1 };
        let start_idx = idx;

        while let Some(ref k) = self.table[idx] {
            if k == key {
                self.table[idx] = None;
                self.size -= 1;
                return;
            }
            idx = (idx + step) % self.capacity;
            if idx == start_idx { break; }
        }
    }

    pub fn print(&self) {
        for k in &self.table {
            if let Some(s) = k {
                print!("{} ", s);
            }
        }
        println!();
    }

    pub fn length_of_longest_substring(&mut self, s: &str) -> usize {
        self.table = vec![None; self.capacity];
        self.size = 0;
        let mut max_len = 0;
        let mut left = 0;
        let chars: Vec<char> = s.chars().collect();

        for right in 0..chars.len() {
            let c_str = chars[right].to_string();
            while self.contains(&c_str) {
                let l_str = chars[left].to_string();
                self.remove(&l_str);
                left += 1;
            }
            self.add(c_str);
            if right - left + 1 > max_len {
                max_len = right - left + 1;
            }
        }
        max_len
    }

    pub fn save_text(&self, path: &str) {
        let mut out = String::new();
        out.push_str(&format!("{}\n", self.size));
        for k in &self.table {
            if let Some(s) = k {
                out.push_str(&format!("{}\n", s));
            }
        }
        std::fs::write(path, out).unwrap();
    }

    pub fn load_text(path: &str) -> Self {
        let content = std::fs::read_to_string(path).unwrap_or_default();
        let mut lines = content.lines();
        let n: usize = lines.next().unwrap_or("0").parse().unwrap_or(0);
        let mut h = HashTable::new(10007, 1);
        for _ in 0..n {
            if let Some(line) = lines.next() {
                h.add(line.to_string());
            }
        }
        h
    }
}

impl Container for HashTable {
    fn as_any(&self) -> &dyn Any { self }
    fn as_any_mut(&mut self) -> &mut dyn Any { self }
}

#[cfg(test)]
mod tests {
    use super::*;

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
}