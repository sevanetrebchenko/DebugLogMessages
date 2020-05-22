#ifndef SANDBOX_LOGMESSAGE_H
#define SANDBOX_LOGMESSAGE_H
#include <memory>   // unique_ptr
#include <cstring>  // strrchr

//#define DEBUG_MESSAGES

class LogMessage {
    public:
        explicit LogMessage(unsigned messageSeverity);
        ~LogMessage();
        void Supply(const char* formatString, ...);
        friend std::ostream& operator<<(std::ostream& os, const LogMessage& message);

    private:
        // Opaque pointer to abstract data
        class LogMessageData;
        std::unique_ptr<LogMessageData> _data;
};

#ifdef DEBUG_MESSAGES
// Class captures caller and records debug information
class DBG_LOG_MESSAGE {
    public:
        explicit DBG_LOG_MESSAGE(unsigned int);
        ~DBG_LOG_MESSAGE();
        void SUPPLY_DBG(std::string&& callingFunction, std::string&& fileName, int lineNumber, const char* formatString, ...);
        friend std::ostream& operator<<(std::ostream& os, const DBG_LOG_MESSAGE& message);

    private:
        // Opaque pointer to abstract data
        class LogMessageData;
        std::unique_ptr<LogMessageData> _data;
};

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#undef LogMessage
#define LogMessage DBG_LOG_MESSAGE
#undef Supply
#define Supply(formatString, ...) SUPPLY_DBG(__PRETTY_FUNCTION__, __FILENAME__, __LINE__, formatString, ##__VA_ARGS__)
#endif

#endif //SANDBOX_LOGMESSAGE_H
