//
// Created by demiaowu on 2017/3/24.
//
#include <cstdio>
#include <cstdlib>

#include "logger.h"

namespace chat {
    namespace common {

        logger::log_level init_log_level() {
            return logger::INFO;
        }

        void default_output(const char *msg, int len) {
            size_t n = ::fwrite(msg, 1, len, stdout); // The best is ::stdout, but it cannot pass the compile for mingw in windows
            (void)n;
        }

        void default_flush() {
            ::fflush(stdout);
        }

        logger::log_level g_log_level = init_log_level();
        logger::output_func g_output = default_output;
        logger::flush_func g_flush = default_flush;

        const char* log_level_names[logger::NUM_LOG_LEVELS] = {
                "TRACE",
                "DEBUG",
                "INFO",
                "WARN",
                "ERROR",
                "FATAL",
        };

        logger::logger(const char* file, int line, logger::log_level level, const char *func) {
            level_ = level;
            stream_ << log_level_names[level_] << file << func<< line;
        }

        logger::~logger() {
            // ' ' -> '\n'
            std::string result = stream_.oss_.str();
            result.pop_back();      // pop the char of blank
            result.push_back('\n'); // push '\n' on the last of the log string
            g_output(result.c_str(), result.size());
            if (level_ == FATAL) {
                g_flush();
                ::abort();
            }
        }

        logger::log_level logger::get_log_level() {
            return g_log_level;
        }

        void logger::set_log_level(logger::log_level level) {
            g_log_level = level;
        }

        std::string logger::get_log_level_name() {
            return std::string(log_level_names[g_log_level]);
        }

        void logger::set_output(logger::output_func out) {
            g_output = out;
        }

        void logger::set_flush(logger::flush_func flush) {
            g_flush = flush;
        }


    }//common namespace
}//chat namespace