#include "DG_Sprite.h"

DG_Sprite::DG_Sprite(std::string file_path, bool lean)
{
	if (__m_pSurface = IMG_Load(file_path.c_str()))
	{
		m_nWidth = __m_pSurface->w, m_nHeight = __m_pSurface->h;
		if (!lean) __m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);
	}
}

DG_Sprite::DG_Sprite(void* mem, int size, bool lean)
{
	if (__m_pSurface = IMG_Load_RW(SDL_RWFromMem(mem, size), 1))
	{
		m_nWidth = __m_pSurface->w, m_nHeight = __m_pSurface->h;
		if (!lean) __m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);
	}
}

DG_Sprite::~DG_Sprite()
{
	if (__m_pSurface)
	{
		SDL_FreeSurface(__m_pSurface);
		__m_pSurface = nullptr;
	}
	
	if (__m_pTexture)
	{
		SDL_DestroyTexture(__m_pTexture);
		__m_pTexture = nullptr;
	}
}

void DG_Sprite::Slim(SlimType type)
{
	if (type == SlimType::SURFACE && __m_pSurface)
	{
		SDL_FreeSurface(__m_pSurface);
		__m_pSurface = nullptr;
	}
	else if (type == SlimType::TEXTURE && __m_pTexture)
	{
		SDL_DestroyTexture(__m_pTexture);
		__m_pTexture = nullptr;
	}
}

void DG_Sprite::SetColorKey(const SDL_Color& color, bool enable)
{
	if (__m_pSurface)
		SDL_SetColorKey(__m_pSurface, enable,
			SDL_MapRGBA(__m_pSurface->format, color.r, color.g, color.b, color.a));
	if (__m_pTexture)
	{
		SDL_DestroyTexture(__m_pTexture);
		__m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);
	}
}

void DG_Sprite::SetAlpha(Uint8 value)
{
	if (__m_pTexture)
	{
		SDL_SetTextureBlendMode(__m_pTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(__m_pTexture, value);
	}
}

void DG_Sprite::Render(const SDL_Rect* src, const SDL_Rect* dst)
{
	if (!__m_pTexture && !__m_pSurface) return;

	if (!__m_pTexture)
		__m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);

	SDL_RenderCopy(g_pRenderer, __m_pTexture, src, dst);
}

void DG_Sprite::RenderEx(const SDL_Rect* src, const SDL_Rect* dst, double angle, const SDL_Point& center, SDL_RendererFlip flip)
{
	if (!__m_pTexture && !__m_pSurface) return;

	if (!__m_pTexture)
		__m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, __m_pSurface);

	SDL_RenderCopyEx(g_pRenderer, __m_pTexture, src, dst, angle, &center, flip);
}
