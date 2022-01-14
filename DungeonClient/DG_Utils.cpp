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

cJSON* LoadJSON(std::string str_path)
{
	std::ifstream fin_json(str_path);
	if (!fin_json.good()) return nullptr;
	std::stringstream ss_json_content;
	ss_json_content << fin_json.rdbuf();
	fin_json.close(); fin_json.clear();
	cJSON* pjson = cJSON_Parse(ss_json_content.str().c_str());
	ss_json_content.clear();
	return pjson;
}