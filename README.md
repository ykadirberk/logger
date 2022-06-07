# Logger - A simple log library

## Initialization
Add the contents of the include folder to your project's include directories and include the Log.h file.
```cpp
#include <logger/Log.h>
```
Then call Initialize function somewhere that can execute code (main() etc.).
```cpp
int main() {
	logger::Utils::Initialize();
```

## Sample
```cpp
#include <logger/Log.h>

// logger is the namespace of this lib, can be avoided by uncommenting the code below
// but be wary, use at your own risk. it may conflict with other libraries.
//using namespace logger;

int main()
{
    // the initalization process is needed to prepare file operations
    logger::Utils::Initialize();

    // to send logs, any of the below can be used, more can be found in logger/Log.h
    LOG << "A LogType::None message.";
    LOGI << "A LogType::Info message.";
    LOGW << "A LogType::Warning message.";
    LOGD << "A LogType::Debug message";
    LOGE << "A LogType::Error message";

    LOGT(logger::LogType::Info) << "A message by using function, a LogType::Info message";

    // just closes the ofstream file, 
    // but everytime a log is sent the std::ofstream::flush is called 
    // so that the logger musn't be affected by crashes
    logger::Utils::Destroy();

    return EXIT_SUCCESS;
}
```

Output of sample will be something like this:
```
[LOG:: 2022_4_5 12h_44min_42s_50ms @sample.cpp:13] A LogType::None message.
[LOG:: 2022_4_5 12h_44min_42s_51ms @sample.cpp:14][INFO] A LogType::Info message.
[LOG:: 2022_4_5 12h_44min_42s_51ms @sample.cpp:15][WARNING] A LogType::Warning message.
[LOG:: 2022_4_5 12h_44min_42s_51ms @sample.cpp:16][DEBUG] A LogType::Debug message
[LOG:: 2022_4_5 12h_44min_42s_52ms @sample.cpp:17][ERROR] A LogType::Error message
[LOG:: 2022_4_5 12h_44min_42s_52ms @sample.cpp:19][INFO] A message by using function, a LogType::Info message
```
