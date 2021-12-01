#include <SDL.h>
#include <SDL_image.h>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <filesystem>

#include "DG_Assert.h"
#include "DG_Sprite.h"

SDL_Window*		g_pWindow;
SDL_Renderer*	g_pRenderer;

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

void OnQuitGame()
{
	DG_Logger::QuitIO();
}

#undef main
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	DG_Logger::InitIO();

	std::filesystem::directory_iterator itor_skins("assets/skins");
	for (const std::filesystem::directory_entry& itor : itor_skins)
	{
		std::filesystem::path path_skin_folder = itor.path();
		cJSON* pjson_config = nullptr;
		DG_Assert(pjson_config = LoadJSON((path_skin_folder / "config.json").string()));
		std::map<std::string, SDL_Surface*> map_filename_surface;
		cJSON* pjson_item = nullptr;
		cJSON* pjson_list_walk = cJSON_GetObjectItem(pjson_config, "walk");
		DG_Assert(pjson_list_walk && pjson_list_walk->type == cJSON_Array);
		cJSON_ArrayForEach(pjson_item, pjson_list_walk)
		{
			if (map_filename_surface.find(pjson_item->valuestring) != map_filename_surface.end())
			{
				map_filename_surface.insert(std::make_pair(pjson_item->valuestring, IMG_Load((path_skin_folder / pjson_item->valuestring).string().c_str())));
			}
		}
	}
}