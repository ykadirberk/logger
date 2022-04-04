#ifndef LOG_H_20220404
#define LOG_H_20220404

#include "Utils.h"
#include "LoggerStream.h"

#define LOGT(type)		logger::LoggerStream::LoggerStream(type, __FILE__, __LINE__)

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