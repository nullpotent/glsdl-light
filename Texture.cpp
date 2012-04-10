#include "Texture.h"

using namespace Fry;

Texture::Texture()
{
    height_  = 0;
    width_   = 0;
    texture_ = 0;
    format_  = 0;
    bpp_     = 0;
}

Texture::~Texture()
{
    //dtor
}

const unsigned int Texture::GetHeight() const
{
    return height_;
}

const unsigned int Texture::GetWidth() const
{
    return width_;
}

const GLuint Texture::GetTexture() const
{
    return texture_;
}

void Texture::SetTexture(const GLuint texture)
{
    texture_ = texture;
}

const void Texture::SetWidth(unsigned int width)
{
    width_ = width;
}

const void Texture::SetHeight(unsigned int height)
{
    height_ = height;
}

const GLuint Texture::GetFormat() const
{
    return format_;
}

const GLuint Texture::GetBpp() const
{
    return bpp_;
}

void Texture::SetFormat(const GLuint format)
{
    format_ = format;
}

void Texture::SetBpp(const GLuint bpp)
{
    bpp_ = bpp;
}
