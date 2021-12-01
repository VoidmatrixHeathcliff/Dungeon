#include "DG_Utils.h"

std::string DG_GetFormattedTime()
{
	time_t tmCurrent; time(&tmCurrent);
	tm tmMsg; localtime_s(&tmMsg, &tmCurrent);
	char strCurrentTime[64];
	strftime(strCurrentTime, sizeof(strCurrentTime), 
		"%Y_%m_%d_%H_%M_%S", &tmMsg);
	return strCurrentTime;
}