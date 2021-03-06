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


