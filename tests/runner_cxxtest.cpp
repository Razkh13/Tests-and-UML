/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_Lab3CxxTestSuite_init = false;
#include "/home/zaharov/programming/Lab3.3/tests/test_cxxtest.h"

static Lab3CxxTestSuite suite_Lab3CxxTestSuite;

static CxxTest::List Tests_Lab3CxxTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Lab3CxxTestSuite( "tests/test_cxxtest.h", 10, "Lab3CxxTestSuite", suite_Lab3CxxTestSuite, Tests_Lab3CxxTestSuite );

static class TestDescription_suite_Lab3CxxTestSuite_testArrayPushAndFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testArrayPushAndFind() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 12, "testArrayPushAndFind" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testArrayPushAndFind(); }
} testDescription_suite_Lab3CxxTestSuite_testArrayPushAndFind;

static class TestDescription_suite_Lab3CxxTestSuite_testArrayPushAtAndPopAt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testArrayPushAtAndPopAt() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 21, "testArrayPushAtAndPopAt" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testArrayPushAtAndPopAt(); }
} testDescription_suite_Lab3CxxTestSuite_testArrayPushAtAndPopAt;

static class TestDescription_suite_Lab3CxxTestSuite_testArrayGetSetPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testArrayGetSetPop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 33, "testArrayGetSetPop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testArrayGetSetPop(); }
} testDescription_suite_Lab3CxxTestSuite_testArrayGetSetPop;

static class TestDescription_suite_Lab3CxxTestSuite_testArrayEdgeCases : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testArrayEdgeCases() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 43, "testArrayEdgeCases" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testArrayEdgeCases(); }
} testDescription_suite_Lab3CxxTestSuite_testArrayEdgeCases;

static class TestDescription_suite_Lab3CxxTestSuite_testStackPushPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testStackPushPop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 50, "testStackPushPop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testStackPushPop(); }
} testDescription_suite_Lab3CxxTestSuite_testStackPushPop;

static class TestDescription_suite_Lab3CxxTestSuite_testStackXML : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testStackXML() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 60, "testStackXML" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testStackXML(); }
} testDescription_suite_Lab3CxxTestSuite_testStackXML;

static class TestDescription_suite_Lab3CxxTestSuite_testStackEdgeCases : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testStackEdgeCases() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 66, "testStackEdgeCases" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testStackEdgeCases(); }
} testDescription_suite_Lab3CxxTestSuite_testStackEdgeCases;

static class TestDescription_suite_Lab3CxxTestSuite_testForwardListPushFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testForwardListPushFind() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 72, "testForwardListPushFind" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testForwardListPushFind(); }
} testDescription_suite_Lab3CxxTestSuite_testForwardListPushFind;

static class TestDescription_suite_Lab3CxxTestSuite_testForwardListPushBeforeAfter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testForwardListPushBeforeAfter() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 80, "testForwardListPushBeforeAfter" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testForwardListPushBeforeAfter(); }
} testDescription_suite_Lab3CxxTestSuite_testForwardListPushBeforeAfter;

static class TestDescription_suite_Lab3CxxTestSuite_testForwardListPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testForwardListPop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 90, "testForwardListPop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testForwardListPop(); }
} testDescription_suite_Lab3CxxTestSuite_testForwardListPop;

static class TestDescription_suite_Lab3CxxTestSuite_testDoublyListPushPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testDoublyListPushPop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 100, "testDoublyListPushPop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testDoublyListPushPop(); }
} testDescription_suite_Lab3CxxTestSuite_testDoublyListPushPop;

static class TestDescription_suite_Lab3CxxTestSuite_testDoublyListPushBeforeAfter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testDoublyListPushBeforeAfter() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 110, "testDoublyListPushBeforeAfter" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testDoublyListPushBeforeAfter(); }
} testDescription_suite_Lab3CxxTestSuite_testDoublyListPushBeforeAfter;

static class TestDescription_suite_Lab3CxxTestSuite_testQueuePushPop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testQueuePushPop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 120, "testQueuePushPop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testQueuePushPop(); }
} testDescription_suite_Lab3CxxTestSuite_testQueuePushPop;

static class TestDescription_suite_Lab3CxxTestSuite_testHashTableAddContains : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testHashTableAddContains() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 130, "testHashTableAddContains" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testHashTableAddContains(); }
} testDescription_suite_Lab3CxxTestSuite_testHashTableAddContains;

static class TestDescription_suite_Lab3CxxTestSuite_testHashTableDoubleHash : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testHashTableDoubleHash() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 139, "testHashTableDoubleHash" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testHashTableDoubleHash(); }
} testDescription_suite_Lab3CxxTestSuite_testHashTableDoubleHash;

static class TestDescription_suite_Lab3CxxTestSuite_testHashTableLongestSubstring : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testHashTableLongestSubstring() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 147, "testHashTableLongestSubstring" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testHashTableLongestSubstring(); }
} testDescription_suite_Lab3CxxTestSuite_testHashTableLongestSubstring;

static class TestDescription_suite_Lab3CxxTestSuite_testAVLTreeInsertFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testAVLTreeInsertFind() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 153, "testAVLTreeInsertFind" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testAVLTreeInsertFind(); }
} testDescription_suite_Lab3CxxTestSuite_testAVLTreeInsertFind;

static class TestDescription_suite_Lab3CxxTestSuite_testAVLTreeHeight : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testAVLTreeHeight() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 162, "testAVLTreeHeight" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testAVLTreeHeight(); }
} testDescription_suite_Lab3CxxTestSuite_testAVLTreeHeight;

static class TestDescription_suite_Lab3CxxTestSuite_testAVLTreePop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Lab3CxxTestSuite_testAVLTreePop() : CxxTest::RealTestDescription( Tests_Lab3CxxTestSuite, suiteDescription_Lab3CxxTestSuite, 170, "testAVLTreePop" ) {}
 void runTest() { suite_Lab3CxxTestSuite.testAVLTreePop(); }
} testDescription_suite_Lab3CxxTestSuite_testAVLTreePop;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
