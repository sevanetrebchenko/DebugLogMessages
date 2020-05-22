#include "LogMessage.h"
#include <iostream>

void test1() {
    // captured return value test
    LogMessage foo(21);
    std::string a = foo.Supply("hello from test 1, here's a floating point number: %f", 0.53);
    std::cout << a << std::endl;
}

void test2() {
    // inline test
    LogMessage foo(42);
    std::cout << foo.Supply("hello from test 2, here's a sentence: %s", "\"incredible!\"") << std::endl;
}

int main(int argc, char** argv) {
    test1();
    test2();
    return 0;
}
