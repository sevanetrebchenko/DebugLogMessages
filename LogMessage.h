#ifndef SANDBOX_LOGMESSAGE_H
#define SANDBOX_LOGMESSAGE_H
#include <memory> // unique ptr

#define DEBUG_MESSAGES

class LogMessage {
    public:
        explicit LogMessage(unsigned messageSeverity);
        ~LogMessage();
        std::string Supply(const char* formatString, ...);

    private:
        // Opaque pointer to abstract data - data should not be available
        class LogMessageData;
        std::unique_ptr<LogMessageData> _data;
};

#ifdef DEBUG_MESSAGES
// class to capture the caller and print it.
class DBG_LOG_MESSAGE {
    public:
        explicit DBG_LOG_MESSAGE(unsigned int);
        ~DBG_LOG_MESSAGE();
        std::string Supply_Aux(const std::string& callingFunction, const std::string& fileName, int lineNumber, const char* formatString, ...);

    private:
        class LogMessageData;
        std::unique_ptr<LogMessageData> _data;
};

#undef LogMessage
#define LogMessage DBG_LOG_MESSAGE
#undef Supply
#define Supply(formatString, ...) Supply_Aux(__FUNCTION__, __FILE__, __LINE__, formatString, __VA_ARGS__)
#endif

#endif //SANDBOX_LOGMESSAGE_H
