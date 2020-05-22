#include "LogMessage.h"
#include <iostream>

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

int main(int argc, char** argv) {
    test1();
    test2();
    return 0;
}
