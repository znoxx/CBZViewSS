#ifndef CVIEWPORT_H
#define CVIEWPORT_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif


class CViewPort
{
    //methods
    public:
        CViewPort();
        virtual ~CViewPort();
        int GetX(){return rctView.x;};
        int GetY(){return rctView.y;};
        int GetWidth(){return rctView.w;};
        int GetHeight(){return rctView.h;};
        void SetNew(SDL_Rect& rctNew);
        SDL_Rect* GetRectPtr(){return &rctView;};
    protected:
    private:
    //properties

    private:
         SDL_Rect rctView;
};

#endif // CVIEWPORT_H
