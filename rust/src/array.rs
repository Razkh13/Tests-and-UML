use crate::container::Container;
use std::any::Any;

pub struct Array {
    pub data: Vec<String>,
}

impl Array {
    pub fn new() -> Self { Array { data: Vec::new() } }
    pub fn push(&mut self, v: String) { self.data.push(v); }
    pub fn print(&self) { for x in &self.data { print!("{} ", x); } println!(); }
    pub fn find(&self, v: &str) -> bool { self.data.iter().any(|x| x == v) }

    pub fn print_subarrays(&self) {
        let n = self.data.len();
        print!("[");
        let mut first_global = true;
        for len in 0..=n {
            for mask in 0..(1 << n) {
                let mut count = 0;
                for i in 0..n { if (mask & (1 << i)) != 0 { count += 1; } }
                if count == len {
                    if !first_global { print!(", "); }
                    first_global = false;
                    print!("{{");
                    let mut first_inner = true;
                    for i in 0..n {
                        if (mask & (1 << i)) != 0 {
                            if !first_inner { print!(", "); }
                            print!("{}", self.data[i]);
                            first_inner = false;
                        }
                    }
                    print!("}}");
                }
            }
        }
        println!("]");
    }

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
        let mut data = Vec::new();
        for _ in 0..n { if let Some(line) = lines.next() { data.push(line.to_string()); } }
        Array { data }
    }
}

impl Container for Array {
    fn as_any(&self) -> &dyn Any { self }
    fn as_any_mut(&mut self) -> &mut dyn Any { self }
}