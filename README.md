# Logger

Logger is a lightweight, header-only logging library for C++. It supports multiple log levels, thread safety (optional), and the ability to log messages to both the console and a file.

## Features
- Header-only implementation (just include `logger.hpp`)
- Supports log levels: TRACE, DEBUG, INFO, WARNING, ERROR, and FATAL
- Thread-safe logging (optional, enabled by default)
- Supports both message-based and stream-based logging
- Can log messages to a file in addition to the console

## Usage

### Basic Logging
```cpp
#include "logger.hpp"

int main() {
    LOG_INFO_MSG("This is an info message");
    LOG_WARNING_MSG("This is a warning");
    LOG_ERROR_MSG("This is an error");

    LOG_DEBUG << "Debugging value: " << 42;
    return 0;
}
```

### Logging to a File and Console
Logger supports logging to a file by calling `setLogFile()`. 

```cpp
#include "logger.hpp"

int main() {
    Logger::getInstance().setLogFile("log.txt");

    LOG_INFO << "This message will be logged to both console and log.txt";
    LOG_ERROR << "Errors are logged in both places too";
    return 0;
}
```

## Installation
Logger is a header-only library, so you just need to include `logger.hpp` in your project. No need to compile anything separately.


## License
This project is licensed under the MIT License.
