#include <iostream>
#include <ostream>
#include <source_location>
#include <string>

class Logger {
 public:
  Logger(const std::source_location& source_location = std::source_location::current(),
         std::ostream& output_stream = std::cout)
      : location_(source_location), output_stream_(output_stream) {
    log("function entered", location_, output_stream_);
  }

  static void log(
      const std::string& message,
      const std::source_location location = std::source_location::current(),
      std::ostream& output_stream = std::cout) {
    output_stream << location.function_name() << " log: " << message
                  << std::endl;
  }

  ~Logger() { log("function exited", location_, output_stream_); }

 private:
  std::source_location location_;
  std::ostream& output_stream_;
};

void foo() {
  Logger logger;
  std::cout << "hi there!" << std::endl;
}

int main() { foo(); Logger::log("cringe string");}