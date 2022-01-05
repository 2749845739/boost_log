// #define BOOST_LOG_DYN_LINK 1
#include <boost/log/core.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/trivial.hpp>

int main(int argc, char *argv[]) {
  BOOST_LOG_TRIVIAL(trace) << "测试中文能否正确输出（GBK编码）";

  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

  return 0;

}
// 编译指令
// g++ log_trivial.cpp -o log_trivial -DBOOST_LOG_DYN_LINK  -lboost_log -lpthread
