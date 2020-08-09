
#ifndef TIMING_TIMESTAMP_H
#define TIMING_TIMESTAMP_H

#include <global_includes.h> // _NODISCARD_
#include <ostream>            // std::ostream

namespace Timing {

    class TimeStamp {
        public:
            /**
             * Sets the base initialization time for all timestamps to base off of.
             * @return
             */
            static void Initialize();

            /**
            * Constructor for a timestamp. Uses std::chrono::high_resolution_clock::now() (time when constructor was
            * called) as the time record.
            */
            TimeStamp();

            /**
            * Timestamp move constructor.
            * @param other - Timestamp to move data from.
            */
            TimeStamp(TimeStamp&& other) noexcept;

            /**
            * Timestamp destructor.
            */
            ~TimeStamp();

            /**
            * Get only the millisecond portion of this timestamp.
            * @return Millisecond portion of this timestamp.
            */
            _NODISCARD_ unsigned GetMillis() const;

            /**
            * Get only the second portion of this timestamp.
            * @return Second portion of this timestamp.
            */
            _NODISCARD_ unsigned GetSeconds() const;

            /**
            * Get only the minute portion of this timestamp.
            * @return Minute portion of this timestamp.
            */
            _NODISCARD_ unsigned GetMinutes() const;

            /**
            * Print this timestamp to the provided stream.
            * @param os    - Stream to print to.
            * @param stamp - Timestamp object to print.
            * @return Printed-to stream.
            */
            friend std::ostream& operator<<(std::ostream& os, const TimeStamp& stamp);

        private:
            // Storage for Timestamp data, back-end functionality, and helper functions.
            struct TimeStampData;
            TimeStampData* _data;
    };

} // namespace Timing

#endif // TIMING_TIMESTAMP_H
