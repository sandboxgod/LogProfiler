//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include "spdlog/common.h"
#include "spdlog/details/os.h"

#include <string>
#include <utility>

namespace spdlog {
namespace details {
struct log_msg
{
    log_msg() = default;

    log_msg(const std::string *loggers_name, level::level_enum lvl, string_view_t view)
        : logger_name(loggers_name)
        , level(lvl)
#ifndef SPDLOG_NO_DATETIME
        , time(os::now())
#endif

#ifndef SPDLOG_NO_THREAD_ID
        , thread_id(os::thread_id())
        , payload(view)
#endif
    {
    }

    log_msg(const log_msg &other) = default;
    log_msg &operator=(const log_msg &other) = default;

    const std::string *logger_name{nullptr};
    level::level_enum level{level::off};
    log_clock::time_point time;
    size_t thread_id{0};
    size_t msg_id;

    // info about wrapping the formatted text with color (updated by pattern_formatter).
    mutable size_t color_range_start{0};
    mutable size_t color_range_end{0};

    const string_view_t payload;
};
} // namespace details
} // namespace spdlog
