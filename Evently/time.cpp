#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <array>
#include <stdexcept>
#include <string>
#include "calendar.h"

namespace Time {
	std::string getCurrentTime() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		std::string time = std::to_string(now_tm->tm_hour) + ":" +
			std::string(2 - std::min(2, static_cast<int>(std::to_string(now_tm->tm_min).length())), '0').append(std::to_string(now_tm->tm_min)) + ":" +
			std::string(2 - std::min(2, static_cast<int>(std::to_string(now_tm->tm_sec).length())), '0').append(std::to_string(now_tm->tm_sec));
		return time;
	}

	std::string getCurrentDate() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		std::string date = std::to_string(now_tm->tm_mon + 1) + "/" + std::to_string(now_tm->tm_mday) + "/" + std::to_string(now_tm->tm_year + 1900);
		return date;
	}

	int getCurrentYear() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_year + 1900;
	}

	// 1-indexed month (1 = January, 2 = February, etc.)
	int getCurrentMonth() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_mon + 1;
	}

	// 1-indexed day (1 = 1st, 2 = 2nd, etc.)
	int getCurrentDay() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_mday;
	}

	int getCurrentHour() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_hour;
	}

	int getCurrentMinute() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_min;
	}

	int getCurrentSecond() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_sec;
	}

	// 0-indexed weekday (0 = Sunday, 1 = Monday, etc.)
	int getCurrentWeekday() {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* now_tm = std::localtime(&now_c);
		return now_tm->tm_wday;
	}

	// 100 * hour + 1 * minute UTC offset
	int getCurrentTimeZone() {
		std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm* now_tm = std::localtime(&now_c);
		int yday = now_tm->tm_yday;
		int hour = now_tm->tm_hour;
		int minute = now_tm->tm_min;
		std::tm* now_utc_tm = std::gmtime(&now_c);
		if (now_utc_tm->tm_yday > yday || (now_utc_tm->tm_yday >= 364 && yday == 0)) {
			hour -= 24;
		}
		hour -= now_utc_tm->tm_hour;
		minute -= now_utc_tm->tm_min;
		return 100 * hour + minute;
	}

	std::string getCurrentTimeZoneString() {
		int timeZone = getCurrentTimeZone();
		return ((timeZone < 0) ? "UTC" : "UTC+") + std::to_string(static_cast<int>(timeZone / 100)) + ":" +
			std::string(2 - std::min(2, static_cast<int>(std::to_string(timeZone % 100).length())), '0').append(std::to_string(timeZone % 100));
	}
}