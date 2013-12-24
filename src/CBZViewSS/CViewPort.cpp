#include "CViewPort.h"
#include "defines.h"

CViewPort::CViewPort()
{
    //ctor
    rctView.x=0;
    rctView.y=0;
    rctView.w=0;
    rctView.h=0;
}

CViewPort::~CViewPort()
{
    //dtor
}

void CViewPort::SetNew(SDL_Rect& rctNew)
{
    rctView.x=rctNew.x;
    rctView.y=rctNew.y;
    rctView.w=rctNew.w;
    rctView.h=rctNew.h;
}
