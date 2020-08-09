
#include <cstdarg>                 // std::va_list, va_copy, va_start, va_end
#include <messaging/log_message.h> // LogMessage

namespace Messaging {
    //------------------------------------------------------------------------------------------------------------------
    // LOG MESSAGE DATA
    //------------------------------------------------------------------------------------------------------------------
    class LogMessage::LogMessageData {
        public:
            /**
             * Allocates the necessary buffers to be able to process log messages.
             */
            explicit LogMessageData(LogMessageSeverity messageSeverity);

            /**
             * Cleans up information related to message processing.
             */
            ~LogMessageData();

        #ifndef DEBUG_MESSAGES
            /**
             * Helper function to process printf-like message with variadic arguments. Emplaces processed message into
             * log record information store.
             * @param formatString - Printf-like format string for log messages.
             * @param argList      - Printf-like variadic arguments.
             * @return Pointer to the buffer which holds the processed message.
             */
            void ProcessMessage(const char* formatString, std::va_list argList);
        #else

            /**
             * Helper function to process printf-like message with variadic arguments. Emplaces processed message into
             * log record information store.
             * @param formatString - Printf-like format string for log messages.
             * @param argList      - Printf-like variadic arguments.
             * @param logRecord    - Log record information.
             * @return Pointer to the buffer which holds the processed message.
             */
            void ProcessMessage(const char* formatString, std::va_list argList, DBG_LOG_RECORD logRecord);
        #endif

            /**
             * Print out the log message to the provided stream.
             * @param stream  - Stream to print to.
             * @return Stream with message data.
             */
            std::ostream& PrintMessage(std::ostream& stream);

        private:
            std::vector<LogRecord> _logMessages; // Store of log record information
            LogMessageSeverity _messageSeverity; // Message severity

            unsigned _processingBufferSize; // Size of the processing buffer.
            char* _processingBuffer;        // Pointer to the processing buffer.
    };

    // Allocates the necessary buffers to be able to process log messages.
    LogMessage::LogMessageData::LogMessageData(LogMessageSeverity messageSeverity) : _messageSeverity(messageSeverity),
                                                                                     _processingBufferSize(64u)
    {
        // Start buffer with (baseline) 64 byte size.
        _processingBuffer = new char[_processingBufferSize];
    }

    // Cleans up information related to message processing.
    LogMessage::LogMessageData::~LogMessageData() {
        delete [] _processingBuffer;
    }


    //------------------------------------------------------------------------------------------------------------------
    // LOG MESSAGE
    //------------------------------------------------------------------------------------------------------------------
    // Construct an instance of a message to log.
    LogMessage::LogMessage(LogMessageSeverity messageSeverity) : _data(new LogMessageData(messageSeverity)) {
        // Nothing to do here.
    }

    // Log message destructor.
    LogMessage::~LogMessage() {
        delete _data;
    }

    std::ostream &LogMessage::LogMessageData::PrintMessage(std::ostream &stream) {
        switch (_messageSeverity) {
            case LogMessageSeverity::DEBUG:
                stream << "[ DEBUG ]" << std::endl;
                break;
            case LogMessageSeverity::WARNING:
                stream << "[ WARNING ]" << std::endl;
                break;
            case LogMessageSeverity::SEVERE:
                stream << "[ SEVERE ]" << std::endl;
                break;
        }

        // Print out given messages: [0000m 0000s 00000ms] - MESSAGE
        for (auto& logRecord : _logMessages) {
            stream << "[ " << logRecord._timestamp << " ] - " << logRecord._message << std::endl;
        #ifdef DEBUG_MESSAGES
            stream << "\t: called from file: " << logRecord._calleeInformation._fileName << ", at " << logRecord._calleeInformation._functionName << ":" << logRecord._calleeInformation._lineNumber << std::endl;
        #endif
        }

        return stream;
    }

#ifdef DEBUG_MESSAGES
    // Construct a debug log record to store callee information about a logged message.
    DBG_LOG_MESSAGE::DBG_LOG_RECORD::DBG_LOG_RECORD(std::string filename, std::string functionName, int lineNumber) : _fileName(std::move(filename)),
                                                                                                                      _functionName(std::move(functionName)),
                                                                                                                      _lineNumber(lineNumber) {
        // Nothing to do here.
    }

    // Construct a log record to store information about a logged message.
    DBG_LOG_MESSAGE::LogRecord::LogRecord(std::string message, Timing::TimeStamp timestamp, DBG_LOG_RECORD calleeInformation) : _message(std::move(message)),
                                                                                                                                _timestamp(std::move(timestamp)),
                                                                                                                                _calleeInformation(std::move(calleeInformation)) {
        // Nothing to do here.
    }

    // Supply an additional message to be appended to this message instance. Allows for multi-line messages by
    // supplying to the same message more than once.
    void DBG_LOG_MESSAGE::SUPPLY_DBG(std::string callingFunction, std::string fileName, int lineNumber, const char* formatString, ...) {
        std::va_list args;
        va_start(args, formatString);
        _data->ProcessMessage(formatString, args, DBG_LOG_RECORD(std::move(callingFunction), std::move(fileName), lineNumber));
        va_end(args);
    }

    std::ostream &operator<<(std::ostream &stream, const DBG_LOG_MESSAGE &message) {
        message._data->PrintMessage(stream);
        return stream;
    }

    // Helper function to process printf-like message with variadic arguments.
    void LogMessage::LogMessageData::ProcessMessage(const char* formatString, std::va_list argList, DBG_LOG_RECORD logRecord) {
        unsigned currentBufferSize = _processingBufferSize;

        // Copy args list to not modify passed parameters (yet).
        std::va_list argsCopy;
        va_copy(argsCopy, argList);

        // If size of the buffer is zero, nothing is written and buffer may be a null pointer, however the return
        // value (number of bytes that would be written not including the null terminator) is still calculated and returned.
        int writeResult = vsnprintf(nullptr, 0, formatString, argsCopy);

        // If buffer size is equal to write result, there will not be space for the null terminator for the string.
        // Multiple buffer size by two to adequately house string in a new buffer.
        while (_processingBufferSize <= writeResult) {
            _processingBufferSize *= 2;
        }

        // Reallocate buffer.
        if (currentBufferSize != _processingBufferSize) {
            delete [] _processingBuffer;
            _processingBuffer = new char[_processingBufferSize];
        }

        vsnprintf(_processingBuffer, _processingBufferSize, formatString, argList);
        _logMessages.emplace_back(_processingBuffer, Timing::TimeStamp(), std::move(logRecord));
    }
#else
    // Construct an instance of a message to log.
    LogMessage::LogRecord::LogRecord(std::string message, Timing::TimeStamp timestamp) : _message(std::move(message)),
                                                                                         _timestamp(std::move(timestamp)) {
        // Nothing to do here.
    }

    // Supply an additional message to be appended to this message instance. Allows for multi-line messages by
    // supplying to the same message more than once.
    void LogMessage::Supply(const char* formatString, ...) {
        std::va_list args;
        va_start(args, formatString);
        _data->ProcessMessage(formatString, args);
        va_end(args);
    }

    std::ostream &operator<<(std::ostream &stream, const LogMessage &message) {
        message._data->PrintMessage(stream);
        return stream;
    }

    // Helper function to process printf-like message with variadic arguments.
    void LogMessage::LogMessageData::ProcessMessage(const char* formatString, std::va_list argList) {
        unsigned currentBufferSize = _processingBufferSize;

        // Copy args list to not modify passed parameters (yet).
        std::va_list argsCopy;
        va_copy(argsCopy, argList);

        // If size of the buffer is zero, nothing is written and buffer may be a null pointer, however the return
        // value (number of bytes that would be written not including the null terminator) is still calculated and returned.
        int writeResult = vsnprintf(nullptr, 0, formatString, argsCopy);

        // If buffer size is equal to write result, there will not be space for the null terminator for the string.
        // Multiple buffer size by two to adequately house string in a new buffer.
        while (_processingBufferSize <= writeResult) {
            _processingBufferSize *= 2;
        }

        // Reallocate buffer.
        if (currentBufferSize != _processingBufferSize) {
            delete [] _processingBuffer;
            _processingBuffer = new char[_processingBufferSize];
        }

        vsnprintf(_processingBuffer, _processingBufferSize, formatString, argList);
        _logMessages.emplace_back(_processingBuffer, Timing::TimeStamp());
    }
#endif
}
