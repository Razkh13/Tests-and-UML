#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "../Array/array.h"
#include "../Stack/stack.h"
#include "../Forward_list/forward_list.h"
#include "../Doubly_list/doubly_list.h"
#include "../Queue/queue.h"
#include "../HashTable/hash_table.h"
#include "../AVL_tree/avl_tree.h"

TEST(ArrayTest, PushSingle) {
    Array a;
    a.Push("apple");
    EXPECT_EQ(a.Size(), 1);
    EXPECT_TRUE(a.Find("apple"));
}

TEST(ArrayTest, PushMultiple) {
    Array a;
    a.Push("apple");
    a.Push("banana");
    a.Push("cherry");
    EXPECT_EQ(a.Size(), 3);
    EXPECT_TRUE(a.Find("banana"));
}

TEST(ArrayTest, FindAbsent) {
    Array a;
    a.Push("apple");
    EXPECT_FALSE(a.Find("orange"));
}

TEST(ArrayTest, PushAtBegin) {
    Array a;
    a.Push("a");
    a.Push("b");
    a.PushAt(0, "x");
    EXPECT_EQ(a.GetAt(0), "x");
    EXPECT_EQ(a.Size(), 3);
}

TEST(ArrayTest, PushAtMiddle) {
    Array a;
    a.Push("a");
    a.Push("b");
    a.PushAt(1, "x");
    EXPECT_EQ(a.GetAt(1), "x");
}

TEST(ArrayTest, PushAtEnd) {
    Array a;
    a.Push("a");
    a.PushAt(1, "x");
    EXPECT_EQ(a.GetAt(1), "x");
}

TEST(ArrayTest, PushAtInvalidNegative) {
    Array a;
    a.Push("a");
    a.PushAt(-1, "x");
    EXPECT_EQ(a.Size(), 1);
}

TEST(ArrayTest, PushAtInvalidLarge) {
    Array a;
    a.Push("a");
    a.PushAt(10, "x");
    EXPECT_EQ(a.Size(), 1);
}

TEST(ArrayTest, PopAtBegin) {
    Array a;
    a.Push("a");
    a.Push("b");
    a.PopAt(0);
    EXPECT_EQ(a.GetAt(0), "b");
    EXPECT_EQ(a.Size(), 1);
}

TEST(ArrayTest, PopAtMiddle) {
    Array a;
    a.Push("a");
    a.Push("b");
    a.Push("c");
    a.PopAt(1);
    EXPECT_EQ(a.GetAt(1), "c");
}

TEST(ArrayTest, PopAtInvalidNegative) {
    Array a;
    a.Push("a");
    a.PopAt(-1);
    EXPECT_EQ(a.Size(), 1);
}

TEST(ArrayTest, PopAtInvalidLarge) {
    Array a;
    a.Push("a");
    a.PopAt(10);
    EXPECT_EQ(a.Size(), 1);
}

TEST(ArrayTest, SetAtValid) {
    Array a;
    a.Push("a");
    a.SetAt(0, "b");
    EXPECT_EQ(a.GetAt(0), "b");
}

TEST(ArrayTest, SetAtInvalidNegative) {
    Array a;
    a.Push("a");
    a.SetAt(-1, "b");
    EXPECT_EQ(a.GetAt(0), "a");
}

TEST(ArrayTest, SetAtInvalidLarge) {
    Array a;
    a.Push("a");
    a.SetAt(10, "b");
    EXPECT_EQ(a.GetAt(0), "a");
}

TEST(ArrayTest, GetAtValid) {
    Array a;
    a.Push("a");
    EXPECT_EQ(a.GetAt(0), "a");
}

TEST(ArrayTest, GetAtInvalidNegative) {
    Array a;
    EXPECT_EQ(a.GetAt(-1), "");
}

TEST(ArrayTest, GetAtInvalidLarge) {
    Array a;
    EXPECT_EQ(a.GetAt(10), "");
}

TEST(ArrayTest, PopValid) {
    Array a;
    a.Push("a");
    a.Push("b");
    a.Pop();
    EXPECT_EQ(a.Size(), 1);
    EXPECT_EQ(a.GetAt(0), "a");
}

TEST(ArrayTest, PopEmpty) {
    Array a;
    testing::internal::CaptureStdout();
    a.Pop();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Массив пуст") != std::string::npos);
}

TEST(ArrayTest, Resize) {
    Array a;
    for (int i = 0; i < 100; ++i) {
        a.Push(std::to_string(i));
    }
    EXPECT_EQ(a.Size(), 100);
    EXPECT_EQ(a.GetAt(99), "99");
}

TEST(ArrayTest, Subarrays) {
    Array a;
    a.Push("x");
    a.Push("y");
    testing::internal::CaptureStdout();
    a.PrintSubarrays();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("{x, y}") != std::string::npos);
}

TEST(ArrayTest, SubarraysEmpty) {
    Array a;
    testing::internal::CaptureStdout();
    a.PrintSubarrays();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
}

TEST(ArrayTest, SaveLoadValid) {
    Array a;
    a.Push("1");
    a.Push("2");
    std::ofstream out("tmp_arr.txt");
    a.Save(out);
    out.close();
    
    Array b;
    std::ifstream in("tmp_arr.txt");
    b.Load(in);
    in.close();
    
    EXPECT_EQ(b.Size(), 2);
    EXPECT_EQ(b.GetAt(0), "1");
    std::remove("tmp_arr.txt");
}

TEST(ArrayTest, SaveLoadEmpty) {
    Array a;
    std::ofstream out("tmp_arr_e.txt");
    a.Save(out);
    out.close();
    
    Array b;
    std::ifstream in("tmp_arr_e.txt");
    b.Load(in);
    in.close();
    
    EXPECT_EQ(b.Size(), 0);
    std::remove("tmp_arr_e.txt");
}

TEST(ArrayTest, LoadInvalid) {
    Array a;
    std::ofstream out("tmp_arr_inv.txt");
    out << "invalid data";
    out.close();
    
    std::ifstream in("tmp_arr_inv.txt");
    a.Load(in);
    in.close();
    
    EXPECT_EQ(a.Size(), 0);
    std::remove("tmp_arr_inv.txt");
}

TEST(ArrayTest, SaveBinary) {
    Array a;
    a.Push("one");
    a.Push("two");
    std::ofstream out("tmp_arr.bin", std::ios::binary);
    a.SaveBinary(out);
    out.close();
    std::remove("tmp_arr.bin");
}

TEST(ArrayTest, LoadBinaryEmpty) {
    Array a;
    std::ofstream out("tmp_arr_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_arr_e.bin", std::ios::binary);
    a.LoadBinary(in);
    in.close();
    
    EXPECT_EQ(a.Size(), 0);
    std::remove("tmp_arr_e.bin");
}

TEST(ArrayTest, LoadBinaryNormal) {
    Array a;
    std::ofstream out("tmp_arr_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_arr_n.bin", std::ios::binary);
    a.LoadBinary(in);
    in.close();
    
    EXPECT_EQ(a.Size(), 1);
    EXPECT_EQ(a.GetAt(0), "abc");
    std::remove("tmp_arr_n.bin");
}

TEST(ArrayTest, LoadBinaryBadLen) {
    Array a;
    std::ofstream out("tmp_arr_bad.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = -1;
    out.write((char*)&len, sizeof(len));
    out.close();
    
    std::ifstream in("tmp_arr_bad.bin", std::ios::binary);
    a.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(a.Size() >= 0);
    std::remove("tmp_arr_bad.bin");
}

TEST(StackTest, PushSingle) {
    Stack s;
    s.Push("A");
    EXPECT_TRUE(s.Find("A"));
}

TEST(StackTest, PushMultiple) {
    Stack s;
    s.Push("A");
    s.Push("B");
    EXPECT_TRUE(s.Find("A"));
    EXPECT_TRUE(s.Find("B"));
}

TEST(StackTest, FindAbsent) {
    Stack s;
    s.Push("A");
    EXPECT_FALSE(s.Find("B"));
}

TEST(StackTest, PopSingle) {
    Stack s;
    s.Push("A");
    s.Pop();
    EXPECT_FALSE(s.Find("A"));
}

TEST(StackTest, PopMultiple) {
    Stack s;
    s.Push("A");
    s.Push("B");
    s.Pop();
    EXPECT_FALSE(s.Find("B"));
    EXPECT_TRUE(s.Find("A"));
}

TEST(StackTest, PopAll) {
    Stack s;
    s.Push("A");
    s.Push("B");
    s.Pop();
    s.Pop();
    EXPECT_FALSE(s.Find("A"));
}

TEST(StackTest, PopEmpty) {
    Stack s;
    testing::internal::CaptureStdout();
    s.Pop();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Стек пуст") != std::string::npos);
}

TEST(StackTest, PrintEmpty) {
    Stack s;
    testing::internal::CaptureStdout();
    s.Print();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
}

TEST(StackTest, PrintNonEmpty) {
    Stack s;
    s.Push("A");
    s.Push("B");
    testing::internal::CaptureStdout();
    s.Print();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("A") != std::string::npos);
    EXPECT_TRUE(out.find("B") != std::string::npos);
}

TEST(StackTest, XMLValid) {
    Stack s;
    EXPECT_TRUE(s.ValidateXML("<a></a>"));
}

TEST(StackTest, XMLNested) {
    Stack s;
    EXPECT_TRUE(s.ValidateXML("<a><b><c></c></b></a>"));
}

TEST(StackTest, XMLMismatch) {
    Stack s;
    EXPECT_FALSE(s.ValidateXML("<a><b></a></b>"));
}

TEST(StackTest, XMLUnclosed) {
    Stack s;
    EXPECT_FALSE(s.ValidateXML("<a><b>"));
}

TEST(StackTest, XMLInvalidChars) {
    Stack s;
    EXPECT_FALSE(s.ValidateXML("<1></1>"));
}

TEST(StackTest, XMLEdgeCases) {
    Stack s;
    EXPECT_FALSE(s.ValidateXML("<>"));
    EXPECT_FALSE(s.ValidateXML("</>"));
    EXPECT_FALSE(s.ValidateXML("<a"));
    EXPECT_FALSE(s.ValidateXML("</a>"));
    EXPECT_FALSE(s.ValidateXML("text"));
}

TEST(StackTest, FixXMLValid) {
    Stack s;
    std::string fixed = s.FixXML("<a><b></x></a>");
    EXPECT_TRUE(fixed == "<a><x></x></a>" || fixed == "<a><b></b></a>");
}

TEST(StackTest, FixXMLIncorrect) {
    Stack s;
    EXPECT_EQ(s.FixXML("invalid"), "Incorrect");
}

TEST(StackTest, FixXMLNoFixPossible) {
    Stack s;
    EXPECT_EQ(s.FixXML("<<<"), "Incorrect");
}

TEST(StackTest, SaveLoadValid) {
    Stack s;
    s.Push("1");
    s.Push("2");
    std::ofstream out("tmp_stack.txt");
    s.Save(out);
    out.close();
    
    Stack t;
    std::ifstream in("tmp_stack.txt");
    t.Load(in);
    in.close();
    
    EXPECT_TRUE(t.Find("1"));
    EXPECT_TRUE(t.Find("2"));
    std::remove("tmp_stack.txt");
}

TEST(StackTest, SaveLoadEmpty) {
    Stack s;
    std::ofstream out("tmp_stack_e.txt");
    s.Save(out);
    out.close();
    
    Stack t;
    std::ifstream in("tmp_stack_e.txt");
    t.Load(in);
    in.close();
    
    EXPECT_FALSE(t.Find("x"));
    std::remove("tmp_stack_e.txt");
}

TEST(StackTest, LoadInvalid) {
    Stack s;
    std::ofstream out("tmp_stack_inv.txt");
    out << "invalid";
    out.close();
    
    std::ifstream in("tmp_stack_inv.txt");
    s.Load(in);
    in.close();
    
    EXPECT_FALSE(s.Find("x"));
    std::remove("tmp_stack_inv.txt");
}

TEST(StackTest, SaveBinary) {
    Stack s;
    s.Push("a");
    s.Push("b");
    std::ofstream out("tmp_st.bin", std::ios::binary);
    s.SaveBinary(out);
    out.close();
    std::remove("tmp_st.bin");
}

TEST(StackTest, LoadBinaryEmpty) {
    Stack s;
    std::ofstream out("tmp_st_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_st_e.bin", std::ios::binary);
    s.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(s.Find("x"));
    std::remove("tmp_st_e.bin");
}

TEST(StackTest, LoadBinaryNormal) {
    Stack s;
    std::ofstream out("tmp_st_n.bin", std::ios::binary);
    int n = 2;
    out.write((char*)&n, sizeof(n));
    
    int len = 1;
    out.write((char*)&len, sizeof(len));
    out.write("a", 1);
    out.write((char*)&len, sizeof(len));
    out.write("b", 1);
    out.close();
    
    std::ifstream in("tmp_st_n.bin", std::ios::binary);
    s.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(s.Find("a"));
    EXPECT_TRUE(s.Find("b"));
    std::remove("tmp_st_n.bin");
}

TEST(StackTest, LoadBinaryBadLen) {
    Stack s;
    std::ofstream out("tmp_st_bad.bin", std::ios::binary);
    int n = 2;
    out.write((char*)&n, sizeof(n));
    int len = -1;
    out.write((char*)&len, sizeof(len));
    out.close();
    
    std::ifstream in("tmp_st_bad.bin", std::ios::binary);
    s.LoadBinary(in);
    in.close();
    
    EXPECT_LE(s.Find("x"), false);
    std::remove("tmp_st_bad.bin");
}

TEST(ForwardListTest, EmptyAndEdgeCases) {
    ForwardList f;
    
    testing::internal::CaptureStdout();
    f.PopTail();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("Список пуст"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PushBefore("none", "x");
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("Список пуст"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PushAfter("none", "x");
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out3.find("Не найдено"), std::string::npos);

    testing::internal::CaptureStdout();
    f.Pop();
    std::string out4 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out4.find("Список пуст"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopBefore("none");
    std::string out5 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out5.find("Нечего удалять"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopAfter("none");
    std::string out6 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out6.find("Нечего удалять"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopValue("none");
    std::string out7 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out7.find("Список пуст"), std::string::npos);
}

TEST(ForwardListTest, PrintMethods) {
    ForwardList f;
    f.Push("A");
    f.PushTail("B");
    f.PushTail("C");
    
    testing::internal::CaptureStdout();
    f.Print();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out1.empty());

    testing::internal::CaptureStdout();
    f.PrintReverse();
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out2.empty());

    testing::internal::CaptureStdout();
    f.PrintEverySecond();
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out3.empty());

    ForwardList empty;
    testing::internal::CaptureStdout();
    empty.PrintReverse();
    std::string out4 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out4.empty());
}

TEST(ForwardListTest, PopHeadTailValue) {
    ForwardList f;
    f.Push("A");
    f.PushTail("B");
    f.PushTail("C");
    f.PushTail("D");
    
    testing::internal::CaptureStdout();
    f.Pop(); 
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out1.empty());
    
    testing::internal::CaptureStdout();
    f.PopTail(); 
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out2.empty());
    
    testing::internal::CaptureStdout();
    f.PopBefore("C"); 
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out3.empty());
    
    testing::internal::CaptureStdout();
    f.PopAfter("A"); 
    std::string out4 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out4.empty());
    
    testing::internal::CaptureStdout();
    f.PopValue("C"); 
    std::string out5 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out5.empty());
}

TEST(ForwardListTest, SaveLoad) {
    ForwardList f;
    f.Push("1");
    f.PushTail("2");
    
    std::ofstream out("tmp_fl.txt");
    f.Save(out);
    out.close();
    
    ForwardList g;
    std::ifstream in("tmp_fl.txt");
    g.Load(in);
    in.close();
    
    EXPECT_TRUE(g.Find("1"));
    EXPECT_TRUE(g.Find("2"));
    std::remove("tmp_fl.txt");
}

TEST(ForwardListTest, SaveBinary) {
    ForwardList f;
    f.Push("a");
    f.PushTail("b");
    std::ofstream out("tmp_fl.bin", std::ios::binary);
    f.SaveBinary(out);
    out.close();
    std::remove("tmp_fl.bin");
}

TEST(ForwardListTest, LoadBinaryEmpty) {
    ForwardList f;
    std::ofstream out("tmp_fl_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_fl_e.bin", std::ios::binary);
    f.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(f.Find("x"));
    std::remove("tmp_fl_e.bin");
}

TEST(ForwardListTest, LoadBinaryNormal) {
    ForwardList f;
    std::ofstream out("tmp_fl_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_fl_n.bin", std::ios::binary);
    f.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(f.Find("abc"));
    std::remove("tmp_fl_n.bin");
}

TEST(ForwardListTest, FullCoverage) {
    ForwardList f;
    
    testing::internal::CaptureStdout();
    f.Print();
    std::string out1 = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    f.PrintEverySecond();
    std::string out2 = testing::internal::GetCapturedStdout();

    f.Push("A");
    f.PushTail("B");
    f.PushTail("C");

    testing::internal::CaptureStdout();
    f.PushBefore("B", "X");
    std::string out3 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    f.PushAfter("B", "Y");
    std::string out4 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    f.PopValue("A");
    std::string out5 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    f.PopValue("C");
    std::string out6 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    f.PopTail();
    std::string out7 = testing::internal::GetCapturedStdout();
}

TEST(ForwardListTest, EmptyErrors) {
    ForwardList f;
    
    testing::internal::CaptureStdout();
    f.PopTail();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("Список пуст"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopValue("none");
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("Список пуст"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PushBefore("A", "X");
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out3.find("Список пуст"), std::string::npos);
}

TEST(ForwardListTest, MissingTarget) {
    ForwardList f;
    f.Push("A");
    
    testing::internal::CaptureStdout();
    f.PushBefore("none", "X");
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("Не найдено"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PushAfter("none", "X");
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("Не найдено"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopBefore("none");
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out3.find("Нечего удалять"), std::string::npos);

    testing::internal::CaptureStdout();
    f.PopAfter("none");
    std::string out4 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out4.find("Нечего удалять"), std::string::npos);
    
    testing::internal::CaptureStdout();
    f.PopValue("none");
    std::string out5 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out5.find("Не найдено"), std::string::npos);
}

TEST(DoublyListTest, PushAndPrint) {
    DoublyList d;
    d.Push("A");
    d.PushTail("B");
    EXPECT_TRUE(d.Find("A"));
    EXPECT_TRUE(d.Find("B"));
    
    testing::internal::CaptureStdout();
    d.Print();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    
    testing::internal::CaptureStdout();
    d.PrintReverse();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    
    testing::internal::CaptureStdout();
    d.PrintEverySecond();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
}

TEST(DoublyListTest, PushBeforeAfter) {
    DoublyList d;
    d.Push("A");
    d.PushTail("B");
    d.PushBefore("B", "X");
    d.PushAfter("A", "Y");
    EXPECT_TRUE(d.Find("X"));
    EXPECT_TRUE(d.Find("Y"));
    
    d.PushBefore("none", "Z");
    d.PushAfter("none", "Z");
    EXPECT_FALSE(d.Find("Z"));
}

TEST(DoublyListTest, PopVariants) {
    DoublyList d;
    d.Push("A");
    d.PushTail("B");
    d.PushTail("C");
    
    testing::internal::CaptureStdout();
    d.Pop();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("A") != std::string::npos);
    EXPECT_FALSE(d.Find("A"));
    
    testing::internal::CaptureStdout();
    d.PopTail();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("C") != std::string::npos);
    EXPECT_FALSE(d.Find("C"));
}

TEST(DoublyListTest, PopBeforeAfterValue) {
    DoublyList d;
    d.Push("A");
    d.PushTail("B");
    d.PushTail("C");
    d.PushTail("D");
    
    testing::internal::CaptureStdout();
    d.PopBefore("C");
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(d.Find("B"));
    
    testing::internal::CaptureStdout();
    d.PopAfter("A");
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(d.Find("C"));
    
    testing::internal::CaptureStdout();
    d.PopValue("A");
    std::string out3 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(d.Find("A"));
    
    testing::internal::CaptureStdout();
    d.PopBefore("none");
    std::string out4 = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    d.PopAfter("none");
    std::string out5 = testing::internal::GetCapturedStdout();
    
    testing::internal::CaptureStdout();
    d.PopValue("none");
    std::string out6 = testing::internal::GetCapturedStdout();
}

TEST(DoublyListTest, PopEmpty) {
    DoublyList d;
    testing::internal::CaptureStdout();
    d.Pop();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Список пуст") != std::string::npos);
    
    testing::internal::CaptureStdout();
    d.PopTail();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Список пуст") != std::string::npos);
    
    testing::internal::CaptureStdout();
    d.PopBefore("none");
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Нечего удалять") != std::string::npos);
    
    testing::internal::CaptureStdout();
    d.PopAfter("none");
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Нечего удалять") != std::string::npos);
}

TEST(DoublyListTest, SaveLoadText) {
    DoublyList d;
    d.Push("1");
    d.PushTail("2");
    std::ofstream out("tmp_dl.txt");
    d.Save(out);
    out.close();
    
    DoublyList e;
    std::ifstream in("tmp_dl.txt");
    e.Load(in);
    in.close();
    
    EXPECT_TRUE(e.Find("1"));
    EXPECT_TRUE(e.Find("2"));
    std::remove("tmp_dl.txt");
}

TEST(DoublyListTest, SaveBinary) {
    DoublyList d;
    d.Push("a");
    d.PushTail("b");
    std::ofstream out("tmp_dl.bin", std::ios::binary);
    d.SaveBinary(out);
    out.close();
    std::remove("tmp_dl.bin");
}

TEST(DoublyListTest, LoadBinaryEmpty) {
    DoublyList d;
    std::ofstream out("tmp_dl_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_dl_e.bin", std::ios::binary);
    d.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(d.Find("x"));
    std::remove("tmp_dl_e.bin");
}

TEST(DoublyListTest, LoadBinaryNormal) {
    DoublyList d;
    std::ofstream out("tmp_dl_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_dl_n.bin", std::ios::binary);
    d.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(d.Find("abc"));
    std::remove("tmp_dl_n.bin");
}

TEST(QueueTest, PushAndFind) {
    Queue q;
    q.Push("1");
    q.Push("2");
    EXPECT_TRUE(q.Find("1"));
    EXPECT_TRUE(q.Find("2"));
    EXPECT_FALSE(q.Find("3"));
}

TEST(QueueTest, PopAndPrint) {
    Queue q;
    q.Push("1");
    q.Push("2");
    
    testing::internal::CaptureStdout();
    q.Print();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("1") != std::string::npos);
    EXPECT_TRUE(out.find("2") != std::string::npos);
    
    testing::internal::CaptureStdout();
    q.Pop();
    out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("1") != std::string::npos);
    EXPECT_FALSE(q.Find("1"));
    EXPECT_TRUE(q.Find("2"));
}

TEST(QueueTest, PopEmpty) {
    Queue q;
    testing::internal::CaptureStdout();
    q.Pop();
    EXPECT_TRUE(testing::internal::GetCapturedStdout().find("Очередь пуста") != std::string::npos);
}

TEST(QueueTest, SaveLoadText) {
    Queue q;
    q.Push("1");
    q.Push("2");
    std::ofstream out("tmp_q.txt");
    q.Save(out);
    out.close();
    
    Queue r;
    std::ifstream in("tmp_q.txt");
    r.Load(in);
    in.close();
    
    EXPECT_TRUE(r.Find("1"));
    EXPECT_TRUE(r.Find("2"));
    std::remove("tmp_q.txt");
}

TEST(QueueTest, SaveBinary) {
    Queue q;
    q.Push("a");
    q.Push("b");
    std::ofstream out("tmp_q.bin", std::ios::binary);
    q.SaveBinary(out);
    out.close();
    std::remove("tmp_q.bin");
}

TEST(QueueTest, LoadBinaryEmpty) {
    Queue q;
    std::ofstream out("tmp_q_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_q_e.bin", std::ios::binary);
    q.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(q.Find("x"));
    std::remove("tmp_q_e.bin");
}

TEST(QueueTest, LoadBinaryNormal) {
    Queue q;
    std::ofstream out("tmp_q_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_q_n.bin", std::ios::binary);
    q.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(q.Find("abc"));
    std::remove("tmp_q_n.bin");
}

TEST(HashTableTest, AddSingle) {
    HashTable h(10007, 1);
    h.Add("apple");
    EXPECT_TRUE(h.Contains("apple"));
}

TEST(HashTableTest, RemoveExisting) {
    HashTable h(10007, 1);
    h.Add("apple");
    h.Remove("apple");
    EXPECT_FALSE(h.Contains("apple"));
}

TEST(HashTableTest, DoubleHash) {
    HashTable h(10007, 2);
    h.Add("apple");
    EXPECT_TRUE(h.Contains("apple"));
}

TEST(HashTableTest, EdgeCasesAndPop) {
    HashTable h(10007, 1);
    
    testing::internal::CaptureStdout();
    h.Pop();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("Таблица пуста"), std::string::npos);

    h.Add("a");
    testing::internal::CaptureStdout();
    h.Pop();
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("a"), std::string::npos);
    EXPECT_FALSE(h.Contains("a"));
}

TEST(HashTableTest, CollisionAndModulo) {
    HashTable h(5, 1);
    h.Add("a");
    h.Add("b");
    h.Add("c");
    h.Add("d");
    h.Add("e");
    h.Add("f");
    
    EXPECT_TRUE(h.Contains("a") || h.Contains("f"));
    
    h.Remove("a");
    h.Remove("none");
    EXPECT_FALSE(h.Contains("a"));
}

TEST(HashTableTest, PrintAndSave) {
    HashTable h(10007, 1);
    h.Add("k1");
    h.Add("k2");
    
    testing::internal::CaptureStdout();
    h.Print();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("k1"), std::string::npos);
    
    std::ofstream out_file("tmp_ht.txt");
    h.Save(out_file);
    out_file.close();
    
    HashTable g(10007, 1);
    std::ifstream in("tmp_ht.txt");
    g.Load(in);
    in.close();
    
    EXPECT_TRUE(g.Contains("k1"));
    EXPECT_TRUE(g.Contains("k2"));
    std::remove("tmp_ht.txt");
}

TEST(HashTableTest, LongestSubstring) {
    HashTable h(10007, 1);
    EXPECT_EQ(h.LengthOfLongestSubstring("abcabcbb"), 3);
}

TEST(HashTableTest, SaveBinary) {
    HashTable h(10007, 1);
    h.Add("k1");
    std::ofstream out("tmp_ht.bin", std::ios::binary);
    h.SaveBinary(out);
    out.close();
    std::remove("tmp_ht.bin");
}

TEST(HashTableTest, LoadBinaryEmpty) {
    HashTable h(10007, 1);
    std::ofstream out("tmp_ht_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_ht_e.bin", std::ios::binary);
    h.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(h.Contains("x"));
    std::remove("tmp_ht_e.bin");
}

TEST(HashTableTest, LoadBinaryNormal) {
    HashTable h(10007, 1);
    std::ofstream out("tmp_ht_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_ht_n.bin", std::ios::binary);
    h.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(h.Contains("abc"));
    std::remove("tmp_ht_n.bin");
}

TEST(AVLTreeTest, InsertSingle) {
    AVLTree t;
    t.Push("10");
    EXPECT_TRUE(t.Find("10"));
    EXPECT_EQ(t.GetHeight(), 1);
}

TEST(AVLTreeTest, InsertMultiple) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("15");
    EXPECT_TRUE(t.Find("5"));
    EXPECT_EQ(t.GetHeight(), 2);
}

TEST(AVLTreeTest, PopLeaf) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("15");
    t.PopValue("5");
    EXPECT_FALSE(t.Find("5"));
}

TEST(AVLTreeTest, PopOneChild) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("3");
    t.PopValue("5");
    EXPECT_FALSE(t.Find("5"));
}

TEST(AVLTreeTest, PopTwoChildren) {
    AVLTree t;
    t.Push("10");
    t.Push("5");
    t.Push("15");
    t.Push("3");
    t.Push("7");
    t.PopValue("5");
    EXPECT_FALSE(t.Find("5"));
}

TEST(AVLTreeTest, RotateRight) {
    AVLTree t;
    t.Push("30");
    t.Push("20");
    t.Push("10");
    EXPECT_EQ(t.GetHeight(), 2);
}

TEST(AVLTreeTest, RotateLeft) {
    AVLTree t;
    t.Push("10");
    t.Push("20");
    t.Push("30");
    EXPECT_EQ(t.GetHeight(), 2);
}

TEST(AVLTreeTest, DoubleRotationLR) {
    AVLTree t;
    t.Push("30");
    t.Push("10");
    t.Push("20");
    EXPECT_EQ(t.GetHeight(), 2);
}

TEST(AVLTreeTest, DoubleRotationRL) {
    AVLTree t;
    t.Push("10");
    t.Push("30");
    t.Push("20");
    EXPECT_EQ(t.GetHeight(), 2);
}

TEST(AVLTreeTest, HuffmanEncodeBasic) {
    AVLTree t;
    testing::internal::CaptureStdout();
    t.HuffmanEncode("aabbcc");
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Таблица кодов"), std::string::npos);
}

TEST(AVLTreeTest, HuffmanEncodeEmpty) {
    AVLTree t;
    testing::internal::CaptureStdout();
    t.HuffmanEncode("");
    EXPECT_NE(testing::internal::GetCapturedStdout().find("Пустая строка"), std::string::npos);
}

TEST(AVLTreeTest, HuffmanDecodeBasic) {
    AVLTree t;
    testing::internal::CaptureStdout();
    t.HuffmanDecode("0101", "a 0,b 1");
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
}

TEST(AVLTreeTest, HuffmanDecodeEmpty) {
    AVLTree t;
    testing::internal::CaptureStdout();
    t.HuffmanDecode("", "");
    EXPECT_NE(testing::internal::GetCapturedStdout().find("Пустой код"), std::string::npos);
}

TEST(AVLTreeTest, HuffmanDecodeBadCode) {
    AVLTree t;
    testing::internal::CaptureStdout();
    t.HuffmanDecode("111111", "a 0");
    EXPECT_NE(testing::internal::GetCapturedStdout().find("Ошибка декодирования"), std::string::npos);
}

TEST(AVLTreeTest, SaveBinary) {
    AVLTree t;
    t.Push("10");
    std::ofstream out("tmp_avl.bin", std::ios::binary);
    t.SaveBinary(out);
    out.close();
    std::remove("tmp_avl.bin");
}

TEST(AVLTreeTest, LoadBinaryEmpty) {
    AVLTree t;
    std::ofstream out("tmp_avl_e.bin", std::ios::binary);
    int n = 0;
    out.write((char*)&n, sizeof(n));
    out.close();
    
    std::ifstream in("tmp_avl_e.bin", std::ios::binary);
    t.LoadBinary(in);
    in.close();
    
    EXPECT_FALSE(t.Find("x"));
    std::remove("tmp_avl_e.bin");
}

TEST(AVLTreeTest, LoadBinaryNormal) {
    AVLTree t;
    std::ofstream out("tmp_avl_n.bin", std::ios::binary);
    int n = 1;
    out.write((char*)&n, sizeof(n));
    int len = 3;
    out.write((char*)&len, sizeof(len));
    out.write("abc", 3);
    out.close();
    
    std::ifstream in("tmp_avl_n.bin", std::ios::binary);
    t.LoadBinary(in);
    in.close();
    
    EXPECT_TRUE(t.Find("abc"));
    std::remove("tmp_avl_n.bin");
}