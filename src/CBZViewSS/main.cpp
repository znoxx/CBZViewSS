#ifdef __cplusplus
    #include <cstdlib>
    #include <iostream>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>

#endif

#include "defines.h"
#include "CPageHolder.h"
#include "unzip.h"
#include "cbzholder.h"


void Slock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    if ( SDL_LockSurface(screen) < 0 )
    {
      return;
    }
  }
}

void Sulock(SDL_Surface *screen)
{
  if ( SDL_MUSTLOCK(screen) )
  {
    SDL_UnlockSurface(screen);
  }
}


void Title()
{
    cout << "ComicViewer for small screens v "<<VERSION_NUMBER<<" by F0lken"<<endl;
}

void Usage(const char* executable)
{
    cout << "Usage:"<<endl;
    cout << executable<<" <filename>"<<endl;
}

int main ( int argc, char** argv )
{
    Title();
    if(argc < MINIMUM_ARGC)
    {
        Usage(argv[0]);
        return 1;
    }

    //options parsing should be here

    const char* filename = argv[1];

    CBZHolder cbzReader;
    CBHolder* pHolder = (CBHolder*)(&cbzReader);

    if ( !(pHolder->InitFile(filename) && pHolder->GetFirstPage()))
    {
        cerr<< "Unable to open file "<<filename<<endl;
        return 1;
    }

    cout<<"Inited file... Starting SDL Loop..."<<endl;


    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cerr<<"Unable to init SDL: "<<SDL_GetError()<<endl;
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, DEPTH,
                                           SDL_SWSURFACE);
    if ( !screen )
    {
        cerr<<"Unable to set desired video: "<<SDL_GetError()<<endl;
        return 1;
    }

#ifdef mips
  SDL_ShowCursor(SDL_DISABLE);
#endif

    CPageHolder *holder=new CPageHolder;
    bool bInited = holder->InitHolder(pHolder->GetCurrentPage(), pHolder->GetCurrentPageSize());
    pHolder->DeleteCurrentPage();


    if (!bInited)
    {
        delete holder;
        atexit(SDL_Quit);
    }

    int gameRunning = 1;
    bool bNeedRedraw(true);
    bool bFirstDraw=true;
    holder->SetScaler(1);

    int nDelta=SCROLLSTEP;

    SDL_Event event;

 bool bUp=false;
 bool bDown=false;
 bool bLeft=false;
 bool bRight=false;
 bool bZoom=false;
 bool bUnZoom=false;
 bool bPgUp = false;
 bool bPgDown = false;
 bool bLF = false;
 bool bExit1 = false;
 bool bExit2 = false;
 bool bFineScroll =false;
	while (gameRunning)
	{
        bool bKeyPressed = bUp || bDown || bLeft || bRight || bZoom || bUnZoom || bPgUp || bPgDown ||
                            bLF || bExit1 || bExit2 || bFineScroll;


		if (bKeyPressed ? SDL_PollEvent(&event) : SDL_WaitEvent(&event))
		{


			switch( event.type ){
              case SDL_KEYDOWN:

					switch( event.key.keysym.sym ){
                    case KEY_LEFT:
                        //holder->MoveViewPort(nDelta*(-1),0);
                        bLeft=true;
                        break;
                    case KEY_RIGHT:
                        //holder->MoveViewPort(nDelta,0);
                        bRight=true;
                        break;
                    case KEY_UP:
                        //holder->MoveViewPort(0,nDelta*(-1) );
                        bUp=true;
                        break;
                    case KEY_DOWN:
                        //holder->MoveViewPort(0,nDelta);
                        bDown=true;
                        break;
                    case KEY_ZOOM:
                        bZoom=true;
                        break;
                    case KEY_UNZOOM:
                        bUnZoom=true;
                        break;

                    case KEY_PGDOWN:
                          bPgDown = true;
                        break;
                    case KEY_PGUP:
                          bPgUp = true;
                        break;
                    case KEY_FOREXIT1:
                          bExit1 = true;
                        break;
                    case KEY_FOREXIT2:
                          bExit2 = true;
                        break;
                    case KEY_LF:
                        bLF = true;
                        break;
                    case KEY_FINESCROLL:
                        bFineScroll=true;
                        break;
                    default:
                        break;
                }


              break;
                 case SDL_KEYUP:
                    bNeedRedraw=true;
					switch( event.key.keysym.sym ){
                    case KEY_LEFT:
                        bLeft=false;
                    case KEY_RIGHT:
                        bRight=false;
                        break;
                    case KEY_UP:
                        bUp=false;
                        break;
                    case KEY_DOWN:
                        bDown=false;
                        break;
                    case KEY_ZOOM:
                        bZoom=false;
                        break;
                    case KEY_UNZOOM:
                        bUnZoom=false;
                        break;
                    case KEY_PGDOWN:
                        bPgDown = false;
                        break;
                    case KEY_PGUP:
                        bPgUp = false;
                        break;
                    case KEY_FOREXIT1:
                          bExit1 = false;
                        break;
                    case KEY_FOREXIT2:
                          bExit1 = false;
                        break;
                    case KEY_LF:
                        bLF = false;
                        break;
                    case KEY_FINESCROLL:
                        bFineScroll=false;
                        break;
                    default:
                        break;
                }


              break;

	          case SDL_QUIT:
               gameRunning = 0;
		      break;

               default:
               break;
             }
		}

		if (bUp)
		{
		    holder->MoveViewPort(0,nDelta*(-1) );
		    bNeedRedraw=true;
		}
		if (bDown)
		{
		    holder->MoveViewPort(0,nDelta);
		    bNeedRedraw=true;
		}
		if(bLeft)
		{
		    holder->MoveViewPort(nDelta*(-1),0);
		    bNeedRedraw=true;
		}

		if(bRight)
		{
		    holder->MoveViewPort(nDelta,0);
		    bNeedRedraw=true;
		}

		if(bZoom)
		{
		    holder->ScaleView(STEP);
		    bNeedRedraw=true;
		    bZoom=false;
		}

		if(bUnZoom)
		{
		    holder->ScaleView(STEP*BACK);
		    bNeedRedraw=true;
		    bUnZoom=false;
		}

		if(bPgDown)
		{
            if (pHolder->GetNextPage())
            {
              double dblScaler=holder->GetScaler();
              if(holder && bInited)
               delete holder;
              holder = new CPageHolder;
              bInited = holder->InitHolder(pHolder->GetCurrentPage(), pHolder->GetCurrentPageSize());
              pHolder->DeleteCurrentPage();
              holder->SetScaler(dblScaler);
              bNeedRedraw = true;
              bPgDown=false;
            }
		}

		if(bPgUp)
		{
            if (pHolder->GetPrevPage())
            {
              double dblScaler=holder->GetScaler();
              if(holder && bInited)
               delete holder;
              holder = new CPageHolder;
              bInited = holder->InitHolder(pHolder->GetCurrentPage(), pHolder->GetCurrentPageSize());
              pHolder->DeleteCurrentPage();
              holder->SetScaler(dblScaler);
              bNeedRedraw = true;
              bPgUp=false;
            }
		}

		if(bExit1 && bExit2)
		{
		    gameRunning = 0;
		    bExit1=false;
		    bExit2=false;

		}



		(bFineScroll) ? nDelta = SCROLLSTEP/SCROLLSTEP : nDelta = SCROLLSTEP;

		if ( bLF )
		{
		    //calc new pos.
		    bNeedRedraw = holder->LineFeed();
		    bLF=false;

		}



		//drawing goes here
		if (bNeedRedraw)
		{
		    Slock(screen);
		    holder->DrawViewPortToScreen(screen);
		    SDL_Flip(screen);
		    if(bFirstDraw)
		    {
		        bFirstDraw=false;
		        SDL_Flip(screen);
		        SDL_Flip(screen);
		        SDL_PumpEvents();
		        bKeyPressed=true;
		    }
    	    Sulock(screen);
		    bNeedRedraw=false;
		}


	}


    delete holder;

    // all is well ;)
    atexit(SDL_Quit);
    cout<<"Exited cleanly"<<endl;
    return 0;
}

