#include "messaging/log_message.h"
#include <iostream>

class Test {
    public:
        Test();
};

Test::Test() {
    LogMessage foo(40);
    foo.Supply("hello from test.");
    std::cout << foo << std::endl;
}

void test1() {
    // captured return value test
    LogMessage foo(21);
    foo.Supply("hello from test 1, here's a floating point number: %f", 0.53);
    std::cout << foo << std::endl;
}

void test2() {
    // inline test
    LogMessage foo(42);
    foo.Supply("hello from test 2, here's a sentence: %s", "\"incredible!\"");
    std::cout << foo << std::endl;
}

void testMultiple4(LogMessage& foo) {
    foo.Supply("from testMultiple4 with exponent: %e", 6.5);
}

void testMultiple3(LogMessage& foo) {
    foo.Supply("from testMultiple3 with hex number: %x", 14);
    testMultiple4(foo);
}

void testMultiple2(LogMessage& foo) {
    foo.Supply("from testMultiple2 with character: %c", '?');
    testMultiple3(foo);
}

void testMultiple1(LogMessage& foo) {
    foo.Supply("from testMultiple1 with floating point: %f", 0.24);
    testMultiple2(foo);
}

void kickstart() {
    LogMessage foo(16);
    foo.Supply("from kickstart with number: %i", 235);
    testMultiple1(foo);
    std::cout << foo << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Single-line log messages: " << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    test1();
    test2();
    Test *a = new Test();
    std::cout << std::endl;

    std::cout << "Multi-line log messages: " << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    kickstart();
    return 0;
}
