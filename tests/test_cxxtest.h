#include <cxxtest/TestSuite.h>
#include "../Array/array.h"
#include "../Stack/stack.h"
#include "../Forward_list/forward_list.h"
#include "../Doubly_list/doubly_list.h"
#include "../Queue/queue.h"
#include "../HashTable/hash_table.h"
#include "../AVL_tree/avl_tree.h"

class Lab3CxxTestSuite : public CxxTest::TestSuite {
public:
    void testArrayPushAndFind() {
        Array a;
        a.Push("apple"); 
        a.Push("banana");
        TS_ASSERT_EQUALS(a.Size(), 2);
        TS_ASSERT(a.Find("apple"));
        TS_ASSERT(!a.Find("orange"));
    }

    void testArrayPushAtAndPopAt() {
        Array a;
        a.Push("a"); 
        a.Push("b");
        a.PushAt(1, "x");
        TS_ASSERT_EQUALS(a.Size(), 3);
        TS_ASSERT_EQUALS(a.GetAt(1), "x");
        
        a.PopAt(1);
        TS_ASSERT_EQUALS(a.Size(), 2);
    }

    void testArrayGetSetPop() {
        Array a;
        a.Push("x"); 
        a.SetAt(0, "y");
        TS_ASSERT_EQUALS(a.GetAt(0), "y");
        
        a.Pop();
        TS_ASSERT_EQUALS(a.Size(), 0);
    }

    void testArrayEdgeCases() {
        Array a;
        a.Pop(); 
        a.PopAt(0);
        TS_ASSERT_EQUALS(a.GetAt(0), "");
    }

    void testStackPushPop() {
        Stack s;
        s.Push("A"); 
        s.Push("B");
        TS_ASSERT(s.Find("A"));
        
        s.Pop();
        TS_ASSERT(!s.Find("B"));
    }

    void testStackXML() {
        Stack s;
        TS_ASSERT(s.ValidateXML("<a><b></b></a>"));
        TS_ASSERT(!s.ValidateXML("<a><b></a></b>"));
    }

    void testStackEdgeCases() {
        Stack s;
        s.Pop();
        TS_ASSERT(!s.Find("x"));
    }

    void testForwardListPushFind() {
        ForwardList f;
        f.Push("A"); 
        f.PushTail("B");
        TS_ASSERT(f.Find("A"));
        TS_ASSERT(f.Find("B"));
    }

    void testForwardListPushBeforeAfter() {
        ForwardList f;
        f.Push("A"); 
        f.Push("B");
        f.PushBefore("B", "X");
        f.PushAfter("A", "Y");
        TS_ASSERT(f.Find("X"));
        TS_ASSERT(f.Find("Y"));
    }

    void testForwardListPop() {
        ForwardList f;
        f.Push("A"); 
        f.PushTail("B");
        f.Pop();
        f.PopTail();
        TS_ASSERT(!f.Find("A"));
        TS_ASSERT(!f.Find("B"));
    }

    void testDoublyListPushPop() {
        DoublyList d;
        d.Push("A"); 
        d.PushTail("B");
        TS_ASSERT(d.Find("A"));
        
        d.PopTail();
        TS_ASSERT(!d.Find("B"));
    }

    void testDoublyListPushBeforeAfter() {
        DoublyList d;
        d.Push("A"); 
        d.PushTail("B");
        d.PushBefore("B", "X");
        d.PushAfter("A", "Y");
        TS_ASSERT(d.Find("X"));
        TS_ASSERT(d.Find("Y"));
    }

    void testQueuePushPop() {
        Queue q;
        q.Push("1"); 
        q.Push("2");
        TS_ASSERT(q.Find("1"));
        
        q.Pop();
        TS_ASSERT(!q.Find("1"));
    }

    void testHashTableAddContains() {
        HashTable h(10007, 1);
        h.Add("apple");
        TS_ASSERT(h.Contains("apple"));
        
        h.Remove("apple");
        TS_ASSERT(!h.Contains("apple"));
    }

    void testHashTableDoubleHash() {
        HashTable h(10007, 2);
        h.Add("apple"); 
        h.Add("banana");
        TS_ASSERT(h.Contains("apple"));
        TS_ASSERT(h.Contains("banana"));
    }

    void testHashTableLongestSubstring() {
        HashTable h(10007, 1);
        TS_ASSERT_EQUALS(h.LengthOfLongestSubstring("abcabcbb"), 3);
        TS_ASSERT_EQUALS(h.LengthOfLongestSubstring("bbbbb"), 1);
    }

    void testAVLTreeInsertFind() {
        AVLTree t;
        t.Push("10"); 
        t.Push("5");
        TS_ASSERT(t.Find("10"));
        TS_ASSERT(t.Find("5"));
        TS_ASSERT(!t.Find("15"));
    }

    void testAVLTreeHeight() {
        AVLTree t;
        t.Push("10"); 
        t.Push("5"); 
        t.Push("15");
        TS_ASSERT_EQUALS(t.GetHeight(), 2);
    }

    void testAVLTreePop() {
        AVLTree t;
        t.Push("10"); 
        t.Push("5"); 
        t.Push("15");
        t.PopValue("15");
        TS_ASSERT(!t.Find("15"));
    }
};