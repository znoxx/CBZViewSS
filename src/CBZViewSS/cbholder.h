#ifndef CBHOLDER_H
#define CBHOLDER_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif


#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

typedef struct _archive
{
   string strFile;
   size_t nUncompressedSize;

} archive_data;

typedef vector<archive_data> CBFiles;

class CBHolder
{
    public:
        CBHolder();
        virtual ~CBHolder();
        virtual bool InitFile(const char* filename) = 0;
        virtual bool GetFirstPage() = 0;
        virtual bool GetNextPage() = 0;
        virtual bool GetPrevPage() = 0;
        virtual Uint8* GetCurrentPage() {return m_pCurrentFile;};
        virtual size_t GetCurrentPageSize() {return vecFiles.at(m_nPage).nUncompressedSize;}
        virtual bool DeleteCurrentPage();
    protected:
        virtual bool EnumerateFiles() = 0;
        virtual bool CloseFile() = 0;

        CBFiles vecFiles;
        bool m_bInited;
        size_t m_nPage;
        string m_strCurrentArchive;
        Uint8 *m_pCurrentFile;
    private:



};

#endif // CBHOLDER_H
