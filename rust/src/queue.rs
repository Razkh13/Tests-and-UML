use std::collections::VecDeque;
use crate::container::Container;
use std::any::Any;

pub struct Queue {
    pub data: VecDeque<String>,
}

impl Queue {
    pub fn new() -> Self { Queue { data: VecDeque::new() } }
    pub fn push(&mut self, value: String) { self.data.push_back(value); }
    pub fn pop(&mut self) -> Option<String> {
        if self.data.is_empty() { println!("Очередь пуста"); return None; }
        self.data.pop_front()
    }
    pub fn find(&self, value: &str) -> bool { self.data.iter().any(|x| x == value) }
    pub fn print(&self) { for x in &self.data { print!("{} ", x); } println!(); }

    pub fn save_text(&self, path: &str) {
        let mut out = String::new();
        out.push_str(&format!("{}\n", self.data.len()));
        for x in &self.data { out.push_str(&format!("{}\n", x)); }
        std::fs::write(path, out).unwrap();
    }

    pub fn load_text(path: &str) -> Self {
        let content = std::fs::read_to_string(path).unwrap_or_default();
        let mut lines = content.lines();
        let n: usize = lines.next().unwrap_or("0").parse().unwrap_or(0);
        let mut data = VecDeque::new();
        for _ in 0..n { if let Some(line) = lines.next() { data.push_back(line.to_string()); } }
        Queue { data }
    }
}

impl Container for Queue {
    fn as_any(&self) -> &dyn Any { self }
    fn as_any_mut(&mut self) -> &mut dyn Any { self }
}
