#ifndef UTILS_H_20220401
#define UTILS_H_20220401

#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

namespace logger
{
	enum class LogType : char {
		None,
		Debug,
		Info,
		Warning,
		Error
	};

	class Utils
	{
		public:
			Utils() {}
			~Utils() {}

			static void Initialize() 
			{
				// retrieves the date to construct a file name
				std::stringstream fileNameStream;
				fileNameStream.clear();
				fileNameStream
					<< logger::Utils::GetCurrentTimeAs_YMD()
					<< '-'
					<< logger::Utils::GetCurrentTimeAs_HH_MM_SS_MS()
					<< "_logs.txt";

				std::string fileName = fileNameStream.str();

				logger::Utils::SetOutputFile(fileName);
			}
			static void Destroy() 
			{
				logger::Utils::file_s.close();
			}

			static inline std::ofstream file_s;


			static std::string GetCurrentTimeAs_YMD()
			{
				// This method returns 
				// years, months and days
				// in this format:
				// yyyy-mm-dd
				auto tp{
					std::chrono::zoned_time{
						std::chrono::current_zone(),
						std::chrono::system_clock::now()
					}.get_local_time()
				};
				auto dp{ std::chrono::floor<std::chrono::days>(tp) };
				std::chrono::year_month_day ymd{ dp };

				std::stringstream concatenateStream;
				concatenateStream.clear();
				concatenateStream
					<< static_cast<int>(ymd.year()) << '_'
					<< static_cast<unsigned>(ymd.month()) << '_'
					<< static_cast<unsigned>(ymd.day());
				return concatenateStream.str();
			}
			static std::string GetCurrentTimeAs_HH_MM_SS_MS()
			{
				// This method returns 
				// hours, minutes, seconds and milliseconds
				// in this format:
				// hh:mm:ss.ms
				auto tp{
					std::chrono::zoned_time{
						std::chrono::current_zone(),
						std::chrono::system_clock::now()
					}.get_local_time()
				};
				auto dp{ std::chrono::floor<std::chrono::days>(tp) };
				std::chrono::hh_mm_ss time{ std::chrono::floor<std::chrono::milliseconds>(tp - dp) };

				std::stringstream concatenateStream;
				concatenateStream.clear();
				concatenateStream
					<< time.hours() << '_'
					<< time.minutes() << '_'
					<< time.seconds() << '_'
					<< time.subseconds();
				return concatenateStream.str();
			}

			static std::string SplitFileName(const std::string& str)
			{
				// __FILE__ macro is returning full path,
				// this method is to get only the file name out of it
				std::size_t found = str.find_last_of("/\\");
				return str.substr(found + 1);
			}

			static void SetOutputFile(const std::string& fileName) 
			{
				// this is for debug purposes
				// uncomment if you need to check if fileName is right
				// std::cerr << fileName << std::endl;

				// creates logs folder so that log files will be in a proper folder
				if (!std::filesystem::exists("logs")) {
					std::filesystem::create_directory("logs");
				}

				// to concatenate the logs folder with fileName
				std::stringstream pathFile;
				pathFile << "logs\\" << fileName;

				std::string fullPath = pathFile.str();

				logger::Utils::file_s.open(fullPath);
			}

			static std::string GetStringOfLogType(LogType logType) 
			{
				switch (logType) 
				{
					case LogType::None: return "";
					case LogType::Debug: return "[DEBUG]";
					case LogType::Info: return "[INFO]";
					case LogType::Warning: return "[WARNING]";
					case LogType::Error: return "[ERROR]";
					default: throw std::invalid_argument("Unimplemented item");
				}
			}
	};
}

#endif

