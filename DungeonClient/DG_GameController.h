#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <filesystem>

#include "DG_Sprite.h"
#include "DG_Logger.h"

class DG_GameController
{
public:
	enum /*class*/ GameState {
		GAME_INIT = 0, GAME_MENU, GAME_STARTING, GAME_RUNNING, GAME_EXIT
	}state;
	void Init();			// 初始化
	void Menu();			// 菜单界面
	void SetupForRun();		// 初始化游戏资源
	void Clear();			// 清除上一帧的内容
	void GetInput();		// 获取玩家输入
	void Do_Logic();		// 处理逻辑
	void Render_Frame();	// 渲染并显示当前帧的内容
	void Wait();			// 控制帧率
	void QuitGame();		// 释放游戏资源并退出
private:
	std::map<std::string, std::map<std::string, DG_Sprite>> Sprite;
	std::map<std::string, std::map<std::string, SDL_Surface*>> GameResource;
	Uint32 start = 0;
	Uint32 end = 0;
};

#endif // !_GAME_CONTROLLER_H_