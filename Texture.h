#pragma once
#include <SDL_opengl.h>
namespace Fry
{

class Texture
{
public:
    Texture();
    virtual ~Texture();


    const void SetHeight(unsigned int height);
    const unsigned int GetHeight() const;

    const void SetWidth(unsigned int width);
    const unsigned int GetWidth() const;

    void SetTexture(const GLuint texture);
    const GLuint GetTexture() const;

    void SetFormat(const GLuint format);
    const GLuint GetFormat() const;

    void SetBpp(const GLuint bpp);
    const GLuint GetBpp() const;

private:
    unsigned int width_;
    unsigned int height_;
    unsigned int texture_;
    GLuint format_;
    GLuint bpp_;
};

};
