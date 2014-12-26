#include "XConfig.h"

XConfig::XConfig(char *filename)
{
    if(path!=NULL)
    {
        delete path;
    }
    path = filename;
}

XConfig::~XConfig()
{
    delete path;
}

void XConfig::GetInt(DWORD &value, char *section, char *var, int def)
{
    value = GetPrivateProfileInt(section,var,0,path);
}
