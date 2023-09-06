#ifndef _XCONFIG_H
#define _XCONFIG_H

#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <cstdio>

class XConfig
{
public:
    XConfig(const char *filename);
    ~XConfig();
    void LoadFile(const char *filename);
    void GetInt(int &value, const char *section, const char *var, int def);
private:
    char *path = NULL;
    void GetVal(char **value, const char *section, const char *var);
};

#endif
