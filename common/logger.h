//
// Created by demiaowu on 2017/3/24.
//

#ifndef TCHAT_LOGGER_H
#define TCHAT_LOGGER_H
#include <sstream>

namespace chat {
    namespace common {

        class log_stream {
        public:
            template<typename T>
            log_stream& operator<<(const T& t) {
                oss_ << t << " ";
                return *this;
            }

        private:
            friend class logger;
            std::ostringstream oss_;
        };

        class logger {
        public:
            enum log_level {
                TRACE = 0,
                DEBUG,
                INFO,
                WARN,
                ERROR,
                FATAL,
                NUM_LOG_LEVELS,
            };

            //TODO
            class source_file {

            };

            logger(const char* file, int line, log_level level, const char* func);
            ~logger();

            log_stream& stream() {   return stream_; }

            static log_level get_log_level();
            static std::string get_log_level_name();
            static void set_log_level(log_level level);

            typedef void (*output_func)(const char*msg, int len);
            typedef void (*flush_func)();

            static void set_output(output_func);
            static void set_flush(flush_func);

        private:
            log_level level_;
            log_stream stream_;
        };//logger class

        #define LOG_TRACE if( chat::common::logger::get_log_level() <= chat::common::logger::TRACE )  \
            chat::common::logger(__FILE__, __LINE__, chat::common::logger::TRACE, __func__).stream()

        #define LOG_DEBUG if( chat::common::logger::get_log_level() <= chat::common::logger::DEBUG ) \
            chat::common::logger(__FILE__, __LINE__, chat::common::logger::DEBUG, __func__).stream()

        #define LOG_INFO if( chat::common::logger::get_log_level() <= chat::common::logger::INFO ) \
            chat::common::logger(__FILE__, __LINE__, chat::common::logger::INFO, __func__).stream()

        #define LOG_WARN chat::common::logger(__FILE__, __LINE__, logger::WARN, __func__).stream()

        #define LOG_ERROR chat::common::logger(__FILE__, __LINE__, logger::ERROR, __func__).stream()

        #define LOG_FATAL chat::common::logger(__FILE__, __LINE__, logger::FATAL, __func__).stream()

    }//common namespace
}//chat namespace


#endif //TCHAT_LOGGER_H
