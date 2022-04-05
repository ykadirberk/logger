#ifndef LOG_H_20220404
#define LOG_H_20220404

#include "Utils.h"
#include "LoggerStream.h"

// these 3 macros needed to make use of wstring_view
#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define WFILE WIDE1(__FILE__)

// with function call
#define LOGT(type)		logger::LoggerStream::LoggerStream(type, WFILE, __LINE__)

#define LOG				LOGT(logger::LogType::None)
#define DEBUG_LOG		LOGT(logger::LogType::Debug)
#define INFO_LOG		LOGT(logger::LogType::Info)
#define WARNING_LOG		LOGT(logger::LogType::Warning)
#define ERROR_LOG		LOGT(logger::LogType::Error)

#define LOGI			INFO_LOG
#define LOGD			DEBUG_LOG
#define LOGW			WARNING_LOG
#define LOGE			ERROR_LOG

#endif