#pragma once
#include <SDL_opengl.h>
#include <stdexcept>
#include "Texture.h"
#include "Assert.h"
#include <SDL/SDL_image.h>
#include "Font.h"

#define COLOR_BLACK 0,0,0
#define COLOR_BLUE 0,0,255
#define COLOR_WHITE 255,255,255
#define COLOR_RED 255,0,0
#define COLOR_GREEN 0,255,0

namespace Fry
{

class Graphics
{
public:
    Graphics();
    ~Graphics();

    //inline const void PushScreenCoordinateMatrix() const;
    //inline const void PopScreenCoordinateMatrix() const;

    const void DrawLine(int x1, int y1, int x2, int y2) const;
    const void SetColor(float r,float g, float b) const;
    const void DrawRect(int x, int y, int width, int height) const;
    Texture*   LoadTexture(const std::string& filename) const;
    const void SetColor(int r,int g,int b,int a) const;
    const void SetColor(int r,int g,int b) const;
    const void DrawImage(const Texture* texture, int x,int y, int alpha) const;
    const void DrawImage(const Texture* texture, int x,int y) const;
    const void DrawText(const Font* fnt,int x, int y, const char *str, ...) const;
    const void DrawText(const Font* fnt,int x, int y, const std::string& str) const;
    const int  Lerp(int x, int y, float time) const;
    static const Graphics *Instance();
    static const bool Instantiate();

private:
    static Graphics* graphics_;
};

};

