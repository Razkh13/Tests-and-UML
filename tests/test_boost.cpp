#define BOOST_TEST_MODULE Lab3_BoostTests
#include <boost/test/included/unit_test.hpp>
#include "../Array/array.h"
#include "../Stack/stack.h"
#include "../Forward_list/forward_list.h"
#include "../Doubly_list/doubly_list.h"
#include "../Queue/queue.h"
#include "../HashTable/hash_table.h"
#include "../AVL_tree/avl_tree.h"

BOOST_AUTO_TEST_SUITE(ArraySuite)

BOOST_AUTO_TEST_CASE(PushAndFind) {
    Array a;
    a.Push("apple");
    a.Push("banana");
    
    BOOST_CHECK_EQUAL(a.Size(), 2);
    BOOST_CHECK(a.Find("apple"));
    BOOST_CHECK(!a.Find("orange"));
}

BOOST_AUTO_TEST_CASE(PushAtAndPopAt) {
    Array a;
    a.Push("A");
    a.Push("B");
    a.PushAt(1, "X");
    
    BOOST_CHECK_EQUAL(a.Size(), 3);
    BOOST_CHECK_EQUAL(a.GetAt(1), "X");
    
    a.PopAt(1);
    BOOST_CHECK_EQUAL(a.Size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(StackSuite)

BOOST_AUTO_TEST_CASE(PushPop) {
    Stack s;
    s.Push("A");
    s.Push("B");
    
    BOOST_CHECK(s.Find("A"));
    
    s.Pop();
    BOOST_CHECK(!s.Find("B"));
    BOOST_CHECK(s.Find("A"));
}

BOOST_AUTO_TEST_CASE(XMLValidation) {
    Stack s;
    
    BOOST_CHECK(s.ValidateXML("<a><b></b></a>"));
    BOOST_CHECK(s.ValidateXML("<root></root>"));
    
    BOOST_CHECK(!s.ValidateXML("<a><b></a></b>"));
    BOOST_CHECK(!s.ValidateXML("<a><b>"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(ForwardListSuite)

BOOST_AUTO_TEST_CASE(PushAndPop) {
    ForwardList f;
    f.Push("A");
    f.PushTail("B");
    
    BOOST_CHECK(f.Find("A"));
    BOOST_CHECK(f.Find("B"));
    
    f.PopTail();
    BOOST_CHECK(!f.Find("B"));
    BOOST_CHECK(f.Find("A"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(DoublyListSuite)

BOOST_AUTO_TEST_CASE(PushAndPop) {
    DoublyList d;
    d.Push("A");
    d.PushTail("B");
    
    BOOST_CHECK(d.Find("A"));
    BOOST_CHECK(d.Find("B"));
    
    d.PopTail();
    BOOST_CHECK(!d.Find("B"));
    BOOST_CHECK(d.Find("A"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(QueueSuite)

BOOST_AUTO_TEST_CASE(PushAndPop) {
    Queue q;
    q.Push("1");
    q.Push("2");
    
    BOOST_CHECK(q.Find("1"));
    BOOST_CHECK(q.Find("2"));
    
    q.Pop();
    BOOST_CHECK(!q.Find("1"));
    BOOST_CHECK(q.Find("2"));
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(HashTableSuite)

BOOST_AUTO_TEST_CASE(AddContainsRemove) {
    HashTable h(10007, 1);
    
    h.Add("apple");
    BOOST_CHECK(h.Contains("apple"));
    
    h.Remove("apple");
    BOOST_CHECK(!h.Contains("apple"));
}

BOOST_AUTO_TEST_CASE(LongestSubstring) {
    HashTable h(10007, 1);
    BOOST_CHECK_EQUAL(h.LengthOfLongestSubstring("abcabcbb"), 3);
    BOOST_CHECK_EQUAL(h.LengthOfLongestSubstring("bbbbb"), 1);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(AVLTreeSuite)

BOOST_AUTO_TEST_CASE(InsertAndHeight) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("15");
    
    BOOST_CHECK(t.Find("5"));
    BOOST_CHECK(t.Find("15"));
    BOOST_CHECK(!t.Find("20"));
    
    BOOST_CHECK_EQUAL(t.GetHeight(), 2);
}

BOOST_AUTO_TEST_CASE(Rotations) {
    AVLTree t1;
    t1.Push("30"); t1.Push("20"); t1.Push("10");
    BOOST_CHECK_EQUAL(t1.GetHeight(), 2);
    
    AVLTree t2;
    t2.Push("10"); t2.Push("20"); t2.Push("30");
    BOOST_CHECK_EQUAL(t2.GetHeight(), 2);
}

BOOST_AUTO_TEST_CASE(PopValue) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("15");
    
    t.PopValue("5");
    BOOST_CHECK(!t.Find("5"));
    BOOST_CHECK(t.Find("10"));
    BOOST_CHECK(t.Find("15"));
}

BOOST_AUTO_TEST_SUITE_END()