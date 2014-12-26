#ifndef _XCONFIG_H
#define _XCONFIG_H

#include <windows.h>

class XConfig
{
public:
    XConfig(char *filename);
    ~XConfig();
    void LoadFile(char *filename);
    void GetInt(DWORD &value, char *section, char *var, int def);
private:
    char *path;
};

#endif
