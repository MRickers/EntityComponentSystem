
#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

enum class Loglevel : int { L_ALL = 0, L_DEBUG = 10, L_INFO = 30, L_WARN = 50, L_ERROR = 70 };

namespace logging {
	class Logger {
		static inline Loglevel log_level_ = Loglevel::L_ALL;
	private:
		static inline std::ostream* stream_ = &std::cout;
		static inline std::ofstream ostream_;
		std::stringstream sstream_;

		constexpr const char* file_name(const char* path) {
			const char* file = path;
			while (*path) {
#if _WIN32
				if (*path++ == '\\') {
					file = path;
				}
#elif __linux__
				if (*path++ == '/') {
					file = path;
				}
#endif
			}
			return file;
		}

		constexpr const char* convertLevel(Loglevel level) const {
			switch (level) {
			case Loglevel::L_DEBUG:
				return " [Debug]";
			case Loglevel::L_INFO:
				return " [Info]";
			case Loglevel::L_WARN:
				return " [Warn]";
			case Loglevel::L_ERROR:
				return " [Error]";
			default:
				return " [All]";
			}
		}

		std::string formatLogging(const Loglevel level, const std::string& file, const int line) {
			std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
			std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch());
			size_t ms_frac = ms.count() % 1000;
			std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
			std::time_t t = s.count();

			std::stringstream ss{};
			ss << std::put_time(std::localtime(&t), "%F %T") << "." << ms_frac << " " << std::this_thread::get_id()
				<< " " << file_name(file.c_str()) << ":" << line << convertLevel(level) << ": ";
			return ss.str();
		}

	public:
		Logger(std::ostream& stream = std::cout) :
			sstream_()
		{}

		~Logger() {
			*stream_ << sstream_.str() << std::endl;
		}
		std::ostream& Get(const Loglevel level, const std::string& file, const int line) {
			sstream_ << formatLogging(level, file, line);
			return sstream_;
		}
		/*
		template<typename T>
		Logger& operator<<(const T& data) {
			sstream_ << data;

			return *this;
		} */

		static void SetLogLevel(const Loglevel level) {
			log_level_ = level;
		}

		static const Loglevel GetLogLevel() {
			return log_level_;
		}

		static void SetStream(std::ostream& stream) {
			stream_ = &stream;
		}

		static void LogToFile(const std::string& filename) {
			ostream_.open(filename, std::ios::out | std::ios::app);
			stream_ = &ostream_;
		}
	};
}

#define lLog(level) if(level < logging::Logger::GetLogLevel());else logging::Logger().Get(level, __FILE__, __LINE__)

#define lAll	(Loglevel::L_ALL)
#define lDebug	(Loglevel::L_DEBUG)
#define lInfo	(Loglevel::L_INFO)
#define lWarn	(Loglevel::L_WARN)
#define lError	(Loglevel::L_ERROR)