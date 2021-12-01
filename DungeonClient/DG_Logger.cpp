#include "DG_Logger.h"

bool DG_Logger::__ms__bInitialized = false;

std::ofstream DG_Logger::__ms__ofOutput;

std::queue<std::string> DG_Logger::__ms_qeTask;

std::mutex DG_Logger::__ms_mtxLock;

std::thread DG_Logger::__ms_tOutput;

void DG_Logger::InitIO()
{
	if (!__ms__bInitialized)
	{
		__ms__ofOutput = std::ofstream("logs/" + DG_GetFormattedTime()
			.append(std::to_string(SDL_GetPerformanceCounter()))
			.append(".txt"), std::ios::out | std::ios::app);
		__ms__bInitialized = true;

		__ms_tOutput = std::thread(
			[&]() -> void
			{
				while (true)
				{
					while (__ms_qeTask.empty())
						std::this_thread::sleep_for(std::chrono::milliseconds(100));

					__ms_mtxLock.lock();
					while (!__ms_qeTask.empty())
					{
						const std::string& strLogInfo = __ms_qeTask.front();

						std::cout << strLogInfo << std::endl;

						if (__ms__ofOutput.good())
							__ms__ofOutput << strLogInfo << std::endl;
						else
							std::cout << "[Log File IO Exception]" << std::endl;

						__ms_qeTask.pop();
					}
					__ms_mtxLock.unlock();

					if (!__ms__bInitialized)
						std::this_thread::yield();
				}
			}
		);

		__ms_tOutput.detach();
	}
}

void DG_Logger::QuitIO()
{
	if (__ms__bInitialized)
	{
		__ms_mtxLock.lock();
		__ms__ofOutput.close();
		__ms__ofOutput.clear();
		__ms__bInitialized = false;
		__ms_mtxLock.unlock();
	}
}

void DG_Logger::Log(const std::string& msg, Type type)
{
	std::string strLogInfo = std::string("[") 
		+ (type == DG_Logger::Type::INFO ? "INFO" : 
			(type == DG_Logger::Type::ERROR ? "ERROR" : "WARN")) 
		+ "][" + DG_GetFormattedTime() + "]" + msg;

	__ms_mtxLock.lock();
	__ms_qeTask.push(strLogInfo);
	__ms_mtxLock.unlock();
}

void DG_Logger::Log(const std::string& msg, const std::string& type_name)
{
	std::string strLogInfo = "[" + type_name + "][" 
		+ DG_GetFormattedTime() + "]" + msg;

	__ms_mtxLock.lock();
	__ms_qeTask.push(strLogInfo);
	__ms_mtxLock.unlock();
}
