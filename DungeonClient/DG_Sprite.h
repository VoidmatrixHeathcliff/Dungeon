#ifndef _DG_SPRITE_H_
#define _DG_SPRITE_H_

#pragma warning(disable:26812)

#include <SDL.h>
#include <SDL_image.h>

#include <string>

extern SDL_Renderer* g_pRenderer;

class DG_Sprite
{
public:
	enum class SlimType { SURFACE, TEXTURE };

	DG_Sprite(std::string file_path, bool lean = false);
	DG_Sprite(void* mem, int size, bool lean = false);
	~DG_Sprite();
	DG_Sprite(const DG_Sprite&) = delete;
	DG_Sprite& operator=(const DG_Sprite&) = delete;
	operator bool() { return __m_pSurface || __m_pTexture; };

	void Slim(SlimType type);
	void SetColorKey(const SDL_Color& color, bool enable = true);
	void SetAlpha(Uint8 value);
	void Render(const SDL_Rect* src, const SDL_Rect* dst);
	void RenderEx(const SDL_Rect* src, 
				const SDL_Rect* dst, 
				double angle, 
				const SDL_Point& center,
				SDL_RendererFlip flip = SDL_FLIP_NONE);

	int m_nWidth = 0, m_nHeight = 0;

private:
	SDL_Surface* __m_pSurface = nullptr;
	SDL_Texture* __m_pTexture = nullptr;
};

#endif // !_DG_SPRITE_H_
