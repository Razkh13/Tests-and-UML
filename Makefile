CXX = g++
CXXFLAGS = -std=c++17 -I. -Wall -Wextra -fprofile-arcs -ftest-coverage
SRCS = Array/array.cpp Stack/stack.cpp Forward_list/forward_list.cpp \
       Doubly_list/doubly_list.cpp Queue/queue.cpp HashTable/hash_table.cpp \
       AVL_tree/avl_tree.cpp

all: dbms test_runner test_boost test_cxxtest benchmark

dbms: main.cpp dbms.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_runner: tests/test_all.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -lgtest -lgtest_main -pthread -o $@

test_boost: tests/test_boost.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_cxxtest: tests/test_cxxtest.h $(SRCS)
	cxxtestgen --error-printer -o tests/runner_cxxtest.cpp tests/test_cxxtest.h
	$(CXX) $(CXXFLAGS) -I/usr/include/cxxtest -o $@ tests/runner_cxxtest.cpp $(SRCS)

benchmark: tests/benchmark.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -lbenchmark -lpthread -o $@

coverage: clean test_runner
	./test_runner
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch --no-external
	lcov --remove coverage.info '*/tests/*' '*.h' -o coverage.info --ignore-errors unused
	genhtml coverage.info --output-directory coverage_html

fast-coverage: test_runner
	./test_runner
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch --no-external
	lcov --remove coverage.info '*/tests/*' '*.h' '*/dbms.cpp' '*/main.cpp' -o coverage.info --ignore-errors unused
	genhtml coverage.info --output-directory coverage_html

clean:
	rm -f dbms test_runner test_boost test_cxxtest benchmark *.gcda *.gcno coverage.info
	rm -rf coverage_html
	rm -f *.bin tmp_*.txt data.txt