
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
#ifdef DEBUG_MESSAGES
        void ProcessMessage(std::string&& file, std::string&& function, unsigned line, const char* formatString, std::va_list argList);
#else
        void ProcessMessage(const char* formatString, std::va_list argList);
#endif
    private:
#ifdef DEBUG_MESSAGES
    struct LogDebugInformation {
                LogDebugInformation(std::string&& file, std::string&& function, unsigned line);
                std::string _file;
                std::string _function;
                unsigned _line;
            };
#endif

    public:
        std::vector<std::string> _messages;

#ifdef DEBUG_MESSAGES
    std::vector<LogDebugInformation> _calleeInformation;
#endif
        unsigned _severity;

    private:
        std::stringstream _format;
        unsigned _processingBufferSize;
        char* _processingBuffer;
};


LogMessage::LogMessageData::LogMessageData(unsigned int messageSeverity) : _severity(messageSeverity) {
    _processingBufferSize = 64;
    try {
        _processingBuffer = new char[_processingBufferSize];
    }
    catch (std::bad_alloc& e) {
        std::cout << "Insufficient memory to allocate instance of LogMessage. Error message: " << e.what() << std::endl;
    }
}



LogMessage::LogMessageData::~LogMessageData() {
    delete[] _processingBuffer;
}
// LogMessageData end

// Functions that are the same between the two classes (overloaded and not)
LogMessage::LogMessage(unsigned int messageSeverity) {
    _data = std::make_unique<LogMessageData>(messageSeverity);
}

LogMessage::~LogMessage() {
    _data.reset();
}

// Functions that are different (overloaded by macro) between the two classes
#ifdef DEBUG_MESSAGES
DBG_LOG_MESSAGE::LogMessageData::LogDebugInformation::LogDebugInformation(std::string &&file, std::string &&function, unsigned int line) : _file(std::move(file)), _function(std::move(function)), _line(line) {
}

void DBG_LOG_MESSAGE::SUPPLY_DBG(std::string&& callingFunction, std::string&& fileName, int lineNumber, const char* formatString, ...) {
    std::va_list args;
    va_start(args, formatString);
    _data->ProcessMessage(std::move(callingFunction), std::move(fileName), lineNumber, formatString, args);
    va_end(args);
}

void LogMessage::LogMessageData::ProcessMessage(std::string&& function, std::string&& file, unsigned line, const char *formatString, std::va_list argList) {
    // record callee information
    _calleeInformation.emplace_back(std::move(file), std::move(function), line);

    // calculate correct number of bytes to write
    unsigned currentBufferSize = _processingBufferSize;

    // copy args list to not modify passed parameters
    std::va_list argsCopy;
    va_copy(argsCopy, argList);
    // If size of the buffer is zero, nothing is written and buffer may be a null pointer, however the return value (number of bytes that would be written not including the null terminator) is still calculated and returned.
    int writeResult = vsnprintf(nullptr, 0, formatString, argsCopy);

    // get buffer size of powers of 2 to match the size correctly
    // if buffer size is equal to write result, there will not be space for the null terminator for the string
    while (_processingBufferSize <= writeResult) {
        _processingBufferSize *= 2;
    }

    // reallocate buffer
    if (currentBufferSize != _processingBufferSize) {
        delete [] _processingBuffer;
        _processingBuffer = new char[_processingBufferSize];
    }

    // write data to buffer
    vsnprintf(_processingBuffer, _processingBufferSize, formatString, argList);

    _messages.emplace_back(_processingBuffer);
}

std::ostream &operator<<(std::ostream &os, const DBG_LOG_MESSAGE &message) {
    unsigned size = message._data->_messages.size();
    for (unsigned i = 0; i < size; ++i) {
        std::string& msg = message._data->_messages[i];
        auto& calleeInfo = message._data->_calleeInformation[i];
        os << "Supply() called in function: " << calleeInfo._function << "(), at " << calleeInfo._file << ":" << calleeInfo._line << std::endl;
        os << "Severity: " << message._data->_severity << ", Message: " << msg << std::endl;
    }

    return os;
}

#else
void LogMessage::Supply(const char* formatString, ...) {
    std::va_list args;
    va_start(args, formatString);
    _data->ProcessMessage(formatString, args);
    va_end(args);
}

void LogMessage::LogMessageData::ProcessMessage(const char *formatString, std::va_list argList) {
    // calculate correct number of bytes to write
    unsigned currentBufferSize = _processingBufferSize;

    // copy args list to not modify passed parameters
    std::va_list argsCopy;
    va_copy(argsCopy, argList);
    // If size of the buffer is zero, nothing is written and buffer may be a null pointer, however the return value (number of bytes that would be written not including the null terminator) is still calculated and returned.
    int writeResult = vsnprintf(nullptr, 0, formatString, argsCopy);

    // get buffer size of powers of 2 to match the size correctly
    // if buffer size is equal to write result, there will not be space for the null terminator for the string
    while (_processingBufferSize <= writeResult) {
        _processingBufferSize *= 2;
    }

    // reallocate buffer
    if (currentBufferSize != _processingBufferSize) {
        delete [] _processingBuffer;
        _processingBuffer = new char[_processingBufferSize];
    }

    // write data to buffer
    vsnprintf(_processingBuffer, _processingBufferSize, formatString, argList);

    _messages.emplace_back(_processingBuffer);
}

std::ostream &operator<<(std::ostream &os, const LogMessage &message) {
    unsigned size = message._data->_messages.size();
    for (unsigned i = 0; i < size; ++i) {
        std::string& msg = message._data->_messages[i];
        os << "Severity: " << message._data->_severity << ", Message: " << msg << std::endl;
    }

    return os;
}
#endif








