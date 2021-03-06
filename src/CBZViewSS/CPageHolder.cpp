#include "CPageHolder.h"

#include "defines.h"
//#include "SDL_rotozoom.h"
//#include "SDL_stretch_.h"
#include "Sprig/sprig.h"
CPageHolder::CPageHolder():bSDLImageInited(false),pLoadedImage(NULL)
{
    //ctor
}

CPageHolder::~CPageHolder()
{
    //dtor
    if (pLoadedImage)
      SDL_FreeSurface(pLoadedImage);
}

bool CPageHolder::InitHolder(Uint8* pImage, size_t nSize)
{
    m_dblScale=1;
    SDL_Surface* temp_image_surface(NULL);
    //creating SDL_RW
    SDL_RWops *rw=SDL_RWFromMem(pImage, nSize);
    temp_image_surface = IMG_LoadJPG_RW(rw);
    SDL_FreeRW(rw);
	if (temp_image_surface)
	{
	    pLoadedImage = SDL_DisplayFormat(temp_image_surface);
	    SDL_FreeSurface(temp_image_surface);
	    if (!pLoadedImage)
	    {
	        return false;
	    }

	    SDL_Rect vp;
	    vp.x=0;
	    vp.y=0;
	    vp.w=SCR_WIDTH;
	    vp.h=SCR_HEIGHT;
	    viewPort.SetNew(vp);
	    return true;
	}
	else
	{
	    return false;
	}

	return false;

}
const int CPageHolder::GetWidth()
{
    if (pLoadedImage)
       return pLoadedImage->w;

    return 0;
}

const int CPageHolder::GetHeight()
{
    if (pLoadedImage)
       return pLoadedImage->h;

    return 0;
}

void CPageHolder::MoveViewPort(int dx, int dy)
{
    //calculating new viewport coords;
    int newX=viewPort.GetX()+dx*m_dblScale;
    int newY=viewPort.GetY()+dy*m_dblScale;
    if (newX < 0) newX=0;
    if (newY < 0) newY=0;
    if ((viewPort.GetWidth() + newX) > GetWidth())
    {
        //out of screen - recalc x
        newX=GetWidth()-viewPort.GetWidth();
    }
    if ((viewPort.GetHeight() + newY) > GetHeight())
    {
        //out of screen - recalc y
        newY=GetHeight()-viewPort.GetHeight();
    }

    SDL_Rect newRect;
    newRect.x=newX;
    newRect.y=newY;
    newRect.w=viewPort.GetWidth();
    newRect.h=viewPort.GetHeight();
    viewPort.SetNew(newRect);
}
void CPageHolder::ScaleView( double k )
{
    double dblNewScaler=m_dblScale+k;
    ScaleViewImpl(dblNewScaler);

}
void CPageHolder::ScaleViewImpl(double dblNewScaler)
{


    int newWidth = ((double)SCR_WIDTH)*dblNewScaler;
    int newHeight = ((double)SCR_HEIGHT)*dblNewScaler;

    SDL_Rect newRect;
    newRect.x=viewPort.GetX();
    newRect.y=viewPort.GetY();
    newRect.w=newWidth;
    newRect.h=newHeight;

    if(newRect.w >= GetWidth())
    {
        newRect.x=0;
    }
    if(newRect.h >= GetHeight())
    {
        newRect.y=0;
    }

    if ((newRect.w + newRect.x) > GetWidth())
    {
        //out of screen - recalc x
        newRect.x=GetWidth()-newRect.w;
        if (newRect.x < 0)
        {
            newRect.x=0;
        }
    }
    if ((newRect.h + newRect.y) > GetHeight())
    {
        //out of screen - recalc y
        newRect.y=GetHeight()-newRect.h;
        if (newRect.y < 0)
        {
            newRect.y=0;
        }
    }



    if((newRect.w<=GetWidth() && newRect.h<=GetHeight() )
        && (dblNewScaler >= 1))
    {
        viewPort.SetNew(newRect);
        m_dblScale=dblNewScaler;
    }

}

void CPageHolder::DrawViewPortToScreen(SDL_Surface* physicalScreen)
{

    SDL_Rect cnstRect;
    cnstRect.w=SCR_WIDTH;
    cnstRect.h=SCR_HEIGHT;
    cnstRect.x=0;
    cnstRect.y=0;
    //temporary!!!!!! resizing goes here;
    //creating temporary surface

//    SDL_Surface* temp_surface = CreateSurface(SCR_WIDTH,SCR_HEIGHT,physicalScreen);

    double zoomX=(double)cnstRect.w/(double)viewPort.GetRectPtr()->w;
    double zoomY=(double)cnstRect.h/(double)viewPort.GetRectPtr()->h;

    //Blit sourceSurface;
    SDL_Surface* source_surface=CreateSurface(viewPort.GetRectPtr()->w,viewPort.GetRectPtr()->h,physicalScreen);
    SDL_BlitSurface(pLoadedImage, viewPort.GetRectPtr(), source_surface,NULL);

    //SDL_Surface* temp_surface = zoomSurface(source_surface, zoomX, zoomY,1);
    SDL_Surface* temp_surface=SPG_Scale(source_surface,zoomX,zoomY);

    //SDL_StretchSurfaceRect(source_surface,NULL,temp_surface,NULL);




    SDL_BlitSurface(temp_surface,&cnstRect,physicalScreen,&cnstRect);
    SDL_FreeSurface(temp_surface);
    SDL_FreeSurface(source_surface);
}

SDL_Surface* CPageHolder::CreateSurface(int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);

  return SDL_CreateRGBSurface(display->flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

bool CPageHolder::LineFeed()
{
    bool bRes(false);

    //get current postion and size.
    int nCurrentY = viewPort.GetY();
    int nHeight = viewPort.GetHeight();
    if((nCurrentY + nHeight) < GetHeight())
    {
        int nNewY = nCurrentY + nHeight*0.75;

        if ( (nNewY + nHeight) > GetHeight())
        {
           //out of screen - recalc y
           nNewY=GetHeight()-viewPort.GetHeight();
        }


            SDL_Rect newRect;
            newRect.x=0;
            newRect.y=nNewY;
            newRect.w=viewPort.GetWidth();
            newRect.h=nHeight;
            viewPort.SetNew(newRect);

            bRes = true;

    }

     return bRes;
}

