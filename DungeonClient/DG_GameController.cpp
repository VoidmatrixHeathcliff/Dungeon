#include "DG_GameController.h"
#include "DG_Assert.h"

void DG_GameController::Init()
{
	// ����SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	// ������־
	DG_Logger::InitIO();
	// ��������Ƥ��
	std::filesystem::directory_iterator itor_skins("assets/skins");
	for (const std::filesystem::directory_entry& itor : itor_skins)
	{
		// ����json�ļ�
		std::filesystem::path path_skin_folder = itor.path();
		cJSON* pjson_config = nullptr;
		DG_Assert(pjson_config = LoadJSON((path_skin_folder / "config.json").string()));
		// ��ȡjson�ļ����ݣ�walk
		std::map<std::string, SDL_Surface*> map_filename_surface;
		cJSON* pjson_item = nullptr;
		cJSON* pjson_list_walk = cJSON_GetObjectItem(pjson_config, "walk");
		DG_Assert(pjson_list_walk && pjson_list_walk->type == cJSON_Array);
		// ����Ƥ����ԴΪsurface
		cJSON_ArrayForEach(pjson_item, pjson_list_walk)
		{
			if (map_filename_surface.find(pjson_item->valuestring) != map_filename_surface.end())
			{
				map_filename_surface.insert(std::make_pair(pjson_item->valuestring, IMG_Load((path_skin_folder / pjson_item->valuestring).string().c_str())));
			}
		}
	}
}

void DG_GameController::QuitGame()
{
	DG_Logger::QuitIO();
}

void DG_GameController::Menu()
{
}

void DG_GameController::SetupForRun()
{
}

void DG_GameController::Clear()
{
}

void DG_GameController::GetInput()
{
}

void DG_GameController::Do_Logic()
{
}

void DG_GameController::Render_Frame()
{
}

void DG_GameController::Wait()
{
}
