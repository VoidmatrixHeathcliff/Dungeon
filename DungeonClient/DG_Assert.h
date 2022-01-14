#ifndef _DG_ASSERT_H_
#define _DG_ASSERT_H_

#include "DG_Logger.h"
#include "DG_GameController.h"

#include <SDL.h>

#include <string>

extern SDL_Window* g_pWindow;

extern DG_GameController g_Game;

inline void _DG_Assert(bool flag, const std::string& code, const std::string& file, int line)
{
	if (!flag)
	{
		std::string strCode = "Code: " + code;
		std::string strFile = "File: " + file + " : " + std::to_string(line);

		DG_Logger::Log("Assertion Failure : \n\t" + strCode + "\n\t" + strFile, DG_Logger::Type::ERROR);

		std::string strMsg = strCode + "\n" + strFile;

		SDL_SetClipboardText(strMsg.c_str());

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"Runtime Error",
			(strMsg + "\n\nThis is a detected assertion error.\n"
				"The complete information has been copied to the clipboard.\n"
				"Please send the latest log file to the developer and describe "
				"in detail how to trigger this error.").c_str(),
			g_pWindow
		);

		g_Game.QuitGame();

		exit(-1);
	}
}

#define DG_Assert(exp) _DG_Assert(exp, #exp, __FILE__, __LINE__)

#endif // !_DG_ASSERT_H_
