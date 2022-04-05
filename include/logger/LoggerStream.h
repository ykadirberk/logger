#ifndef LOGGER_STREAM_H_20220403
#define LOGGER_STREAM_H_20220403

#include "Utils.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

namespace logger {
	class LoggerStream
	{
		public:
			LoggerStream(LogType logType, std::wstring_view fileName, int line) {
				mLogType = logType;
				mFileName = std::wstring(fileName);
				mLine = line;
			}

			LoggerStream(const LoggerStream& ls) {
				mLogType = ls.mLogType;
				mFileName = ls.mFileName;
				mLine = ls.mLine;
			}

			~LoggerStream() {
                // Sends the log to the log file

                // retrieves the current time in current time zone
                // and puts it into a stringstream to construct the string
                // as intended
                std::wstringstream timeHolder;
                timeHolder.clear();
                timeHolder
                    << logger::Utils::GetCurrentTimeAs_YMD() << ' '
                    << logger::Utils::GetCurrentTimeAs_HH_MM_SS_MS();

                std::wstring message = messageStream.str();

                // the output line is constructed here
                // example output should be like this:
                // [LOG:: yyyy_mm_dd hh_mm_ss_ms @file_name.ext:line_num] message
                std::wstringstream outputLine;
                outputLine.clear();
                outputLine
                    << "[LOG:: "
                    << timeHolder.str() << " @"
                    << logger::Utils::SplitFileName(mFileName) << ":"
                    << mLine << "]"
                    << logger::Utils::GetStringOfLogType(mLogType) << ' '
                    << message
                    << '\n';

                // defined an std::string to ensure there's
                // nothing wrong with the constructed output
                std::wstring resultString = outputLine.str();

                // this line is to debug this function
                // uncomment if you need to check if the output is right
                //std::cerr << resultString;

                // sends the resultString to the file named yyyy_mm_dd-hh_mm_ss_ms_logs.txt
                // in logs folder
                logger::Utils::file_s << resultString;
                logger::Utils::file_s.flush();
            }

			std::wstringstream messageStream;
			
			template<typename T>
			LoggerStream& operator<<( const T& t) {
				this->messageStream << t;
				return (*this);
			}

		private:
			LogType mLogType;
			std::wstring mFileName;
			int mLine;
	};
}


#endif

