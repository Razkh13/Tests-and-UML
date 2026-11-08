use crate::container::Container;
use std::any::Any;

struct TNode {
    data: String,
    left: Option<Box<TNode>>,
    right: Option<Box<TNode>>,
    height: i32,
}

pub struct BST {
    root: Option<Box<TNode>>,
}

impl BST {
    pub fn new() -> Self { BST { root: None } }
    
    pub fn insert(&mut self, val: String) {
        fn ins(n: &mut Option<Box<TNode>>, v: String) {
            if n.is_none() { *n = Some(Box::new(TNode { data: v, left: None, right: None, height: 1 })); return; }
            let node = n.as_mut().unwrap();
            if v < node.data { ins(&mut node.left, v); }
            else if v > node.data { ins(&mut node.right, v); }
            
            let lh = node.left.as_ref().map_or(0, |x| x.height);
            let rh = node.right.as_ref().map_or(0, |x| x.height);
            node.height = 1 + std::cmp::max(lh, rh);
        }
        ins(&mut self.root, val);
    }
    pub fn height(&self) -> i32 { self.root.as_ref().map_or(0, |n| n.height) }

    pub fn save_text(&self, path: &str) {
        let mut items = Vec::new();
        fn collect(n: &Option<Box<TNode>>, items: &mut Vec<String>) {
            if let Some(node) = n {
                items.push(node.data.clone());
                collect(&node.left, items);
                collect(&node.right, items);
            }
        }
        collect(&self.root, &mut items);
        let mut out = String::new();
        out.push_str(&format!("{}\n", items.len()));
        for x in items { out.push_str(&format!("{}\n", x)); }
        std::fs::write(path, out).unwrap();
    }

    pub fn load_text(path: &str) -> Self {
        let content = std::fs::read_to_string(path).unwrap_or_default();
        let mut lines = content.lines();
        let n: usize = lines.next().unwrap_or("0").parse().unwrap_or(0);
        let mut t = BST::new();
        for _ in 0..n { if let Some(line) = lines.next() { t.insert(line.to_string()); } }
        t
    }
}

impl Container for BST {
    fn as_any(&self) -> &dyn Any { self }
    fn as_any_mut(&mut self) -> &mut dyn Any { self }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_insert_and_height() {
        let mut t = BST::new();
        t.insert("10".to_string());
        t.insert("5".to_string());
        t.insert("15".to_string());
        assert_eq!(t.height(), 3);
    }
}