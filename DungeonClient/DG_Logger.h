#ifndef _DG_LOGGER_H_
#define _DG_LOGGER_H_

#include "DG_Utils.h"

#include <queue>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>

class DG_Logger
{
public:
	enum class Type { INFO, WARN, ERROR };
	static void InitIO();
	static void QuitIO();
	static void Log(const std::string& msg, Type type = Type::INFO);
	static void Log(const std::string& msg, const std::string& type_name);

private:
	static bool __ms__bInitialized;
	static std::ofstream __ms__ofOutput;
	static std::queue<std::string> __ms_qeTask;
	static std::mutex __ms_mtxLock;
	static std::thread __ms_tOutput;
};

#endif // !_DG_LOGGER_H_
