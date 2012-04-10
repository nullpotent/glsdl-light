#include "Graphics.h"
#include <iostream>

using namespace Fry;

Graphics* Graphics::graphics_ = NULL;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
    std::cout<<"Graphics down"<<std::endl;
}

const Graphics* Graphics::Instance()
{
    if(graphics_==NULL)
    {
        graphics_ = new Graphics();
    }
    return graphics_;
}

const bool Graphics::Instantiate()
{
    graphics_ = new Graphics();
    return graphics_!=NULL;
}

const void Graphics::DrawImage(const Texture *texture, int x,int y) const
{
    assert(texture!=NULL);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslated(x,y,0);
    glBindTexture(GL_TEXTURE_2D,texture->GetTexture());
    glBegin(GL_QUADS);
    {
        glTexCoord2i(0,1);
        glVertex2i(0,0);
        glTexCoord2i(0,0);
        glVertex2i(0,texture->GetHeight());
        glTexCoord2i(1,0);
        glVertex2i(texture->GetWidth(),texture->GetHeight());
        glTexCoord2i(1,1);
        glVertex2i(texture->GetWidth(),0);
    }
    glEnd();
    glFlush();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

const void Graphics::DrawImage(const Texture *texture, int x,int y, int alpha) const
{
    assert(texture!=NULL);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f,((float)alpha/255.0f));
    glPushMatrix();
    glTranslated(x,y,0);
    glBindTexture(GL_TEXTURE_2D,texture->GetTexture());
    glBegin(GL_QUADS);
    {
        glTexCoord2i(0,1);
        glVertex2i(0,0);
        glTexCoord2i(0,0);
        glVertex2i(0,texture->GetHeight());
        glTexCoord2i(1,0);
        glVertex2i(texture->GetWidth(),texture->GetHeight());
        glTexCoord2i(1,1);
        glVertex2i(texture->GetWidth(),0);
    }
    glEnd();
    glFlush();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

const void Graphics::DrawLine(int x1, int y1, int x2, int y2) const
{
    glPushMatrix();
    glTranslated(x1,y1,0);
    glBegin(GL_LINES);
    {
        glVertex2i(0,0);
        glVertex2i(x2-x1,y2-y1);
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void Graphics::DrawRect(int x, int y, int width, int height) const
{
    glPushMatrix();
    glTranslated(x,y,0);
    glBegin(GL_QUADS);
    {
        glVertex2i(0,0);
        glVertex2i(0,height);
        glVertex2i(width,height);
        glVertex2i(width,0);
    }
    glEnd();
    glFlush();
    glPopMatrix();

}

const void Graphics::SetColor(int r,int g,int b,int a) const
{

    assert(r<=255 && r>=0);
    assert(g<=255 && g>=0);
    assert(b<=255 && b>=0);
    assert(a<=255 && a>=0);

    glColor4f(((float)r/255),((float)g/255),((float)b/255),((float)a/255));
}

const void Graphics::SetColor(int r,int g,int b) const
{

    assert(r<=255 && r>=0);
    assert(g<=255 && g>=0);
    assert(b<=255 && b>=0);

    glColor3f(((float)r/255),((float)g/255),((float)b/255));
}

const void Graphics::DrawText(const Font* fnt, int x, int y, const char *str, ...) const
{

    assert(fnt->IsValid());

    glEnable(GL_TEXTURE_2D);
    std::va_list args;
    static char buf[1024];

    va_start(args,str);
    vsnprintf(buf, 1024, str, args);   // avoid buffer overflow
    va_end(args);

    glBindTexture(GL_TEXTURE_2D, fnt->GetTexture());
    glPushMatrix();
    glTranslated(x,y,0);

    for(int i=0; i < strlen(buf); ++i)
    {
        unsigned char ch( buf[i] - Font::SPACE );     // ch-SPACE = DisplayList offset
        // replace characters outside the valid range with undrawable
        if(ch > Font::NUM_CHARS)
        {
            ch = Font::NUM_CHARS-1;   // last character is 'undrawable'
        }
        glCallList(fnt->GetListBase()+ch);    // calculate list to call
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

const void Graphics::DrawText(const Font* fnt, int x, int y, const std::string& str) const
{

    assert(fnt->IsValid());

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fnt->GetTexture());
    glPushMatrix();
    glTranslated(x,y,0);

    for(std::string::const_iterator i = str.begin(); i != str.end(); ++i)
    {
        unsigned char ch( *i - Font::SPACE );    // ch-SPACE = DisplayList offset
        // replace characters outside the valid range with undrawable
        if(ch > Font::NUM_CHARS)
        {
            ch = Font::NUM_CHARS-1;              // last character is 'undrawable'
        }
        glCallList(fnt->GetListBase()+ch);        // calculate list to call
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

Texture* Graphics::LoadTexture(const std::string& filename) const
{
    SDL_Surface *surface;
    GLuint texid;
    surface = IMG_Load(filename.c_str());
    Texture *texture = new Texture;
    int mode;
    if(!surface)
    {
        std::cout<<"Error loading texture "+filename<<std::endl;
        return 0;
    }
    switch(surface->format->BytesPerPixel)
    {
        case 3:
        {
            mode = GL_RGB;
            break;
        }
        case 4:
        {
            mode = GL_RGBA;
            break;
        }
        default:
        {
            SDL_FreeSurface(surface);
            std::cout<<"Couldn't determine image bpp"<<std::endl;
            return 0;
        }
    }

    texture->SetWidth(surface->w);
    texture->SetHeight(surface->h);
    glGenTextures(1, &texid);
    texture->SetTexture(texid);
    texture->SetBpp(mode);
    glBindTexture(GL_TEXTURE_2D,texid);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h,0,mode,GL_UNSIGNED_BYTE,surface->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    SDL_FreeSurface(surface);
    return texture;
}

const int Graphics::Lerp(int x, int y, float time) const
{
    return (int)(x * (1.0f - time) + y * time);
}
