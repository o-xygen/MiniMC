#pragma once
#include <string>
#include <vector>
class ErrorLog {
public:
	static void logError(const std::string& msg) {
		logs.push_back(msg);
	}

private:
	static std::vector<std::string> logs;
};

std::vector<std::string> ErrorLog::logs{};