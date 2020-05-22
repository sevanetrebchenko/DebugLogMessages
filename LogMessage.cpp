
#include <cstdarg>      // va_list
#include <vector>       // vector
#include <sstream>      // stringstream
#include <iostream>     // cout
#include "LogMessage.h" // functions

// LogMessageData begin
class LogMessage::LogMessageData {
    public:
        explicit LogMessageData(unsigned messageSeverity);
        ~LogMessageData();
        void ProcessMessage(const char* formatString, std::va_list argList);

        std::vector<std::string> _messages;
        unsigned _severity;

    private:
        unsigned _processingBufferSize;
        char* _processingBuffer;
};

LogMessage::LogMessageData::LogMessageData(unsigned int messageSeverity) : _severity(messageSeverity) {
    _processingBufferSize = 256;
    _processingBuffer = new(std::nothrow) char[_processingBufferSize];
}

void LogMessage::LogMessageData::ProcessMessage(const char *formatString, std::va_list argList) {
    vsnprintf(_processingBuffer, _processingBufferSize, formatString, argList);
    _messages.emplace_back(_processingBuffer);
}

LogMessage::LogMessageData::~LogMessageData() {
    delete[] _processingBuffer;
}
// LogMessageData end

// Functions that are the same between the two classes (overloaded and not)
LogMessage::LogMessage(unsigned int messageSeverity) {
    std::cout << "calling constructor" << std::endl;
    _data = std::make_unique<LogMessageData>(messageSeverity);
}

LogMessage::~LogMessage() {
    std::cout << "calling destructor" << std::endl;
    _data.reset();
}

// Functions that are different (overloaded by macro) between the two classes
#ifdef DEBUG_MESSAGES
std::string DBG_LOG_MESSAGE::Supply_Aux(const std::string &callingFunction, const std::string &fileName, int lineNumber, const char* formatString, ...) {
    std::va_list args;
    va_start(args, formatString);
    _data->ProcessMessage(formatString, args);
    va_end(args);
    std::stringstream s;
    s << "Supply() is being called by " << callingFunction << "() in " << fileName << ":" << lineNumber << ". Provided message: " << _data->_messages[0].c_str() << std::endl;

    return s.str();
}
#else
std::string LogMessage::Supply(const char* formatString, ...) {
    std::va_list args;
    va_start(args, formatString);
    _data->ProcessMessage(formatString, args);
    va_end(args);

    return _data->_messages[0];
}
#endif








