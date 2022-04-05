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
				std::wstringstream fileNameStream;
				fileNameStream.clear();
				fileNameStream
					<< logger::Utils::GetCurrentTimeAs_YMD()
					<< '-'
					<< logger::Utils::GetCurrentTimeAs_HH_MM_SS_MS()
					<< "_logs.txt";

				std::wstring fileName = fileNameStream.str();

				logger::Utils::SetOutputFile(fileName);
			}
			static void Destroy() 
			{
				logger::Utils::file_s.close();
			}

			static inline std::wofstream file_s;


			static std::wstring GetCurrentTimeAs_YMD()
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

				std::wstringstream concatenateStream;
				concatenateStream.clear();
				concatenateStream
					<< static_cast<int>(ymd.year()) << '_'
					<< static_cast<unsigned>(ymd.month()) << '_'
					<< static_cast<unsigned>(ymd.day());
				return concatenateStream.str();
			}
			static std::wstring GetCurrentTimeAs_HH_MM_SS_MS()
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

				std::wstringstream concatenateStream;
				concatenateStream.clear();
				concatenateStream
					<< time.hours() << '_'
					<< time.minutes() << '_'
					<< time.seconds() << '_'
					<< time.subseconds();
				return concatenateStream.str();
			}

			static std::wstring SplitFileName(std::wstring_view str)
			{
				// __FILE__ macro is returning full path,
				// this method is to get only the file name out of it
				std::size_t found = str.find_last_of(L"/\\");
				return std::wstring(str.substr(found + 1));
			}

			static void SetOutputFile(std::wstring_view fileName) 
			{
				// this is for debug purposes
				// uncomment if you need to check if fileName is right
				// std::cerr << fileName << std::endl;

				// creates logs folder so that log files will be in a proper folder
				if (!std::filesystem::exists("logs")) {
					std::filesystem::create_directory("logs");
				}

				// to concatenate the logs folder with fileName
				std::wstringstream pathFile;
				pathFile << L"logs\\" << fileName;

				std::wstring fullPath = pathFile.str();

				logger::Utils::file_s.open(fullPath);
			}

			static std::wstring GetStringOfLogType(LogType logType) 
			{
				switch (logType) 
				{
					case LogType::None: return L"";
					case LogType::Debug: return L"[DEBUG]";
					case LogType::Info: return L"[INFO]";
					case LogType::Warning: return L"[WARNING]";
					case LogType::Error: return L"[ERROR]";
					default: throw std::invalid_argument("Unimplemented item");
				}
			}
	};
}

#endif

