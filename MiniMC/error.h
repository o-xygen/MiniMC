#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#define DEBUG
class ErrorLog {
public:
	static void logError(const std::string& msg) {
		logs.push_back(msg);
#ifdef DEBUG
		cout << msg << endl;
#endif // DEBUG

	}

private:
	static std::vector<std::string> logs;
};