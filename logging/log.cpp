/**
 * @file log.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <locale>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/expressions/predicates/has_attr.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "logging/log.h"
#include "logging/terminal.h"

namespace logging {

template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, severity_level lvl) {
    static const char* const str[] = {
        GzRedBold "[F]" GzReset,
        GzYellowBold "[M]" GzReset,
        GzPurpleBold "[m]" GzReset,
        GzCyan "{I}" GzReset,
        GzLime"{C}" GzReset,
        GzBlue "{D}" GzReset,
        GzTeal"(e)" GzReset,
        GzNavy "(x)" GzReset,
        GzGreen "(i)" GzReset
    };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str))) {
        strm << str[lvl];
    } else {
        strm << static_cast<int>(lvl);
    }
    return strm;
}

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(module, "Module", std::string)

boost::shared_ptr<sink_t> logger::sink = nullptr;

bool logger::init(std::string log_path) {
  boost::log::add_common_attributes();
  boost::shared_ptr<boost::log::core> lg_core = boost::log::core::get();
#ifdef LOG_SCOPE
  lg_core->add_global_attribute("Scope", boost::log::attributes::named_scope());
#endif  // LOG_SCOPE
  sink = boost::log::add_console_log();
  sink->imbue(boost::locale::generator()("en_US.UTF-8"));
  sink->set_formatter(boost::log::expressions::stream
    << "" GzViolet << boost::log::expressions::format_date_time<
      boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
#ifdef LOG_TID
    << "[" << boost::log::expressions::attr<
      boost::log::attributes::current_process_name::value_type>("Process") << "] "
#endif  // LOG_TID
    << severity.or_default(MAJOR)

    << boost::log::expressions::if_(boost::log::expressions::has_attr(module)
    [ 
        boost::log::expressions::stream << GzLimeBold " " << std::setw(8) << module
    ]
#ifdef LOG_SCOPE
    .else_
    [
      boost::log::expressions::stream << " " GzOrange
        << boost::log::expressions::format_named_scope(
          "Scope", boost::log::keywords::format = "%n (%f:%l) ", boost::log::keywords::depth = 1)
    ]
#endif  // LOG_SCOPE

    << GzReset " " << boost::log::expressions::smessage);
  lg_core->add_sink(sink);
  return true;
}

void logger::stop() {
  if (!sink) return;
  boost::shared_ptr<boost::log::core> lg_core = boost::log::core::get();
  lg_core->remove_sink(sink);
  sink->flush();
  sink.reset();
}

}  // namespace logging
