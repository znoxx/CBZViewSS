#include "cbholder.h"
#include <stdio.h>

CBHolder::CBHolder()
{
    //ctor
    m_strCurrentArchive.clear();
    m_pCurrentFile=NULL;
    m_bInited=true;
    m_nPage = 0;

}

CBHolder::~CBHolder()
{


}

bool CBHolder::DeleteCurrentPage()
{
    if ( m_pCurrentFile )
    {
        free( m_pCurrentFile);
        m_pCurrentFile=NULL;
    }
    return true;
}

