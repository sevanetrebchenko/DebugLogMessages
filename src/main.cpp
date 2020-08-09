
#include <timing/timestamp.h>
#include <messaging/log_message.h>
#include <iostream>
#include <chrono>
#include <thread>


int main(int argc, char** argv) {
    Timing::TimeStamp::Initialize();
    std::cout << "Single-line log messages: " << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    Messaging::LogMessage message1;
    message1.Supply("Hello, world!");
    std::cout << message1 << std::endl;

    // Delay for timestamp demonstration purposes.
    std::this_thread::sleep_for (std::chrono::milliseconds (100));

    Messaging::LogMessage message2 { Messaging::LogMessageSeverity::WARNING };
    message2.Supply("My favorite number is %i.", 7);
    std::cout << message2 << std::endl;

    // Delay for timestamp demonstration purposes.
    std::this_thread::sleep_for (std::chrono::milliseconds (100));

    Messaging::LogMessage message3 { Messaging::LogMessageSeverity::SEVERE };
    message3.Supply("Do you like green eggs and ham?");
    std::cout << message3 << std::endl;

    std::cout << std::endl;

    std::cout << "Multi-line log messages: " << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    Messaging::LogMessage message4;
    message4.Supply("Hello, world...");
    message4.Supply("Hello, again!");
    std::cout << message4 << std::endl;

    Messaging::LogMessage message5 { Messaging::LogMessageSeverity::WARNING };
    message5.Supply("I thought my favorite number was %i before...", 7);
    message5.Supply("but it's now %f!", 5.4);
    std::cout << message5 << std::endl;

    // Delay for timestamp demonstration purposes.
    std::this_thread::sleep_for (std::chrono::milliseconds (100));

    Messaging::LogMessage message6 { Messaging::LogMessageSeverity::SEVERE };
    message6.Supply("I do not like them,");
    message6.Supply("Sam-I-am.");
    message6.Supply("I do not like");
    message6.Supply("Green eggs and ham.");
    std::cout << message6 << std::endl;

    return 0;
}
